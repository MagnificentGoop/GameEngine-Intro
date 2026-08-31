#include "pch.h"
#include "SpriteAnimatorRendererComponent.h"
#include "Renderer/TextureFrames.h"
#include "Core/StringUtils.h"
#include "Core/Factory.h"
#include "Engine.h"

namespace bad {
	FACTORY_REGISTER(SpriteAnimatorRendererComponent);

	void SpriteAnimatorRendererComponent::Start(){
		if (m_defaultAnimationName.empty()) {
			auto iter = m_spriteAnimations.begin();
			m_defaultAnimationName = iter->first;
		}

		Play(m_defaultAnimationName);
	}
	void SpriteAnimatorRendererComponent::Update(float dt){
		if (!m_spriteAnimation.textureFrames) return;

		m_frameTimer += dt;
		float frameTime = 1.0f / m_spriteAnimation.fps;
		while (m_frameTimer > frameTime) {

			m_frame++;

			if (m_spriteAnimation.loop) {
				m_frame = m_frame % m_spriteAnimation.textureFrames->GetTotalFrames();
			}
			else {
				if (m_frame >= m_spriteAnimation.textureFrames->GetTotalFrames() - 1) {

					m_frame = m_spriteAnimation.textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
		}

		m_sourceRect = m_spriteAnimation.textureFrames->GetFrameRect(m_frame);
	}
	void SpriteAnimatorRendererComponent::Play(const std::string & name){
		auto iter = m_spriteAnimations.find(ToLower(name));
		if (iter == m_spriteAnimations.end()) {
			std::cerr << "Could not find that animation: " << name << std::endl;
			return;
		}


		m_spriteAnimation = iter->second;

		m_frame = 0;
		m_frameTimer = 0;

		m_texture = m_spriteAnimation.textureFrames->GetTexture();
		m_sourceRect = m_spriteAnimation.textureFrames->GetFrameRect(0);
	}
	void SpriteAnimatorRendererComponent::Read(const json::value_t & value){
		SpriteRendererComponent::Read(value);

		JSON_READ_NAME(value, "default_animation", m_defaultAnimationName);

		if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray())
		{
			for (auto& animatorValue : JSON_GET(value, animations).GetArray())
			{
				SpriteAnimation spriteAnimation;

				std::string textureAnimationName;

				JSON_READ_NAME(animatorValue, "name", spriteAnimation.name);

				std::string texture_frames;
				JSON_READ_REQ(animatorValue, texture_frames);

				if (!texture_frames.empty())
				{
					spriteAnimation.textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
					if (!spriteAnimation.textureFrames)
					{
						std::cerr << "Could not load texture frames: " << texture_frames << std::endl;
					}
				}

				JSON_READ_NAME_REQ(animatorValue, "frames_per_second", spriteAnimation.fps);
				JSON_READ_NAME(animatorValue, "loop", spriteAnimation.loop);

				m_spriteAnimations[ToLower(spriteAnimation.name)] = spriteAnimation;
			}
		}

	}
}