#pragma once
#include <SDL3/SDL.h>
#include "Model.h"
#include "Transform2D.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace bad
{
	class Renderer {
		public:
			inline const float GetWidth() const{ 
				return m_size->x;
			}
			inline const float GetHeight() const{ 
				return m_size->y;
			}
			inline const Vector2<float> GetSize() const{ 
				return Vector2{ m_size->x, m_size->y }; 
			}

			bool Initialize(const char* name, const float width, const float height);

			void SetBackgroundColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 255);
			void SetBackgroundColor(const Color8& c);
			void SetBackgroundColor(const ColorF& c);

			void SetColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha = 255) const;
			void SetColor(const Color8& c) const;
			void SetColor(const ColorF& c) const;

			void Clear();

			void DrawPoint(const float x, const float y, const Color8 c) const;
			void DrawPoint(const Vector2<float>& p, const Color8 c) const{
				DrawPoint(p.x, p.y, c);
			}

			void DrawRect(const float x, const float y, const float width, const float height, const Color8 c, const bool shouldFill = false) const;
			void DrawRect(const Vector4<float>& rect, const Color8 c, const bool shouldFill = false) const{
				DrawRect(rect.x, rect.y, rect.w, rect.w, c, shouldFill);
			};
			void DrawRect(const Vector3<float>& rect, const Color8 c, const bool shouldFill = false) const {
				DrawRect(rect.x, rect.y, rect.s, rect.s, c, shouldFill);
			}

			void DrawLine(const float x1, const float y1, const float x2, const float y2, const Color8 c) const;
			void DrawLine(const Vector4<float>& l, const Color8 c) const {DrawLine(l.x, l.y, l.z, l.w, c);}
			void DrawLine(const Vector2<float>& pointA, const Vector2<float>& pointB, const Color8 c) const {DrawLine(pointA.x, pointA.y, pointB.x, pointB.y, c);}

			void DrawText(const char* text, const float x, const float y, const Color8 c, const int fontSize = 32, const char* fontPath = nullptr) const;
			void DrawText(const char* text, const Vector2<float>& p, const Color8 c, const int fontSize = 32, const char* fontPath = nullptr) const {
				DrawText(text, p.x, p.y, c, fontSize, fontPath);
			}
			void DrawText(const char* text, const Vector3<float>& v, const Color8 c, const char* fontPath = nullptr) const {
				DrawText(text, v.x, v.y, c, static_cast<int>(v.s), fontPath);
			}

			void DrawModel(const Model& model, const Transform2D& transform) const;

			void DrawTexture(const class Texture& texture, float x, float y) const;
			void DrawTexture(const class Texture& texture, float x, float y, float angle, const Vector2<float>& scale = {1.0f, 1.0f}, bool flipH = false) const;
			void DrawTexture(const Texture& texture, const Transform2D& transform, bool flipH = false) const;

			void Render();
			void DestroyRenderer();
			void DistroyWindow();
			void Quit();

	private:
		friend class Text;
		friend class Texture;

		private:
			SDL_Window* m_window = nullptr;
			SDL_Renderer* m_renderer = nullptr;
			Vector2<float>* m_size = nullptr;

			Color8* m_backgroundColor = nullptr;
			bool m_tempColor = false;
	};
}