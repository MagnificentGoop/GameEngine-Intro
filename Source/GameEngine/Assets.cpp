#include "Assets.h"

namespace Assets {
    bad::Color8 WHITE{ 255,255,255 };
    bad::Color8 RED{ 255,0,0 };
    std::vector<bad::Vector2<float>> points1{ {3,0},{-2,2},{-1,0 }, {-2, -2 }, {3, 0 } };
    std::vector<bad::Vector2<float>> points2{ {-3,0}, {-5,2}, {-5,-2},{-3,0} };
    bad::Model playerModel{ {bad::Mesh(points1, WHITE), bad::Mesh(points2, RED)} };
    bad::Model enemyModel{ {bad::Mesh(points1, RED), bad::Mesh(points2, RED)} };

    std::vector<bad::Vector2<float>> bullet{ {-1,-1},{-1,1},{1,0 }, {-1,-1}, };
    bad::Model bulletModel{ {bad::Mesh(bullet, WHITE)} };
}