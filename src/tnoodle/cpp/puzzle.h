#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdint.h>

class Puzzle {
    public:
        virtual char const *getShortName() = 0;
        virtual char const *getLongName() = 0;
        virtual int getWcaNotSolvableInLtFilter() = 0;
        virtual char *generateFilteredSeededScramble(int notSolvableInLt, int64_t seed) = 0;
        virtual char *drawScramble(char const *scramble) = 0;
};

#endif // PUZZLE_H
