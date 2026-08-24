#pragma once
#include "Vector4.h"
namespace bad {
	struct ColorF;

	struct Color8 : public Vector4<uint8_t> {
		Color8(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255) : Vector4(r, g, b, a) {};
		Color8(const Vector2<uint8_t>* v, uint8_t b = 0, uint8_t a = 255) : Vector4(v, b, a) {};
		Color8(const Vector3<uint8_t>* v, uint8_t a = 255) : Vector4(v, a) {};
		Color8(const Vector4<uint8_t>* v) : Vector4(v) {};

		ColorF MakeColorF() const;
	};
}