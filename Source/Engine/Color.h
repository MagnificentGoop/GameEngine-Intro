#pragma once
#include "Color8.h"
#include "ColorF.h"
namespace bad {
	inline Color8 ColorF::MakeColor8() const { return Color8((uint8_t)(x * 255), (uint8_t)(y * 255), (uint8_t)(z * 255), (uint8_t)(w * 255)); }
	inline ColorF Color8::MakeColorF() const { return ColorF((x / 255.0f), (y / 255.0f), (float)(z / 255.0f), (float)(w / 255.0f)); }
}