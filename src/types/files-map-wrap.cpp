#include "files-map-wrap.h"

FilesMapWrap::FilesMapWrap(const Napi::CallbackInfo &info)
    : ObjectWrap(info)
{
    if (info.Length() == 1)
    {
        if (info[0].IsObject())
        {
            Napi::Object obj = info[0].ToObject();
            process_from_napi_object(obj, &this->_value);
        }
    }
}

/** JS functions */
void FilesMapWrap::Append(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    }

    if (!info[0].IsString())
    {
        Napi::TypeError::New(env, "Argument 'path' has invalid type").ThrowAsJavaScriptException();
    }

    if (!info[1].IsString())
    {
        Napi::TypeError::New(env, "Argument 'checksum' has invalid type").ThrowAsJavaScriptException();
    }

    const std::string path = (std::string)info[0].ToString();
    const std::string checksum = (std::string)info[1].ToString();

    this->_value.insert(std::make_pair(path, checksum));
}

Napi::Value FilesMapWrap::GetValue(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    return FilesMapWrap::transform_to_napi_object(env, this);
}

Napi::Function FilesMapWrap::GetClass(Napi::Env env)
{
    return DefineClass(
        env,
        "ObjectWrapDemo",
        {FilesMapWrap::InstanceMethod("getValue", &FilesMapWrap::GetValue),
         FilesMapWrap::InstanceMethod("append", &FilesMapWrap::Append)});
}

Napi::Object FilesMapWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::String name = Napi::String::New(env, "FilesMapWrap");
    exports.Set(name, FilesMapWrap::GetClass(env));
    return exports;
}

Napi::Value FilesMapWrap::transform_to_napi_object(Napi::Env env, FilesMap *fm)
{
    Napi::Object result = Napi::Object::New(env);

    const boost::unordered_map<std::string, std::string> *map = fm->get_value();

    for (const auto &e : *map)
    {
        result.Set(
            Napi::String::New(env, e.first.c_str()),
            Napi::String::New(env, e.second.c_str()));
    }

    return result;
}

Napi::Value FilesMapWrap::transform_to_napi_object(Napi::Env env, FilesMapShorthand *fm)
{
    Napi::Object result = Napi::Object::New(env);

    for (const auto &e : *fm)
    {
        result.Set(
            Napi::String::New(env, e.first.c_str()),
            Napi::String::New(env, e.second.c_str()));
    }

    return result;
}

FilesMapShorthand FilesMapWrap::transform_from_napi_object(Napi::Object *obj)
{
    FilesMapShorthand fm;

    process_from_napi_object(*obj, &fm);

    return fm;
}

void FilesMapWrap::from_napi_object(Napi::Object *obj)
{
    process_from_napi_object(*obj, &this->_value);
}