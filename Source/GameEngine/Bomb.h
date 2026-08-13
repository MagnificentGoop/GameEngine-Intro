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
	~Bomb();

	CLASS_PROTOTYPE(Bomb)

	void Update() override;
	void OnCollision(bad::Object* other) override;
private:
	void EXPLOOD();
	int m_shrapnelAmount;
};