#ifndef PUZZLE_H
#define PUZZLE_H

#include <random>

#include <stdint.h>

class Puzzle {
    protected:
        virtual char *generateScramble(int notSolvableInLt, std::mt19937& r) = 0;
    public:
        virtual char const *getShortName() = 0;
        virtual char const *getLongName() = 0;
        virtual int getWcaNotSolvableInLtFilter() = 0;
        virtual char *drawScramble(char const *scramble, char const *colorScheme) = 0;
        inline char *generateScramble(int notSolvableInLt, int seed) {
            if(seed == 0) {
                static std::mt19937 rand; // TODO - seed from something truly random, such as random_device
                return generateScramble(notSolvableInLt, rand);
            } else {
                std::mt19937 rand(seed);
                return generateScramble(notSolvableInLt, rand);
            }
        }
};

#endif // PUZZLE_H
