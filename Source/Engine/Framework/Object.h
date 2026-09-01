#pragma once

#include "Renderer/Model.h"
#include "Renderer/Renderer.h"
#include <string>
#include <memory>
#include "Resources/ResourceManager.h"
#include "Serialization/Json.h"

#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() const { return std::make_unique<classname>(*this); }

namespace bad {
	class Scene;

	struct ObjectDesc {
		std::string name = "NONE";
		std::vector<std::string> tags;
		float lifespan = -1;
	};
	class Object {
	public:
		Object() = default;
		Object(const ObjectDesc& a) :
			m_name{ a.name },
			m_tags{ a.tags } {};
		~Object() {};

		CLASS_PROTOTYPE(Object);

		Object(const Object& other);

		const void SetName(const std::string& s) { m_name = s; }
		const std::string& GetName() const { return m_name; }
		const void SetTags(const std::vector<std::string>& s) { m_tags = s; }
		const std::vector<std::string>& GetTags() const { return m_tags; }
		const void AddTag(const std::string s) { m_tags.push_back(s); }

		void SetActive(bool active = false) { m_active = active; }
		bool GetActive() const { return m_active; }

		bool GetDestroyed() const { return m_destroyed; }
		void SetDestroyed(bool destroyed = true) { m_destroyed = destroyed; }

		virtual void Read(const json::value_t& value);
	protected:
		std::string m_name = "Default";
		std::vector<std::string> m_tags;

		bool m_active = true;
		bool m_destroyed = false;
	};
}