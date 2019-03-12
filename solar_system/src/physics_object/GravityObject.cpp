//
// Created by Thijs on 02/03/2019.
//

#include "GravityObject.h"
#include "Vector2.h"

namespace physics {

void GravityObject::onUpdate(std::vector<physicsPtr> &bodies) {
    this->acc = {0,0};
    for (auto &body : bodies) {

        Vector2 r = {pos.x - body->getPos().x,
                     pos.y - body->getPos().y};

        if (r.length() < 1e2) {
            continue;
        }
        else if (r.length() < 3e18) {
            this->pos = {1e100, 1e100};
            continue;
        }
        double dist2 = r.x * r.x + r.y * r.y;
        double dist = sqrt(dist2);

        double gmmDivDist = G * mass * body->getMass() / (dist2);

        Vector2 force = {gmmDivDist * r.x / dist, gmmDivDist * r.y / dist};
        this->acc += force * (-1 / mass);
    }

}

} //physics

