//
// Created by Thijs on 02/03/2019.
//

#include "GravityObject.h"
#include "Vector2.h"

namespace physics {

void GravityObject::onUpdate(std::vector<physicsPtr> &bodies) {
    acc = Vector2();

    for (auto &body : bodies) {

        Vector2 dPos = pos - body->getPos();

        if (dPos.length() < 1e2) {
            continue;
        }

        double dist2 = dPos.x * dPos.x + dPos.y * dPos.y;
        double dist = sqrt(dist2);

        double gmmDivDist = G * mass * body->getMass() / (dist2);

        Vector2 force = {gmmDivDist * dPos.x / dist, gmmDivDist * dPos.y / dist};
        acc += force * (-1 / mass);
    }

}
void GravityObject::afterUpdate(const double &dt) {

}

} //physics

