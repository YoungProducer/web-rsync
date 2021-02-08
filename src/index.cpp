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

    return exports;
}

NODE_API_MODULE(file_checksum, Init)
