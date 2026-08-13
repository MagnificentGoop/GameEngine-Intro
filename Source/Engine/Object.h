#pragma once

#include "Model.h"
#include "Renderer.h"
#include <string>
#include <memory>
#include "ResourceManager.h"
#include "Json.h"

namespace bad {
	class Scene;

	struct ObjectDesc {
		std::string name = "NONE";
		std::vector<std::string> tags;
		Transform2D transform = { {0,0},0, {1,1} };
		std::shared_ptr<Model> model;
		res_t<bad::Texture> texture;
		float lifespan = -1;
	};
	class Object {
	public:
		Object() = default;
		Object(const ObjectDesc& a) :
			m_name{ a.name },
			m_tags{ a.tags },
			m_transform{ a.transform },
			m_model{ a.model },
			m_texture{a.texture},
			m_lifespan{ a.lifespan } {};

		virtual void Update();
		virtual void Draw() const;

		const void SetTransform(const Transform2D& t) { m_transform = t; }
		const Transform2D& GetTransform() const { return m_transform; }
		const void SetPosition(const Vector2<float>& position) { m_transform.position = position; };
		const Vector2<float> GetPosition() { return m_transform.position; }
		const void SetRotatoin(float rotation) { m_transform.rotation = rotation; };
		const float GetRotation() { return m_transform.rotation; }
		const void AddRotation(float a) { m_transform.rotation += a; }
		const void SetScale(float scale) { m_transform.scale = scale; };
		const Vector2<float> GetScale() { return m_transform.scale; }

		const void SetName(const std::string& s) { m_name = s; }
		const std::string& GetName() const { return m_name; }
		const void SetTags(const std::vector<std::string>& s) { m_tags = s; }
		const std::vector<std::string>& GetTags() const { return m_tags; }
		const void AddTag(const std::string s) { m_tags.push_back(s); }

		void SetModel(std::shared_ptr<Model> model) { m_model = model; }

		float GetRadius() const;
		virtual void OnCollision(Object* other) {};

		void SetActive(bool active = false) { m_active = active; }
		bool GetActive() const { return m_active; }

		virtual void Read(const json::value_t& value) {
			JSON_READ_NAME(value, "name", m_name);
			JSON_READ_NAME(value, "tags", m_tags);

			if (JSON_HAS_NAME(value, "transform")) {
				m_transform.Read(value["transform"]);
			}
			JSON_READ_NAME(value, "active", m_active);
			JSON_READ_NAME(value, "lifespan", m_lifespan);

			std::string textureName;
			JSON_READ_NAME(value, "texture", textureName);
			if (!textureName.empty()) {
				//m_texture = bad::Resources().SetWithID("player", "/Assets/Images/" + textureName)
			}
		}

		friend Scene;
	protected:
		std::string m_name = "Default";
		std::vector<std::string> m_tags;
		Transform2D m_transform;
		std::shared_ptr<Model> m_model;
		res_t<bad::Texture> m_texture;

		Scene* m_scene = nullptr;
		bool m_active = true;
		float m_lifespan = -1;
	};
}