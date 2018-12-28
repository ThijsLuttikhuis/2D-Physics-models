//
// Created by thijs on 27-12-18.
//

#ifndef FINDBALL_WINDOW_H
#define FINDBALL_WINDOW_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

namespace solarSystem {
namespace window {

class Window {

    private:
        static int pixelWidth;
        static int pixelHeight;
        static cv::Mat image;

    public:

        static cv::Mat getImage();
        static cv::Vec3b getPixel(const int &x, const int &y);

        static void setImage(cv::Mat &newImage);
        static void setPixel(const int &x, const int &y, const cv::Vec3b &color);

        static void initializeWindow();
        static void updateWindow();

};

} //window
} //solarSystem

#endif //FINDBALL_WINDOW_H
