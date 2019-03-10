//
// Created by thijs on 27-12-18.
//

#include <random>
#include <memory>
#include <thread>
#include <vector>
#include <utility>
#include "planetary_body/PlanetaryBody.h"
#include "planetary_body/PlanetData.h"
#include "planetary_body/Vector2.h"
#include "planetary_body/Vector2Int.h"
#include "time_keeping/Timer.h"
#include "window/Color.h"
#include "window/Drawer.h"
#include "window/Window.h"

#include "../include/GLFW/glfw3.h"

namespace solarSystem {

namespace planetaryBody {
class PlanetaryBody;
}

namespace timeKeeping {
class Timer;
}

namespace window {
class Window;
class Drawer;
}
}

using bodyPtr = std::shared_ptr<solarSystem::planetaryBody::PlanetaryBody>;

std::vector<double> getRandomNumbers(double min, double max, unsigned int nNumbers) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(min, max);

    std::vector<double> randVec;
    randVec.reserve(nNumbers);

    for (unsigned int i = 0; i < nNumbers; i ++) {
        randVec.push_back(dist(mt));
    }
    return randVec;
}

std::vector<bodyPtr> initPlanetaryBodies(int what = 0) {
    std::vector<bodyPtr> planetaryBodies;
    unsigned int NBODIES;
    std::vector<std::string> bodyNames;
    std::vector<double> bodyMasses;
    std::vector<double> bodyRadii;
    std::vector<solarSystem::planetaryBody::Vector2> bodyPositions;
    std::vector<solarSystem::planetaryBody::Vector2> bodyVelocities;
    auto* bodyColors = new solarSystem::window::Color[100];

    switch (what) {
    case 1: {
        NBODIES = 50;
        planetaryBodies.reserve(NBODIES);

        bodyMasses = getRandomNumbers(1e24, 1e32, NBODIES);
        bodyRadii = getRandomNumbers(1e7, 1e9, NBODIES);
        std::vector<double> pos = getRandomNumbers(- 1e11, 1e11, NBODIES*2);
        std::vector<double> vel = getRandomNumbers(- 1e1, 1e1, NBODIES*2);
        std::vector<double> colors = getRandomNumbers(0.00, 255.99, NBODIES*4);

        for (unsigned int i = 0; i < NBODIES; i ++) {
            bodyNames.push_back(static_cast<std::string>("random"));

            bodyPositions.emplace_back(pos[2*i + 0], pos[2*i + 1]);
            bodyVelocities.emplace_back(vel[2*i + 0], vel[2*i + 1]);

            bodyColors[i] = solarSystem::window::Color(
                    static_cast<unsigned char>(colors[i*4 + 0]),
                    static_cast<unsigned char>(colors[i*4 + 1]),
                    static_cast<unsigned char>(colors[i*4 + 2]),
                    static_cast<unsigned char>(colors[i*4 + 3]));
        }
        break;
    }
    case 0:
    default:NBODIES = 3;
        planetaryBodies.reserve(NBODIES);

        bodyNames = {"Earth",
                     "Sun",
                     "Moon"};

        bodyMasses = {5.972e24,
                      1.988e30,
                      7.346e22};

        bodyRadii = {6.371e6,
                     6.957e9,
                     1.738e6};

        bodyPositions = {
                {0, 1.496e11},
                {0, 0},
                {3.844e8, 1.496e11}};

        bodyVelocities = {
                {- 2.978e4, 0},
                {0, 0},
                {- 2.978e4, 1.0e3}};

        bodyColors[0] = solarSystem::window::Color(0, 127, 191, 255);
        bodyColors[1] = solarSystem::window::Color(191, 191, 0, 255);
        bodyColors[2] = solarSystem::window::Color(63, 127, 127, 255);
        break;
    }

    for (unsigned int i = 0; i < NBODIES; i ++) {
        solarSystem::planetaryBody::PlanetaryBody body = solarSystem::planetaryBody::PlanetaryBody
                (bodyNames[i], bodyMasses[i], bodyRadii[i], bodyPositions[i],
                        bodyVelocities[i], (bodyColors + i));

        bodyPtr pointer = std::make_shared<solarSystem::planetaryBody::PlanetaryBody>(body);
        planetaryBodies.push_back(pointer);
    }
    solarSystem::window::Window::resizeWindow(planetaryBodies);
    return planetaryBodies;
}

