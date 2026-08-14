#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Engine.h"
#include "Factory.h"
#include <iostream>
#include <iterator>

namespace bad {
	void Scene::RemoveAllObjects(){
		m_objects.clear();
		m_pendingObjects.clear();
	}

	void Scene::AddObject(std::unique_ptr<Object> actor) {
		if (!actor)
		{
			std::cerr << "Scene::AddObject received a null Object.\n";
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
					JSON_READ_NAME(objectValue, "type", typeName);

					auto object = Factory::Instance().Create<Object>(typeName);
					if (!object)
					{
						std::cerr << "Failed to create object of type: " << typeName << std::endl;
						continue;
					}
					object->Read(objectValue);

					bool prototype = false;
					JSON_READ(objectValue, prototype);
					
					if(prototype){
						std::string name;
						JSON_READ(objectValue, name);
						Factory::Instance().RegisterPrototype<Object>("PlayerPrototype", std::move(object)); 
					}
					else {
						AddObject(std::move(object));
					}
				}
			}
			//JSON_READ(document, type);
		}
		else {
			return false;
		}

		return true;
	}

	void Scene::Update() {
		bad::Engine::Get().Update();
		for (auto& object : m_objects)
		{
			object->Update();
		}
		UpdateCollisions();

		//remove destroyed actors
		std::erase_if(m_objects, [](const auto& object) {return !object->m_active;});
		

		//insert new actors
		m_objects.insert(m_objects.end(),std::make_move_iterator(m_pendingObjects.begin()),std::make_move_iterator(m_pendingObjects.end()));

		m_pendingObjects.clear();
	}

	void Scene::Draw() {
		for (auto& object : m_objects) {
			object->Draw();
		}
		Engine::Get().GetRenderer().Render();
	}

	void Scene::UpdateCollisions()
	{
		for (auto& actorA : m_objects) {
			for (auto& actorB : m_objects) {
				if (actorA == actorB || !actorA->m_active || !actorB->m_active) continue;

				float distance = (actorA->GetTransform().position - actorB->GetTransform().position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
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