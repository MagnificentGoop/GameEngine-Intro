#include "Bomb.h"
#include <iostream>
#include <memory>
#include "Components/Box2DPhysicsComponent.h"

FACTORY_REGISTER(Bomb)

void Bomb::Update(float dt){
	if (m_lifespan <= 0) {
        EXPLOOD();
	}
    Bullet::Update(dt);
}

void Bomb::EXPLOOD(){
	for (int i = 0; i < m_shrapnelAmount; i++)
	{
        BulletDesc desc;
        desc.bulletDesc.object.name = "Bullet";
        desc.bulletDesc.object.tags.push_back("PlayerBullet");
        desc.bulletDesc.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {1,1} };
        desc.bulletDesc.object.lifespan = 1;


        m_scene->AddActor(std::make_unique<Bullet>(desc));
        bad::g_audio.PlaySound("boom");
	}
}

void Bomb::OnCollision(bad::Actor* other)
{
    for (int i = 0; i < other->GetTags().size(); i++)
    {
        if (other->GetTags().at(i) == "PlayerBullet") {
            SetDestroyed();
            other->SetDestroyed();

            EXPLOOD();
        }
    }
}
