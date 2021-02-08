#pragma once

#ifndef TYPE_TRANSFORM
#define TYPE_TRANSFORM

#include <napi.h>
#include <vector>

#include "../types/simple.h"

namespace TypeTransform
{
    namespace Embedded
    {
        inline Napi::Value file_action_to_napi_object(Napi::Env &env, FileAction act)
        {
            Napi::Object result = Napi::Object::New(env);

            result.Set(
                Napi::String::New(env, "path"),
                Napi::String::New(env, act.path));

            result.Set(
                Napi::String::New(env, "type"),
                Napi::String::New(env, act.type));

            return result;
        };

        inline Napi::Value file_action_to_napi_object(Napi::Env &env, FileAction *act)
        {
            Napi::Object result = Napi::Object::New(env);

            result.Set(
                Napi::String::New(env, "path"),
                Napi::String::New(env, act->path));

            result.Set(
                Napi::String::New(env, "type"),
                Napi::String::New(env, act->type));

            return result;
        };

        inline Napi::Value files_map_to_napi_object(Napi::Env env, FilesMap &fm)
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

        inline void files_map_to_napi_object(Napi::Env env, FilesMap &fm, Napi::Object *obj)
        {
            for (const auto &e : fm)
            {
                obj->Set(
                    Napi::String::New(env, e.first.c_str()),
                    Napi::String::New(env, e.second.c_str()));
            }
        }

        inline FilesMap napi_object_to_files_map(Napi::Object &obj)
        {
            FilesMap result;

            const Napi::Array propertiesNames = obj.GetPropertyNames();
            std::cout << "hello" << std::endl;
            const short length = propertiesNames.Length();

            std::cout << "hello" << length << std::endl;

            for (int i = 0; i < length; i++)
            {
                std::string p_key = (std::string)propertiesNames[i].ToString();
                std::string p_value = (std::string)obj.Get(p_key).ToString();
                result.insert(std::make_pair(p_key, p_value));
            }

            return result;
        }

        inline void napi_object_to_files_map(Napi::Object &obj, FilesMap *fm)
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

    namespace Advanced
    {
        template <typename T>
        inline Napi::Array vector_to_napi_array(Napi::Env &env, std::vector<T> &source, Napi::Value (*f)(Napi::Env &env, T param))
        {
            Napi::Array array = Napi::Array::New(env);

            for (int i = 0, length = source.size(); i < length; i++)
            {
                array.Set(i, f(env, source[i]));
            }

            return array;
        }

    } // namespace Advanced

} // namespace TypeTransform

#endif // TYPE_TRANSFORM