#pragma once
namespace bad {
	class Game {
	public:
		Game() = default;
		Game(class Scene* scene) { m_scene = scene; }

		virtual bool Initialize() { return true; }
		virtual void Shutdown() {};

		virtual void Update();
		virtual void Draw();

		void SetScene(class Scene* scene) { m_scene = scene; }

	protected:
		class Scene* m_scene = nullptr;
	};
}