#ifndef CUBE_H
#define CUBE_H

#include "puzzle.h"

namespace tnoodle {

namespace puzzle {

class Cube : public Puzzle {
public:
    Cube();
    char const *getShortName();
    char const *getLongName();
    int getWcaNotSolvableInLtFilter();
    char const *generateFilteredSeededScramble(int notSolvableInLt, int64_t seed);
    char const *drawScramble(char const *scramble);
};

} // puzzle

} // tnoodle

#endif // CUBE_H
