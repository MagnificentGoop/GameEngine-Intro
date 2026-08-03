#pragma once
#include "Vector4.h"

namespace bad {
	struct Color8;

	struct ColorF : public Vector4<float> {
		ColorF(float r = 0, float g = 0, float b = 0, float a = 1.0f) : Vector4(r, g, b, a) { Normallize(); };
		ColorF(const Vector2<float>* v, float b = 0, float a = 1.0f) : Vector4(v, b, a) { Normallize(); };
		ColorF(const Vector3<float>* v, float a = 1.0f) : Vector4(v, a) { Normallize(); };
		ColorF(const Vector4<float>* v) : Vector4(v) { Normallize(); };

		void Normallize() {
			if (x > 1) x = 1;
			if (x < 0) x = 0;
			if (y > 1) y = 1;
			if (y < 0) y = 0;
			if (z > 1) z = 1;
			if (z < 0) z = 0;
			if (w > 1) w = 1;
			if (w < 0) w = 0;
		}

		Color8 MakeColor8() const;
	};
}