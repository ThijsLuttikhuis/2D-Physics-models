//
// Created by thijs on 27-12-18.
//

#include <random>
#include <memory>
#include <thread>
#include <vector>
#include <utility>

#include "physics_object/PhysicsObject.h"
#include "physics_object/GravityObject.h"
#include "physics_object/ObjectData.h"
#include "physics_object/Vector2.h"
#include "physics_object/Vector2Int.h"

#include "time_keeping/Timer.h"
#include "window/Color.h"
#include "window/Drawer.h"
#include "window/Window.h"

#include "../include/GLFW/glfw3.h"

#define PI 3.141592653589793

namespace physics {
class PhysicsObject;
class GravityObject;
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

std::vector<physicsPtr> initBodies(const double maxR) {
    std::vector<physicsPtr> bodies;

    double power = 0.8;
    double factor = 0.7;

    int nBodies2 = 10;
    for (double r = maxR/nBodies2; r < maxR; r+=maxR/nBodies2) {
        for (double theta = 0.2; theta < 2*PI; theta+=(2*PI*(maxR-r)/maxR)/nBodies2) {
            double mass = 1e30;
            double radius = 1e10;
            physics::Vector2 pos = {r*sin(theta), r*cos(theta)};
            physics::Vector2 vel = {pow(r,power)*cos(theta)*pow(10,-20*power)*factor, -pow(r,power)*sin(theta)*pow(10,-20*power)*factor};
            auto* color = new window::Color(255,0,0,255);

            physics::GravityObject gravityObject =
                    physics::GravityObject(mass, radius, pos, vel, color);

            auto gravityP = std::make_shared<physics::GravityObject>(gravityObject);
            bodies.push_back(gravityP);
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
            double x = -(body->getPos().x*500/1e21 - window::Window::getWidth()*0.5);
            double y = -(body->getPos().y*500/1e21 - window::Window::getHeight()*0.5);
            double r = body->getRadius()*768/10e20;
            window::Color* color = body->getColor();
            window::Window::drawCircle(static_cast<const short &>(x), static_cast<const short &>(y), r, color);
        }

        glDrawPixels(xPixels, yPixels, GL_RGBA, GL_UNSIGNED_BYTE, window::Window::getImage()); //draw pixel

        glfwSwapBuffers(window);

// check for keypress
        glfwPollEvents();

    }

    *exitPtr = true;
}

void updateBodiesThread(const double &dt, bool* exitPtr) {

    double maxR = 10e20;
    std::vector<physicsPtr> bodies = initBodies(maxR);

    while (! *exitPtr) {
        for (auto &body : bodies) {
            body->onUpdate(bodies);
        }
        for (auto &body : bodies) {
            body->updateVelocity(dt);
            body->updatePosition(dt);
        }

        physics::ObjectData::setBodies(bodies);
    }
}

int main() {

    double dt = 2e17;
    const short xPixels = 1366;
    const short yPixels = 768;
    bool exit = false;
    bool* exitPtr = &exit;

    window::Window::initializeWindow();

    std::thread t1(windowThread, xPixels, yPixels, exitPtr);
    std::thread t2(updateBodiesThread, dt, exitPtr);

    t1.join();
    t2.join();

    return 0;
}
