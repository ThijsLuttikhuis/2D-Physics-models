//
// Created by Thijs on 02/03/2019.
//

#ifndef SOLARSYSTEM_COLOR_H
#define SOLARSYSTEM_COLOR_H

namespace solarSystem {
namespace window {


class Color {
    public:
        constexpr Color()
                :red(0), green(0), blue(0), alpha(0) {}
        constexpr Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
                :red(red), green(green), blue(blue), alpha(alpha) {}

        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char alpha;
};

}
}
#endif //SOLARSYSTEM_COLOR_H
