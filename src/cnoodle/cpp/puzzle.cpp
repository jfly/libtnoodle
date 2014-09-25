#include "puzzle.h"

#include <string.h>

Puzzle::~Puzzle() {}

static void join(char separator, char const **arr, size_t arrLen, char *dst, size_t dstSize) {
    size_t written = 0;
    for(size_t i = 0; i < arrLen && written < dstSize; i++) {
        char const *str = arr[i];
        if(i > 0) {
            dst[written++] = separator;
        }
        written += snprintf(dst + written, dstSize - written, "%s", str);
    }
}

char const *Puzzle::getDefaultColorSchemeStr() {
    if(!defaultColorSchemeStrInitialized) {
        join(',', getDefaultColorScheme(), getColorSchemeNamesCount(),
                defaultColorSchemeStr, MAX_COLORSCHEME_LENGTH + 1);
        defaultColorSchemeStrInitialized = true;
    }
    return defaultColorSchemeStr;
}

char const *Puzzle::getColorSchemeNamesStr() {
    if(!colorSchemeNamesStrInitialized) {
        join(',', getColorSchemeNames(), getColorSchemeNamesCount(),
                colorSchemeNamesStr, MAX_COLORSCHEME_LENGTH + 1);
        colorSchemeNamesStrInitialized = true;
    }
    return colorSchemeNamesStr;
}

char *Puzzle::generateScramble(unsigned int notSolvableInLt, int64_t seed) {
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

char *Puzzle::drawScramble(char const *scramble, char const *colorScheme) {
    char const **defaultColorScheme = getDefaultColorScheme();
    if(colorScheme == NULL || colorScheme[0] == '\0') {
        // If the user passed in NULL or empty string, use the default
        // color scheme.
        return drawScramble(scramble, defaultColorScheme);
    }

    size_t len = strnlen(colorScheme, MAX_COLORSCHEME_LENGTH);
    char colorSchemeCopy[len + 1];
    strncpy(colorSchemeCopy, colorScheme, len);
    colorSchemeCopy[len] = '\0';

    char const *colorSchemeArr[getColorSchemeNamesCount()];
    size_t colorIndex = 0;

    // Split colorSchemeCopy up into multiple strings by turning each
    // comma into a null terminator. Populate colorSchemeArr with pointers
    // to each of these new strings.
    colorSchemeArr[colorIndex++] = colorSchemeCopy;
    for(size_t i = 0; i < len && colorIndex < getColorSchemeNamesCount(); i++) {
        if(colorSchemeCopy[i] == ',') {
            colorSchemeCopy[i] = '\0';
            colorSchemeArr[colorIndex++] = colorSchemeCopy + i + 1;
        }
    }

    // If we didn't fill up colorSchemeArr, fill the remaining entries with empty string
    while(colorIndex < getColorSchemeNamesCount()) {
        colorSchemeArr[colorIndex++] = "";
    }

    return drawScramble(scramble, colorSchemeArr);
}
