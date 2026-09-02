#pragma once
#include "RendererComponent.h"
#include "Physics/PhysicsBody.h"

namespace bad {
	class TilemapRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(TilemapRendererComponent);

		TilemapRendererComponent() {};
		TilemapRendererComponent(const TilemapRendererComponent& other);

		void Start() override;
		void Draw(const Renderer& renderer) const override;

		void Read(const json::value_t& value) override;
	private:
		std::string m_tilemapName;
		res_t<class Tilemap> m_tilemap;

		std::vector<std::unique_ptr<class PhysicsBody>> m_physicsBodies;
	};
}