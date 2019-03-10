//
// Created by thijs on 31-12-18.
//

#include "PlanetData.h"

namespace solarSystem {
namespace planetaryBody {

std::vector<std::shared_ptr<PlanetaryBody>> PlanetData::planetaryBodies;
bool PlanetData::exit = false;
double PlanetData::dt;
bool PlanetData::bodiesChanged = false;

std::mutex PlanetData::bodiesMutex;
std::mutex PlanetData::dtMutex;

bool PlanetData::setPlanetaryBodies(std::vector<bodyPtr> &bodies, bool change) {

    if (change) {
        bodiesChanged = true;
    }
    else if (bodiesChanged) {
        bodiesChanged = false;
        return false;
    }
    bodiesMutex.lock();
    planetaryBodies.clear();
    for (auto &body : bodies) {
        planetaryBodies.push_back(body);
    }

    bodiesMutex.unlock();
    return true;
}

std::vector<PlanetData::bodyPtr> PlanetData::getPlanetaryBodies() {
    bodiesMutex.lock();
    std::vector<bodyPtr> bodies;

    bodies.reserve(planetaryBodies.size());
    for (auto &body : planetaryBodies) {
        bodies.push_back(body);
    }

    bodiesMutex.unlock();
    return bodies;
}

double PlanetData::getDt() {
    dtMutex.lock();
    double dt = PlanetData::dt;
    dtMutex.unlock();
    return dt;
}

void PlanetData::setDt(double &dt) {
    dtMutex.lock();
    PlanetData::dt = dt;
    dtMutex.unlock();
}

} //planetaryBody
} //solarSystem