#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "MathUtils.h"
#include "Bomb.h"
#include "Assets.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt) {
    bad::Vector2<float> velocity{ 1,0 };
    velocity = velocity.Rotate(m_transform.rotation * bad::DegToRad) * m_speed * dt;

    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_W)) AddVelocity(velocity);
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_S)) AddVelocity(bad::Vector2<float>{-1,-1} * velocity);
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_D)) AddRotation(180 * dt);
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_A)) AddRotation(-180 * dt);
    if (bad::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_F)) {
        BulletDesc desc;
        bad::Vector2<float> forward{ 1,0 };
        desc.bulletDesc.object.name = "Bullet";
        desc.bulletDesc.object.tags.push_back("PlayerBullet");
        desc.bulletDesc.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {3,3} };
        desc.bulletDesc.velocity = forward.Rotate(m_transform.rotation * bad::DegToRad) * m_speed;
        desc.bulletDesc.object.lifespan = 5;
        desc.bulletDesc.speed = 1000;
        desc.bulletDesc.damping = 1.0f;

        m_scene->AddActor(std::make_unique<Bullet>(desc));
        ((SpaceGame*)m_scene->GetGame())->AddPoints(1);
        bad::g_audio.PlaySound("bullet");

    }
    if (bad::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        BombDesc desc;
        bad::Vector2<float> forward{ 1,0 };

        desc.bulletDesc.bulletDesc.object.name = "Bomb";
        desc.bulletDesc.bulletDesc.object.tags.push_back("PlayerBomb");
        desc.bulletDesc.bulletDesc.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {3,3} };
        desc.bulletDesc.bulletDesc.object.lifespan = 1;
        desc.bulletDesc.bulletDesc.speed = 1000;
        desc.bulletDesc.bulletDesc.velocity = forward.Rotate(m_transform.rotation * bad::DegToRad) * m_speed / 2;
        desc.bulletDesc.bulletDesc.damping = 0.16f;
        desc.shrapnelAmount = 20;

        m_scene->AddActor(std::make_unique<Bomb>(desc));
        ((SpaceGame*)m_scene->GetGame())->AddPoints(5);

        bad::g_audio.PlaySound("bomb");
    }

    Actor::Update(dt);
}

void Player::OnCollision(Object* other)
{
    for (int i = 0; i < other->GetTags().size(); i++)
    {
        if (other->GetTags().at(i) == "Death") { 
            bad::g_audio.PlaySound("scream");
            m_active = false;
            other->SetActive(); 
            ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
        }
    }
}