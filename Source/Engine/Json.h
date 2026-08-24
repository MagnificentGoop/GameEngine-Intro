#pragma once
#include <rapidjson/document.h>
#include <string>
#include "Math/Color.h"
#include <iostream>
#include <vector>

#define JSON_READ(value, data) bad::json::Read(value, #data, data)
#define JSON_READ_NAME(value, name, data) bad::json::Read(value, name, data)

#define JSON_HAS_NAME(value, name) value.HasMember(name)
#define JSON_HAS(value, data) value.HasMember(#data)

#define JSON_GET(value, data) value[#data]
#define JSON_GET_NAME(value, name) value[name]

namespace bad::json
{
	using value_t = rapidjson::Value;
	using document_t = rapidjson::Document;

	bool Load(const std::string& filename, document_t& document);

	// read json data
	bool Read(const value_t& value, const std::string& name, int& data);
	bool Read(const value_t& value, const std::string& name, float& data);
	bool Read(const value_t& value, const std::string& name, bool& data);
	bool Read(const value_t& value, const std::string& name, std::string& data);

	bool Read(const value_t& value, const std::string& name, std::vector<int>& data);
	bool Read(const value_t& value, const std::string& name, std::vector<float>& data);
	bool Read(const value_t& value, const std::string& name, std::vector<bool>& data);
	bool Read(const value_t& value, const std::string& name, std::vector<std::string>& data);

	template <typename T>
	bool Read(const value_t& value, const std::string& name, Vector2<T>& data);
	template <typename T>
	bool Read(const value_t& value, const std::string& name, Vector3<T>& data);

	template<typename T>
	bool Read(const value_t& value, const std::string& name, Vector2<T>& data)
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
	bool Read(const value_t& value, const std::string& name, Vector3<T>& data)
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