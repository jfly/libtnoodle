#include <random>

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
    // TODO - there's probably a nicer way to do this...
    std::mt19937 *r = NULL;
    if(seed == 0) {
        static std::mt19937 rand; // TODO - seed from something truly random, such as random_device
        r = &rand;
    } else {
        std::mt19937 rand(seed);
        r = &rand;
    }
    printf("yo! generateFilteredSeededScramble %d\n", (*r)());//<<<
    return "R2 R2 R2";//<<< TODO - put in heap?
}

char *Cube::drawScramble(char const *scramble) {
    return "<svg></svg>";//<<< TODO - put in heap?
}

} // puzzle

} // tnoodle
