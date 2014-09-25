#include "cube.h"

#include <random>
#include <iostream>

#include <string.h>

namespace tnoodle {

namespace puzzle {

#define NUM_FACES 6
static char const *colorSchemeNames[NUM_FACES] =   { "R",   "U",     "F",     "L",      "D",      "B" };
static char const *defaultColorScheme[NUM_FACES] = { "red", "white", "green", "orange", "yellow", "blue" };

Cube::Cube() {}
Cube::~Cube() {}

char const *Cube::getShortName() {
    return "333";
}

char const *Cube::getLongName() {
    return "Rubik's Cube";
}

unsigned int Cube::getWcaNotSolvableInLtFilter() {
    return 2;
}

char *Cube::generateScramble(unsigned int notSolvableInLt, std::mt19937& r) {
    return strdup("R2 R2 R2");
}

char *Cube::drawScramble(char const *scramble, char const **colorScheme) {
    return strdup("<svg></svg>");
}

size_t Cube::getColorSchemeNamesCount() {
    return NUM_FACES;
}

char const **Cube::getColorSchemeNames() {
    return colorSchemeNames;
}

char const **Cube::getDefaultColorScheme() {
    return defaultColorScheme;
}

} // puzzle

} // tnoodle
