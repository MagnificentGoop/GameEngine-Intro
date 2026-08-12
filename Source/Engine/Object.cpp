#pragma once

#include "Object.h"
#include "Engine.h"

void bad::Object::Update(){
	if (m_lifespan <= 0 && m_lifespan > -1) {
		m_active = false;
	}
	else if (m_lifespan <= -1) {
		m_lifespan = -1;
	}
	else {
		m_lifespan -= bad::g_time.GetDeltaTime();
	}
}

void bad::Object::Draw() const{
	if (!m_texture && m_model) {
		Engine::Get().GetRenderer().DrawModel(*m_model, m_transform);
	}
	if (m_texture) {
		Engine::Get().GetRenderer().DrawTexture(*m_texture, m_transform);
	}
}

float bad::Object::GetRadius() const
{
	if (!m_texture && m_model) return m_model->GetRadius() * ((m_transform.scale.x + m_transform.scale.y) / 2) * 0.95f;
	else if (m_texture) return m_texture->GetRadius() * ((m_transform.scale.x + m_transform.scale.y) / 2) * 0.95f;
	else return 0;
}