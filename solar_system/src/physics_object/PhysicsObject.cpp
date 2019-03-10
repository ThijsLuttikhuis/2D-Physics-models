//
// Created by Thijs on 10/03/2019.
//

#include "PhysicsObject.h"

namespace physics {

void physics::PhysicsObject::updatePosition(const double &dt) {
    this->pos = this->pos + this->vel * dt;
}

void physics::PhysicsObject::updateVelocity(const double &dt){
    this->vel = this->vel + this->acc * dt;
}

} //physics
