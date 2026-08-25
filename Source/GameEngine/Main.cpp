#include "Engine.h"
#include "SpaceGame.h"
#include "Framework/Actor.h"

int main()
{
    //INITIALIZATION/*
    if (!bad::Engine::Get().Initialize()) return 1;
    {
        SpaceGame game;
        game.Initialize();

        //INITIALIZATION*/
        while (!bad::Engine::Get().GetIfQuit()) {
            //UPDATE*/
            game.Update();
            //UPDATE/*

            //RENDER*/
            game.Draw();
            //RENDER/*
        }
    }
    bad::Engine::Get().Shutdown();
    return 0;
}