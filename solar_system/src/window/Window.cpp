//
// Created by thijs on 27-12-18.
//

#include "Window.h"
#include "Drawer.h"
#include "Color.h"
#include "../physics_object/Vector2.h"
#include "../physics_object/Vector2Int.h"
#include "../physics_object/PhysicsObject.h"

namespace window {

short Window::width;
short Window::height;
unsigned char* Window::image;

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


void Window::drawCircle(const short &xCenter, const short &yCenter, double radius, Color *color) {
    auto width = getWidth();
    auto height = getHeight();
    int pixels = width > height ? height : width;
    if (xCenter < 0 || xCenter > width || yCenter < 0 || yCenter > height) return;
    if (radius < 4.0 || radius < pixels*0.005) {
        double inner = pixels*0.010;
        double outer = (pixels*0.002 > 1.0 ? pixels*0.012 : pixels*0.010 + 1.0) ;
        drawCircle(xCenter, yCenter, inner, outer, color);
    }
    double radiusSquared = radius*radius;
    for (int x = static_cast<int>(round(xCenter - radius)); x < round(xCenter + radius); x ++) {
        for (int y = static_cast<int>(round(yCenter - radius)); y < round(yCenter + radius); y ++) {
            double dx = x - xCenter;
            double dy = y - yCenter;
            if (dx*dx + dy*dy < radiusSquared) {
                setPixel(x, y, color);
            }
        }
    }
}

void Window::drawCircle(const short &xCenter, const short &yCenter, double innerRadius, double outerRadius,
                        Color* color) {

    double outerRadiusSquared = outerRadius*outerRadius;
    double innerRadiusSquared = innerRadius*innerRadius;
    for (auto x = static_cast<short>(round(xCenter - outerRadius)); x < round(xCenter + outerRadius); x ++) {
        for (auto y = static_cast<short>(round(yCenter - outerRadius)); y < round(yCenter + outerRadius); y ++) {
            double dx = x - xCenter;
            double dy = y - yCenter;
            if (dx*dx + dy*dy < outerRadiusSquared && dx*dx + dy*dy > innerRadiusSquared) {
                setPixel(x, y, color);
            }
        }
    }
}

} //window
