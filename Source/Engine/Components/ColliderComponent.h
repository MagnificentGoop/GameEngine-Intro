#pragma once
#include "Component.h"

namespace bad {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(const ColliderComponent& other) = 0;
		virtual void Read(const json::value_t& value);
	};
}