//
// Created by thijs on 27-12-18.
//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include "window/Window.h"
#include "window/Drawer.h"
#include "planetary_body/PlanetaryBody.h"
#include <set>
#include <memory>

namespace window = solarSystem::window;
namespace planetaryBody = solarSystem::planetaryBody;
using w = window::Window;
using d = window::Drawer;
using body = planetaryBody::PlanetaryBody;
using bodyPtr = std::shared_ptr<body>;

std::vector<bodyPtr> initPlanetaryBodies() {

    std::vector<bodyPtr> planetaryBodies;

    body earth("Earth", 5.972e24, 6.371e6, {0, 149.6e9}, {0, 29.78}, {200, 50, 20});
    bodyPtr earthPtr = std::make_shared<body>(earth);

    body sun("Sun", 1.988e30, 6.957e9, {0, 0}, {0, 0}, {20, 200, 200});
    bodyPtr sunPtr = std::make_shared<body>(sun);

    planetaryBodies.push_back(earthPtr);
    planetaryBodies.push_back(sunPtr);

    // _________________________________________________________________________________________________________________

    cv::Mat image = w::getImage();
    int xPixels = image.cols;
    int yPixels = image.rows;

    body::Vector2 minRealPos = {1e100, 1e100};
    body::Vector2 maxRealPos = {-1e100, -1e100};

    for (auto &body : planetaryBodies) {
        body::Vector2 pos = body->getPosition();

        if (pos.x < minRealPos.x) minRealPos.x = pos.x;
        if (pos.y < minRealPos.y) minRealPos.y = pos.y;
        if (pos.x > maxRealPos.x) maxRealPos.x = pos.x;
        if (pos.y > maxRealPos.y) maxRealPos.y = pos.y;
    }

    double xFactor = xPixels/(maxRealPos.x-minRealPos.x);
    double yFactor = yPixels/(maxRealPos.y-minRealPos.y);
    if (xFactor < yFactor) d::setRealToPixel(xFactor);
    else d::setRealToPixel(yFactor);

    double xCenter = (maxRealPos.x+minRealPos.x)*0.5;
    double yCenter = (maxRealPos.y+minRealPos.x)*0.5;
    d::setRealCenter(xCenter, yCenter);
    return planetaryBodies;
}


int main(int argc, char* argv[]) {

    w::initializeWindow();
    std::vector<bodyPtr> planetaryBodies = initPlanetaryBodies();
    for (auto &body : planetaryBodies) {
        std::cout << body->getName() << std::endl;
        d::drawPlanetaryBody(body);
    }


    w::updateWindow();

    cv::waitKey(0);
    return 0;
}
