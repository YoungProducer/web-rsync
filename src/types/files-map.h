#ifndef _FILES_MAP_H_
#define _FILES_MAP_H_

#include <napi.h>
#include <string>
#include <boost/unordered_map.hpp>

#include "../utils/type-transform.h"

typedef boost::unordered_map<std::string, std::string> FilesMapShorthand;

void process_from_napi_object(Napi::Object &, FilesMapShorthand *);

class FilesMap : public Napi::ObjectWrap<FilesMap>
{
public:
    FilesMap(const Napi::CallbackInfo &);

    static Napi::Function GetClass(Napi::Env);

    static Napi::Object Init(Napi::Env env, Napi::Object exports);

    /** JS functions */
    void Append(const Napi::CallbackInfo &info);
    Napi::Value GetValue(const Napi::CallbackInfo &);
    void From(const Napi::CallbackInfo &info);
    /** end of JS functions */

    static Napi::Value transform_to_napi_object(Napi::Env env, FilesMap *fm);
    static Napi::Value transform_to_napi_object(Napi::Env env, FilesMapShorthand *fm);
    static FilesMapShorthand transform_from_napi_object(Napi::Object *obj);
    void from_napi_object(Napi::Object *obj);

    void append(std::string path, std::string checksum);
    void append(std::pair<std::string, std::string> pair);

    void remove(FilesMapShorthand it);

    FilesMapShorthand *get_value();

private:
    FilesMapShorthand _value;
};

#endif // _FILES_MAP_H_