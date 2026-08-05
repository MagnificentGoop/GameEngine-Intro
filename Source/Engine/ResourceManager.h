#pragma once
#include "Resource.h"
#include <string>
#include <map>

namespace bad {
	class ResourceManager {
	public:

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};
}