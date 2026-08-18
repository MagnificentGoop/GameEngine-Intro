#pragma once
#include "Component.h"

namespace bad {
	class ColliderComponent : public Component {
		virtual bool CheckCollision(const ColliderComponent& other);
		virtual void Read(const json::value_t& value);
	};
}