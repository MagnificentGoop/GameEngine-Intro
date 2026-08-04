#pragma once

#include "Model.h"
#include "Renderer.h"
#include <string>
#include <memory>

namespace bad {
	class Scene;

	struct SceneObjectDesc {
		std::string name = "NONE";
		std::vector<std::string> tags;
		Transform2D transform = { {0,0},0, {1,1} };
		std::shared_ptr<Model> model;
		float lifespan = -1;
	};
	class SceneObject {
	public:
		SceneObject() = default;
		SceneObject(const SceneObjectDesc& a) :
			m_name{ a.name },
			m_tags{ a.tags },
			m_transform{ a.transform },
			m_model{ a.model },
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
		virtual void OnCollision(SceneObject* other) {};

		void SetDistroyed(bool distroyed = true) { m_distroyed = distroyed; }
		bool GetDistroyed() const { return m_distroyed; }

		friend Scene;
	protected:
		std::string m_name = "Default";
		std::vector<std::string> m_tags;
		Transform2D m_transform;
		std::shared_ptr<Model> m_model;

		Scene* m_scene = nullptr;
		bool m_distroyed = false;
		float m_lifespan = -1;
	};
}
