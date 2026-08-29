#pragma once

#include <string>
#include <memory>

#include "Math/Transform2D.h"
#include "Renderer/Model.h"
#include "Resources/Resource.h"

#include "Components/Component.h"
#include "Object.h"



namespace bad
{
	class Scene;
	class Texture;

	struct ActorDesc
	{
		Transform2D transform{ {0.0, 0.0}, 0.0, {1.0,1.0} };
		ObjectDesc object;
	};

	class Actor : public Object
	{
	public:
		Actor() = default;
		Actor(const ActorDesc& ad) :
			m_transform{ ad.transform } {};

		CLASS_PROTOTYPE(Actor);

		Actor(const Actor& other);

		virtual void Update(float dt);
		virtual void Draw(const Renderer& renderer) const;

		virtual void Start();
		virtual void OnDestroy();

		virtual void OnCollision(Actor* other) {}

		void SetTransform(const Transform2D& transform) { m_transform = transform; }
		const Transform2D& GetTransform() const { return m_transform; }

		void SetPosition(const Vector2<float>& pos) { m_transform.position = pos; }
		Vector2<float> GetPosition() const { return m_transform.position; }

		void SetRotation(float rotation) { m_transform.rotation = rotation; }
		float GetRotation() const { return m_transform.rotation; }
		void AddRotation(float rotation) { m_transform.rotation += rotation; }

		void SetScale(Vector2<float> scale) { m_transform.scale = scale; }
		Vector2<float> GetScale() const { return m_transform.scale; }

		float GetRadius() const;
		virtual void OnCollision(bad::Object* other);

		virtual void Read(const json::value_t& value) override;

		void AddComponent(std::unique_ptr<Component> component);

		template<std::derived_from<Component> T>
		T* GetComponent();

		bool GetPersistent() const { return m_persistent; }

		friend Scene;
		Scene* GetScene() { return m_scene; }

	protected:
		Transform2D m_transform;
		float m_lifespan = -1.0f;
		bool m_persistent = false;

		std::vector<res_t<Component>> m_components;

		Scene* m_scene = nullptr;
	};

	template<std::derived_from<Component> T>

	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*> (component.get());
			if (result) return result;
		}
		return nullptr;
	}
}