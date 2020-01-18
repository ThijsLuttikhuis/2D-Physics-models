//
// Created by Thijs on 10/03/2019.
//

#ifndef SOLARSYSTEM_PHYSICSOBJECT_H
#define SOLARSYSTEM_PHYSICSOBJECT_H

#include "Vector2.h"
#include "../Physics.h"
#include "../window/Color.h"
#include "../window/Window.h"
#include <memory>
#include <vector>
#include <string>
#include <cmath>

namespace physics {

class Vector2;

class PhysicsObject : public Physics {
    protected:
        enum PhysicsType {
          GRAVITY,
          COLLISION,
          WALL,
          GRID
        };

        using physicsObjectPtr = std::shared_ptr<PhysicsObject>;
        using Color = window::Color;

        double mass;
        double radius;
        Vector2 pos;
        Vector2 vel;
        Vector2 acc;
        Color* color;
        PhysicsType type;

        Vector2 temp;

        void updatePosition(const double &dt);
        void updateVelocity(const double &dt);
    public:
        constexpr PhysicsObject(const double &mass, const double &radius,
                                const Vector2 &pos, const Vector2 &vel,
                                Color* color, PhysicsType type) : Physics(),
                mass(mass), radius(radius), pos(pos), vel(vel), color(color), type(type) { }

        const Vector2 &getPos() const;
        const Vector2 &getVel() const;
        const Vector2 &getAcc() const;
        double getMass() const;
        double getRadius() const;
        Color* getColor() const;
        PhysicsType getType() const;

        void setPos(Vector2 pos);
        void setVel(Vector2 vel);
        void setAcc(Vector2 acc);
        void setMass(double mass);
        void setRadius(double radius);
        void setColor(const Color* color);

        virtual void update() = 0;
        void onUpdate(std::vector<physicsPtr> &bodies) override;
        void updateTimeStep(const double &dt) override;
};

} // physics



#endif //SOLARSYSTEM_PHYSICSOBJECT_H
