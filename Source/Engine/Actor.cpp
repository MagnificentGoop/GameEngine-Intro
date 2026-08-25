#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "Math/MathUtils.h"
#include "Texture.h"
#include "Engine.h"

#include "Components/RendererComponent.h"


namespace bad
{
	FACTORY_REGISTER(Actor)

		Actor::Actor(const Actor& other) :
		Object{ other },
		m_transform{ other.m_transform },
		m_damping{ other.m_damping },
		m_lifespan{ other.m_lifespan },
		m_speed{ other.m_speed }
		{
			for (const auto& component : other.m_components)
			{
				auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			}
		};

	void Actor::Update(float dt)
	{
			if (m_destroyed) {
				m_lifespan = 0.0f;
			}
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0.0f && m_lifespan > 1.0f);

		for (auto component : m_components) {
			component->Update(dt);
		}

		m_transform.position += (m_velocity * dt);
		m_velocity *= (1.0f / (1.0f + m_damping * dt));

		m_transform.position.x = Wrap(m_transform.position.x, 0.0f, Engine::Get().GetRenderer().GetWidth());
		m_transform.position.y = Wrap(m_transform.position.y, 0.0f, Engine::Get().GetRenderer().GetHeight());
	}

	void Actor::Draw(const Renderer& renderer) const
	{
		
	}

	float Actor::GetRadius() const
	{
		return m_transform.scale.x + m_transform.scale.y / 2;
	}
	void Actor::OnCollision(bad::Object* other)
	{
		//die
	}
	void Actor::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ_NAME(value, "lifespan", m_lifespan);
		JSON_READ_NAME(value, "damping", m_damping);

		if (JSON_HAS_NAME(value, "transform")) {
			m_transform.Read(JSON_GET_NAME(value, "transform"));
		}

		if (JSON_HAS_NAME(value, "components")) {
			for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray()) {
				std::string typeName;
				JSON_READ_NAME(componentValue, "type", typeName);

				auto component = Factory::Instance().Create<Component>(typeName);

				if (component) {
					component->Read(componentValue);
				}
			}
		}

	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->SetOwner(this);
		m_components.push_back(std::move(component));
	}
}