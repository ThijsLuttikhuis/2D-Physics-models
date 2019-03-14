//
// Created by Thijs on 10/03/2019.
//

#ifndef SOLARSYSTEM_PHYSICSOBJECT_H
#define SOLARSYSTEM_PHYSICSOBJECT_H

#include "Vector2.h"
#include "../window/Color.h"
#include <memory>
#include <vector>
#include <string>
#include <cmath>

namespace physics {
class Vector2;

class PhysicsObject {
    protected:
        using physicsPtr = std::shared_ptr<PhysicsObject>;
        using Color = window::Color;

        double mass;
        double radius;
        Vector2 pos;
        Vector2 vel;
        Vector2 acc;
        Color* color;

    public:
        constexpr PhysicsObject(const double &mass, const double &radius,
                                const Vector2 &pos, const Vector2 &vel, Color* color) :
                mass(mass), radius(radius), pos(pos), vel(vel), color(color) { }

        const Vector2 &getPos() const;
        const Vector2 &getVel() const;
        const Vector2 &getAcc() const;
        double getMass() const;
        double getRadius() const;
        Color* getColor() const;

        void setPos(Vector2 pos);
        void setVel(Vector2 vel);
        void setAcc(Vector2 acc);
        void setMass(double mass);
        void setRadius(double radius);
        void setColor(const Color* color);

        void updatePosition(const double &dt);
        void updateVelocity(const double &dt);
        virtual void onUpdate(std::vector<physicsPtr> &bodies) = 0;
        virtual void afterUpdate(const double &dt) = 0;

};

} // physics



#endif //SOLARSYSTEM_PHYSICSOBJECT_H
