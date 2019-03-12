//
// Created by thijs on 30-12-18.
//

#ifndef SOLARSYSTEM_PLANETDATA_H
#define SOLARSYSTEM_PLANETDATA_H

#include <thread>
#include <mutex>
#include <vector>

namespace physics {

class PhysicsObject;

class ObjectData {

    private:
        using physicsPtr = std::shared_ptr<physics::PhysicsObject>;

        static std::mutex bodiesMutex;
        static std::vector<physicsPtr> bodies;
    public:
        static void setBodies(const std::vector<physicsPtr> &bodies);
    public:
        static std::vector<physicsPtr> &getBodies();

    public:


};

} //planetaryBody

#endif //SOLARSYSTEM_PLANETDATA_H
