//
// Created by thijs on 27-12-18.
//

#include <random>
#include <memory>
#include <thread>
#include <vector>
#include <utility>
#include "physics_object/GravityObject.h"
#include "physics_object/PlanetData.h"
#include "physics_object/Vector2.h"
#include "physics_object/Vector2Int.h"
#include "time_keeping/Timer.h"
#include "window/Color.h"
#include "window/Drawer.h"
#include "window/Window.h"

#include "../include/GLFW/glfw3.h"


namespace physics {
class GravityObject;
}

namespace timeKeeping {
class Timer;
}

namespace window {
class Window;
class Drawer;
}

using physicsPtr = std::shared_ptr<physics::PhysicsObject>;

void windowThread(const short &xPixels, const short &yPixels) {

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

    while (! glfwWindowShouldClose(window)) {

//  show figure
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2f(- 1, - 1);

        glDrawPixels(xPixels, yPixels, GL_RGBA, GL_UNSIGNED_BYTE, window::Window::getImage()); //draw pixel

        glfwSwapBuffers(window);

// check for keypress
        glfwPollEvents();

    }

}

void updateBodiesThread(const double &dt) {
    std::vector<physicsPtr> objects;
    while (dt != 0) {

        for (auto &object : objects) {
            object->updateAcceleration();
            object->updateVelocity(dt);
            object->updatePosition(dt);
        }
    }
}

int main() {

    double dt = 10.0;
    const short xPixels = 1366;
    const short yPixels = 768;

    std::thread t1(windowThread, xPixels, yPixels);
    std::thread t2(updateBodiesThread, dt);

    t1.join();
    t2.join();

    return 0;
}
