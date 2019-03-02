//
// Created by thijs on 31-12-18.
//

#include "PlanetData.h"

namespace solarSystem {
namespace planetaryBody {

std::vector<std::shared_ptr<PlanetaryBody>> PlanetData::planetaryBodies;
std::mutex PlanetData::mutex;
bool PlanetData::exit = false;

void PlanetData::setPlanetaryBodies(std::vector<bodyPtr> &bodies) {
    mutex.lock();
    planetaryBodies.clear();
    for (auto &body : bodies) {
        planetaryBodies.push_back(body);
    }
    mutex.unlock();
}

std::vector<PlanetData::bodyPtr> PlanetData::getPlanetaryBodies() {
    mutex.lock();
    std::vector<bodyPtr> bodies;

    bodies.reserve(planetaryBodies.size());
    for (auto &body : planetaryBodies) {
        bodies.push_back(body);
    }

    mutex.unlock();
    return bodies;
}

} //planetaryBody
} //solarSystem