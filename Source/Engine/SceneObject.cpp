#pragma once

#include "SceneObject.h"
#include "Engine.h"

void bad::SceneObject::Update(){
	if (m_lifespan <= 0 && m_lifespan > -1) {
		m_distroyed = true;
	}
	else if (m_lifespan <= -1) {
		m_lifespan = -1;
	}
	else {
		m_lifespan -= bad::g_time.GetDeltaTime();
	}
}

void bad::SceneObject::Draw() const{
	if (m_model) {
		Engine::Get().GetRenderer().DrawModel(*m_model, m_transform);
	}
}

float bad::SceneObject::GetRadius() const
{
	return m_model->GetRadius() * ((m_transform.scale.x + m_transform.scale.y) / 2) * 0.95f;
}