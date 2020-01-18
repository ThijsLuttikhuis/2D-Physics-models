//
// Created by Thijs on 14/03/2019.
//

#include "CollisionObject.h"
#include "../window/Window.h"

namespace physics {

unsigned int CollisionObject::collisions = 0;

void CollisionObject::onUpdate(std::vector<physicsPtr> &bodies) {
    acc = Vector2();
    temp = vel;

    for (auto &body : bodies) {

        if (body->getType() == WALL) {
            body->getAction(this);
        }

        double maxRadius = radius + body->getRadius();
        Vector2 dPos = pos - body->getPos();

        if (dPos.length() > radius * 1e-2 && dPos.length() <= maxRadius) {
            if (body->getType() == COLLISION) {
                collisions ++;
            }

            double massF = 2 * body->getMass() / (mass + body->getMass());
            Vector2 dV = vel - body->getVel();
            Vector2 newV = dPos * ((massF * dV.dot(dPos)) / dPos.length2());
            temp -= newV;
        }
    }
}

void CollisionObject::afterUpdate(const double &dt) {
    vel = temp;
}

void CollisionObject::onInitialize() {

}

void CollisionObject::getAction(const Physics* body) {

}

void CollisionObject::draw() {
    Vector2Int drawPos = window::Window::toPixel(pos);
    short drawR = window::Window::toPixel(radius);

    window::Window::drawCircle(static_cast<const short &>(drawPos.x),
                               static_cast<const short &>(drawPos.y),
                               drawR, getColor());
}
unsigned int CollisionObject::getCollisions() {
    return collisions;
}

} //physics
