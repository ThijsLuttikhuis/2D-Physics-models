//
// Created by thijs on 27-12-18.
//

#include "Window.h"

namespace solarSystem {

int Window::pixelWidth;
int Window::pixelHeight;
cv::Mat Window::image;

cv::Mat Window::getImage() {
    return image;
}

cv::Vec3b Window::getPixel(const int &x, const int &y) {
    if (x >= 0 && y >= 0 && x < image.rows && y < image.cols) {
        return image.at<cv::Vec3b>(x, y);
    }
    else {
        std::cout << "ERROR: pixel is not within margins." << std::endl;
        return {};
    }
}

void Window::setImage(cv::Mat &newImage) {
    image = newImage;
}

void Window::setPixel(const int &x, const int &y, const cv::Vec3b &color) {
    if (x >= 0 && y >= 0 && x < image.rows && y < image.cols) {
        image.at<cv::Vec3b>(x, y) = color;
    }
    else {
        std::cout << "ERROR: pixel is not within margins." << std::endl;
    }
}

void Window::initializeWindow() {
    pixelWidth = 1366;
    pixelHeight = 768;
    image = cv::Mat(pixelHeight, pixelWidth, CV_8UC3);

    cv::namedWindow("Window", CV_WINDOW_FULLSCREEN);
}

void Window::updateWindow() {

    cv::imshow("Window", image);
    cv::waitKey(1);
}

}