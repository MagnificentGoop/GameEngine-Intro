#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureFrames.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace bad {
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::Update(float dt) {
		if (!m_textureFrames) return;

		m_frameTimer += dt;
		float frameTime = 1.0f / m_framesPerSecond;
		while (m_frameTimer > frameTime) {

			m_frame++;

			if (m_loop) {
				m_frame = m_frame % m_textureFrames->GetTotalFrames();
			}
			else {
				if (m_frame >= m_textureFrames->GetTotalFrames() - 1) {

					m_frame = m_textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
		}
	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer) const{
		if (!m_textureFrames) return;

		auto transform = GetOwner()->GetTransform();
		renderer.DrawTexture(*m_textureFrames->GetTexture(), m_textureFrames->GetFrameRect(m_frame), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value) {
		RendererComponent::Read(value);

		JSON_READ_NAME(value, "frames_per_second", m_framesPerSecond);
		JSON_READ_NAME_REQ(value, "loop", m_loop);

		std::string textureFrameName;
		JSON_READ_NAME_REQ(value, "texture_frames", textureFrameName);

		if (!textureFrameName.empty()) {
			m_textureFrames = Resources().Get<TextureFrames>(textureFrameName, Engine::Get().GetRenderer());
		}
	}
}