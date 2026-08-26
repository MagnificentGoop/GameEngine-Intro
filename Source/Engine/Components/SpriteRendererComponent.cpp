#include "Components/SpriteRendererComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Core/Factory.h"

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

		if (!m_texture)
		{
			std::cerr << "FAILED TO LOAD TEXTURE: " << textureName << '\n';
		}
	}
}