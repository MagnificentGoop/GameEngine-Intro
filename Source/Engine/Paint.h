#pragma once

#include "Input.h"
#include "Renderer.h"

namespace bad {
	class paint {
	public:
		paint();
		void Update(Input& input);
		void Render(Renderer& rend);
	private:
		std::vector<std::vector<bad::Vector2<float>*>*>* points;
	};
}