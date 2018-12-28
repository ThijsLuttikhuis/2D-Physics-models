//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_DRAWER_H
#define SOLARSYSTEM_DRAWER_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Window.h"
#include "../planetary_body/PlanetaryBody.h"
#include <memory>

namespace solarSystem {
namespace window {

class Drawer {

    private:
        static double pixelToReal;
        static double realToPixel;
        static double xPixelCenter;
        static double yPixelCenter;
    public:
        static void drawCircle(const double &xCenter, const double &yCenter, double &radius,
                const cv::Vec3b &color);
        static void drawPlanetaryBody(const std::shared_ptr<planetaryBody::PlanetaryBody> &body);
        static void setPixelToReal(const double &factor);
        static void setRealToPixel(const double &factor);
        static void setRealCenter(const double &x, const double &y);
        static void setPixelCenter(const int &x, const int &y);

};

} //window
} //solarSystem

#endif //SOLARSYSTEM_DRAWER_H

