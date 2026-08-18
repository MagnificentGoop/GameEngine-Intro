#pragma once
#include "Actor.h"

struct PlayerDesc {
	bad::ActorDesc actorDesc;
};

class Player : public bad::Actor {
public:
	Player() = default;
	Player(const PlayerDesc& p) : Actor(p.actorDesc) {};
	Player(const bad::ActorDesc& a) : Actor(a) {};
	~Player() {};

	CLASS_PROTOTYPE(Player)

	void Update(float dt) override;

	void OnCollision(bad::Object* other) override;
private:
};