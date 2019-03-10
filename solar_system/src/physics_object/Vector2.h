//
// Created by Thijs on 02/03/2019.
//

#ifndef SOLARSYSTEM_VECTOR2_H
#define SOLARSYSTEM_VECTOR2_H


namespace physics {

class Vector2 {
    public:
        using Hi = Vector2;
        constexpr Vector2()
                :x(0.0), y(0.0) { }
        constexpr Vector2(double x, double y)
                :x(x), y(y) { }
        constexpr Vector2(const Vector2 &copy) = default;

        double x;
        double y;

        Hi operator+(const Vector2 &other) {
            return Vector2(this->x + other.x, this->y + other.y);
        }
        Vector2 operator+(const double &scalar) {
            return Vector2(this->x + scalar, this->y + scalar);
        }
        Vector2 operator-(const Vector2 &other) {
            return Vector2(this->x - other.x, this->y - other.y);
        }
        Vector2 operator-(const double &scalar) {
            return Vector2(this->x - scalar, this->y - scalar);
        }
        Vector2 operator*(const Vector2 &other) {
            return Vector2(this->x * other.x, this->y * other.y);
        }
        Vector2 operator*(const double &scalar) {
            return Vector2(this->x * scalar, this->y * scalar);
        }
        Vector2 operator/(const Vector2 &other) {
            return Vector2(this->x / other.x, this->y / other.y);
        }
        Vector2 operator/(const double &scalar) {
            return Vector2(this->x / scalar, this->y / scalar);
        }
};

}

#endif //SOLARSYSTEM_VECTOR2_H
