#include "Enemy.h"
#include "Player.h"
#include "Engine.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt) {
    Player* player = m_scene->GetObjectByName<Player>("Player");
    if (player) {
        bad::Vector2<float> direction = player->GetTransform().position - m_transform.position;
        float rotatoin = direction.Angle();
        SetRotation(rotatoin * bad::RadToDeg);

        bad::Vector2<float> forward{ 1,0 };
        forward = forward.Rotate(m_transform.rotation * bad::DegToRad);
        AddVelocity(forward * m_speed * dt);
    }

    bad::Vector2<float> velocity{ 1,0 };
    velocity = velocity.Rotate(m_transform.rotation * bad::DegToRad) * m_speed * dt;

    Actor::Update(dt);
}

void Enemy::OnCollision(Object* other)
{
    for (int i = 0; i < other->GetTags().size(); i++)
    {
        if (other->GetTags().at(i) == "PlayerBullet") {
            SetActive();
            other->SetActive(); 

            ((SpaceGame*)m_scene->GetGame())->AddPoints(100);

            for (int i = 0; i < 50; i++)
            {
                bad::Particle particle;
                particle.position = m_transform.position;
                particle.lifespan = bad::RandomFloat(0.5f, 2.0f);
                particle.velocity = { bad::RandomFloat(-100.0f, 100.0f), bad::RandomFloat(-100.0f, 100.0f) };
                particle.SetColor({255,20,20});

                bad::Engine::Get().GetPS().AddParticle(particle);
            }
            bad::g_audio.PlaySound("boom");
        }
    }
}
