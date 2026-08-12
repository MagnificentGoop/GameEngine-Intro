#pragma once
#include "Actor.h"
#include "Engine.h"
#include <iostream>
struct BulletDesc {
	ActorDesc bulletDesc;
};

class Bullet : public Actor {
public:
	Bullet() = default;
	Bullet(const BulletDesc& p) : Actor(p.bulletDesc) { m_startingTime = bad::g_time.GetTime(); }
	Bullet(const ActorDesc& a) : Actor(a) { m_startingTime = bad::g_time.GetTime(); }

	virtual void Update() override;
private:
	float m_startingTime;
};