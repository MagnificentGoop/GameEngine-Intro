#pragma once
#include "ColliderComponent.h"

namespace bad {
	class CircleColliderComponent : public ColliderComponent {
	public:
		bool CheckCollision(const ColliderComponent& other) override;

		void Read(const json::value_t& value) override;

		float GetRadius() const { return m_radius; }

	private:
		float m_radius;
	};
}