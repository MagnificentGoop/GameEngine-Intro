#pragma once
#include "Color.h"
#include <string>

struct SDL_Texture;

namespace bad {

	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);

		Vector2<float> GetSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};
}