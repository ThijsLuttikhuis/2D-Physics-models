//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_DRAWER_H
#define SOLARSYSTEM_DRAWER_H


#include <iostream>
#include "Window.h"
#include <memory>
#include <cmath>



namespace physics {
class GravityObject;
class Vector2;
class Vector2int;
}


namespace window {
class Color;

class Drawer {
        using Vector2 = physics::Vector2;
        using Vector2int = physics::Vector2int;
    public:


        static void drawCircle(const short &xCenter, const short &yCenter, double radius,
                Color* color);

        static void drawCircle(const double &xCenter, const double &yCenter, double innerRadius, double outerRadius,
                Color* color);

        static void drawPlanetaryBody(const std::shared_ptr<physics::GravityObject> &body);
        static void setPixelToReal(const double &factor);
        static void setRealToPixel(const double &factor);
        static Vector2int transformRealToPixel(const Vector2 &pos);

        static void setRealCenter(const double &x, const double &y);
        static void setRealCenter(const Vector2 &pos);
        static void setPixelCenter(const int &x, const int &y);
        static void setPixelCenter(const Vector2int &pos);

    private:
        static double pixelToReal;
    public:
        static double getPixelToReal();
        static double getRealToPixel();
        static double getXPixelCenter();
        static double getYPixelCenter();
    private:
        static double realToPixel;
        static double xPixelCenter;
        static double yPixelCenter;

};

} //window

#endif //SOLARSYSTEM_DRAWER_H

