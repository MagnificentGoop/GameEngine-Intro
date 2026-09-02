#include "Game.h"
#include "Scene.h"
#include "Engine.h"

namespace bad {
	Game::~Game(){

	}
	void Game::Update() {
		Engine::Get().Update();
		m_scene->Update(g_time.GetDeltaTime());
	}

	void Game::Draw() const {
		m_scene->Draw();
	}
	void Game::SetScene(std::unique_ptr<class Scene> scene){
		m_scene = std::move(scene);
	}
}