//
// Created by thijs on 27-12-18.
//

#include "Drawer.h"

namespace solarSystem {
namespace window {

double Drawer::pixelToReal;
double Drawer::realToPixel;
double Drawer::xPixelCenter;
double Drawer::yPixelCenter;

void Drawer::drawCircle(const double &xCenter, const double &yCenter, double &radius, const cv::Vec3b &color) {

    if (radius < 2.0) radius = 2.0;
    double radiusSquared = radius*radius;
    for (int x = static_cast<int>(round(xCenter - radius)); x < round(xCenter + radius); x ++) {
        for (int y = static_cast<int>(round(yCenter - radius)); y < round(yCenter + radius); y ++) {
            double dx = x-xCenter;
            double dy = y-yCenter;
            if ( dx*dx + dy*dy < radiusSquared) {
                Window::setPixel(x,y,color);
            }
        }
    }
}

void Drawer::drawPlanetaryBody(const std::shared_ptr<planetaryBody::PlanetaryBody> &body) {
    cv::Vec3b color = body->getColor();
    double r = body->getRadius() * realToPixel;
    double x = body->getPosition().x * realToPixel + xPixelCenter;
    double y = body->getPosition().y * realToPixel + yPixelCenter;

    drawCircle(x, y, r, color);
}

void Drawer::setPixelToReal(const double &factor) {
    pixelToReal = factor;
    realToPixel = 1.0/factor;
}

void Drawer::setRealToPixel(const double &factor) {
    realToPixel = factor;
    pixelToReal = 1.0/factor;
}

void Drawer::setRealCenter(const double &x, const double &y) {
    xPixelCenter = x*realToPixel;
    yPixelCenter = y*realToPixel;
}

void Drawer::setPixelCenter(const int &x, const int &y) {
    xPixelCenter = x;
    yPixelCenter = y;
}

} //window
} //solarSystem