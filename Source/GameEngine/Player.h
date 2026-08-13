#pragma once
#include "Actor.h"

struct PlayerDesc {
	ActorDesc actorDesc;
};

class Player : public Actor {
public:
	Player() = default;
	Player(const PlayerDesc& p) : Actor(p.actorDesc) {};
	Player(const ActorDesc& a) : Actor(a) {};
	~Player() {};

	CLASS_PROTOTYPE(Player)

	void Update() override;

	void OnCollision(bad::Object* other) override;
private:
};