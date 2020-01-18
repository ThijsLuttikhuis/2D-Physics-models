//
// Created by Thijs on 10/03/2019.
//

#include "PhysicsObject.h"

namespace physics {

void physics::PhysicsObject::updatePosition(const double &dt) {
    pos += vel * dt;
}

void physics::PhysicsObject::updateVelocity(const double &dt){
    vel += acc * dt;
}

void PhysicsObject::setPos(Vector2 pos) {
    PhysicsObject::pos = pos;
}

void PhysicsObject::setVel(Vector2 vel) {
    PhysicsObject::vel = vel;
}

void PhysicsObject::setAcc(Vector2 acc) {
    PhysicsObject::acc = acc;
}

void PhysicsObject::setMass(double mass) {
    PhysicsObject::mass = mass;
}

void PhysicsObject::setRadius(double radius) {
    PhysicsObject::radius = radius;
}

void PhysicsObject::setColor(const PhysicsObject::Color* color) {
    *PhysicsObject::color = *color;
}


const Vector2 &PhysicsObject::getPos() const {
    return pos;
}

const Vector2 &PhysicsObject::getVel() const {
    return vel;
}

const Vector2 &PhysicsObject::getAcc() const {
    return acc;
}

double PhysicsObject::getMass() const {
    return mass;
}

double PhysicsObject::getRadius() const {
    return radius;
}

PhysicsObject::Color* PhysicsObject::getColor() const {
    return color;
}

PhysicsObject::PhysicsType PhysicsObject::getType() const {
    return type;
}

void PhysicsObject::updateTimeStep(const double &dt) {
    updatePosition(dt);
    updateVelocity(dt);
}

void PhysicsObject::onUpdate(std::vector<Physics::physicsPtr> &bodies) {
    std::vector<physicsObjectPtr> physicsBodies;
    for (auto &body : bodies) {
        physicsBodies.push_back(bodies);
    }
}

} //physics
