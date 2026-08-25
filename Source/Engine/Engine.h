#pragma once
#include "Core/Gametime.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Audio/Audio.h"

//Includes for others
#include "Framework/Scene.h"
#include "Math/MathUtils.h"
#include "Core/Random.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"
#include "Resources/ResourceManager.h"
#include "Serialization/Json.h"
#include "Core/File.h"
#include "Core/StringUtils.h"
#include "Core/Factory.h"

#include "Physics/Physics.h"

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

		Physics& GetPhysics() { return m_physics; }
	private:
		Engine() = default;
		Input m_input;
		Renderer m_renderer;
		ParticleSystem m_particleSystem;
		Physics m_physics;

		bool m_quit = false;
	};
	extern Audio g_audio;
	extern Time g_time;
}