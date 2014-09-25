#ifndef PUZZLE_H
#define PUZZLE_H

#include <random>

#include <stdint.h>

#define MAX_COLORSCHEME_LENGTH (128 - 1)
// 777 is 100 moves, each of which is 4 characters, so this should be plenty large.
#define MAX_SCRAMBLE_LENGTH (1024 - 1)

class Puzzle {
    protected:
        virtual char *generateScramble(unsigned int notSolvableInLt, std::mt19937& r) = 0;
        virtual char *drawScramble(char const *scramble, char const **colorScheme) = 0;
        virtual char const **getDefaultColorScheme() = 0;
        virtual char const **getColorSchemeNames() = 0;
        virtual size_t getColorSchemeNamesCount() = 0;
    private:
        char defaultColorSchemeStr[MAX_COLORSCHEME_LENGTH + 1];
        char defaultColorSchemeStrInitialized = false;
        char colorSchemeNamesStr[MAX_COLORSCHEME_LENGTH + 1];
        char colorSchemeNamesStrInitialized = false;
    public:
        virtual ~Puzzle() = 0;

        char const *getDefaultColorSchemeStr();
        char const *getColorSchemeNamesStr();
        char *drawScramble(char const *scramble, char const *colorScheme);
        char *generateScramble(unsigned int notSolvableInLt, int64_t seed);

        virtual char const *getShortName() = 0;
        virtual char const *getLongName() = 0;
        virtual unsigned int getWcaNotSolvableInLtFilter() = 0;
};

#endif // PUZZLE_H
