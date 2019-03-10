//
// Created by Thijs on 02/03/2019.
//

#include "PlanetaryBody.h"
#include "Vector2.h"

namespace solarSystem {
namespace planetaryBody {

PlanetaryBody::PlanetaryBody(std::string &name, const double &mass, const double &radius, const Vector2 &pos,
        const Vector2 &vel, Color* color)
        :name(name), mass(fabs(mass)), radius(fabs(radius)),
         pos(pos), vel(vel), force({0, 0}), color(color), G(6.67e-11) { }

void PlanetaryBody::setName(const std::string &name) {
    PlanetaryBody::name = name;
}

void PlanetaryBody::setMass(const double &mass) {
    PlanetaryBody::mass = fabs(mass);
}

void PlanetaryBody::setRadius(const double &radius) {
    PlanetaryBody::radius = fabs(radius);
}

void PlanetaryBody::setPosition(const Vector2 &pos) {
    PlanetaryBody::pos = pos;
}

void PlanetaryBody::setVelocity(const Vector2 &vel) {
    PlanetaryBody::vel = vel;
}

void PlanetaryBody::setForce(const Vector2 &force) {
    PlanetaryBody::force = force;
}

void PlanetaryBody::setColor(Color* color) {
    PlanetaryBody::color = color;
}

std::string PlanetaryBody::getName() const {
    return name;
}

double PlanetaryBody::getMass() const {
    return mass;
}

double PlanetaryBody::getG() const {
    return G;
}

double PlanetaryBody::getRadius() const {
    return radius;
}

Vector2 PlanetaryBody::getPosition() const {
    return pos;
}

Vector2 PlanetaryBody::getVelocity() const {
    return vel;
}

Vector2 PlanetaryBody::getForce() const {
    return force;
}

Color* PlanetaryBody::getColor() const {
    return color;
}

void PlanetaryBody::updateVelocity(const double &dt) {
    vel.x = vel.x + dt*force.x/mass;
    vel.y = vel.y + dt*force.y/mass;
}

void PlanetaryBody::updatePosition(const double &dt) {
    pos.x = pos.x + dt*vel.x;
    pos.y = pos.y + dt*vel.y;
}

void PlanetaryBody::updateForces(std::vector<bodyPtr> &bodies) {
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

Vector2 PlanetaryBody::getCenterOfMass(const std::vector<bodyPtr> &bodies) {
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

double PlanetaryBody::getFurthestObject(const std::vector<bodyPtr> &bodies, Vector2 relativeToPos) {
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
} //solarSystem
