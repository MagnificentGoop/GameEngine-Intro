#pragma once
#include "Font.h"
#include "Color.h"
#include "Object.h"

struct SDL_Texture;

namespace bad {

	enum class HOrigin {
		Left,
		Middle,
		Right,
	};
	enum class VOrigin {
		Top,
		Middle,
		Bottom
	};
	class Text : public Resource{
	public:
		Text() = default;
		Text(res_t<Font> font) : m_font{ font } {}
		~Text();

		bool Create(const std::string& text, const Color8& color);
		void Draw(float x, float y, HOrigin hOrigin, VOrigin vOrigin) const;
		void Draw(float x, float y) const { Draw(x, y, m_hOrigin, m_vOrigin); } //overload
		void SetHorizontalOrigin(HOrigin h) { m_hOrigin = h; }
		void SetVerticalOrigin(VOrigin v) { m_vOrigin = v; }
		HOrigin GetHorizontalOrigin() { return m_hOrigin; }
		VOrigin GetVerticalOrigin() { return m_vOrigin; }

	private:
		res_t<Font> m_font;
		SDL_Texture* m_texture{ nullptr };
		HOrigin m_hOrigin = HOrigin::Left;
		VOrigin m_vOrigin = VOrigin::Top;
	};
}