#pragma once
#include "Framework/Actor.h"

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
	void OnCollision(bad::Actor* other) override;

	void Read(const bad::json::value_t& value) override;
private:
	float m_speed = 0.0f;
};