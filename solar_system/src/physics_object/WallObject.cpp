//
// Created by Thijs on 15/03/2019.
//

#include "WallObject.h"

namespace physics {

#define PI 3.14159265358979323846

void WallObject::onInitialize() {
    mass = 1e300;
    temp = vel;
    acc = pos;
    vel = Vector2();
    pos = Vector2();
}

void WallObject::onUpdate(std::vector<physicsPtr> &bodies) {

}

void WallObject::afterUpdate(const double &dt) {

}

void WallObject::getAction(const PhysicsObject* body) {
    Vector2 point = body->getPos();
    Vector2 projection = project(point, acc, temp);
//    Vector2 collisionVec = projection - point;
    pos = projection;
    vel = Vector2();

//
//    if (collisionVec.length() <= radius + body->getRadius()) {
//        if (collisionVec.dot(temp - acc) != 0) {
//        }
//    }
}

Vector2 WallObject::project(const Vector2 &point, const Vector2 &lineStart,
                            const Vector2 &lineEnd) {

    Vector2 ab = lineEnd - lineStart;
    Vector2 ap = point - lineStart;
    double t = ap.dot(ab) / ab.dot(ab);
    if (t < 0) {
        return lineStart;
    }
    else if (t > 1) {
        return lineEnd;
    }
    return lineStart + ab * t;
}

void WallObject::draw() {
    unsigned int n = 30;
    for (unsigned int i = 0; i < n; i++) {
        Vector2 p = acc + (temp-acc)*i*1.0/n;
        Vector2Int drawPos = window::Window::toPixel(p);
        short drawR = window::Window::toPixel(radius);

        window::Window::drawCircle(static_cast<const short &>(drawPos.x),
                                   static_cast<const short &>(drawPos.y),
                                   drawR, getColor());
    }
}

} //physics






