//
// Created by Thijs on 01/04/2019.
//

#ifndef SOLARSYSTEM_PHYSICS_H
#define SOLARSYSTEM_PHYSICS_H

#define PI 3.14159265358979323846

#include "physics_object/Vector2.h"
#include "window/Color.h"
#include "window/Window.h"
#include <memory>
#include <vector>
#include <string>
#include <cmath>

namespace physics {

class Vector2;

class Physics {
    protected:
        using physicsPtr = std::shared_ptr<Physics>;
        using Color = window::Color;

    public:
        constexpr Physics() = default;

        virtual void draw() = 0;
        virtual void updateTimeStep(const double &dt) = 0;
        virtual void onInitialize() = 0;
        virtual void onUpdate(std::vector<physicsPtr> &bodies) = 0;
        virtual void afterUpdate(const double &dt) = 0;
        virtual void getAction(const Physics* body) = 0;
};

} // physics

#endif //SOLARSYSTEM_PHYSICS_H
