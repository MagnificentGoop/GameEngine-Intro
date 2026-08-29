#pragma once
#include <vector>
#include <string>
#include "Actor.h"
namespace bad {
	class Engine;
	class Scene {
	public:
		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors(bool force = false);


		bool Load(const std::string& sceneName);

		void Update();
		void Draw() const;
		void Clear();

		template<typename T = Actor>
		T* GetObjectByName(const std::string& name);

		void SetGame(class Game* game) { m_game = game; }
		class Game* GetGame() { return m_game; }

	private:
		void UpdateCollisions();

	private:
		std::vector< std::unique_ptr<Actor>> m_objects;
		std::vector< std::unique_ptr<Actor>> m_pendingObjects;

		class Game* m_game = nullptr;
	};

	template<typename T>
	inline T* Scene::GetObjectByName(const std::string& name)
	{
		for (auto& actor : m_objects) {
			T* objectT = dynamic_cast<T*>(actor.get());
			if (objectT && objectT->m_name == name) {
				return objectT;
			}
		}
		return NULL;
	}
}