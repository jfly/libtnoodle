#include "puzzle.h"

#include <string.h>

char *Puzzle::generateScramble(int notSolvableInLt, int64_t seed) {
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

char const *Puzzle::getColorScheme() {
    return "red,blue";
}

char const *Puzzle::getColorSchemeNames() {
    return "U,D";
}

char *Puzzle::drawScramble(char const *scramble, char const *colorScheme) {
    char *colorSchemeCopy = strndup(colorScheme, MAX_COLORSCHEME_LENGTH);
    char const **colorSchemeArr = NULL;
    char *svg = drawScramble(scramble, colorSchemeArr);//<<<
    free(colorSchemeCopy);
    return svg;
}

Puzzle::~Puzzle() {};
