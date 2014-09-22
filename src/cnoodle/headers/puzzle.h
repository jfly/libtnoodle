#ifndef PUZZLE_H
#define PUZZLE_H

#include <random>

#include <stdint.h>

class Puzzle {
    public:
        virtual char const *getShortName() = 0;
        virtual char const *getLongName() = 0;
        virtual int getWcaNotSolvableInLtFilter() = 0;
        virtual char *drawScramble(char const *scramble, char const *colorScheme) = 0;
        virtual char *generateScramble(int notSolvableInLt, std::mt19937& r) = 0;
};

#endif // PUZZLE_H
