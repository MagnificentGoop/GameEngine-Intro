#pragma once
#include "Actor.h"
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

	virtual void Update();
private:
	float m_startingTime;
};