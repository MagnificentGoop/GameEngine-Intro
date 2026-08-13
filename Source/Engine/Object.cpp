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

void bad::Object::Read(const json::value_t& value){

	JSON_READ_NAME(value, "name", m_name);
	JSON_READ_NAME(value, "tags", m_tags);

	if (JSON_HAS_NAME(value, "transform")) {
		m_transform.Read(value["transform"]);
	}
	JSON_READ_NAME(value, "active", m_active);
	JSON_READ_NAME(value, "lifespan", m_lifespan);

	std::string textureName;
	JSON_READ_NAME(value, "texture", textureName);
	if (!textureName.empty()) {
		m_texture = bad::Resources().SetWithID<bad::Texture>("player", "/Assets/Images/" + textureName);
	}
}
