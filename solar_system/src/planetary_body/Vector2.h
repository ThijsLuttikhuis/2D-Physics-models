//
// Created by Thijs on 02/03/2019.
//

#ifndef SOLARSYSTEM_VECTOR2_H
#define SOLARSYSTEM_VECTOR2_H

namespace solarSystem {
namespace planetaryBody {

class Vector2 {
    public:
        constexpr Vector2()
                :x(0.0), y(0.0) { }
        constexpr Vector2(double x, double y)
                :x(x), y(y) { }
        constexpr Vector2(const Vector2 &copy) = default;

        double x;
        double y;
};

}
}
#endif //SOLARSYSTEM_VECTOR2_H
