//
// Created by thijs on 30-12-18.
//

#ifndef SOLARSYSTEM_PLANETDATA_H
#define SOLARSYSTEM_PLANETDATA_H

#include <thread>
#include <mutex>
#include <vector>

namespace solarSystem {
namespace planetaryBody {

class PlanetaryBody;

class PlanetData {

    private:
        using bodyPtr = std::shared_ptr<PlanetaryBody>;
        static std::vector<bodyPtr> planetaryBodies;
        static std::mutex mutex;
        static bool exit;

    public:
        static std::vector<bodyPtr> getPlanetaryBodies();
        static void setPlanetaryBodies(std::vector<bodyPtr> &bodies);

        static void setExit() {
            exit = true;
        }
        static void setExit(const bool e) {
            exit = e;
        }
        static bool getExit() {
            return exit;
        }

};

} //planetaryBody
} //solarSystem

#endif //SOLARSYSTEM_PLANETDATA_H