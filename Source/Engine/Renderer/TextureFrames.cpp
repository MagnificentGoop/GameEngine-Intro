#include "pch.h"
#include "TextureFrames.h"
#include "Json.h"
#include "Texture.h"
#include "Renderer.h"

namespace bad {
	bool TextureFrames::Load(const std::string& filename, Renderer& renderer) {
		json::document_t document;

		if (!json::Load(filename, document)) {
			std::cerr << "Could not load Texture Frames: " << filename << std::endl;
			return false;
		}

		std::string textureName;
		JSON_READ(document, textureName);
		if (textureName.empty()) {
			return false;
		}

		m_texture = Resources().Get<Texture>(textureName);
		if (!m_texture) {
			std::cerr << "Could not load Texture Frame texture: " << textureName << std::endl;
			return false;
		}

		JSON_READ_NAME_REQ(document, "columns", m_numColumns);
		JSON_READ_NAME_REQ(document, "rows", m_numRows);
		JSON_READ_NAME_REQ(document, "startFrame", m_startFrame);
		JSON_READ_NAME_REQ(document, "totalFrames", m_totalFrames);

		if (m_numColumns <= 0 || m_numRows <= 0) {
			std::cerr << "Texture Frame Rows or Colums are 0" << std::endl;
			return false;
		}

		Vector2<float> textureSize = m_texture->GetSize();
		m_frameSize = textureSize / Vector2<float>{(float)m_numColumns, (float)m_numRows};
		return true;
	}

	Rect TextureFrames::GetFrameRect(unsigned int frame) {

		if (frame > m_startFrame) {
			std::cerr << "Texture Frames frame is out of bounds" << std::endl;
			frame = 0;
		}
		int currentFrame = m_startFrame + frame;
		int column = currentFrame % m_numColumns;
		int row = currentFrame / m_numColumns;

		float x = column * m_frameSize.x;
		float y = row * m_frameSize.y;

		return Rect {
			x, y, m_frameSize.x, m_frameSize.y
		};
	}
}