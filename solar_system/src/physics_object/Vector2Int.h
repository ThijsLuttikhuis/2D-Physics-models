//
// Created by Thijs on 02/03/2019.
//

#ifndef SOLARSYSTEM_VECTOR2INT_H
#define SOLARSYSTEM_VECTOR2INT_H

namespace physics {

class Vector2Int {
    public:
        constexpr Vector2Int()
                :x(0), y(0) { }
        constexpr Vector2Int(int x, int y)
                :x(x), y(y) { }
        constexpr Vector2Int(const Vector2Int &copy) = default;

        int x;
        int y;
};

}


#endif //SOLARSYSTEM_VECTOR2INT_H
