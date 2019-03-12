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

using Drawer = window::Drawer;
using Color = window::Color;

class GravityObject : public PhysicsObject {
    private:
        using gravityPtr = std::shared_ptr<GravityObject>;
    public:
        const double G = 6.67e-11;

        constexpr GravityObject(const double &mass, const double &radius,
                                const Vector2 &pos, const Vector2 &vel, Color* color) :
                PhysicsObject(mass, radius, pos, vel, color) { }

        void onUpdate(std::vector<physicsPtr> &bodies) override;

};

} //window


#endif //SOLARSYSTEM_PLANETARYBODY_H
