#pragma once
#include "Math/Transform2D.h"
#include "Math/Vector2.h"
#include <box2d/box2d.h>

namespace bad
{
	class PhysicsBody 
	{
	public:
		enum class Shape 
		{
			Box,
			Circle,
			Capsule
		};

		struct PhysicsBodyDef 
		{
			// body
			float gravityScale = 1.0f;
			float linearDamping = 0.2f;
			float angularDamping = 0.2f;
			bool  constrainAngle = false;
			bool  isDynamic = true;

			// material
			float friction = 0.3f;
			float restitution = 0.5f;
			float density = 1.0f;

			// shape
			Shape shape = Shape::Box;
			bool isSensor = false;

			// actor associated with the body
			class Actor* actor{ nullptr };
		};

	public:
		PhysicsBody(const Transform2D& transform, const Vector2<float>& size, const PhysicsBodyDef& def, const class Physics& physics);
		~PhysicsBody();

		void ApplyForce(const Vector2<float>& force);
		void SetVelocity(const Vector2<float>& velocity);
		Vector2<float> GetVelocity();
				
		void ApplyTorque(float torque);
		void SetAngularVelocity(float angularVelocity);
		float GetAngularVelocity();

		Vector2<float> GetPosition() const;
		void SetPosition(const Vector2<float>& position) const;

		float GetRotation() const;
		void SetRotation(float radians) const;

	private:
		b2BodyId m_bodyId{ b2_nullBodyId };
	};
}