//
// Created by thijs on 27-12-18.
//
#include "window/Drawer.h"
#include "window/Window.h"
#include "planetary_body/PlanetaryBody.h"
#include "planetary_body/PlanetData.h"
#include "time_keeping/Timer.h"
#include <opencv2/imgcodecs.hpp>
#include <memory>
#include <thread>

namespace window = solarSystem::window;
namespace planetaryBody = solarSystem::planetaryBody;
namespace timeKeeping = solarSystem::timeKeeping;

using w = window::Window;
using d = window::Drawer;
using body = planetaryBody::PlanetaryBody;
using data = planetaryBody::PlanetData;
using bodyPtr = std::shared_ptr<body>;
using Timer = timeKeeping::Timer;

std::vector<bodyPtr> initPlanetaryBodies() {

    std::vector<bodyPtr> planetaryBodies;

    body earth("Earth", 5.972e24, 6.371e6, {0, 1.496e11}, {- 2.978e4, 0}, {200, 50, 20});
    bodyPtr earthPtr = std::make_shared<body>(earth);

    body sun("Sun", 1.988e30, 6.957e9, {0, 0}, {0, 0}, {20, 200, 200});
    bodyPtr sunPtr = std::make_shared<body>(sun);

    body moon("Moon", 7.346e22, 1.738e6, {3.844e8, 1.496e11}, {- 2.978e4, 1.0e3}, {80, 80, 80});
    bodyPtr moonPtr = std::make_shared<body>(moon);

    planetaryBodies.push_back(earthPtr);
    planetaryBodies.push_back(sunPtr);
    planetaryBodies.push_back(moonPtr);

    // _________________________________________________________________________________________________________________

    w::resizeWindow(planetaryBodies);

    return planetaryBodies;
}

void windowThread(const int &xPixels, const int &yPixels) {
    w::initializeWindow(xPixels, yPixels);
    std::vector<bodyPtr> planetaryBodies;
    while (cv::waitKey(1) != 27) {
        w::resetWindow();
        planetaryBodies = data::getPlanetaryBodies();

        w::resizeWindow(planetaryBodies, "Earth", 3.844e8);
        for (auto &body : planetaryBodies) {
            d::drawPlanetaryBody(body);
        }
        w::updateWindow();
    }

}

void updateBodies(const double &dt) {
    std::vector<bodyPtr> planetaryBodies;

    while (cv::waitKey(1) != 27) {
        planetaryBodies = data::getPlanetaryBodies();
        planetaryBodies.front()->updateForces(planetaryBodies);
        for (auto &body : planetaryBodies) {
            body->updateVelocity(dt);
            body->updatePosition(dt);
        }
        data::setPlanetaryBodies(planetaryBodies);
    }
}

int main() {

    std::vector<bodyPtr> planetaryBodies = initPlanetaryBodies();
    data::setPlanetaryBodies(planetaryBodies);

    const double dt = 1000;
    const int xPixels = 8000;
    const int yPixels = 6000;
    std::thread t1(windowThread, xPixels, yPixels);
    std::thread t2(updateBodies, dt);

    while (true) {
        if (cv::waitKey(100) == 27) {
            data::setExit();
            break;
        }
    }

    t1.join();
    t2.join();


    return 0;
}
