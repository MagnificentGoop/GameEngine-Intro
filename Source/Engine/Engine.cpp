#include "Engine.h"
#include <windows.h>
#include "Core/Gametime.h"
#include "Renderer/ParticleSystem.h"

namespace bad {
	Audio g_audio;
	Time g_time;
	bool Engine::Initialize(){
		if (!(m_renderer.Initialize("Window", 1920, 1080) || m_input.Initialize())) {
			return false;
		}
		g_audio.Initialize();
		m_particleSystem.Initialize(5000);
		m_physics.Initialize();
		return true;
	}
	void Engine::Shutdown(){
		m_physics.Shutdown();
		Resources().RemoveAll();
		m_particleSystem.Shutdown();
		g_audio.Shutdown();
		m_renderer.Quit();
	}
	void Engine::Update(){
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				m_quit = true;
			}
		}

		m_input.Update();
		g_time.Tick();
		g_audio.Update();
		m_particleSystem.Update();
		m_physics.Update(g_time.GetDeltaTime());

	}
}
