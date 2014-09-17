#include "tnoodle.h"
#include "puzzle.h"
#include "cube.h"

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

char const *tnoodle_generateFilteredSeededScramble(int puzzleId, int notSolvableInLt, int64_t seed) {
    return puzzles[puzzleId]->generateFilteredSeededScramble(notSolvableInLt, seed);
}

char const *tnoodle_generateFilteredScramble(int puzzleId, int notSolvableInLt) {
    return tnoodle_generateFilteredSeededScramble(puzzleId, notSolvableInLt, 0);
}

char const *tnoodle_generateSeededScramble(int puzzleId, int64_t seed) {
    int filter = tnoodle_getWcaNotSolvableInLtFilter(puzzleId);
    return tnoodle_generateFilteredSeededScramble(puzzleId, filter, seed);
}

char const *tnoodle_generateScramble(int puzzleId) {
    int filter = tnoodle_getWcaNotSolvableInLtFilter(puzzleId);
    return tnoodle_generateFilteredSeededScramble(puzzleId, filter, 0);
}

char const *tnoodle_drawScramble(int puzzleId, char *scramble) {
    return puzzles[puzzleId]->drawScramble(scramble);
}
