//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_WINDOW_H
#define SOLARSYSTEM_WINDOW_H

#include <iostream>
#include <vector>
#include <memory>

namespace solarSystem {

namespace planetaryBody {
class PlanetaryBody;
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

        static short getWidth();
        static short getHeight();

        static unsigned char* getPixel(const int &x, const int &y);

        static void setImage(unsigned char* image);
        static void setPixel(const short &x, const short &y, Color* color);

        static void initializeWindow();
        static void initializeWindow(const short &width, const short &height);
        static void resetWindow();
        static void resizeWindow(std::vector<std::shared_ptr<planetaryBody::PlanetaryBody>> bodies, std::string focus, double radius);
        static void resizeWindow(std::vector<std::shared_ptr<planetaryBody::PlanetaryBody>> bodies);
        static void updateWindow();

};

} //window
} //solarSystem

#endif //FINDBALL_WINDOW_H
