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

void Drawer::drawCircle(const int &xCenter, const int &yCenter, double radius, const cv::Vec3b &color) {

    int pixels = Window::getXPixels() > Window::getYPixels() ? Window::getYPixels() : Window::getXPixels();
    if (xCenter < 0 || xCenter > Window::getXPixels() || yCenter < 0 || yCenter > Window::getYPixels()) return;
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
                Window::setPixel(x, y, color);
            }
        }
    }
}

void Drawer::drawCircle(const double &xCenter, const double &yCenter, double innerRadius, double outerRadius,
        const cv::Vec3b &color) {

    double outerRadiusSquared = outerRadius*outerRadius;
    double innerRadiusSquared = innerRadius*innerRadius;
    for (int x = static_cast<int>(round(xCenter - outerRadius)); x < round(xCenter + outerRadius); x ++) {
        for (int y = static_cast<int>(round(yCenter - outerRadius)); y < round(yCenter + outerRadius); y ++) {
            double dx = x - xCenter;
            double dy = y - yCenter;
            if (dx*dx + dy*dy < outerRadiusSquared && dx*dx + dy*dy > innerRadiusSquared) {
                Window::setPixel(x, y, color);
            }
        }
    }
}

void Drawer::drawPlanetaryBody(const std::shared_ptr<planetaryBody::PlanetaryBody> &body) {
    cv::Vec3b color = body->getColor();
    double r = body->getRadius()*realToPixel;
    Vector2int pos = transformRealToPixel(body->getPosition());
    drawCircle(pos.x, pos.y, r, color);
}

planetaryBody::PlanetaryBody::Vector2int Drawer::transformRealToPixel(const Vector2 &pos) {
    Vector2int pixelPos;
    pixelPos.x = static_cast<int>(round(pos.x*realToPixel - xPixelCenter));
    pixelPos.y = static_cast<int>(round(pos.y*realToPixel - yPixelCenter));
    return pixelPos;
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
    Vector2 center = {x, y};
    setRealCenter(center);
}

void Drawer::setPixelCenter(const int &x, const int &y) {
    xPixelCenter = x;
    yPixelCenter = y;
}

void Drawer::setRealCenter(const Vector2 &pos) {
    Vector2int pixel = {static_cast<int>(pos.x*realToPixel) - Window::getXPixels()/2,
                        static_cast<int>(pos.y*realToPixel) - Window::getYPixels()/2};
    setPixelCenter(pixel);
}

void Drawer::setPixelCenter(const Drawer::Vector2int &pos) {
    setPixelCenter(pos.x, pos.y);
}

} //window
} //solarSystem