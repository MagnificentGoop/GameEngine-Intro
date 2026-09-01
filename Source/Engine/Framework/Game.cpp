#include "Game.h"
#include "Scene.h"
#include "Engine.h"

namespace bad {
	void Game::Update() {
		Engine::Get().Update();
		m_scene->Update();
	}

	void Game::Draw() const {
		m_scene->Draw();
	}
}