//
// Created by Thijs on 14/03/2019.
//

#include "CollisionObject.h"

void physics::CollisionObject::onUpdate(std::vector<physics::PhysicsObject::physicsPtr> &bodies) {
    acc = Vector2();
    tempVel = vel;
    for (auto &body : bodies) {

        double maxRadius = radius + body->getRadius();
        Vector2 dPos = pos - body->getPos();

        if (dPos.length() > radius * 1e-2 && dPos.length() <= maxRadius) {
            double massF = 2*body->getMass() / (mass + body->getMass());
            Vector2 dV = vel - body->getVel();
            Vector2 newV = dPos * ( (massF * dV.dot(dPos)) / dPos.length2() );
            tempVel = vel - newV;
        }
    }
}

void physics::CollisionObject::afterUpdate(const double &dt) {
    vel = tempVel;
}
