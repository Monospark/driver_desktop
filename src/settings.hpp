#pragma once

#include <string>
#include <openvr_driver.h>
#include <memory>

namespace Settings
{
template <typename T>
class Entry
{
public:
    Entry(const std::string& section, const std::string& name, T defaultValue)
        : section(section)
        , name(name)
        , defaultValue(defaultValue) {}

    virtual ~Entry() {}

    virtual T parseValue(vr::IVRSettings* settings) = 0;

protected:
    const std::string section;
    const std::string name;
    const T defaultValue;
};

class BoolEntry final : Entry<bool>
{
public:
    BoolEntry(const std::string& section, const std::string& name, bool defaultValue)
        : Entry(section, name, defaultValue) { }

    bool parseValue(vr::IVRSettings* settings) override
    {
        return settings->GetBool(section.c_str(), name.c_str(), defaultValue);
    }
};

class IntEntry final : Entry<int32_t>
{
public:
    IntEntry(const std::string& section, const std::string& name, int32_t defaultValue)
        : Entry(section, name, defaultValue) { }

    int32_t parseValue(vr::IVRSettings* settings) override
    {
        return settings->GetInt32(section.c_str(), name.c_str(), defaultValue);
    }
};

class FloatEntry final : Entry<float>
{
public:
    FloatEntry(const std::string& section, const std::string& name, float defaultValue)
        : Entry(section, name, defaultValue) {}

    float parseValue(vr::IVRSettings* settings) override
    {
        return settings->GetFloat(section.c_str(), name.c_str(), defaultValue);
    }
};

class StringEntry final : Entry<std::string>
{
public:
    StringEntry(const std::string& section, const std::string& name, const std::string& defaultValue)
        : Entry(section, name, defaultValue) { }

    std::string parseValue(vr::IVRSettings* settings) override
    {
        char buffer[1024];
        settings->GetString(section.c_str(), name.c_str(), buffer, sizeof(buffer), defaultValue.c_str());
        return std::string(buffer);
    }
};
};
