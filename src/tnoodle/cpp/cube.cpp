#include "cube.h"

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

char *Cube::generateFilteredSeededScramble(int notSolvableInLt, int64_t seed) {
    return "R2 R2 R2";//<<< TODO - put in heap?
}

char *Cube::drawScramble(char const *scramble) {
    return "<svg></svg>";//<<< TODO - put in heap?
}

} // puzzle

} // tnoodle
