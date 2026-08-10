#pragma once

#include "Model.h"
#include <memory>
#include "Engine.h"

namespace Assets {
	extern bad::res_t<bad::Texture> playerTexture;
	extern bad::res_t<bad::Texture> enemyTexture;
	extern std::shared_ptr<bad::Model> bulletModel;
}