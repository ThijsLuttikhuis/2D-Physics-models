//
// Created by Thijs on 15/03/2019.
//

#ifndef SOLARSYSTEM_WALLOBJECT_H
#define SOLARSYSTEM_WALLOBJECT_H

#include "PhysicsObject.h"

namespace physics {

class WallObject : public PhysicsObject {
    private:
        using gravityPtr = std::shared_ptr<WallObject>;

        Vector2 project(const Vector2 &point, const Vector2 &lineStart, const Vector2 &lineEnd);

    public:
        constexpr WallObject(const double &mass, const double &thickness,
                             const Vector2 &posA, const Vector2 &posB, Color* color) :
                PhysicsObject(mass, thickness, posA, posB, color, WALL) { }

        void draw() override;
        void onInitialize() override;
        void onUpdate(std::vector<physicsPtr> &bodies) override;
        void afterUpdate(const double &dt) override;
        void getAction(const PhysicsObject* body) override;
};

} //physics

#endif //SOLARSYSTEM_WALLOBJECT_H
