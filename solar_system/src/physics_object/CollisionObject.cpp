//
// Created by Thijs on 14/03/2019.
//

#include "CollisionObject.h"
#include "../window/Window.h"

void physics::CollisionObject::onUpdate(std::vector<physicsPtr> &bodies) {
    acc = Vector2();
    temp = vel;

    for (auto &body : bodies) {

        if (body->getType() == PhysicsType::WALL) {
            body->getAction(this);
        }

        double maxRadius = radius + body->getRadius();
        Vector2 dPos = pos - body->getPos();

        if (dPos.length() > radius * 1e-2 && dPos.length() <= maxRadius) {
            double massF = 2 * body->getMass() / (mass + body->getMass());
            Vector2 dV = vel - body->getVel();
            Vector2 newV = dPos * ((massF * dV.dot(dPos)) / dPos.length2());
            temp -= newV;
        }
    }
}

void physics::CollisionObject::afterUpdate(const double &dt) {
    vel = temp;
}

void physics::CollisionObject::onInitialize() {

}

void physics::CollisionObject::getAction(const physics::PhysicsObject* body) {

}

void physics::CollisionObject::draw() {
    Vector2Int drawPos = window::Window::toPixel(pos);
    short drawR = window::Window::toPixel(radius);

    window::Window::drawCircle(static_cast<const short &>(drawPos.x),
                               static_cast<const short &>(drawPos.y),
                               drawR, getColor());
}
