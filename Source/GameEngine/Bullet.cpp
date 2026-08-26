#include "Bullet.h"
#include "Math/MathUtils.h"
#include "Renderer/Renderer.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt) {

    bad::PhysicsComponent* physicsComponent = GetComponent<bad::PhysicsComponent>();
    if (physicsComponent) {
        bad::Vector2<float> forward{ 1,0 };
        bad::Vector2<float> force = forward.Rotate(m_transform.rotation * bad::DegToRad) * m_speed;

        physicsComponent->SetVelocity(force);
    }

	Actor::Update(dt);
}

void Bullet::Read(const bad::json::value_t& value){
    Actor::Read(value);

    JSON_READ_NAME_REQ(value, "speed", m_speed);
}
