#include "cube.h"

#include <random>
#include <iostream>

#include <string.h>

namespace tnoodle {

namespace puzzle {

Cube::Cube() {}

char const *Cube::getShortName() {
    return "333";
}

char const *Cube::getLongName() {
    return "Rubik's Cube";
}

int Cube::getWcaNotSolvableInLtFilter() {
    return 4242;//<<<
}

char *Cube::generateScramble(int notSolvableInLt, std::mt19937& r) {
    std::cout << "yo! generateFilteredSeededScramble " << r() << std::endl;//<<<
    return strdup("R2 R2 R2");
}

char *Cube::drawScramble(char const *scramble, char const *colorScheme) {
    return strdup("<svg></svg>");
}

} // puzzle

} // tnoodle
