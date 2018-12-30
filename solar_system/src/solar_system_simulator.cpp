//
// Created by thijs on 27-12-18.
//
#include <opencv2/imgcodecs.hpp>
#include "window/Drawer.h"
#include <chrono>

namespace window = solarSystem::window;
namespace planetaryBody = solarSystem::planetaryBody;
using w = window::Window;
using d = window::Drawer;
using body = planetaryBody::PlanetaryBody;
using bodyPtr = std::shared_ptr<body>;

class Timer
{
    public:
        void start()
        {
            m_StartTime = std::chrono::system_clock::now();
            m_bRunning = true;
        }

        void stop()
        {
            m_EndTime = std::chrono::system_clock::now();
            m_bRunning = false;
        }

        double elapsedMilliseconds()
        {
            std::chrono::time_point<std::chrono::system_clock> endTime;

            if(m_bRunning)
            {
                endTime = std::chrono::system_clock::now();
            }
            else
            {
                endTime = m_EndTime;
            }

            return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
        }

        double elapsedSeconds()
        {
            return elapsedMilliseconds() / 1000.0;
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> m_StartTime;
        std::chrono::time_point<std::chrono::system_clock> m_EndTime;
        bool                                               m_bRunning = false;
};

std::vector<bodyPtr> initPlanetaryBodies() {

    std::vector<bodyPtr> planetaryBodies;

    body earth("Earth", 5.972e24, 6.371e6, {0, 1.496e11}, {-2.978e4, 0}, {200, 50, 20});
    bodyPtr earthPtr = std::make_shared<body>(earth);

    body sun("Sun", 1.988e30, 6.957e9, {0, 0}, {0, 0}, {20, 200, 200});
    bodyPtr sunPtr = std::make_shared<body>(sun);

    body moon("Moon", 7.346e22, 1.738e6, {3.844e8, 1.496e11}, {-2.978e4, 1.0e3}, {80,80,80});
    bodyPtr moonPtr = std::make_shared<body>(moon);

    planetaryBodies.push_back(earthPtr);
    planetaryBodies.push_back(sunPtr);
    planetaryBodies.push_back(moonPtr);

    // _________________________________________________________________________________________________________________

    w::resizeWindow(planetaryBodies);

    return planetaryBodies;
}

int main() {

    w::initializeWindow(800, 600);
    std::vector<bodyPtr> planetaryBodies = initPlanetaryBodies();

    const double dt = 1000;
    double t = 0;


    Timer timer;
    timer.start();

    while (cv::waitKey(1) != 27) {
        t+=dt;
        w::resetWindow();

        planetaryBodies.front()->updateForces(planetaryBodies);
        for (auto &body : planetaryBodies) {
            body->updateVelocity(dt);
            body->updatePosition(dt);
        }

        if (timer.elapsedMilliseconds() > 16) {
            w::resizeWindow(planetaryBodies, "Earth", 3.844e8);
            for (auto &body : planetaryBodies) {
                d::drawPlanetaryBody(body);
            }
            w::updateWindow();
            timer.stop();
            timer.start();
        }
    }
    return 0;
}
