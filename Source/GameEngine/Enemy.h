   #pragma once
#include "Actor.h"

struct EnemyDesc {
	ActorDesc enemyDesc;
};
class Enemy : public Actor {
public:
	Enemy() = default;
	Enemy(const EnemyDesc& p) : Actor(p.enemyDesc) {};
	Enemy(const ActorDesc& a) : Actor(a) {};
	~Enemy();

	CLASS_PROTOTYPE(Enemy)

	void Update() override;

	void OnCollision(bad::Object* other) override;
private:
};