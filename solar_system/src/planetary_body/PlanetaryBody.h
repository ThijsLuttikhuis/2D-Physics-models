//
// Created by thijs on 27-12-18.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

#ifndef SOLARSYSTEM_PLANETARYBODY_H
#define SOLARSYSTEM_PLANETARYBODY_H

namespace solarSystem {
namespace planetaryBody {

class PlanetaryBody {

    public:
        struct Vector2 {
          double x;
          double y;
        };

    private:
        std::string name;
        double mass;
        double radius;
        Vector2 pos;
        Vector2 vel;
        cv::Vec3b color;

    public:
        PlanetaryBody() = default;

        PlanetaryBody(const std::string &n, const double &m, const double &r, const Vector2 &p, const Vector2 &v, const cv::Vec3b &c) {
            name = n;

            if (m > 0) mass = m;
            else std::cout << "ERROR: mass is negative." << std::endl;

            if (r > 0) radius = r;
            else std::cout << "ERROR: radius is negative." << std::endl;

            pos = p;
            vel = v;
            color = c;
        }

        void setName(const std::string &n) {
            name = n;
        }

        void setMass(const double &m) {
            if (m > 0) mass = m;
            else std::cout << "ERROR: mass is negative." << std::endl;
        }

        void setRadius(const double &r) {
            if (r > 0) radius = r;
            else std::cout << "ERROR: radius is negative." << std::endl;
        }

        void setPosition(const Vector2 &p) {
            pos = p;
        }

        void setVelocity(const Vector2 &v) {
            vel = v;
        }

        void setColor(const cv::Vec3b &c) {
            color = c;
        }

        std::string getName() {
            return name;
        }

        double getMass() {
            return mass;
        }

        double getRadius() {
            return radius;
        }

        Vector2 getPosition() {
            return pos;
        }

        Vector2 getVelocity() {
            return vel;
        }

        cv::Vec3b getColor() {
            return color;
        }


};

} //window
} //solarSystem

#endif //SOLARSYSTEM_PLANETARYBODY_H
