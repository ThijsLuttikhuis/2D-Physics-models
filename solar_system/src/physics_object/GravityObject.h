//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_PLANETARYBODY_H
#define SOLARSYSTEM_PLANETARYBODY_H


#include "PhysicsObject.h"

namespace physics {

class GravityObject : public PhysicsObject {
    private:
        using gravityPtr = std::shared_ptr<GravityObject>;
    public:
        const double G = 6.67e-11;

        constexpr GravityObject(const double &mass, const double &radius,
                                const Vector2 &pos, const Vector2 &vel, Color* color) :
                PhysicsObject(mass, radius, pos, vel, color, GRAVITY) { }

        void draw() override;
        void onInitialize() override {};
        void onUpdate(std::vector<physicsPtr> &bodies) override;
        void afterUpdate(const double &dt) override;
        void getAction(const Physics* body) override;
};

} //physics

#endif //SOLARSYSTEM_PLANETARYBODY_H
