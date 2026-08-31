#pragma once
#include "RendererComponent.h"

namespace bad {
	class TilemapLoaderComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(TilemapLoaderComponent);

		TilemapLoaderComponent();
		TilemapLoaderComponent(const TilemapLoaderComponent& other);

		void Start() override;
		void Draw(const Renderer& renderer) const override;

		void Read(const json::value_t& value) override;
	private:
		std::string m_tilemapName;
		res_t<class Tilemap> m_tilemap;

		std::vector<std::unique_ptr<class PhysicsBody>> m_physicsBodies;
	};
}