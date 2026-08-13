#pragma once

#include "Model.h"
#include "Renderer.h"
#include "Object.h"
#include <string>

	struct ActorDesc {
		bad::Vector2<float> velocity = { 0,0 };
		float drag = 0.3f;
		float speed = 1000.0f;
		bad::ObjectDesc Object;
	};
	class Actor : public bad::Object{
	public:
		Actor() = default;
		Actor(const ActorDesc& a) : bad::Object(a.Object), m_velocity(a.velocity), m_drag(a.drag), m_speed(a.speed) {};
		~Actor() {};

		CLASS_PROTOTYPE(Actor)

		virtual void Update() override;
		virtual void Draw() const override { bad::Object::Draw(); };

		
		float GetDrag() { return m_drag; }
		void SetDrag(float drag) { m_drag = drag; }
		bad::Vector2<float> GetVelocity() const { return m_velocity; }
		void SetVelocity(const bad::Vector2<float>& v) { m_velocity = v; }
		void AddVelocity(const bad::Vector2<float>& v) { m_velocity += v; }

		virtual void Read(const bad::json::value_t& value) override;

	protected:

		bad::Vector2<float> m_velocity{ 0,0 };
		float m_drag;
		float m_speed;
	};
