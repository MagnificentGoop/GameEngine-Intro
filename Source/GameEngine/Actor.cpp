#include "Actor.h"
#include "MathUtils.h"
#include "Engine.h"

namespace bad {
	void Actor::Update() {
		m_transform.position += (m_velocity * bad::g_time.GetDeltaTime());
		m_velocity *= std::pow(m_drag, bad::g_time.GetDeltaTime());

		Wrap(m_transform.position.x, 0.0f, (float)bad::Engine::Get().GetRenderer().GetWidth());
		Wrap(m_transform.position.y, 0.0f, (float)bad::Engine::Get().GetRenderer().GetHeight());

		Object::Update();
	}
	void Actor::Read(const json::value_t& value){
		Object::Read(value);

		JSON_READ_NAME(value, "velocity", m_velocity);
	}
}