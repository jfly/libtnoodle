#ifndef PUZZLE_H
#define PUZZLE_H

#include <random>

#include <stdint.h>

#define MAX_COLORSCHEME_LENGTH (128)
// 777 is 100 moves, each of which is 4 characters, so 1024
// should be plenty large.
#define MAX_SCRAMBLE_LENGTH (1024)

class Puzzle {
    protected:
        virtual char *generateScramble(int notSolvableInLt, std::mt19937& r) = 0;
        virtual char *drawScramble(char const *scramble, char const **colorScheme) = 0;
    public:
        virtual char const *getShortName() = 0;
        virtual char const *getLongName() = 0;
        virtual int getWcaNotSolvableInLtFilter() = 0;
        char const *getColorScheme();
        char const *getColorSchemeNames();
        char *drawScramble(char const *scramble, char const *colorScheme);
        char *generateScramble(int notSolvableInLt, int64_t seed);
        virtual ~Puzzle() = 0;
};

#endif // PUZZLE_H
