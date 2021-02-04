#include <napi.h>
#include <string>
#include "sha256-checksum.h"

Napi::String sha256_checksum(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string filepath = (std::string)info[0].ToString();
    std::string result = SHA256_CHECKSUM(filepath.data());

    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "sha256_checksum"),
        Napi::Function::New(env, sha256_checksum)
    );

    return exports;
}

NODE_API_MODULE(file_checksum, Init)
