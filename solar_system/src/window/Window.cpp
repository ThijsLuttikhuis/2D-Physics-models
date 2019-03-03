//
// Created by thijs on 27-12-18.
//

#include "Window.h"
#include "Drawer.h"
#include "Color.h"
#include "../planetary_body/Vector2.h"
#include "../planetary_body/Vector2Int.h"
#include "../planetary_body/PlanetaryBody.h"

namespace solarSystem {
namespace window {

short Window::width;
short Window::height;
unsigned char* Window::image;
int Window::focusBody = -1;


unsigned char* Window::getImage() {
    return image;
}

short Window::getWidth() {
    return width;
}

short Window::getHeight() {
    return height;
}

unsigned char* Window::getPixel(const int &x, const int &y) {
    if (x > 0 && y > 0 && x < width-1 && y < height-1) {
        int index = x + y * width;
        return (image + index * 4);
    }
    return image;
}

void Window::setImage(unsigned char* image) {
    Window::image = image;
}

void Window::setPixel(const short &x, const short &y, Color* color) {
    if (x > 0 && y > 0 && x < width - 1 && y < height - 1) {
        int index = x + y*width;
        *(image + index*4 + 0) = color->red;
        *(image + index*4 + 1) = color->green;
        *(image + index*4 + 2) = color->blue;
        *(image + index*4 + 3) = color->alpha;
    }
}

void Window::initializeWindow() {
    width = 1366;
    height = 768;
    image = new unsigned char [width*height*4];
}

void Window::initializeWindow(const short &width, const short &height) {
    Window::width = width;
    Window::height = height;
    image = new unsigned char [width*height*4];
}

void Window::updateWindow() {
    //TODO: update
}


void Window::resetWindow() {
    delete[] image;
    image = nullptr;
    image = new unsigned char [width*height*4];
}

void Window::resizeWindow(std::vector<std::shared_ptr<planetaryBody::PlanetaryBody>> bodies) {
    planetaryBody::Vector2 centerOfMass = bodies.front()->getCenterOfMass(bodies);
    double furthestDistance = bodies.front()->getFurthestObject(bodies, centerOfMass);

    focusBody = -1;

    double factor;
    if (width < height)
        factor = 0.45 * width/furthestDistance;
    else
        factor = 0.45 * height/furthestDistance;

    Drawer::setRealToPixel(factor);
    Drawer::setRealCenter(centerOfMass);
}

void Window::resizeWindow(std::vector<std::shared_ptr<planetaryBody::PlanetaryBody>> bodies, int focus,
        double radius) {

    auto bodiesSize = static_cast<int>(bodies.size());

    planetaryBody::Vector2 focusPos;
    if (focus < 0) {
        if (focus == -1 || focusBody == -1) {
            if (focus != -1) {
                focusBody = 0;
                focusPos = bodies[focusBody]->getPosition();
            }
            else {
                focusPos = {0, 0};
                focusBody = - 1;
            }
        }
        else {
            if (focus == - 2)
                focusBody = (focusBody < bodiesSize - 1 ? focusBody + 1 : 0);
            else if (focus == - 3)
                focusBody = (focusBody > 0 ? focusBody - 1 : bodiesSize - 1);

            focusPos = bodies[focusBody]->getPosition();
        }
    }
    else {
        focus = focus < bodiesSize - 1 ? focus : bodiesSize - 1;
        focusPos = bodies[focus]->getPosition();
        focusBody = focus;
    }

    double factor;
    if (radius < 0.0) {
        factor = Drawer::getRealToPixel()*radius*-1;
    }
    else {
        if (width < height)
            factor = 0.45 * width/radius;
        else
            factor = 0.45 * height/radius;
    }


    Drawer::setRealToPixel(factor);
    Drawer::setRealCenter(focusPos);

}

} //window
} //solarSystem