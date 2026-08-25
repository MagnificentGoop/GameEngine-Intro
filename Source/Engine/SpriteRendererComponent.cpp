#include "Components/SpriteRendererComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Factory.h"

namespace bad {

	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer) const{
		if (m_texture) {
			renderer.DrawTexture(*m_texture, GetOwner()->GetTransform());
		}
	}

	void SpriteRendererComponent::Read(const json::value_t& value) {
		RendererComponent::Read(value);

		std::string textureName;
		JSON_READ_NAME_REQ(value, "texture", textureName);
		if (!textureName.empty()) {
			m_texture = Resources().Get<Texture>(textureName);
		}
	}
}