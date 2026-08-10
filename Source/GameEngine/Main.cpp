#include "Engine.h"
#include "SpaceGame.h"
#include <fstream>

int main()
{

    {
        //read file (input file)
        std::ifstream file("Assets/Data/txt.txt");
        if (file.is_open()) {
            std::string str;
            std::getline(file, str);
            std::cout << str << std::endl;
        }
        else {
            std::cout << "crine" << std::endl;
        }
    }
    //return 0;

    //INITIALIZATION/*
    if (!bad::Engine::Get().Initialize()) return 1;
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

    bad::Engine::Get().Shutdown();
    return 0;
}