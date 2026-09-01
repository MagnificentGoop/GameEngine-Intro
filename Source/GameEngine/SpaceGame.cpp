#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"
#include <memory>

bool SpaceGame::Initialize()
{
    Game::Initialize();

    m_scene = new bad::Scene();
    m_scene->SetGame(this);
    m_scene->Load("Assets/SpaceGame/Data/stupid.json");

    bad::g_audio.Initialize();
    bad::g_audio.AddSound("scream", "Assets/SpaceGame/Sounds/scream.mp3");
    bad::g_audio.AddSound("bullet", "Assets/SpaceGame/Sounds/bullet_lazer.mp3");
    bad::g_audio.AddSound("bomb", "Assets/SpaceGame/Sounds/bomb_lazer.mp3");
    bad::g_audio.AddSound("boom", "Assets/SpaceGame/Sounds/boom.mp3");

    m_titleText = std::make_shared<bad::Text>(bad::Resources().GetWithID<bad::Font>("font64", "Assets/SpaceGame/Fonts/font.ttf", 64));
    m_titleText->Create("AHHHH..", bad::Color8{ 255, 255, 255 });

    m_scoreText = new bad::Text(bad::Resources().GetWithID<bad::Font>("font32", "Assets/SpaceGame/Fonts/font.ttf", 32));
    m_livesText = new bad::Text(bad::Resources().GetWithID<bad::Font>("font32", "Assets/SpaceGame/Fonts/font.ttf", 32));
    return true;
}

void SpaceGame::Update()
{
    switch (m_gameState)
    {
    case GameState::Title:
        if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;
    case GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartLevel;
        break;
    case GameState::StartLevel:
        m_spawnTimer = 1;
        m_scene->RemoveAllActors();
        SpawnPlayer();
        m_gameState = GameState::Game;
        break;
    case GameState::Game:
        m_spawnTimer -= bad::g_time.GetDeltaTime();
        if (m_spawnTimer <= 0.0f) {
            if (m_score == 0)m_spawnTimer = bad::RandomFloat(2.0f, 10.0f);
            else m_spawnTimer = bad::RandomFloat(1.0,10.0f - (m_score/180));
            SpawnEnemy();
        }
        break;
    case GameState::Dead:
        m_stateTimer -= bad::g_time.GetDeltaTime();
        if (m_stateTimer <= 0.0f) {
            m_stateTimer = 3;
            m_gameState = GameState::StartLevel;
        }
        break;
    case GameState::GameOver:
        if (bad::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_scene->RemoveAllActors();
            m_gameState = GameState::StartGame;
        }
        break;
    default:
        break;
    }

    Game::Update();
}

void SpaceGame::Draw() const
{
    bad::Engine::Get().GetRenderer().Clear();
    switch (m_gameState)
    {
    case GameState::Title:
        m_titleText->Draw(bad::Engine::Get().GetRenderer().GetWidth()/2, bad::Engine::Get().GetRenderer().GetHeight()/2, bad::HOrigin::Middle, bad::VOrigin::Middle);
        break;
    case GameState::StartGame:
    case GameState::StartLevel:
    case GameState::Game:
    case GameState::Dead:
        m_scoreText->Create("Score: " + std::to_string(m_score), { 255,255,255 });
        m_scoreText->Draw(40, 40, bad::HOrigin::Left, bad::VOrigin::Top);
        m_livesText->Create("Lives: " + std::to_string(m_lives), {255,255,255});
        m_livesText->Draw(1880, 40,bad::HOrigin::Right, bad::VOrigin::Top);
        bad::Engine::Get().GetPS().Draw();
        break;
    case GameState::GameOver:
        m_titleText->Create("Final Score: " + std::to_string(m_score), {255,255,255});
        m_titleText->Draw(bad::Engine::Get().GetRenderer().GetWidth() / 2, bad::Engine::Get().GetRenderer().GetHeight() / 2, bad::HOrigin::Middle, bad::VOrigin::Middle);
        break;
    default:
        break;
    }

    Game::Draw();
}

void SpaceGame::OnPlayerDead(){
    m_lives--;
    if (m_lives == 0) m_gameState = GameState::GameOver;
    else {
        m_gameState = GameState::Dead;
    }
    m_stateTimer = 3;
}

void SpaceGame::SpawnPlayer(){
    auto object = bad::Factory::Instance().Create<Player>("PlayerPrototype");

    m_scene->AddActor(std::move(object));
}

void SpaceGame::SpawnEnemy(){
    auto object = bad::Factory::Instance().Create<Enemy>("enemyPrototype");

    m_scene->AddActor(std::move(object));
}