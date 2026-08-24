#include "Bullet.h"
#include "MathUtils.h"
#include "Renderer.h"

FACTORY_REGISTER(Bullet)

void Bullet::Update(float dt) {
	SetVelocity(m_velocity);
	if (m_startingTime > 0) {
		if (bad::g_time.GetTime() - m_startingTime > 0.5) {
			m_startingTime = -1;
			AddTag("Death");

		}
	}

	Actor::Update(dt);
}