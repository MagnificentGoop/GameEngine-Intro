#include "pch.h"
#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include "Renderer.h"
#include "Engine.h"

namespace bad {
	Text::~Text() {
		if (m_texture != nullptr) {
			SDL_DestroyTexture(m_texture);
		}
	}

	bool Text::Create(const std::string& text, const Color8& color) {
		// create a surface using the font, text string and color
		SDL_Color c{ (uint8_t)(color.r), (uint8_t)(color.g), (uint8_t)(color.b), (uint8_t)(color.a) };
		SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), text.size(), c);
		if (surface == nullptr) {
			std::cerr << "Could not create surface.\n";
			return false;
		}

		// create a texture from the surface, only textures can render to the renderer
		m_texture = SDL_CreateTextureFromSurface(bad::Engine::Get().GetRenderer().m_renderer, surface);
		if (m_texture == nullptr) {
			SDL_DestroySurface(surface);
			std::cerr << "Could not create texture" << SDL_GetError() << std::endl;
			return false;
		}

		// free the surface, no longer needed after creating the texture
		SDL_DestroySurface(surface);
		return true;
	}

	void Text::Draw(float x, float y, HOrigin hOrigin, VOrigin vOrigin) {
		// get the texture width and height
		float width, height;
		bool success = SDL_GetTextureSize(m_texture, &width, &height);
		if (!success) {
			std::cout << SDL_GetError() << std::endl;
		}

		//set the origin

		switch (hOrigin)
		{
		case bad::HOrigin::Left:
			break;
		case bad::HOrigin::Middle:
			x -= width / 2;
			break;
		case bad::HOrigin::Right:
			x -= width;
			break;
		default:
			break;
		}

		switch (vOrigin)
		{
		case bad::VOrigin::Top:
			break;
		case bad::VOrigin::Middle:
			y -= height / 2;
			break;
		case bad::VOrigin::Bottom:
			y -= height;
			break;
		default:
			break;
		}

		// set the texture into the renderer at rect 
		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(bad::Engine::Get().GetRenderer().m_renderer, m_texture, NULL, &rect);
		if (!success) {
			std::cout << SDL_GetError() << std::endl;
		}
	}
}