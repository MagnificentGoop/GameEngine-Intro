#pragma once
#include <memory>

namespace bad {
	class Game {
	public:
		Game() = default;
		virtual ~Game();

		virtual bool Initialize() { return true; }
		virtual void Shutdown() {};

		virtual void Update();
		virtual void Draw() const;

		void SetScene(std::unique_ptr<class Scene> scene);

	protected:
		std::unique_ptr<class Scene> m_scene = nullptr;
	};
}