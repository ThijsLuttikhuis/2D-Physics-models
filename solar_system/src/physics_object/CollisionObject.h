//
// Created by Thijs on 14/03/2019.
//

#ifndef SOLARSYSTEM_COLLISIONOBJECT_H
#define SOLARSYSTEM_COLLISIONOBJECT_H

#include "PhysicsObject.h"

namespace physics {

class CollisionObject : public PhysicsObject {
    private:
        using collisionPtr = std::shared_ptr<CollisionObject>;

        Vector2 tempVel;
    public:
        constexpr CollisionObject(const double &mass, const double &radius,
                                const Vector2 &pos, const Vector2 &vel, Color* color) :
                PhysicsObject(mass, radius, pos, vel, color) { }

        void onUpdate(std::vector<physicsPtr> &bodies) override;
        void afterUpdate(const double &dt) override;

};

} //physics

#endif //SOLARSYSTEM_COLLISIONOBJECT_H
