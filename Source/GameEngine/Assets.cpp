#include "Assets.h"

namespace Assets {
    bad::Color8 WHITE{ 255,255,255 };
    bad::Color8 RED{ 255,0,0 };
    std::vector<bad::Vector2<float>> points1{ {3,0},{-2,2},{-1,0 }, {-2, -2 }, {3, 0 } };
    std::vector<bad::Vector2<float>> points2{ {-3,0}, {-5,2}, {-5,-2},{-3,0} };

    std::shared_ptr<bad::Model> playerModel = std::make_shared<bad::Model>(( bad::Mesh(points1, WHITE), bad::Mesh(points2, RED) ));

    std::shared_ptr<bad::Model> enemyModel = std::make_shared<bad::Model>( (bad::Mesh(points1, RED), bad::Mesh(points2, RED)) );

    std::vector<bad::Vector2<float>> bullet{ {-1,-1},{-1,1},{1,0 }, {-1,-1}, };
    std::shared_ptr<bad::Model> bulletModel = std::make_shared<bad::Model>(((bad::Mesh(bullet, WHITE)) ));
}