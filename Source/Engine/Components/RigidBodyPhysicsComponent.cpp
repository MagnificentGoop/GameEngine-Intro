#include "pch.h"
#include "RigidBodyPhysicsComponent.h"
#include "Actor.h"

namespace bad {
	FACTORY_REGISTER(RigidBodyPhysicsComponent);
	void RigidBodyPhysicsComponent::Update(float dt){
		m_velocity += m_acceleration * dt;
		m_velocity *= 1.0f / ((1.0f) + m_damping * dt);

		m_angularVelocity += m_angularAcceleration * dt;
		m_angularVelocity *= 1.0f / ((1.0f) + m_angularDamping * dt);

		Vector2<float> position = GetOwner()->GetTransform().position;
		position += m_velocity * dt;
		GetOwner()->SetPosition(position);

		float rotation = GetOwner()->GetTransform().rotation;
		GetOwner()->AddRotation(m_angularVelocity * dt);

		m_acceleration = Vector2<float>{ 0,0 };
		m_angularAcceleration = 0;
	}
	void RigidBodyPhysicsComponent::ApplyForce(const Vector2<float>& force){
		m_acceleration += force / m_mass;
	}
	void RigidBodyPhysicsComponent::SetVelocity(const Vector2<float>&velocity){
		m_velocity = velocity;
	}
	Vector2<float> RigidBodyPhysicsComponent::GetVelocity(){
		return m_velocity;
	}
	void RigidBodyPhysicsComponent::ApplyTorque(float torque){
		m_angularAcceleration += torque / m_mass;
	}
	void RigidBodyPhysicsComponent::SetAngularVelocity(float angularVelocity){
		m_angularVelocity = angularVelocity;
	}
	float RigidBodyPhysicsComponent::GetAngularVelocity() const{
		return m_angularVelocity;
	}
	void RigidBodyPhysicsComponent::SetPosition(const Vector2<float>& position){
		GetOwner()->SetPosition(position);
	}
	Vector2<float> RigidBodyPhysicsComponent::GetPosition() const{
		return GetOwner()->GetTransform().position;
	}
	void RigidBodyPhysicsComponent::Read(const json::value_t& value){
		PhysicsComponent::Read(value);

		JSON_READ_NAME(value, "velocity", m_velocity);
		JSON_READ_NAME(value, "angular_velocity", m_angularVelocity);
	}
}