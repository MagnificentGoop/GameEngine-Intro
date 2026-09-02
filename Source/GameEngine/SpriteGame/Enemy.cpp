#include "Enemy.h"
#include "Player.h"
#include "Engine.h"
#include "SpriteGame.h"
#include "Components/PhysicsComponent.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt) {
    float thrust = m_speed;

    bad::PhysicsComponent* physicsComponent = GetComponent<bad::PhysicsComponent>();
    auto player = m_scene->GetObjectByName("playerPrototype");
    if (physicsComponent && player != NULL) {
        bad::Vector2<float> forward{ 1,0 };
        bad::Vector2<float> force = forward.Rotate(m_transform.rotation * bad::DegToRad) * thrust;

        physicsComponent->ApplyForce(force);
        physicsComponent->ApplyTorque(1);

        bad::Vector2<float> position = physicsComponent->GetPosition();

        position.x = bad::Wrap(position.x, 0.0f, bad::Engine::Get().GetRenderer().GetWidth());
        position.y = bad::Wrap(position.y, 0.0f, bad::Engine::Get().GetRenderer().GetHeight());

        physicsComponent->SetPosition(position);
    }

    Actor::Update(dt);
}

void Enemy::OnCollision(bad::Actor* other)
{
    for (int i = 0; i < other->GetTags().size(); i++)
    {
        if (other->GetTags().at(i) == "PlayerBullet") {
            SetDestroyed();
            other->SetDestroyed(); 

            ((SpriteGame*)m_scene->GetGame())->AddPoints(100);

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
