#pragma once
#include "Vector2.h"
namespace bad {
	struct Transform2D {
		Vector2<float> position;
		float rotation;
		Vector2<float> scale;
	};
}