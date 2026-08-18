#pragma once
#include "Component.h"

namespace bad {
	class RendererComponent : public Component {
	public:
		virtual void Draw(const class Renderer& renderer) const = 0;

	};
}