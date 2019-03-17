//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_WINDOW_H
#define SOLARSYSTEM_WINDOW_H

#include <iostream>
#include <vector>
#include <memory>
#include "../physics_object/Vector2.h"
#include "../physics_object/Vector2Int.h"
#include "Color.h"

namespace physics {
class GravityObject;
class Vector2;
class Vector2Int;
}

namespace window {

class Color;

class Window {

    private:
        using Vector2 = physics::Vector2;
        using Vector2Int = physics::Vector2Int;

        static short width;
        static short height;
        static unsigned char* image;

    public:

        static unsigned char* getImage();

        static void drawCircle(const short &xCenter, const short &yCenter, double radius,
                               Color* color);

        static void drawCircle(const short &xCenter, const short &yCenter, double innerRadius, double outerRadius,
                               Color* color);

        static short getWidth();
        static short getHeight();

        static unsigned char* getPixel(const int &x, const int &y);

        static short toPixel(double &real);
        static physics::Vector2Int toPixel(physics::Vector2 &real);

        static void setImage(unsigned char* image);
        static void setPixel(const short &x, const short &y, Color* color);

        static void initializeWindow();
        static void initializeWindow(const short &width, const short &height);
        static void resetWindow();

        static void updateWindow();

};

} //window

#endif //FINDBALL_WINDOW_H
