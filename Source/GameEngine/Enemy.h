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
	~Enemy() {};

	CLASS_PROTOTYPE(Enemy)

	void Update(float dt) override;

	void OnCollision(bad::Object* other) override;
private:
};