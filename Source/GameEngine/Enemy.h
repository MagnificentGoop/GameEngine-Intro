   #pragma once
#include "Framework/Actor.h"

struct EnemyDesc {
	bad::ActorDesc enemyDesc;
};
class Enemy : public bad::Actor {
public:
	Enemy() = default;
	Enemy(const EnemyDesc& p) : Actor(p.enemyDesc) {};
	Enemy(const bad::ActorDesc& a) : Actor(a) {};
	~Enemy() {};

	CLASS_PROTOTYPE(Enemy)

	void Update(float dt) override;
	void OnCollision(bad::Actor* other) override;

private:
	float m_speed = 0.0f;
};