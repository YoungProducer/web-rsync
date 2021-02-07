#ifndef _FILES_MAP_WRAP_H_
#define _FILES_MAP_WRAP_H_

#include <napi.h>

#include "files-map.h"

class FilesMapWrap : public Napi::ObjectWrap<FilesMapWrap>, public FilesMap
{
public:
    FilesMapWrap(const Napi::CallbackInfo &);

    static Napi::Function GetClass(Napi::Env);

    static Napi::Object Init(Napi::Env env, Napi::Object exports);

    /** JS functions */
    void Append(const Napi::CallbackInfo &info);
    Napi::Value GetValue(const Napi::CallbackInfo &info);
    void From(const Napi::CallbackInfo &info);
    /** end of JS functions */

    static Napi::Value transform_to_napi_object(Napi::Env env, FilesMap *fm);
    static Napi::Value transform_to_napi_object(Napi::Env env, FilesMapShorthand *fm);
    static FilesMapShorthand transform_from_napi_object(Napi::Object *obj);
    void from_napi_object(Napi::Object *obj);
};

#endif // _FILES_MAP_WRAP_H_