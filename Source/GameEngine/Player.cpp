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
        desc.bulletDesc.sceneObject.name = "Bullet";
        desc.bulletDesc.sceneObject.tags.push_back("PlayerBullet");
        desc.bulletDesc.sceneObject.texture = bad::Resources().GetWithID<bad::Texture>("bullet");
        desc.bulletDesc.sceneObject.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {3,3} };
        desc.bulletDesc.velocity = forward.Rotate(m_transform.rotation * bad::DegToRad) * m_speed;
        desc.bulletDesc.sceneObject.lifespan = 5;
        desc.bulletDesc.speed = 1000;
        desc.bulletDesc.drag = 1.0f;

        m_scene->AddSceneObject(new Bullet(desc));
        ((SpaceGame*)m_scene->GetGame())->AddPoints(1);
        bad::g_audio.PlaySound("bullet");

    }
    if (bad::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
        BombDesc desc;
        bad::Vector2<float> forward{ 1,0 };

        desc.bulletDesc.bulletDesc.sceneObject.name = "Bomb";
        desc.bulletDesc.bulletDesc.sceneObject.tags.push_back("PlayerBomb");
        desc.bulletDesc.bulletDesc.sceneObject.texture = bad::Resources().GetWithID<bad::Texture>("shrapnel");
        desc.bulletDesc.bulletDesc.sceneObject.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {3,3} };
        desc.bulletDesc.bulletDesc.sceneObject.lifespan = 1;
        desc.bulletDesc.bulletDesc.speed = 1000;
        desc.bulletDesc.bulletDesc.velocity = forward.Rotate(m_transform.rotation * bad::DegToRad) * m_speed / 2;
        desc.bulletDesc.bulletDesc.drag = 0.16f;
        desc.shrapnelAmount = 20;

        m_scene->AddSceneObject(new Bomb(desc));
        ((SpaceGame*)m_scene->GetGame())->AddPoints(5);

        bad::g_audio.PlaySound("bomb");
    }

    Actor::Update();
}

void Player::OnCollision(SceneObject* other)
{
    for (int i = 0; i < other->GetTags().size(); i++)
    {
        if (other->GetTags().at(i) == "Death") { 
            bad::g_audio.PlaySound("scream");
            m_distroyed = true; 
            other->SetDistroyed(); 
            ((SpaceGame*)m_scene->GetGame())->OnPlayerDead();
        }
    }
}