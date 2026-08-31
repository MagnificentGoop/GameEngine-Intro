#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "Renderer/Texture.h"
#include "Math/Rect.h"

namespace bad {
	class SpriteRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteRendererComponent);

		void Start() override;
		virtual void Read(const json::value_t& value) override;

		const Vector2<float>& GetSize() const { return m_size; }

		void SetFlipH(bool flipH = true) { m_flipH = flipH; }
		bool GetFlipH() const { return m_flipH; }

		void Draw(const Renderer& renderer) const override;
	protected:
		std::string m_textureName;
		Rect m_sourceRect;
		Vector2<float> m_size{ 0.0f,0.0f };
		bool m_flipH = false;

		res_t<Texture> m_texture;
	};
}