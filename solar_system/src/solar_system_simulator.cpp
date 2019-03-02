//
// Created by thijs on 27-12-18.
//

#include <memory>
#include <thread>
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

std::vector<bodyPtr> initPlanetaryBodies() {
    const unsigned int NBODIES = 3;

    std::vector<bodyPtr> planetaryBodies;
    planetaryBodies.reserve(NBODIES);

    std::string bodyNames[] = {"Earth",
                               "Sun",
                               "Moon"};

    double bodyMasses[] = {5.972e24,
                           1.988e30,
                           7.346e22};

    double bodyRadii[] = {6.371e6,
                          6.957e9,
                          1.738e6};

    solarSystem::planetaryBody::Vector2 bodyPositions[] = {
            {0, 1.496e11},
            {0, 0},
            {3.844e8, 1.496e11}};

    solarSystem::planetaryBody::Vector2 bodyVelocities[] = {
            {- 2.978e4, 0},
            {0, 0},
            {- 2.978e4, 1.0e3}};

    auto* bodyColors = new solarSystem::window::Color[NBODIES];
    bodyColors[0] = solarSystem::window::Color(0, 127, 191, 255);
    bodyColors[1] = solarSystem::window::Color(191, 191, 0, 255);
    bodyColors[2] = solarSystem::window::Color(63, 127, 127, 255);

    for (unsigned int i = 0; i < NBODIES; i ++) {
        solarSystem::planetaryBody::PlanetaryBody earth = solarSystem::planetaryBody::PlanetaryBody
                (bodyNames[i], bodyMasses[i], bodyRadii[i], bodyPositions[i],
                        bodyVelocities[i], (bodyColors + i));

        bodyPtr pointer = std::make_shared<solarSystem::planetaryBody::PlanetaryBody>(earth);
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

    while (!solarSystem::planetaryBody::PlanetData::getExit()) {
        if (glfwWindowShouldClose(window)) {
            solarSystem::planetaryBody::PlanetData::setExit();
            break;
        }
        solarSystem::window::Window::resetWindow();
        planetaryBodies = solarSystem::planetaryBody::PlanetData::getPlanetaryBodies();

        solarSystem::window::Window::resizeWindow(planetaryBodies);//, "Earth", 5e8);

        for (auto &body : planetaryBodies) {
            solarSystem::window::Drawer::drawPlanetaryBody(body);
        }
        solarSystem::window::Window::updateWindow();

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2f(- 1, - 1);

        glDrawPixels(xPixels, yPixels, GL_RGBA, GL_UNSIGNED_BYTE, solarSystem::window::Window::getImage()); //draw pixel

        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            solarSystem::planetaryBody::PlanetData::setExit();
        }
    }

}

void updateBodies(const double &dt) {
    std::vector<bodyPtr> planetaryBodies;

    while (!solarSystem::planetaryBody::PlanetData::getExit()) {
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

    const double dt = 10;
    const short xPixels = 1600;
    const short yPixels = 900;

    std::thread t1(windowThread, xPixels, yPixels);
    std::thread t2(updateBodies, dt);

    t1.join();
    t2.join();

    return 0;
}
