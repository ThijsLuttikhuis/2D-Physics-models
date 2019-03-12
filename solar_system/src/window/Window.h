//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_WINDOW_H
#define SOLARSYSTEM_WINDOW_H

#include <iostream>
#include <vector>
#include <memory>


namespace physics {
class GravityObject;
}

namespace window {

class Color;

class Window {

    private:
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

        static void setImage(unsigned char* image);
        static void setPixel(const short &x, const short &y, Color* color);

        static void initializeWindow();
        static void initializeWindow(const short &width, const short &height);
        static void resetWindow();

        static void updateWindow();

};

} //window

#endif //FINDBALL_WINDOW_H
