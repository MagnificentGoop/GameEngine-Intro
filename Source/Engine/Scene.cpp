#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Engine.h"
#include "Factory.h"
#include <iostream>
#include <iterator>
#include "Components/ColliderComponent.h"

namespace bad {
	void Scene::RemoveAllActors(){
		m_objects.clear();
		m_pendingObjects.clear();
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		if (!actor)
		{
			std::cerr << "Scene::AddActor received a null Actor.\n";
			return;
		}

		actor->m_scene = this;
		m_pendingObjects.push_back(std::move(actor));
	}

	bool Scene::Load(const std::string& sceneName)
	{
		bad::json::document_t document;
		if (bad::json::Load(sceneName, document)) {

			if (JSON_HAS_NAME(document, "actors"))
			{
				for (auto& objectValue : JSON_GET_NAME(document, "actors").GetArray())
				{
					std::string typeName;
					JSON_READ_NAME_REQ(objectValue, "type", typeName);

					auto actor = Factory::Instance().Create<Actor>(typeName);
					if (!actor)
					{
						std::cerr << "Failed to create actor of type: " << typeName << std::endl;
						continue;
					}
					actor->Read(objectValue);

					bool prototype = false;
					JSON_READ_REQ(objectValue, prototype);
					
					if(prototype){
						std::string name;
						JSON_READ_REQ(objectValue, name);
						Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor)); 
					}
					else {
						AddActor(std::move(actor));
					}
				}
			}
		}
		else {
			return false;
		}

		return true;
	}

	void Scene::Update() {
		bad::Engine::Get().Update();
		for (auto& actor : m_objects)
		{
			actor->Update(g_time.GetDeltaTime());
		}
		UpdateCollisions();

		//remove destroyed actors
		std::erase_if(m_objects, [](const auto& actor) {return !actor->m_active;});
		

		//insert new actors
		m_objects.insert(m_objects.end(),std::make_move_iterator(m_pendingObjects.begin()),std::make_move_iterator(m_pendingObjects.end()));

		m_pendingObjects.clear();
	}

	void Scene::Draw() const {
		for (auto& actor : m_objects) {
			actor->Draw(Engine::Get().GetRenderer());
		}
		Engine::Get().GetRenderer().Render();
	}

	void Scene::UpdateCollisions()
	{
		for (auto& actorA : m_objects) {
			for (auto& actorB : m_objects) {
				if (actorA == actorB || !actorA->m_active || !actorB->m_active) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
	void Scene::Clear() {
		Engine::Get().GetRenderer().Clear();
	}
}