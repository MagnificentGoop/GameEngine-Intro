#pragma once
#include "Vector2.h"
#include "Json.h"
namespace bad {
	struct Transform2D {
		Vector2<float> position;
		float rotation;
		Vector2<float> scale;

		void Read(const json::value_t& value) {
			JSON_READ(value, position);
			JSON_READ(value, rotation);
			JSON_READ(value, scale);
		}
	};
}