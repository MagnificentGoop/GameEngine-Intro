#include "Player.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "Math/MathUtils.h"
#include "Bomb.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Components/Box2DPhysicsComponent.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt) {
    float thrust = 0.0f;
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_W)) thrust = m_speed; 
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_D)) rotate = 10.0f;
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_A)) rotate = -10.0f;

    bad::PhysicsComponent* physicsComponent = GetComponent<bad::PhysicsComponent>();
    if (physicsComponent) {
        bad::Vector2<float> forward{ 1,0 };
        bad::Vector2<float> force = forward.Rotate(m_transform.rotation * bad::DegToRad) * thrust;

        physicsComponent->ApplyForce(force);
        physicsComponent->ApplyTorque(rotate);

        bad::Vector2<float> position = physicsComponent->GetPosition();

        position.x = bad::Wrap(position.x, 0.0f, bad::Engine::Get().GetRenderer().GetWidth());
        position.y = bad::Wrap(position.y, 0.0f, bad::Engine::Get().GetRenderer().GetHeight());

        physicsComponent->SetPosition(position);
    }

    if (bad::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_F)) {
        auto object = bad::Factory::Instance().Create<Bullet>("bulletPrototype");
        object->SetTransform(this->GetTransform());
        m_scene->AddActor(std::move(object));

        bad::g_audio.PlaySound("bullet");

    }
    if (bad::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        auto object = bad::Factory::Instance().Create<Bomb>("bombPrototype");
        object->SetTransform(this->GetTransform());
        m_scene->AddActor(std::move(object));

        bad::g_audio.PlaySound("bomb");
    }

    Actor::Update(dt);
}

void Player::OnCollision(bad::Actor* other)
{
    for (int i = 0; i < other->GetTags().size(); i++)
    {
        if (other->GetTags().at(i) == "Death") { 
            bad::g_audio.PlaySound("scream");
            SetDestroyed();
            other->SetDestroyed(); 
            ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
        }
    }
}

void Player::Read(const bad::json::value_t& value){
    Actor::Read(value);

    JSON_READ_NAME_REQ(value, "speed", m_speed);
}
