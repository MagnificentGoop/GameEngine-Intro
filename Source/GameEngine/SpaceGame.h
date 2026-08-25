#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Resources/ResourceManager.h"

class SpaceGame : public bad::Game {
public:
	enum class GameState {
		Title,
		StartGame,
		StartLevel,
		Game,
		Dead,
		GameOver
	};

	SpaceGame() = default;
	SpaceGame(bad::Scene* scene) : Game(scene) {};

	bool Initialize() override;
	void Update() override;
	void Draw() const override;

	void OnPlayerDead();
	void AddPoints(int points) { m_score += points; }
private:
	void SpawnPlayer();
	void SpawnEnemy();

	float m_spawnTimer = 0.0f;
	float m_stateTimer = 0.0f;

	int m_score = 0;
	int m_lives = 0;

	//bad::Font* m_titleFont = nullptr;
	bad::res_t<bad::Text> m_titleText;

	//bad::Font* m_gameOverFont = nullptr;
	bad::res_t<bad::Text> m_gameOverText;

	//bad::Font* m_gameFont = nullptr;

	bad::Text* m_scoreText = nullptr;

	bad::Text* m_livesText = nullptr;

	GameState m_gameState = GameState::Title;

	std::shared_ptr<bad::Texture> m_texture;
};
