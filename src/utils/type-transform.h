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
        Napi::Value file_action_to_napi_object(Napi::Env &env, FileAction act);
        Napi::Value file_action_to_napi_object(Napi::Env &env, FileAction *act);

        Napi::Value files_map_to_napi_object(Napi::Env env, FilesMap &fm);
        void files_map_to_napi_object(Napi::Env env, FilesMap &fm, Napi::Object *obj);

        FilesMap napi_object_to_files_map(Napi::Object &obj);
        void napi_object_to_files_map(Napi::Object &obj, FilesMap *fm);

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