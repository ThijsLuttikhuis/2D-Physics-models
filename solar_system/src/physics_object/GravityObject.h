//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_PLANETARYBODY_H
#define SOLARSYSTEM_PLANETARYBODY_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include "Vector2.h"
#include <utility>
#include "PhysicsObject.h"


namespace window {
class Drawer;
class Color;
}

namespace physics {
class GravityObject;
class Vector2;
class Vector2int;
using bodyPtr = std::shared_ptr<GravityObject>;

using Drawer = window::Drawer;
using Color = window::Color;

class GravityObject : public PhysicsObject {

    public:

        GravityObject(std::string &name, const double &mass, const double &radius,
                const Vector2 &pos, const Vector2 &vel, Color* color);

        void setName(const std::string &name);
        void setMass(const double &mass);
        void setRadius(const double &radius);
        void setPosition(const Vector2 &pos);
        void setVelocity(const Vector2 &vel);
        void setForce(const Vector2 &force);
        void setColor(Color* color);

        std::string getName() const;
        double getMass() const;
        double getG() const;
        double getRadius() const;
        Vector2 getPosition() const;
        Vector2 getVelocity() const;
        Vector2 getForce() const;
        Color* getColor() const;

        void updateAcceleration(std::vector<bodyPtr> &bodies);

        Vector2 getCenterOfMass(const std::vector<bodyPtr> &bodies);
        double getFurthestObject(const std::vector<bodyPtr> &bodies, Vector2 relativeToPos);

    private:
        using bodyPtr = std::shared_ptr<GravityObject>;
        std::string name;
        double mass;
        double radius;
        Vector2 pos;
        Vector2 vel;
        Vector2 force;
        Color* color;
        const double G;
};

} //window


#endif //SOLARSYSTEM_PLANETARYBODY_H
