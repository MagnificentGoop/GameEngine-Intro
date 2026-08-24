#pragma once

namespace bad {
	struct Rect {
		float x, y, h, w;

		Rect() :  x { 0 }, y{ 0 }, h{ 0 }, w{ 0 } {};
		Rect(float x, float y, float h, float w) : x{ x }, y{ y }, h{ h }, w { w } {};
	};
}