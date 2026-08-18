#pragma once
#include "RendererComponent.h"
#include "Resource.h"
#include "Texture.h"
namespace bad {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent);

		virtual void Read(const json::value_t& value) override;

		void Draw(const Renderer& renderer) const override;
	protected:
		res_t<Texture> m_texture;
	};
}