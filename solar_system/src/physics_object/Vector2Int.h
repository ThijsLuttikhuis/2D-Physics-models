//
// Created by Thijs on 02/03/2019.
//

#ifndef SOLARSYSTEM_VECTOR2INT_H
#define SOLARSYSTEM_VECTOR2INT_H

namespace physics {

class Vector2int {
    public:
        constexpr Vector2int()
                :x(0), y(0) { }
        constexpr Vector2int(int x, int y)
                :x(x), y(y) { }
        constexpr Vector2int(const Vector2int &copy) = default;

        int x;
        int y;
};

}


#endif //SOLARSYSTEM_VECTOR2INT_H
