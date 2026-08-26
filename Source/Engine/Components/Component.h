#pragma once
#include "Framework/Object.h"
namespace bad {
	class Actor;

	class Component : public Object {
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void Start() {};
		virtual void OnDestroy() {};
		virtual void Update(float dt) {}

		Actor* GetOwner() const { return m_owner; }
		void SetOwner(Actor* owner) { m_owner = owner; }

	private:
		Actor* m_owner = nullptr;
	};
}