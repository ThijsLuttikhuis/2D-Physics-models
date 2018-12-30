//
// Created by thijs on 27-12-18.
//

#include "Window.h"
#include "Drawer.h"

namespace solarSystem {
namespace window {

int Window::xPixels;
int Window::yPixels;
cv::Mat Window::image;

cv::Mat Window::getImage() {
    return image;
}

int Window::getXPixels() {
    return xPixels;
}

int Window::getYPixels() {
    return yPixels;
}

cv::Vec3b Window::getPixel(const int &x, const int &y) {
    if (x >= 0 && y >= 0 && x < xPixels && y < yPixels) {
        return image.at<cv::Vec3b>(y, x);
    }
    else {
        //std::cout << "ERROR: pixel is not within margins." << std::endl;
        return {};
    }
}

void Window::setImage(cv::Mat &newImage) {
    image = newImage;
}

void Window::setPixel(const int &x, const int &y, const cv::Vec3b &color) {
    if (x >= 0 && y >= 0 && x < xPixels && y < yPixels) {
        image.at<cv::Vec3b>(y, x) = color;
    }
    else {
        //std::cout << "ERROR: pixel is not within margins." << std::endl;
    }
}

void Window::initializeWindow() {
    xPixels = 1366;
    yPixels = 768;
    image = cv::Mat(yPixels, xPixels, CV_8UC3);

    cv::namedWindow("Window", CV_WINDOW_NORMAL);
}

void Window::initializeWindow(const int &width, const int &height) {
    xPixels = width;
    yPixels = height;
    image = cv::Mat(yPixels, xPixels, CV_8UC3);

    cv::namedWindow("Window", CV_WINDOW_NORMAL);
}

void Window::updateWindow() {

    cv::imshow("Window", image);
    cv::waitKey(1);
}


void Window::resetWindow() {
    image = cv::Mat::zeros(yPixels, xPixels, CV_8UC3);

}

void Window::resizeWindow(std::vector<std::shared_ptr<planetaryBody::PlanetaryBody>> bodies) {
    planetaryBody::PlanetaryBody::Vector2 centerOfMass = bodies.front()->getCenterOfMass(bodies);
    double furthestDistance = bodies.front()->getFurthestObject(bodies, centerOfMass);

    double factor;
    if (getXPixels() < getYPixels())
        factor = 0.45 * getXPixels()/furthestDistance;
    else
        factor = 0.45 * getYPixels()/furthestDistance;

    Drawer::setRealToPixel(factor);
    Drawer::setRealCenter(centerOfMass);
}

void Window::resizeWindow(std::vector<std::shared_ptr<planetaryBody::PlanetaryBody>> bodies, std::string focus,
        double radius) {

    planetaryBody::PlanetaryBody::Vector2 focusPos = {0,0};
    for (auto &body : bodies) {
        if (body.get()->getName() == focus) {
            focusPos = body->getPosition();
            break;
        }
    }
    double factor;
    if (getXPixels() < getYPixels())
        factor = 0.45 * getXPixels()/radius;
    else
        factor = 0.45 * getYPixels()/radius;

    Drawer::setRealToPixel(factor);
    Drawer::setRealCenter(focusPos);

}

} //window
} //solarSystem