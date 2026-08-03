#pragma once
#include <cstdint>
#include <SDL3/SDL.h>

namespace bad {
	class Time
	{
	public:
		Time();

		void Reset();
		void Tick();

		float GetTime() const{ return TicksToSeconds(static_cast<float>(m_currentTicks - m_startTicks)); }
		float GetDeltaTime() const { return TicksToSeconds(static_cast<float>(m_deltaTicks * m_timeScale)); }

		float TicksToSeconds(float ticks) const { return (ticks / 1'000'000'000.0f); }

		void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
		float GetTimeScale() const { return m_timeScale; }
	private:
		float m_timeScale = 1.0f;

		uint64_t m_startTicks;
		uint64_t m_currentTicks;
		uint64_t m_frameTicks;
		uint64_t m_deltaTicks;
	};
}