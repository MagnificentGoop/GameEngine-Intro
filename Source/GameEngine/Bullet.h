#pragma once
#include "Framework/Actor.h"
#include "Engine.h"
#include <iostream>

struct BulletDesc {
	bad::ActorDesc bulletDesc;
};

class Bullet : public bad::Actor {
public:
	Bullet() = default;
	Bullet(const BulletDesc& p) : Actor(p.bulletDesc) { m_startingTime = bad::g_time.GetTime(); }
	Bullet(const bad::ActorDesc& a) : Actor(a) { m_startingTime = bad::g_time.GetTime(); }
	~Bullet() {};

	CLASS_PROTOTYPE(Bullet)

	virtual void Update(float dt) override;
private:
	float m_startingTime;
};