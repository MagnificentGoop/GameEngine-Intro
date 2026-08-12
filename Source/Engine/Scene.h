#pragma once
#include <vector>
#include <string>
#include "Object.h"
namespace bad {
	class Engine;
	class Scene {
	public:
		void RemoveAllObjects();

		void AddObject(Object* actor) { actor->m_scene = this; m_pendingObjects.push_back(actor); }
		void Update();
		void Draw();
		void Clear();

		template<typename T = Object>
		T* GetObjectByName(const std::string& name);

		void SetGame(class Game* game) { m_game = game; }
		class Game* GetGame() { return m_game; }

	private:
		void UpdateCollisions();

	private:
		std::vector<Object*> m_objects;
		std::vector<Object*> m_pendingObjects;

		class Game* m_game = nullptr;
	};

	template<typename T>
	inline T* Scene::GetObjectByName(const std::string& name)
	{
		for (auto object : m_objects) {
			T* objectT = dynamic_cast<T*>(object);
			if (objectT && objectT->m_name == name) {
				return objectT;
			}
		}
		return NULL;
	}
}