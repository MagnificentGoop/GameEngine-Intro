#include "Engine.h"
#include "SpaceGame/SpaceGame.h"
#include "Framework/Actor.h"
//unique pointer game = make unique <previous game>()

int main()
{
    //INITIALIZATION/*
    if (!bad::Engine::Get().Initialize()) return 1;
    {
        std::unique_ptr<bad::Game> game = std::make_unique<SpaceGame>();
        game->Initialize();

        //INITIALIZATION*/
        while (!bad::Engine::Get().GetIfQuit()) {
            //UPDATE*/
            game->Update();
            //UPDATE/*

            //RENDER*/
            game->Draw();
            //RENDER/*
        }
    }
    bad::Engine::Get().Shutdown();
    return 0;
}