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

    planetaryBodies = solarSystem::planetaryBody::PlanetData::getPlanetaryBodies();
    solarSystem::window::Window::resizeWindow(planetaryBodies);

    bool period = false;
    bool comma = false;
    bool tab = false;
    bool minus = false;
    bool equal = false;

    while (!solarSystem::planetaryBody::PlanetData::getExit()) {
        if (glfwWindowShouldClose(window)) {
            solarSystem::planetaryBody::PlanetData::setExit();
            break;
        }

//  reset bodies in window
        solarSystem::window::Window::resetWindow();
        planetaryBodies = solarSystem::planetaryBody::PlanetData::getPlanetaryBodies();
        solarSystem::window::Window::resizeWindow(planetaryBodies,-4,-1.0);

//  draw bodies in window
        for (auto &body : planetaryBodies) {
            solarSystem::window::Drawer::drawPlanetaryBody(body);
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

        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS && !period) {
            period = true;

            double dt = solarSystem::planetaryBody::PlanetData::getDt()*2.0;
            solarSystem::planetaryBody::PlanetData::setDt(dt);

        }
        if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS && !comma) {
            comma = true;

            double dt = solarSystem::planetaryBody::PlanetData::getDt()*0.5;
            solarSystem::planetaryBody::PlanetData::setDt(dt);

        }
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !tab) {
            tab = true;

            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
                solarSystem::window::Window::resizeWindow(planetaryBodies, -3, -1.0);
            else
                solarSystem::window::Window::resizeWindow(planetaryBodies, -2, -1.0);
        }
        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS && !equal) {
            equal = true;

            solarSystem::window::Window::resizeWindow(planetaryBodies, -4, -0.75);
        }
        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS && !minus) {
            minus = true;

            solarSystem::window::Window::resizeWindow(planetaryBodies, -4, -1.33);
        }


        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_RELEASE) {
            period = false;
        }
        if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_RELEASE) {
            comma = false;
        }
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
            tab = false;
        }
        if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE) {
            equal = false;
        }
        if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE) {
            minus = false;
        }
    }

}

void updateBodies() {
    std::vector<bodyPtr> planetaryBodies;

    while (!solarSystem::planetaryBody::PlanetData::getExit()) {
        double dt = solarSystem::planetaryBody::PlanetData::getDt();


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
    const short xPixels = 1600;
    const short yPixels = 900;

    solarSystem::planetaryBody::PlanetData::setDt(dt);

    std::thread t1(windowThread, xPixels, yPixels);
    std::thread t2(updateBodies);

    t1.join();
    t2.join();

    return 0;
}
