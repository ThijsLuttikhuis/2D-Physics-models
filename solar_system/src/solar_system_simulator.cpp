//
// Created by thijs on 27-12-18.
//
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include "window/Window.h"

namespace ss = solarSystem;

int main() {

    ss::Window::initializeWindow();
    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            ss::Window::setPixel(x, y, {0,255,0});
        }
    }

    ss::Window::updateWindow();

    cv::waitKey(0);
    return 0;
}
