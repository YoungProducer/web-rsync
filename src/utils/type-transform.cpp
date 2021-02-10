#include "type-transform.h"

namespace TypeTransform
{
    namespace Embedded
    {
        Napi::Value file_action_to_napi_object(Napi::Env &env, FileAction act)
        {
            Napi::Object result = Napi::Object::New(env);

            result.Set(
                Napi::String::New(env, "path"),
                Napi::String::New(env, act.path));

            result.Set(
                Napi::String::New(env, "type"),
                Napi::String::New(env, act.type));

            return result;
        }

        Napi::Value file_action_to_napi_object(Napi::Env &env, FileAction *act)
        {
            Napi::Object result = Napi::Object::New(env);

            result.Set(
                Napi::String::New(env, "path"),
                Napi::String::New(env, act->path));

            result.Set(
                Napi::String::New(env, "type"),
                Napi::String::New(env, act->type));

            return result;
        }

        Napi::Value files_map_to_napi_object(Napi::Env env, FilesMap &fm)
        {
            Napi::Object result = Napi::Object::New(env);

            for (const auto &e : fm)
            {
                result.Set(
                    Napi::String::New(env, e.first.c_str()),
                    Napi::String::New(env, e.second.c_str()));
            }

            return result;
        }

        void files_map_to_napi_object(Napi::Env env, FilesMap &fm, Napi::Object *obj)
        {
            for (const auto &e : fm)
            {
                obj->Set(
                    Napi::String::New(env, e.first.c_str()),
                    Napi::String::New(env, e.second.c_str()));
            }
        }

        FilesMap napi_object_to_files_map(Napi::Object &obj)
        {
            FilesMap result;

            const Napi::Array propertiesNames = obj.GetPropertyNames();
            const short length = propertiesNames.Length();

            for (int i = 0; i < length; i++)
            {
                std::string p_key = (std::string)propertiesNames[i].ToString();
                std::string p_value = (std::string)obj.Get(p_key).ToString();
                result.insert(std::make_pair(p_key, p_value));
            }

            return result;
        }

        void napi_object_to_files_map(Napi::Object &obj, FilesMap *fm)
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
    } // namespace Embedded
} // namespace TypeTransform