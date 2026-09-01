#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Engine.h"
#include "Core/Factory.h"
#include "Components/ColliderComponent.h"

namespace bad {
	void Scene::RemoveAllActors(bool force) {
		std::erase_if(m_actors, [force](auto& actor) {return !actor->GetPersistent() || force; });
	}

	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		if (!actor)
		{
			std::cerr << "Scene::AddActor received a null Actor.\n";
			return;
		}

		actor->m_scene = this;
		m_pendingActors.push_back(std::move(actor));
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

					if (prototype) {
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

	void Scene::Update(float dt)
	{
		for (auto& actor : m_actors)
		{
			actor->Update(dt);
		}

		for (auto& actor : m_actors)
		{
			if (actor->m_destroyed) actor->OnDestroy();
		}

		std::erase_if(m_actors, [](auto& actor) {return actor->GetDestroyed(); });

		for (auto& actor : m_pendingActors) {
			actor->Start();
			m_actors.push_back(std::move(actor));
		}

		m_pendingActors.clear();

		//UpdateCollisions();
	}

	void Scene::Draw() const {
		for (auto& actor : m_actors) {
			actor->Draw(Engine::Get().GetRenderer());
		}
		Engine::Get().GetRenderer().Render();
	}

	void Scene::UpdateCollisions()
	{
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
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