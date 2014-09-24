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
                static std::random_device trueRandom;
                // Unfortunately, there is no good way of checking if
                // trueRandom is truly random. The entropy() method is
                // supposed to tell us, but according to
                // http://en.cppreference.com/w/cpp/numeric/random/random_device/entropy,
                // it returns 0 even on platforms that do give us truly random
                // numbers. Checking via strace and gdb, I was unable to verify
                // that std::random_device is accessing /dev/random on my t410
                // running 64 bit arch linux. It is possible that it calls
                // http://en.wikipedia.org/wiki/RdRand instead.
                static std::mt19937 rand(trueRandom());
                return generateScramble(notSolvableInLt, rand);
            } else {
                std::mt19937 rand(seed);
                return generateScramble(notSolvableInLt, rand);
            }
        }
};

#endif // PUZZLE_H
