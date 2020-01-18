//
// Created by thijs on 27-12-18.
//

#include <memory>
#include <thread>
#include <vector>
#include <utility>

#include "Physics.h"

#include "physics_object/PhysicsObject.h"
#include "physics_object/GravityObject.h"
#include "physics_object/CollisionObject.h"
#include "physics_object/WallObject.h"

#include "physics_object/ObjectData.h"
#include "physics_object/Vector2.h"
#include "physics_object/Vector2Int.h"

#include "time_keeping/Timer.h"
#include "window/Color.h"
#include "window/Window.h"

#include "../include/GLFW/glfw3.h"


namespace physics {
class Physics;

class PhysicsObject;
class GravityObject;
class CollisionObject;
class WallObject;
class Vector2;
class Vector2Int;
}

namespace timeKeeping {
class Timer;
}

namespace window {
class Window;
class Drawer;
}

using physicsPtr = std::shared_ptr<physics::Physics>;

std::vector<physicsPtr> initBodies() {

    int thingy = 1;
    std::vector<physicsPtr> bodies;

    switch (thingy) {
    default: break;
    case 1: {
        auto* color1 = new window::Color(255, 0, 0, 255);
        auto cObj1 = physics::CollisionObject(1e10, 1, physics::Vector2(1.11, 0), physics::Vector2(- 4, 0), color1);
        physicsPtr cObjPtr1 = std::make_shared<physics::CollisionObject>(cObj1);
        bodies.push_back(cObjPtr1);

        auto* color2 = new window::Color(255, 0, 0, 255);
        auto cObj2 = physics::CollisionObject(1, 0.1, physics::Vector2(0, 0), physics::Vector2(0, 0), color2);
        physicsPtr cObjPtr2 = std::make_shared<physics::CollisionObject>(cObj2);
        bodies.push_back(cObjPtr2);

        auto* color3 = new window::Color(255, 255, 255, 255);
        auto wObj = physics::WallObject(1e300, 1, physics::Vector2(- 1.11, - 10), physics::Vector2(- 1.11, 10), color3);
        physicsPtr wObjPtr = std::make_shared<physics::WallObject>(wObj);
        bodies.push_back(wObjPtr);
        break;
    }
    case 2: {
        const unsigned short AMOUNT_OF_OBJECTS = 3;
        std::vector<double> mass = {1.989e30, 5.972e24, 7.34e22};
        std::vector<double> radius = {6.955e8, 6.371e6, 1.737e6};
        std::vector<physics::Vector2> pos = {{0.0, 0.0}, {1.496e11, 0.0}, {1.496e11, 3.84e8}};
        std::vector<physics::Vector2> vel = {{0.0, 0.0}, {0.0, 2.96e4}, {1.023e3, 2.96e4}};

        for (int i = 0; i < AMOUNT_OF_OBJECTS; i ++) {
            auto* color = new window::Color(255 - 64 * i, 0 + 64 * i, 0, 255);
            physics::GravityObject gObj = physics::GravityObject(mass[i], radius[i],
                                                                 pos[i], vel[i], color);
            physicsPtr gObjPtr = std::make_shared<physics::GravityObject>(gObj);
            bodies.push_back(gObjPtr);
        }
        break;
    }
    case 3: {



    }
    }
    return bodies;
}

void windowThread(const short &xPixels, const short &yPixels, bool* exitPtr) {

    GLFWwindow* window;
    if (! glfwInit()) {
        return;
    }

    window = glfwCreateWindow(xPixels, yPixels, "Solar System", nullptr, nullptr);
    if (! window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    std::vector<physicsPtr> bodies;
    while (! glfwWindowShouldClose(window) && ! *exitPtr) {
//clear screen
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2f(- 1, - 1);
        window::Window::resetWindow();

//draw objects
        bodies = physics::ObjectData::getBodies();

        for (auto &body : bodies) {
            body->draw();
        }

        glDrawPixels(xPixels, yPixels, GL_RGBA, GL_UNSIGNED_BYTE, window::Window::getImage()); //draw pixel

        glfwSwapBuffers(window);

// check for keypress
        glfwPollEvents();

    }

    *exitPtr = true;
}

void updateBodiesThread(const double &dt, bool* exitPtr) {

    std::vector<physicsPtr> bodies = initBodies();
    for (auto &body : bodies) {
        body->onInitialize();
    }

    while (! *exitPtr) {
        for (auto &body : bodies) {
            body->onUpdate(bodies);
        }

        for (auto &body : bodies) {
            body->afterUpdate(dt);
            body->updateVelocity(dt);
            body->updatePosition(dt);
        }

        physics::ObjectData::setBodies(bodies);
    }
}

int main() {

    double dt = 1e-8;
    double zoomFactor = 1.2e2;
    const short xPixels = 1200;
    const short yPixels = 500;
    bool exit = false;
    bool* exitPtr = &exit;

    window::Window::initializeWindow(xPixels, yPixels);
    window::Window::setZoomFactor(zoomFactor);

    std::thread t1(windowThread, xPixels, yPixels, exitPtr);
    std::thread t2(updateBodiesThread, dt, exitPtr);

    t1.join();
    t2.join();
    delete exitPtr;

    return 0;
}
