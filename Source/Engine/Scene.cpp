#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Engine.h"
#include <iostream>

namespace bad {
	void Scene::RemoveAllObjects(){
		for (auto object : m_objects)
		{
			delete object;
		}
		m_objects.clear();
	}

	void Scene::Update() {
		bad::Engine::Get().Update();
		for (Object* object : m_objects)
		{
			object->Update();
		}
		UpdateCollisions();
		//remove destroyed actors
		std::erase_if(m_objects, [](auto Object) {return !Object->m_active;});
		

		//insert new actors
		m_objects.insert(m_objects.end(), m_pendingObjects.begin(), m_pendingObjects.end());

		m_pendingObjects.clear();
	}

	void Scene::Draw() {
		for (Object* object : m_objects) {
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
					actorA->OnCollision(actorB);
					actorB->OnCollision(actorA);
				}
			}
		}
	}
	void Scene::Clear() {
		Engine::Get().GetRenderer().Clear();
	}
}