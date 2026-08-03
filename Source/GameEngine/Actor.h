#pragma once

#include "Model.h"
#include "Renderer.h"
#include "SceneObject.h"
#include <string>

namespace bad {

	struct ActorDesc {
		Vector2<float> velocity = { 0,0 };
		float drag = 0.3f;
		float speed = 1000.0f;
		SceneObjectDesc sceneObject;
	};
	class Actor : public SceneObject{
	public:
		Actor() = default;
		Actor(const ActorDesc& a) : SceneObject(a.sceneObject), m_velocity(a.velocity), m_drag(a.drag), m_speed(a.speed) {};

		virtual void Update();
		void Draw() const { SceneObject::Draw(); }

		
		float GetDrag() { return m_drag; }
		void SetDrag(float drag) { m_drag = drag; }
		Vector2<float> GetVelocity() const { return m_velocity; }
		void SetVelocity(const Vector2<float>& v) { m_velocity = v; }
		void AddVelocity(const Vector2<float>& v) { m_velocity += v; }

	protected:

		Vector2<float> m_velocity{ 0,0 };
		float m_drag;
		float m_speed;
	};
}
