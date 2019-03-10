//
// Created by Thijs on 10/03/2019.
//

#ifndef SOLARSYSTEM_PHYSICSOBJECT_H
#define SOLARSYSTEM_PHYSICSOBJECT_H

#include "Vector2.h"
#include "../window/Color.h"


namespace physics {
class Vector2;

class PhysicsObject {
    protected:
        using Color = window::Color;
        Vector2 pos;
        Vector2 vel;
        Vector2 acc;

        double mass;
        double radius;
        Color color;

    public:
        PhysicsObject() = default;

        void updatePosition(const double &dt);
        void updateVelocity(const double &dt);
        virtual void updateAcceleration() = 0;



};

} // physics



#endif //SOLARSYSTEM_PHYSICSOBJECT_H
