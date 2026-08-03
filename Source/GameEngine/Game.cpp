#include "Game.h"
#include "Scene.h"

namespace bad {
	void Game::Update() {
		m_scene->Update();
	}

	void Game::Draw() {
		m_scene->Draw();
	}
}