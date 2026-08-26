#pragma once

#include <box2d/box2d.h>
#include "Math/Vector2.h"

namespace bad
{
	class Physics
	{
	public:
		Physics() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);


		static float m_pixelsPerUnit;
		friend class PhysicsBody;
	private:
		b2WorldId m_worldId;
	};
}

namespace bad::SceneConversions {
	static Vector2<float> PixelToWorld(const Vector2<float>& screen) { return screen / Physics::m_pixelsPerUnit; }
	static Vector2<float> WorldToPixel(const Vector2<float>& world) { return world * Physics::m_pixelsPerUnit; }

	static b2Vec2 ToB2(const Vector2<float> v) { return b2Vec2{ v.x, v.y }; }
	static Vector2<float> ToVector2(const b2Vec2 v) { return Vector2<float>{ v.x, v.y }; }

}