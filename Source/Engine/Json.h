#pragma once
#include <rapidjson/document.h>
#include <string>
#include "Color.h"
#include <iostream>

#define JSON_READ(value, data) bad::json::Read(value, #data, data)


namespace bad::json
{
	bool Load(const std::string& filename, rapidjson::Document& document);

	// read json data
	bool Read(const rapidjson::Value& value, const std::string& name, int& data);

	bool Read(const rapidjson::Value& value, const std::string& name, float& data);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data);

	template <typename T>
	bool Read(const rapidjson::Value& value, const std::string& name, Vector2<T>& data);
	template <typename T>
	bool Read(const rapidjson::Value& value, const std::string& name, Vector3<T>& data);

	template<typename T>
	bool Read(const rapidjson::Value& value, const std::string& name, Vector2<T>& data)
	{
		// check if the value has the "<name>" and is an array with 2 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
		{
			std::cerr << "Could not read JSON value (Vector2):" << name << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[name.c_str()];
		// get array values, iterate through each element
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				std::cerr << "Could not read JSON value (Vector2):" << name << std::endl;
				return false;
			}

			// get the data
			data[i] = array[i].GetFloat();
		}

		return true;
	}
	template<typename T>
	bool Read(const rapidjson::Value& value, const std::string& name, Vector3<T>& data)
	{
		// check if the value has the "<name>" and is an array with 3 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 3)
		{
			std::cerr << "Could not read JSON value (Vector3):" << name << std::endl;
			return false;
		}

		// get json array object
		auto& array = value[name.c_str()];
		// get array values, iterate through each element
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				std::cerr << "Could not read JSON value (Vector3):" << name << std::endl;
				return false;
			}

			// get the data
			data[i] = array[i].GetFloat();
		}

		return true;
	}
}