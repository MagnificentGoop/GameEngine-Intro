   #pragma once
#include "Actor.h"

struct EnemyDesc {
	bad::ActorDesc enemyDesc;
};
class Enemy : public bad::Actor {
public:
	Enemy() = default;
	Enemy(const EnemyDesc& p) : Actor(p.enemyDesc) {};
	Enemy(const bad::ActorDesc& a) : Actor(a) {};

	void Update();

	void OnCollision(Object* other) override;
private:
};