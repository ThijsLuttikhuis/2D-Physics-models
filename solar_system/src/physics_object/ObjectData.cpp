//
// Created by thijs on 31-12-18.
//

#include "ObjectData.h"

namespace physics {

std::mutex ObjectData::bodiesMutex;
std::vector<ObjectData::physicsPtr> ObjectData::bodies;

std::vector<ObjectData::physicsPtr> &ObjectData::getBodies() {
    std::lock_guard<std::mutex> lock(bodiesMutex);
    return bodies;
}

void ObjectData::setBodies(const std::vector<ObjectData::physicsPtr> &bodies) {
    std::lock_guard<std::mutex> lock(bodiesMutex);
    ObjectData::bodies = bodies;
}
} //physics
