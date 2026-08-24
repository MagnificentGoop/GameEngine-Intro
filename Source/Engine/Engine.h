#pragma once
#include "Gametime.h"
#include "Input.h"
#include "Renderer.h"
#include "Audio.h"

//Includes for others
#include "Scene.h"
#include "Math/MathUtils.h"
#include "Random.h"
#include "Text.h"
#include "ParticleSystem.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Json.h"
#include "File.h"
#include "StringUtils.h"
#include "Factory.h"

#include <iostream>

namespace bad{
	class Engine{
	public:
		static Engine& Get() { static Engine engine; return engine; }

		bool Initialize();
		void Shutdown();

		void Update();

		Input& GetInput() { return m_input; }
		Renderer& GetRenderer() { return m_renderer; }
		bool GetIfQuit() { return m_quit; }

		ParticleSystem& GetPS() { return m_particleSystem; }
	private:
		Engine() = default;
		Input m_input;
		Renderer m_renderer;
		ParticleSystem m_particleSystem;

		bool m_quit = false;
	};
	extern Audio g_audio;
	extern Time g_time;
}