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

/** must be removed in future */
Napi::Array test(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string prevDirectoryPath = (std::string)info[0].ToString();
    std::string nextDirectoryPath = (std::string)info[1].ToString();

    auto start = std::chrono::high_resolution_clock::now();
    FilesMap prev = scan_dir(prevDirectoryPath);
    FilesMap next = scan_dir(nextDirectoryPath);

    std::vector<FileAction *> diff = get_folders_diff(prev, &next);
    auto stop = std::chrono::high_resolution_clock::now();

    // for (const auto &e : result)
    // {
    //     std::cout << "path: " << e.first << std::endl
    //               << "checksum: " << e.second << std::endl
    //               << std::endl;
    // }

    // for (const auto &e : diff)
    // {
    //     std::cout << "path: " << e->path << std::endl
    //               << "action: " << e->type << std::endl
    //               << std::endl;
    // }

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    Napi::Array arr = Napi::Array::New(env);

    auto startCoerce = std::chrono::high_resolution_clock::now();
    for (int i = 0, length = diff.size(); i < length; i++)
    {
        Napi::Object value = Napi::Object::New(env);
        value.Set(
            Napi::String::New(env, "path"),
            Napi::String::New(env, diff[i]->path.c_str()));
        value.Set(
            Napi::String::New(env, "type"),
            Napi::String::New(env, diff[i]->type.c_str()));
        arr.Set(i, value);
    }
    auto stopCoerce = std::chrono::high_resolution_clock::now();

    auto durationCoerce = std::chrono::duration_cast<std::chrono::microseconds>(stopCoerce - startCoerce);

    std::cout << "Time taken by function: "
              << durationCoerce.count() << " microseconds" << std::endl;

    Napi::Array result = TypeTransform::Advanced::vector_to_napi_array<FileAction *>(env, diff, TypeTransform::Embedded::file_action_to_napi_object);

    // return Napi::String::New(env, "good");
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

    return exports;
}

NODE_API_MODULE(file_checksum, Init)