void windowThread(const short &xPixels, const short &yPixels) {

    solarSystem::window::Window::initializeWindow(xPixels, yPixels);
    std::vector<bodyPtr> planetaryBodies;

    GLFWwindow* window;
    if (! glfwInit()) {
        solarSystem::planetaryBody::PlanetData::setExit();
        return;
    }
    window = glfwCreateWindow(xPixels, yPixels, "Solar System", nullptr, nullptr);
    if (! window) {
        glfwTerminate();
        solarSystem::planetaryBody::PlanetData::setExit();
        return;
    }
    glfwMakeContextCurrent(window);

    std::vector<std::pair<solarSystem::planetaryBody::Vector2, solarSystem::window::Color*>> pathPoints;
    planetaryBodies = solarSystem::planetaryBody::PlanetData::getPlanetaryBodies();
    solarSystem::window::Window::resizeWindow(planetaryBodies);

    bool key_period = false;
    bool key_comma = false;
    bool key_tab = false;
    bool key_minus = false;
    bool key_equal = false;

    bool key_0 = false;
    bool key_1 = false;
    bool key_2 = false;
    bool key_3 = false;
    bool key_4 = false;
    bool key_5 = false;
    bool key_6 = false;
    bool key_7 = false;
    bool key_8 = false;
    bool key_9 = false;

    while (! solarSystem::planetaryBody::PlanetData::getExit()) {
        if (glfwWindowShouldClose(window)) {
            solarSystem::planetaryBody::PlanetData::setExit();
            break;
        }

//  reset bodies in window
        solarSystem::window::Window::resetWindow();
        planetaryBodies = solarSystem::planetaryBody::PlanetData::getPlanetaryBodies();
        solarSystem::window::Window::resizeWindow(planetaryBodies, - 4, - 1.0);

//  draw bodies in window
        for (auto &body : planetaryBodies) {
            solarSystem::window::Drawer::drawPlanetaryBody(body);

            std::pair<solarSystem::planetaryBody::Vector2, solarSystem::window::Color*> pathPoint =
                    {body->getPosition(), body->getColor()};

            pathPoints.push_back(pathPoint);
        }

        for (auto &pathPoint : pathPoints) {

            auto pos = solarSystem::window::Drawer::transformRealToPixel(pathPoint.first);
            auto color = pathPoint.second;
            solarSystem::window::Window::setPixel(
                    static_cast<const short &>(pos.x),
                    static_cast<const short &>(pos.y),
                    color);
        }

        solarSystem::window::Window::updateWindow();

//  show figure
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2f(- 1, - 1);

        glDrawPixels(xPixels, yPixels, GL_RGBA, GL_UNSIGNED_BYTE, solarSystem::window::Window::getImage()); //draw pixel

        glfwSwapBuffers(window);

// check for keypress
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            solarSystem::planetaryBody::PlanetData::setExit();
            break;
        }

        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS && ! key_period) {
            key_period = true;

            double dt = solarSystem::planetaryBody::PlanetData::getDt()*2.0;
            solarSystem::planetaryBody::PlanetData::setDt(dt);

        }
        if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS && ! key_comma) {
            key_comma = true;

            double dt = solarSystem::planetaryBody::PlanetData::getDt()*0.5;
            solarSystem::planetaryBody::PlanetData::setDt(dt);

        }
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && ! key_tab) {
            key_tab = true;

            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                solarSystem::window::Window::resizeWindow(planetaryBodies, - 3, - 1.0);
            else
                solarSystem::window::Window::resizeWindow(planetaryBodies, - 2, - 1.0);
        }
        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS && ! key_equal) {
            key_equal = true;

            solarSystem::window::Window::resizeWindow(planetaryBodies, - 4, - 0.75);
        }
        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS && ! key_minus) {
            key_minus = true;

            solarSystem::window::Window::resizeWindow(planetaryBodies, - 4, - 1.33);
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {

            if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS && ! key_0) {
                key_0 = true;

                auto newBodies = initPlanetaryBodies(0);
                solarSystem::planetaryBody::PlanetData::setPlanetaryBodies(newBodies, true);
                solarSystem::window::Window::resizeWindow(planetaryBodies);
                pathPoints.clear();

            }
            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && ! key_1) {
                key_1 = true;

                auto newBodies = initPlanetaryBodies(1);
                solarSystem::planetaryBody::PlanetData::setPlanetaryBodies(newBodies, true);
                solarSystem::window::Window::resizeWindow(planetaryBodies);
                pathPoints.clear();

            }
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && ! key_2) {
                key_2 = true;

                auto newBodies = initPlanetaryBodies(2);
                solarSystem::planetaryBody::PlanetData::setPlanetaryBodies(newBodies, true);
                solarSystem::window::Window::resizeWindow(planetaryBodies);
                pathPoints.clear();

            }
            if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && ! key_3) {
                key_3 = true;

                auto newBodies = initPlanetaryBodies(3);
                solarSystem::planetaryBody::PlanetData::setPlanetaryBodies(newBodies, true);
                solarSystem::window::Window::resizeWindow(planetaryBodies);
                pathPoints.clear();

            }
            if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && ! key_4) {
                key_4 = true;

                auto newBodies = initPlanetaryBodies(4);
                solarSystem::planetaryBody::PlanetData::setPlanetaryBodies(newBodies, true);
                solarSystem::window::Window::resizeWindow(planetaryBodies);
                pathPoints.clear();

            }

            if (glfwGetKey(window, GLFW_KEY_0) == GLFW_RELEASE) {
                key_0 = false;
            }
            if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE) {
                key_1 = false;
            }
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE) {
                key_2 = false;
            }
            if (glfwGetKey(window, GLFW_KEY_3) == GLFW_RELEASE) {
                key_3 = false;
            }
            if (glfwGetKey(window, GLFW_KEY_4) == GLFW_RELEASE) {
                key_4 = false;
            }

        }

        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_RELEASE) {
            key_period = false;
        }
        if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_RELEASE) {
            key_comma = false;
        }
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
            key_tab = false;
        }
        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE) {
            key_equal = false;
        }
        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE) {
            key_minus = false;
        }
    }

}

void updateBodies() {
    std::vector<bodyPtr> planetaryBodies;
    double dt;
    while (! solarSystem::planetaryBody::PlanetData::getExit()) {
        dt = solarSystem::planetaryBody::PlanetData::getDt();

        planetaryBodies = solarSystem::planetaryBody::PlanetData::getPlanetaryBodies();
        planetaryBodies.front()->updateForces(planetaryBodies);
        for (auto &body : planetaryBodies) {
            body->updateVelocity(dt);
            body->updatePosition(dt);
        }
        solarSystem::planetaryBody::PlanetData::setPlanetaryBodies(planetaryBodies);
    }
}

int main() {

    std::vector<bodyPtr> planetaryBodies = initPlanetaryBodies();
    solarSystem::planetaryBody::PlanetData::setPlanetaryBodies(planetaryBodies);
    solarSystem::window::Window::resizeWindow(planetaryBodies);

    double dt = 10.0;
    const short xPixels = 1366;
    const short yPixels = 768;

    solarSystem::planetaryBody::PlanetData::setDt(dt);

    std::thread t1(windowThread, xPixels, yPixels);
    std::thread t2(updateBodies);

    t1.join();
    t2.join();

    return 0;
}
