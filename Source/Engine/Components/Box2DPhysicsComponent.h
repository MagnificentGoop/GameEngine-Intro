#include "PhysicsComponent.h"
#include "Physics/PhysicsBody.h"

namespace bad {
	class Box2DPhysicsComponent : public PhysicsComponent {
	public:
		CLASS_PROTOTYPE(Box2DPhysicsComponent);

		Box2DPhysicsComponent() = default;
		Box2DPhysicsComponent(const Box2DPhysicsComponent& other);

		void Start() override;
		void Update(float dt) override;

		void ApplyForce(const Vector2<float>& force) override;

		void SetVelocity(const Vector2<float>& velocity) override;

		Vector2<float> GetVelocity() override;

		void ApplyTorque(float torque) override;

		void SetAngularVelocity(float angularVelocity) override;

		float GetAngularVelocity() const override;

		void SetPosition(const Vector2<float>& position) override;

		Vector2<float> GetPosition() const override;

		void SetRotation(float rotation) override;

		float GetRotation() const override;

		void Read(const json::value_t& value) override;
	private:
		Vector2<float> m_size{ 0,0 };
		Vector2<float> m_scale{ 1,1 };

		PhysicsBody::PhysicsBodyDef m_bodyDef;
		std::unique_ptr<PhysicsBody> m_physicsBody;
	};
}