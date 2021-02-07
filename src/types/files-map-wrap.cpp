#include "files-map-wrap.h"

void process_from_napi_object(Napi::Object &obj, FilesMapShorthand *fm)
{
    const Napi::Array propertiesNames = obj.GetPropertyNames();
    const short length = propertiesNames.Length();

    for (int i = 0; i < length; i++)
    {
        std::string p_key = (std::string)propertiesNames[i].ToString();
        std::string p_value = (std::string)obj.Get(p_key).ToString();
        fm->insert(std::make_pair(p_key, p_value));
    }
}

void process_to_napi_object(Napi::Env env, FilesMapShorthand &fm, Napi::Object *obj)
{
    for (const auto &e : fm)
    {
        obj->Set(
            Napi::String::New(env, e.first.c_str()),
            Napi::String::New(env, e.second.c_str()));
    }
}

FilesMapWrap::FilesMapWrap(const Napi::CallbackInfo &info)
    : ObjectWrap(info),
      FilesMap()
{
    this->From(info);
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

    this->append(path, checksum);
}

void FilesMapWrap::From(const Napi::CallbackInfo &info)
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

void FilesMapWrap::Clear(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() > 0)
    {
        Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    }
    else
    {
        this->clear();
    }
}

Napi::Value FilesMapWrap::GetValue(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    return FilesMapWrap::Helpers::transform_to_napi_object(env, this);
}

Napi::Function FilesMapWrap::GetClass(Napi::Env env)
{
    return DefineClass(
        env,
        "ObjectWrapDemo",
        {FilesMapWrap::InstanceMethod("getValue", &FilesMapWrap::GetValue),
         FilesMapWrap::InstanceMethod("append", &FilesMapWrap::Append),
         FilesMapWrap::InstanceMethod("from", &FilesMapWrap::From),
         FilesMapWrap::InstanceMethod("clear", &FilesMapWrap::Clear)});
}

Napi::Object FilesMapWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::String name = Napi::String::New(env, "FilesMapWrap");
    exports.Set(name, FilesMapWrap::GetClass(env));
    return exports;
}

/** Native helpers functions */
Napi::Value FilesMapWrap::Helpers::transform_to_napi_object(Napi::Env env, FilesMap *fm)
{
    Napi::Object result = Napi::Object::New(env);

    process_to_napi_object(env, *fm->get_value(), &result);

    return result;
}

Napi::Value FilesMapWrap::Helpers::transform_to_napi_object(Napi::Env env, FilesMapShorthand *fm)
{
    Napi::Object result = Napi::Object::New(env);

    process_to_napi_object(env, *fm, &result);

    return result;
}

FilesMapShorthand FilesMapWrap::Helpers::transform_from_napi_object(Napi::Object *obj)
{
    FilesMapShorthand fm;

    process_from_napi_object(*obj, &fm);

    return fm;
}

void FilesMapWrap::from_napi_object(Napi::Object *obj)
{
    process_from_napi_object(*obj, &this->_value);
}