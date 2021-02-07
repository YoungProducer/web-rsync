#include "files-map.h"

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

/** Native functions */
boost::unordered_map<std::string, std::string> *FilesMap::get_value()
{
    return &(this->_value);
}
