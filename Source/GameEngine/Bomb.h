#pragma once
#include "Engine.h"
#include "Assets.h"
#include "SpaceGame.h"
#include "Bullet.h"

struct BombDesc {
	int shrapnelAmount = 10;
	BulletDesc bulletDesc;
};

class Bomb : public Bullet {
public:
	Bomb() = default;
	Bomb(const BombDesc& b) : Bullet(b.bulletDesc)  { m_shrapnelAmount=b.shrapnelAmount; }

	void Update();
	void OnCollision(SceneObject* other);
private:
	void EXPLOOD();
	int m_shrapnelAmount;
};