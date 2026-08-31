#include "Components/SpriteRendererComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Core/Factory.h"

namespace bad {

	FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer) const{
		if (m_texture) {
			if (m_sourceRect.w > 0 && m_sourceRect.h > 0) {
				renderer.DrawTexture(*m_texture, m_sourceRect, GetOwner()->GetTransform().position.x, GetOwner()->GetTransform().position.y, GetOwner()->GetTransform().rotation, GetOwner()->GetTransform().scale, m_flipH);
			}
			renderer.DrawTexture(*m_texture, GetOwner()->GetTransform(), m_flipH);
		}
	}

	void SpriteRendererComponent::Start(){
		if (!m_textureName.empty()) {
			m_texture = Resources().Get<Texture>(m_textureName);
			if (m_texture) {
				m_size = m_texture->GetSize();
			}
		}
		if (!m_texture)
		{
			std::cerr << "FAILED TO LOAD TEXTURE: " << m_textureName << '\n';
		}
	}

	void SpriteRendererComponent::Read(const json::value_t& value) {
		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "texture", m_textureName);
		JSON_READ_NAME(value, "flip_h", m_flipH);
	}
}