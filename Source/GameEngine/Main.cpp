#include "Engine.h"
#include "SpaceGame.h"
#include "Actor.h"

int main()
{
    // read/show the data from the json file
    std::string name;
    int age;
    float speed;
    bool isAwake;
    bad::Vector2<int> position;
    bad::Vector3<float> color;

    rapidjson::Document document;
    bad::json::Load("Assets/Data/data.json", document);

    // read the json data
    JSON_READ(document, name);
    JSON_READ(document, age);
    JSON_READ(document, speed);
    JSON_READ(document, isAwake);
    JSON_READ(document, position);
    JSON_READ(document, color);

    // show the data
    std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
    std::cout << position.x << " " << position.y << std::endl;
    std::cout << color.x << " " << color.y << " " << color.z << " " << std::endl;

    bad::Factory::Instance().Register<Actor>("Actor");
    bad::Factory::Instance().Register<bad::Object>("Object");

    auto actor = bad::Factory::Instance().Create<Actor>("Actor");
    std::cout << actor->GetActive() << std::endl;

    auto object = bad::Factory::Instance().Create("Object");

    bad::json::document_t documentb;
    if (bad::json::Load("Assets/Data/stupid.json", documentb)) {
        object->Read(documentb);
        std::cout << object->GetName() << std::endl;
    }

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