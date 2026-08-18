#include "Components/SpriteRendererComponent.h"
#include "Renderer.h"
#include "Actor.h"

namespace bad {
	void SpriteRendererComponent::Draw(const Renderer& renderer) const{
		if (m_texture) {
			renderer.DrawTexture(*m_texture, GetOwner()->GetTransform());
		}
	}

	void SpriteRendererComponent::Read(const json::value_t& value) {

	}
}