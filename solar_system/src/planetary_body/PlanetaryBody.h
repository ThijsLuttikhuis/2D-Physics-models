//
// Created by thijs on 27-12-18.
//

#ifndef SOLARSYSTEM_PLANETARYBODY_H
#define SOLARSYSTEM_PLANETARYBODY_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <memory>


namespace solarSystem {
namespace planetaryBody {

class PlanetaryBody {
    public:
        struct Vector2 {
          double x;
          double y;
        };
        struct Vector2int {
          int x;
          int y;
        };

    private:
        using bodyPtr = std::shared_ptr<PlanetaryBody>;
        std::string name;
        double mass;
        double radius;
        Vector2 pos;
        Vector2 vel;
        Vector2 force;
        cv::Vec3b color;
        const double G = 6.67e-11;

    public:
        PlanetaryBody() = default;

        PlanetaryBody(const std::string &n, const double &m, const double &r, const Vector2 &p, const Vector2 &v,
                const cv::Vec3b &c) {
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

        void setForce(const Vector2 &f) {
            force = f;
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

        double getG() {
            return G;
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

        Vector2 getForce() {
            return force;
        }

        cv::Vec3b getColor() {
            return color;
        }

        void updateVelocity(const double &dt) {
            vel.x = vel.x + dt*force.x/mass;
            vel.y = vel.y + dt*force.y/mass;
        }

        void updatePosition(const double &dt) {
            pos.x = pos.x + dt*vel.x;
            pos.y = pos.y + dt*vel.y;
        }

        void updateForces(std::vector<bodyPtr> &bodies) {
            for (auto &body : bodies) {
                Vector2 f = {0,0};
                body->setForce(f);
            }
            for (auto first = bodies.begin(); first < bodies.end(); first ++) {
                for (auto second = first + 1; second < bodies.end(); second ++) {
                    Vector2 r = {second->get()->getPosition().x - first->get()->getPosition().x,
                                 second->get()->getPosition().y - first->get()->getPosition().y};
                    double dist = sqrt(r.x*r.x + r.y*r.y);
                    double gmmDivDist =
                            second->get()->getG()*second->get()->getMass()*first->get()->getMass()/(dist*dist);
                    Vector2 f = {gmmDivDist*r.x/dist, gmmDivDist*r.y/dist};

                    Vector2 secondForce = {second->get()->getForce().x - f.x, second->get()->getForce().y - f.y};
                    second->get()->setForce(secondForce);

                    Vector2 firstForce = {first->get()->getForce().x + f.x, first->get()->getForce().y + f.y};
                    first->get()->setForce(firstForce);
                };
            }

        }

        Vector2 getCenterOfMass(const std::vector<bodyPtr> &bodies) {
            Vector2 centerOfMass = {0, 0};
            double totalMass = 0;

            for (auto &body : bodies) {
                double bodyMass = body->getMass();
                Vector2 bodyPos = body->getPosition();
                centerOfMass.x += bodyPos.x*bodyMass;
                centerOfMass.y += bodyPos.y*bodyMass;
                totalMass += bodyMass;
            }
            return {centerOfMass.x/totalMass, centerOfMass.y/totalMass};
        }

        double getFurthestObject(const std::vector<bodyPtr> &bodies, Vector2 relativeToPos) {
            double distanceSquared = 0;

            for (auto &body : bodies) {
                double dx = body->pos.x - relativeToPos.x;
                double dy = body->pos.y - relativeToPos.y;
                if (dx*dx + dy*dy > distanceSquared) {
                    distanceSquared = dx*dx + dy*dy;

                }
            }
            return sqrt(distanceSquared);
        }

};

} //window
} //solarSystem

#endif //SOLARSYSTEM_PLANETARYBODY_H
