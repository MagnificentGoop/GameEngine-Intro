#pragma once

#include "Object.h"
#include "Engine.h"

namespace bad {
	Object::Object(const Object& other) {
		m_name = other.m_name;
		for (size_t i = 0; i < other.m_tags.size(); i++)
		{
			m_tags.push_back(other.m_tags.at(i));
		}
		m_active = other.m_active;
	}

	void Object::Read(const json::value_t& value) {

		JSON_READ_NAME(value, "name", m_name);
		JSON_READ_NAME(value, "tags", m_tags);
		JSON_READ_NAME(value, "active", m_active);
	}

}