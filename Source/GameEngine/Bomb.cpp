#include "Bomb.h"
#include <iostream>
#include <memory>

void Bomb::Update(){
	if (m_lifespan <= 0) {
        EXPLOOD();
	}
	Bullet::Update();

    
}

void Bomb::EXPLOOD(){
	for (int i = 0; i < m_shrapnelAmount; i++)
	{
        BulletDesc desc;
        desc.bulletDesc.Object.name = "Bullet";
        desc.bulletDesc.Object.tags.push_back("PlayerBullet");
        desc.bulletDesc.Object.model = Assets::bulletModel;
        desc.bulletDesc.Object.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {1,1} };
        desc.bulletDesc.Object.lifespan = 1;
        desc.bulletDesc.velocity = { bad::RandomFloat(-140,140), bad::RandomFloat(-150,150) };
        desc.bulletDesc.speed = bad::RandomFloat(900, 1100);
        desc.bulletDesc.drag = 1.0f;


        m_scene->AddObject(new Bullet(desc));
        bad::g_audio.PlaySound("boom");


	}
}

void Bomb::OnCollision(bad::Object* other)
{
    for (int i = 0; i < other->GetTags().size(); i++)
    {
        if (other->GetTags().at(i) == "PlayerBullet") {
            SetActive();
            other->SetActive();

            EXPLOOD();
        }
    }
}
