#include <napi.h>
#include <string>
#include <chrono>

#include "./lib/scan-dir.h"
#include "./lib/folders-diff.h"
#include "./lib/sha256-checksum.h"
#include "./utils/type-transform.h"

Napi::String sha256_checksum(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string filepath = (std::string)info[0].ToString();
    std::string result = SHA256_CHECKSUM(filepath.data());

    return Napi::String::New(env, result);
}

Napi::Value scanDir(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string dirpath = (std::string)info[0].ToString();
    FilesMap content = scan_dir(dirpath);

    return TypeTransform::Embedded::files_map_to_napi_object(env, content);
}

Napi::Array getFoldersDiff(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (!(info[0].IsObject() && info[1].IsObject()) && !(info[0].IsString() && info[1].IsObject()))
    {
        Napi::TypeError::New(env, "Invalid function arguments").ThrowAsJavaScriptException();
    }

    std::vector<FileAction *> diff;

    Napi::Object nextScan = info[1].As<Napi::Object>();
    FilesMap nextFm;
    TypeTransform::Embedded::napi_object_to_files_map(nextScan, &nextFm);

    if (info[0].IsObject())
    {
        Napi::Object prevScan = info[0].As<Napi::Object>();
        FilesMap prevFm;
        TypeTransform::Embedded::napi_object_to_files_map(prevScan, &prevFm);
        diff = get_folders_diff(prevFm, &nextFm);
    }

    if (info[0].IsString())
    {
        std::string prevPath = (std::string)info[0].ToString();
        diff = get_folders_diff(&prevPath, &nextFm);
    }

    return TypeTransform::Advanced::vector_to_napi_array<FileAction *>(env, diff, TypeTransform::Embedded::file_action_to_napi_object);
}

/** must be removed in future */
Napi::Array test(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string prevDirectoryPath = (std::string)info[0].ToString();
    std::string nextDirectoryPath = (std::string)info[1].ToString();

    auto start = std::chrono::high_resolution_clock::now();
    boost::unordered_map<std::string, std::string> prev = scan_dir(prevDirectoryPath);
    boost::unordered_map<std::string, std::string> next = scan_dir(nextDirectoryPath);

    std::vector<FileAction *> diff = get_folders_diff(prev, &next);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    auto startCoerce = std::chrono::high_resolution_clock::now();

    Napi::Array result = TypeTransform::Advanced::vector_to_napi_array<FileAction *>(env, diff, TypeTransform::Embedded::file_action_to_napi_object);

    auto stopCoerce = std::chrono::high_resolution_clock::now();

    auto durationCoerce = std::chrono::duration_cast<std::chrono::microseconds>(stopCoerce - startCoerce);

    std::cout << "Time taken by function: "
              << durationCoerce.count() << " microseconds" << std::endl;

    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(
        Napi::String::New(env, "sha256_checksum"),
        Napi::Function::New(env, sha256_checksum));

    exports.Set(
        Napi::String::New(env, "test"),
        Napi::Function::New(env, test));

    exports.Set(
        Napi::String::New(env, "scanDir"),
        Napi::Function::New(env, scanDir));

    exports.Set(
        Napi::String::New(env, "getFoldersDiff"),
        Napi::Function::New(env, getFoldersDiff));

    return exports;
}

NODE_API_MODULE(file_checksum, Init)
