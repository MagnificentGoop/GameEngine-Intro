#pragma once
#include <vector>
#include "Color.h"
namespace bad {
	class Mesh{
	public:
		Mesh() = default;
		Mesh(const std::vector<Vector2<float>>& points, Color8& color) : m_points{ points }, m_color{ color } {};

		void SetPoints(const std::vector<Vector2<float>>& points) { m_points = points;}
		const std::vector<Vector2<float>>& GetPoints() const { return m_points; }

		void SetColor(const Color8& color) { m_color = color; }
		const Color8& GetColor() const { return m_color; }

		float GetRadius() const;
	private:
		std::vector<Vector2<float>> m_points;
		Color8 m_color = Color8{ 255,255,255 };
	};
}