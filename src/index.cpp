#include <napi.h>
#include <string>
#include <chrono>

#include "scan-dir.h"
#include "sha256-checksum.h"

Napi::String sha256_checksum(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string filepath = (std::string)info[0].ToString();
    std::string result = SHA256_CHECKSUM(filepath.data());

    return Napi::String::New(env, result);
}

/** must be removed in future */
Napi::String test(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    std::string directoryPath = (std::string)info[0].ToString();

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<FileData> result = scanDir(directoryPath);
    auto stop = std::chrono::high_resolution_clock::now();

    for (const auto e : result)
    {
        std::cout << "path: " << e.path << std::endl
                  << "checksum: " << e.checksum << std::endl
                  << std::endl;
    }

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
              << duration.count() << " microseconds" << std::endl;

    return Napi::String::New(env, "good");
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
