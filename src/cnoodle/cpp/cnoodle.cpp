#include "cnoodle.h"
#include "puzzle.h"
#include "cube.h"

#include <random>

int summer() {
    return 42;
}

static Puzzle *puzzles[] = {
    new tnoodle::puzzle::Cube()
};

char const *tnoodle_getShortPuzzleName(int puzzleId) {
    return puzzles[puzzleId]->getShortName();
}

char const *tnoodle_getLongPuzzleName(int puzzleId) {
    return puzzles[puzzleId]->getLongName();
}

int tnoodle_getWcaNotSolvableInLtFilter(int puzzleId) {
    return puzzles[puzzleId]->getWcaNotSolvableInLtFilter();
}

char *tnoodle_generateFilteredSeededScramble(int puzzleId, int notSolvableInLt, int64_t seed) {
    return puzzles[puzzleId]->generateScramble(notSolvableInLt, seed);
}

char *tnoodle_generateFilteredScramble(int puzzleId, int notSolvableInLt) {
    return tnoodle_generateFilteredSeededScramble(puzzleId, notSolvableInLt, 0);
}

char *tnoodle_generateSeededScramble(int puzzleId, int64_t seed) {
    int filter = tnoodle_getWcaNotSolvableInLtFilter(puzzleId);
    return tnoodle_generateFilteredSeededScramble(puzzleId, filter, seed);
}

char *tnoodle_generateScramble(int puzzleId) {
    int filter = tnoodle_getWcaNotSolvableInLtFilter(puzzleId);
    return tnoodle_generateFilteredSeededScramble(puzzleId, filter, 0);
}

char *tnoodle_drawScramble(int puzzleId, char *scramble, char *colorScheme) {
/*
  <<< maroon #800000 red #ff0000 orange #ffA500 yellow #ffff00 olive #808000
purple #800080 fuchsia #ff00ff white #ffffff lime #00ff00 green #008000
navy #000080 blue #0000ff aqua #00ffff teal #008080
black #000000 silver #c0c0c0 gray #808080 >>>
*/
    return puzzles[puzzleId]->drawScramble(scramble, colorScheme);
}

char const *tnoodle_getColorScheme(int puzzleId) {
    return puzzles[puzzleId]->getColorScheme();
}

char const *tnoodle_getColorSchemeNames(int puzzleId) {
    return puzzles[puzzleId]->getColorSchemeNames();
}
