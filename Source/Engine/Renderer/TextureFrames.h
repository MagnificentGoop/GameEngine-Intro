#pragma once
#include "ResourceManager.h"
#include <string>
#include "Math/Vector2.h"
#include "Math/Rect.h"

namespace bad {
	class TextureFrames : public Resource{
	public:
		bool Load(const std::string& filename, class Renderer& renderer);
		Rect GetFrameRect(unsigned int frame);
	private:
		int m_numColumns = 0;
		int m_numRows = 0;
		int m_startFrame = 0;
		int m_totalFrames = 0;

		Vector2<float> m_frameSize = { 0,0 };
		res_t<class Texture> m_texture;
 	};
}