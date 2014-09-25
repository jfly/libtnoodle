#ifndef CUBE_H
#define CUBE_H

#include "puzzle.h"

#include <random>

namespace tnoodle {

namespace puzzle {

class Cube : public Puzzle {
protected:
    char *generateScramble(unsigned int notSolvableInLt, std::mt19937& r);
    char *drawScramble(char const *scramble, char const **colorScheme);
    char const **getDefaultColorScheme();
    char const **getColorSchemeNames();
public:
    Cube();
    ~Cube();
    char const *getShortName();
    char const *getLongName();
    unsigned int getWcaNotSolvableInLtFilter();
    size_t getColorSchemeNamesCount();
};

} // puzzle

} // tnoodle

#endif // CUBE_H
