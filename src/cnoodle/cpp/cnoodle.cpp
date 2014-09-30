#include "cnoodle.h"
#include "puzzle.h"
#include "cube.h"

static Puzzle *puzzles[MAX_PUZZLEID + 1] = {
    new tnoodle::puzzle::Cube(),
    new tnoodle::puzzle::Cube()
};

//<<<puzzles[PUZZLE_333] = new tnoodle::puzzle::Cube(3);
//<<<puzzles[PUZZLE_222] = new tnoodle::puzzle::Cube(2);

char const *tnoodle_getShortPuzzleName(int puzzleId) {
    return puzzles[puzzleId]->getShortName();
}

char const *tnoodle_getLongPuzzleName(int puzzleId) {
    return puzzles[puzzleId]->getLongName();
}

unsigned int tnoodle_getWcaNotSolvableInLtFilter(int puzzleId) {
    return puzzles[puzzleId]->getWcaNotSolvableInLtFilter();
}

char *tnoodle_generateFilteredSeededScramble(int puzzleId, unsigned int notSolvableInLt, int64_t seed) {
    return puzzles[puzzleId]->generateScramble(notSolvableInLt, seed);
}

char *tnoodle_generateFilteredScramble(int puzzleId, unsigned int notSolvableInLt) {
    return tnoodle_generateFilteredSeededScramble(puzzleId, notSolvableInLt, 0);
}

char *tnoodle_generateSeededScramble(int puzzleId, int64_t seed) {
    unsigned int filter = tnoodle_getWcaNotSolvableInLtFilter(puzzleId);
    return tnoodle_generateFilteredSeededScramble(puzzleId, filter, seed);
}

char *tnoodle_generateScramble(int puzzleId) {
    unsigned int filter = tnoodle_getWcaNotSolvableInLtFilter(puzzleId);
    return tnoodle_generateFilteredSeededScramble(puzzleId, filter, 0);
}

char *tnoodle_drawScramble(int puzzleId, char *scramble, char *colorScheme) {
    return puzzles[puzzleId]->drawScramble(scramble, colorScheme);
}

char const *tnoodle_getDefaultColorScheme(int puzzleId) {
    return puzzles[puzzleId]->getDefaultColorSchemeStr();
}

char const *tnoodle_getColorSchemeNames(int puzzleId) {
    return puzzles[puzzleId]->getColorSchemeNamesStr();
}
