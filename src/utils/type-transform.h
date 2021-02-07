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
        };
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
        };
    } // namespace Embedded

    namespace Advanced
    {
        template <typename T>
        Napi::Array vector_to_napi_array(Napi::Env &env, std::vector<T> &source, Napi::Value (*f)(Napi::Env &env, T param))
        {
            Napi::Array array = Napi::Array::New(env);

            for (int i = 0, length = source.size(); i < length; i++)
            {
                array.Set(i, f(env, source[i]));
            }

            return array;
        }

    } // namespace Advanced

}; // namespace TypeTransform

#endif // TYPE_TRANSFORM