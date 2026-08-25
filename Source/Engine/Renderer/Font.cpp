#include "pch.h"
#include "Font.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace bad {
	Font::~Font() {
		if (m_ttfFont != nullptr)
		{
			TTF_CloseFont(m_ttfFont);
			m_ttfFont = nullptr;
		}
	}

	bool Font::Load(const std::string& name, float fontSize) {
		m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (m_ttfFont == nullptr)
		{
			return false;
		}
		return true;
	}
}