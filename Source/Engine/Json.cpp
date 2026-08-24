#include "pch.h"
#include "Json.h"
#include "File.h"


namespace bad::json
{
    bool Load(const std::string& filename, document_t& document)
    {
        // read the file into a string
        std::string buffer;
        if (!ReadTextFile(filename, buffer))
        {
            std::cerr << "Could not read file:" << filename << std::endl;
            return false;
        }

        // convert the string into a json stream
        std::stringstream stream(buffer);
        rapidjson::IStreamWrapper istream(stream);

        // set the json document from the stream
        document.ParseStream(istream);

        // check if the parse was successful
        if (document.HasParseError())
        {
            std::cerr << "Could not parse JSON: " << filename << std::endl;
            std::cerr << "Error: " << rapidjson::GetParseError_En(document.GetParseError()) << std::endl;

            return false;
        }

        // check that the root value is an object, not an array/string/number/etc.
        if (!document.IsObject())
        {
            std::cerr << "JSON root is not an object: " << filename << std::endl;
            return false;
        }

        return true;
    }

    bool Read(const value_t& value, const std::string& name, int& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
        {
            std::cerr << "Could not read JSON value (int):" << name << std::endl;
            return false;
        }

        // get the data
        data = value[name.c_str()].GetInt();

        return true;
    }
    bool Read(const value_t& value, const std::string& name, float& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber()) {
            std::cerr << "Could not read JSON value (float):" << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetFloat();

        return true;
    }
    bool Read(const value_t& value, const std::string& name, bool& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
        {
            std::cerr << "Could not read JSON value (bool):" << name << std::endl;
            return false;
        }

        // get the data
        data = value[name.c_str()].GetBool();

        return true;
    }
    bool Read(const value_t& value, const std::string& name, std::string& data)
    {
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {
            std::cerr << "Could not read JSON value (string):" << name << std::endl;
            return false;
        }

        data = value[name.c_str()].GetString();

        return true;
    }
    bool Read(const value_t& value, const std::string& name, std::vector<int>& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read JSON value (int[]):" << name << std::endl;
            return false;
        }

        // get the data
        data.clear();
        const auto& array = value[name.c_str()];

        for (const auto& element : array.GetArray())
        {
            if (!element.IsInt())
            {
                std::cerr << "Could not read JSON value (int[]):" << name << std::endl;
                return false;
            }

            data.push_back(element.GetInt());
        }

        return true;
    }
    bool Read(const value_t& value, const std::string& name, std::vector<float>& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read JSON value (float[]):" << name << std::endl;
            return false;
        }

        // get the data
        data.clear();
        const auto& array = value[name.c_str()];

        for (const auto& element : array.GetArray())
        {
            if (!element.IsFloat())
            {
                std::cerr << "Could not read JSON value (float[]):" << name << std::endl;
                return false;
            }

            data.push_back(element.GetFloat());
        }

        return true;
    }
    bool Read(const value_t& value, const std::string& name, std::vector<bool>& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read JSON value (bool[]):" << name << std::endl;
            return false;
        }

        // get the data
        data.clear();
        const auto& array = value[name.c_str()];

        for (const auto& element : array.GetArray())
        {
            if (!element.IsBool())
            {
                std::cerr << "Could not read JSON value (bool[]):" << name << std::endl;
                return false;
            }

            data.push_back(element.GetBool());
        }

        return true;
    }
    bool Read(const value_t& value, const std::string& name, std::vector<std::string>& data)
    {
        // check if the value has the "<name>" and the correct data type
        if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
        {
            std::cerr << "Could not read JSON value (std::string[]):" << name << std::endl;
            return false;
        }

        // get the data
        data.clear();
        const auto& array = value[name.c_str()];

        for (const auto& element : array.GetArray())
        {
            if (!element.IsString())
            {
                std::cerr << "Could not read JSON value (std::string[]):" << name << std::endl;
                return false;
            }

            data.push_back(element.GetString());
        }

        return true;
    }
}