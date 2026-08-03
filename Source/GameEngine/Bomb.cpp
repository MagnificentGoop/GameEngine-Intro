#include "Bomb.h"
#include <iostream>

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
        desc.bulletDesc.sceneObject.name = "Bullet";
        desc.bulletDesc.sceneObject.tags.push_back("PlayerBullet");
        desc.bulletDesc.sceneObject.model = Assets::bulletModel;
        desc.bulletDesc.sceneObject.transform = bad::Transform2D{ m_transform.position, m_transform.rotation, {1,1} };
        desc.bulletDesc.sceneObject.lifespan = 1;
        desc.bulletDesc.velocity = { bad::RandomFloat(-140,140), bad::RandomFloat(-150,150) };
        desc.bulletDesc.speed = bad::RandomFloat(900, 1100);
        desc.bulletDesc.drag = 1.0f;


        m_scene->AddSceneObject(new Bullet(desc));
        bad::g_audio.PlaySound("boom");


	}
}

void Bomb::OnCollision(SceneObject* other)
{
    for (int i = 0; i < other->GetTags().size(); i++)
    {
        if (other->GetTags().at(i) == "PlayerBullet") {
            SetDistroyed();
            other->SetDistroyed();

            EXPLOOD();
        }
    }
}
