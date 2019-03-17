//
// Created by thijs on 27-12-18.
//

#include <memory>
#include <thread>
#include <vector>
#include <utility>

#include "physics_object/PhysicsObject.h"
#include "physics_object/GravityObject.h"
#include "physics_object/CollisionObject.h"
#include "physics_object/WallObject.h"

#include "physics_object/ObjectData.h"
#include "physics_object/Vector2.h"
#include "physics_object/Vector2Int.h"

#include "time_keeping/Timer.h"
#include "window/Color.h"
#include "window/Drawer.h"
#include "window/Window.h"

#include "../include/GLFW/glfw3.h"
#include "physics_object/WallObject.h"

#define PI 3.141592653589793

namespace physics {
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

using physicsPtr = std::shared_ptr<physics::PhysicsObject>;

std::vector<physicsPtr> initBodies() {

    std::vector<physicsPtr> bodies;
    for (int i = 0; i < 2; i++) {
        auto* color = new window::Color(255, 0, 0, 255);
        auto cObj = physics::CollisionObject(1+i*99999, 1, physics::Vector2(i*10, 0), physics::Vector2(-1*i*i, 0), color);
        physicsPtr cObjPtr = std::make_shared<physics::CollisionObject>(cObj);
        bodies.push_back(cObjPtr);
    }

    auto* color = new window::Color(255, 255, 255, 255);
    auto wObj = physics::WallObject(1e300, 1, physics::Vector2(-10, -10), physics::Vector2(-10, 10), color);
    physicsPtr wObjPtr = std::make_shared<physics::WallObject>(wObj);
    bodies.push_back(wObjPtr);

    return bodies;
//
//    const unsigned short AMOUNT_OF_OBJECTS = 3;
//    std::vector<double> mass = {1.989e30, 5.972e24, 7.34e22};
//    std::vector<double> radius = {6.955e8, 6.371e6, 1.737e6};
//    std::vector<physics::Vector2> pos = {{0.0,0.0},{1.496e11,0.0},{1.496e11,3.84e8}};
//    std::vector<physics::Vector2> vel = {{0.0,0.0},{0.0,2.96e4},{1.023e3,2.96e4}};
//
//    for (int i = 0; i < AMOUNT_OF_OBJECTS; i++) {
//        auto* color = new window::Color(255-64*i,0+64*i,0,255);
//        physics::GravityObject gObj = physics::GravityObject(mass[i], radius[i],
//                pos[i], vel[i], color);
//        physicsPtr gObjPtr = std::make_shared<physics::GravityObject>(gObj);
//        bodies.push_back(gObjPtr);
//    }
//
//    return bodies;
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

//        double zoomFactor = 4e0;

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

    double dt = 1e-5;
    const short xPixels = 2200;
    const short yPixels = 500;
    bool exit = false;
    bool* exitPtr = &exit;

    window::Window::initializeWindow(xPixels, yPixels);

    std::thread t1(windowThread, xPixels, yPixels, exitPtr);
    std::thread t2(updateBodiesThread, dt, exitPtr);

    t1.join();
    t2.join();
    delete exitPtr;

    return 0;
}
