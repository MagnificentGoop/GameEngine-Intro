#include "Bullet.h"
#include "MathUtils.h"
#include "Renderer.h"

void Bullet::Update() {
	SetVelocity(m_velocity);
	if (m_startingTime > 0) {
		if (bad::g_time.GetTime() - m_startingTime > 0.5) {
			m_startingTime = -1;
			AddTag("Death");

		}
	}

	Actor::Update();
}