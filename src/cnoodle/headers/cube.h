#ifndef CUBE_H
#define CUBE_H

#include "puzzle.h"

#include <random>

namespace tnoodle {

namespace puzzle {

class Cube : public Puzzle {
public:
    Cube();
    char const *getShortName();
    char const *getLongName();
    int getWcaNotSolvableInLtFilter();
    char *generateScramble(int notSolvableInLt, std::mt19937& r);
    char *drawScramble(char const *scramble, char const **colorScheme);
};

} // puzzle

} // tnoodle

#endif // CUBE_H
