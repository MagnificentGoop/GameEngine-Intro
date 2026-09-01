#pragma once
#include "Math/Color.h"
#include "Resources/Resource.h"

struct SDL_Texture;

namespace bad {

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		const Vector2<float>& GetSize() const { return m_size; }

		void SetScale(const Vector2<float>& scale) { m_scale = scale; }
		float GetRadius() { return (m_size / 2).Length() * ((m_scale.x * m_scale.y) / 2); }

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
		Vector2<float> m_size{ 0.0f, 0.0f };
		Vector2<float> m_scale{ 1.0f, 1.0f };
	};
}