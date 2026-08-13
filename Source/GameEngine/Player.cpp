#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "MathUtils.h"
#include "Bomb.h"
#include "Assets.h"
#include "SpaceGame.h"

void Player::Update() {
    bad::Vector2<float> velocity{ 1,0 };
    velocity = velocity.Rotate(m_transform.rotation * bad::DegToRad) * m_speed * bad::g_time.GetDeltaTime();

    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_W)) AddVelocity(velocity);
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_S)) AddVelocity(bad::Vector2<float>{-1,-1} * velocity);
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_D)) AddRotation(180 * bad::g_time.GetDeltaTime());
    if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_A)) AddRotation(-180 * bad::g_time.GetDeltaTime());
    if (bad::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_F)) {
        BulletDesc desc;
        bad::Vector2<float> forward{ 1,0 };
        desc.bulletDesc.Object.name = "Bullet";
        desc.bulletDesc.Object.tags.push_back("PlayerBullet");
        desc.bulletDesc.Object.texture = bad::Resources().GetWithID<bad::Texture>("bullet");
        desc.bulletDesc.Object.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {3,3} };
        desc.bulletDesc.velocity = forward.Rotate(m_transform.rotation * bad::DegToRad) * m_speed;
        desc.bulletDesc.Object.lifespan = 5;
        desc.bulletDesc.speed = 1000;
        desc.bulletDesc.drag = 1.0f;

        m_scene->AddObject(std::make_unique<Bullet>(desc));
        ((SpaceGame*)m_scene->GetGame())->AddPoints(1);
        bad::g_audio.PlaySound("bullet");

    }
    if (bad::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        BombDesc desc;
        bad::Vector2<float> forward{ 1,0 };

        desc.bulletDesc.bulletDesc.Object.name = "Bomb";
        desc.bulletDesc.bulletDesc.Object.tags.push_back("PlayerBomb");
        desc.bulletDesc.bulletDesc.Object.texture = bad::Resources().GetWithID<bad::Texture>("shrapnel");
        desc.bulletDesc.bulletDesc.Object.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {3,3} };
        desc.bulletDesc.bulletDesc.Object.lifespan = 1;
        desc.bulletDesc.bulletDesc.speed = 1000;
        desc.bulletDesc.bulletDesc.velocity = forward.Rotate(m_transform.rotation * bad::DegToRad) * m_speed / 2;
        desc.bulletDesc.bulletDesc.drag = 0.16f;
        desc.shrapnelAmount = 20;

        m_scene->AddObject(std::make_unique<Bomb>(desc));
        ((SpaceGame*)m_scene->GetGame())->AddPoints(5);

        bad::g_audio.PlaySound("bomb");
    }

    Actor::Update();
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