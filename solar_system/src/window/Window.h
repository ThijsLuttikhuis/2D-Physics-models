//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_WINDOW_H
#define SOLARSYSTEM_WINDOW_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "../planetary_body/PlanetaryBody.h"

namespace solarSystem {
namespace window {

class Window {

    private:
        static int xPixels;
        static int yPixels;
        static cv::Mat image;

    public:

        static cv::Mat getImage();

        static int getXPixels();
        static int getYPixels();

        static cv::Vec3b getPixel(const int &x, const int &y);

        static void setImage(cv::Mat &newImage);
        static void setPixel(const int &x, const int &y, const cv::Vec3b &color);

        static void initializeWindow();
        static void initializeWindow(const int &width, const int &height);
        static void resetWindow();
        static void resizeWindow(std::vector<std::shared_ptr<planetaryBody::PlanetaryBody>> bodies, std::string focus, double radius);
        static void resizeWindow(std::vector<std::shared_ptr<planetaryBody::PlanetaryBody>> bodies);
        static void updateWindow();

};

} //window
} //solarSystem

#endif //FINDBALL_WINDOW_H
