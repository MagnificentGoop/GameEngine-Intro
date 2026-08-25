#pragma once
#include "Vector2.h"
#include "Json.h"
namespace bad {
	struct Transform2D {
		Vector2<float> position;
		float rotation;
		Vector2<float> scale;

		void Read(const json::value_t& value) {
			JSON_READ_REQ(value, position);
			JSON_READ_REQ(value, rotation);
			JSON_READ_REQ(value, scale);
		}
	};
}