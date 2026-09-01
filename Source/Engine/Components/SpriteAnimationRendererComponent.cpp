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
		if (m_framesPerSecond <= 0.0f) return;

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

		std::cout
			<< "Frame: " << m_frame
			<< " / " << m_textureFrames->GetTotalFrames()
			<< std::endl;

		m_sourceRect = m_textureFrames->GetFrameRect(m_frame);
	}

	void SpriteAnimationRendererComponent::Start(){
		if (!m_textureFramesName.empty()) {
			m_textureFrames = Resources().Get<TextureFrames>(m_textureFramesName, Engine::Get().GetRenderer());
			if (m_textureFrames) {
				m_sourceRect = m_textureFrames->GetFrameRect(0);
				m_size = Vector2<float>{ m_sourceRect.w, m_sourceRect.h };
				m_texture = m_textureFrames->GetTexture();
			}
			if (!m_textureFrames) {
				std::cerr << "Could not load texture frames: " << m_textureFramesName << std::endl;
			}
		}
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value) {
		SpriteRendererComponent::Read(value);

		JSON_READ_NAME(value, "frames_per_second", m_framesPerSecond);
		JSON_READ_NAME_REQ(value, "loop", m_loop);

		JSON_READ_NAME_REQ(value, "texture_frames", m_textureFramesName);
	}
}