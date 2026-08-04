#include <iostream>
#include "Renderer.h"
#include "MathUtils.h"
#include "Texture.h"

namespace bad
{
    /// <summary>
    /// Initializes the render engine
    /// </summary>
    /// <param name="name">Name of the window made</param>
    /// <param name="width">Width of the screen wanted</param>
    /// <param name="height">Height of the screen wanted</param>
    /// <returns>1 if error occoured</returns>
    bool Renderer::Initialize(const char* name, const float width, const float height) {
        SDL_Init(SDL_INIT_VIDEO);

        m_window = SDL_CreateWindow(name, (int)width, (int)height, 0);
        if (m_window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        m_renderer = SDL_CreateRenderer(m_window, NULL);
        if (m_renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return 1;
        }

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_size = new Vector2{ width, height };

        SDL_SetRenderVSync(m_renderer, 1);
        
        SetBackgroundColor(0, 0, 0);
        return 0;
	}

    void Renderer::SetColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) const{
        SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(red), static_cast<Uint8>(green), static_cast<Uint8>(blue), static_cast<Uint8>(alpha));
    }
    void Renderer::SetColor(const Color8& c) const {
        SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(c.r), static_cast<Uint8>(c.g), static_cast<Uint8>(c.b), static_cast<Uint8>(c.a));
    }
    void Renderer::SetColor(const ColorF& c) const{
        SDL_SetRenderDrawColor(m_renderer, static_cast<Uint8>(c.r), static_cast<Uint8>(c.g), static_cast<Uint8>(c.b), static_cast<Uint8>(c.a));
    }


    void Renderer::SetBackgroundColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) {
        if (m_backgroundColor != nullptr) {
            delete m_backgroundColor;
            m_backgroundColor = nullptr;
        }
        m_backgroundColor = new Color8(red, green, blue, alpha);
    }
    void Renderer::SetBackgroundColor(const Color8& c) {
        if (m_backgroundColor != nullptr) {
            delete m_backgroundColor;
            m_backgroundColor = nullptr;
        }
        m_backgroundColor = new Color8(c.r, c.g, c.b, c.a);
    }
    void Renderer::SetBackgroundColor(const ColorF& c) {
        if (m_backgroundColor != nullptr) {
            delete m_backgroundColor;
            m_backgroundColor = nullptr;
        }
        m_backgroundColor = new Color8(c.MakeColor8());
    }

	void Renderer::Clear(){
        SetColor(*m_backgroundColor);
        SDL_RenderClear(m_renderer);
    }
	void Renderer::DrawPoint(float x, float y, const Color8 c) const{
        SetColor(c);
		SDL_RenderPoint(m_renderer, x, y);
	}
    void Renderer::DrawRect(float x, float y, float width, float height, const Color8 c, bool shouldFill) const{
        SetColor(c);
		SDL_FRect rect{ x, y, width, height };
        if (shouldFill) {
			SDL_RenderFillRect(m_renderer, &rect);
        }
        else {
            SDL_RenderRect(m_renderer, &rect);
        }
    }
    void Renderer::DrawLine(const float x1, const float y1, const float x2, const float y2, const Color8 c) const {
        SetColor(c);
		SDL_RenderLine(m_renderer, x1, y1, x2, y2);
    }
    void Renderer::DrawText(const char* text, float x, float y, const Color8 c, int fontSize, const char* fontPath) const{
		if (fontPath == nullptr) {
			fontPath = "C:/Windows/Fonts/Calibri/calibri.ttf"; // Default font path
		}
        SetColor(c);
		SDL_RenderDebugText(m_renderer, x, y, text);
    }

    void Renderer::DrawModel(const Model& model, const Transform2D& transform) const {
        for (auto mesh : model.GetMeshes()) {
            auto& points = mesh.GetPoints();
            for (int i = 0; i + 1< points.size(); i++)
            {
                auto v1 = points.at(i);
                auto v2 = points.at(i + 1);

                v1 *= transform.scale;
                v2 *= transform.scale;

                v1 = v1.Rotate(transform.rotation * DegToRad);
                v2 = v2.Rotate(transform.rotation * DegToRad);

                v1 += transform.position;
                v2 += transform.position;

                DrawLine(v1,v2, mesh.GetColor());
            }
        }
    }

    void Renderer::DrawTexture(Texture* texture, float x, float y)
    {
        Vector2<float> size = texture->GetSize();

        SDL_FRect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = size.x;
        destRect.h = size.y;

        SDL_RenderTexture(m_renderer, texture->m_texture, NULL, &destRect);
    }

    void Renderer::Render() {
		SDL_RenderPresent(m_renderer);
    }
    void Renderer::DestroyRenderer() {
		SDL_DestroyRenderer(m_renderer);
    }
    void Renderer::DistroyWindow() {
		SDL_DestroyWindow(m_window);
    }
    void Renderer::Quit() {
        TTF_Quit();
        DestroyRenderer();
        DistroyWindow();
		SDL_Quit();
    }
}