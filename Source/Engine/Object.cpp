#pragma once

#include "Object.h"
#include "Engine.h"

void bad::Object::Read(const json::value_t& value){

	JSON_READ_NAME(value, "name", m_name);
	JSON_READ_NAME(value, "tags", m_tags);
	JSON_READ_NAME(value, "active", m_active);
}
