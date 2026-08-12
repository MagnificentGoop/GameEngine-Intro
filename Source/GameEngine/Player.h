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

	void Update();

	void OnCollision(Object* other) override;
private:
};