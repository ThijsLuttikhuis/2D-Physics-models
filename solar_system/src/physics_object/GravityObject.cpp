//
// Created by Thijs on 02/03/2019.
//

#include "GravityObject.h"
#include "Vector2.h"

namespace physics {

GravityObject::GravityObject(std::string &name, const double &mass, const double &radius, const Vector2 &pos,
        const Vector2 &vel, Color* color)
        :name(name), mass(fabs(mass)), radius(fabs(radius)),
         pos(pos), vel(vel), force({0, 0}), color(color), G(6.67e-11) { }

void GravityObject::setName(const std::string &name) {
    GravityObject::name = name;
}

void GravityObject::setMass(const double &mass) {
    GravityObject::mass = fabs(mass);
}

void GravityObject::setRadius(const double &radius) {
    GravityObject::radius = fabs(radius);
}

void GravityObject::setPosition(const Vector2 &pos) {
    GravityObject::pos = pos;
}

void GravityObject::setVelocity(const Vector2 &vel) {
    GravityObject::vel = vel;
}

void GravityObject::setForce(const Vector2 &force) {
    GravityObject::force = force;
}

void GravityObject::setColor(Color* color) {
    GravityObject::color = color;
}

std::string GravityObject::getName() const {
    return name;
}

double GravityObject::getMass() const {
    return mass;
}

double GravityObject::getG() const {
    return G;
}

double GravityObject::getRadius() const {
    return radius;
}

Vector2 GravityObject::getPosition() const {
    return pos;
}

Vector2 GravityObject::getVelocity() const {
    return vel;
}

Vector2 GravityObject::getForce() const {
    return force;
}

Color* GravityObject::getColor() const {
    return color;
}

void GravityObject::updateAcceleration(std::vector<bodyPtr> &bodies) {
    for (auto &body : bodies) {
        Vector2 f = {0, 0};
        body->setForce(f);
    }
    for (auto first = bodies.begin(); first < bodies.end(); first ++) {
        for (auto second = first + 1; second < bodies.end(); second ++) {
            Vector2 r = {second->get()->getPosition().x - first->get()->getPosition().x,
                         second->get()->getPosition().y - first->get()->getPosition().y};
            double dist = sqrt(r.x*r.x + r.y*r.y);
            double gmmDivDist =
                    second->get()->getG()*second->get()->getMass()*first->get()->getMass()/(dist*dist);

            Vector2 f = {gmmDivDist*r.x/dist, gmmDivDist*r.y/dist};

            Vector2 secondForce = {second->get()->getForce().x - f.x, second->get()->getForce().y - f.y};
            second->get()->setForce(secondForce);

            Vector2 firstForce = {first->get()->getForce().x + f.x, first->get()->getForce().y + f.y};
            first->get()->setForce(firstForce);
        };
    }

}

Vector2 GravityObject::getCenterOfMass(const std::vector<bodyPtr> &bodies) {
    Vector2 centerOfMass = {0, 0};
    double totalMass = 0;

    for (auto &body : bodies) {
        double bodyMass = body->getMass();
        Vector2 bodyPos = body->getPosition();
        centerOfMass.x += bodyPos.x*bodyMass;
        centerOfMass.y += bodyPos.y*bodyMass;
        totalMass += bodyMass;
    }
    return {centerOfMass.x/totalMass, centerOfMass.y/totalMass};
}

double GravityObject::getFurthestObject(const std::vector<bodyPtr> &bodies, Vector2 relativeToPos) {
    double distanceSquared = 0;

    for (auto &body : bodies) {
        double dx = body->pos.x - relativeToPos.x;
        double dy = body->pos.y - relativeToPos.y;
        if (dx*dx + dy*dy > distanceSquared) {
            distanceSquared = dx*dx + dy*dy;

        }
    }
    return sqrt(distanceSquared);
}

} //window

