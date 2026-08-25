#include "Game.h"
#include "Scene.h"

namespace bad {
	void Game::Update() {
		m_scene->Update();
	}

	void Game::Draw() const {
		m_scene->Draw();
	}
}