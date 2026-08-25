#pragma once
#include "PhysicsComponent.h"
#include "Core/Factory.h"

namespace bad {
	class RigidBodyPhysicsComponent : public PhysicsComponent {
	public:
		CLASS_PROTOTYPE(RigidBodyPhysicsComponent);

		void Update(float dt) override;
		void ApplyForce(const Vector2<float>& force) override;
		void SetVelocity(const Vector2<float>& velocity) override;
		Vector2<float> GetVelocity() override;
		void ApplyTorque(float torque) override;
		void SetAngularVelocity(float angularVelocity) override;
		float GetAngularVelocity() const override;
		void SetPosition(const Vector2<float>& position) override;
		Vector2<float> GetPosition() const override;

		void Read(const json::value_t& value) override;
	private:
		Vector2<float> m_acceleration{ 0,0 };
		float m_angularAcceleration = 0.0f;

		Vector2<float> m_velocity{ 0,0 };
		float m_angularVelocity = 0;
	};
}