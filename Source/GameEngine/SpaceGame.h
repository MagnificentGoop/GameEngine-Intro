#pragma once
#include "Game.h"
#include "Text.h"
#include "Font.h"
#include "ResourceManager.h"

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
	void Draw() override;

	void OnPlayerDead();
	void AddPoints(int points) { m_score += points; }
private:
	void SpawnPlayer();
	void SpawnEnemy();

	float m_spawnTimer = 0.0f;
	float m_stateTimer = 0.0f;

	int m_score = 0;
	int m_lives = 0;

	bad::res_t<bad::Font> m_titleFont;
	bad::res_t<bad::Font> m_gameFont;
	bad::res_t<bad::Font> m_gameOverFont;

	//bad::Font* m_titleFont = nullptr;
	bad::Text* m_titleText = nullptr;

	//bad::Font* m_gameOverFont = nullptr;
	bad::Text* m_gameOverText = nullptr;

	//bad::Font* m_gameFont = nullptr;

	bad::Text* m_scoreText = nullptr;

	bad::Text* m_livesText = nullptr;

	GameState m_gameState = GameState::Title;

	std::shared_ptr<bad::Texture> m_texture;
};
