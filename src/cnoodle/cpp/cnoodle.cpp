#include "cnoodle.h"
#include "puzzle.h"
#include "cube.h"

#include <assert.h>

static Puzzle *puzzles[MAX_PUZZLEID + 1] = { NULL };

static bool initialize() {
    puzzles[PUZZLE_333] = new tnoodle::puzzle::Cube();
    puzzles[PUZZLE_222] = new tnoodle::puzzle::Cube();
    return true;
}
static bool initialized = initialize();

bool tnoodle_isValidPuzzleId(int puzzleId) {
    if(puzzleId < MIN_PUZZLEID || puzzleId > MAX_PUZZLEID) {
        return false;
    }
    return puzzles[puzzleId] != NULL;
}

char const *tnoodle_getShortPuzzleName(int puzzleId) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    return puzzles[puzzleId]->getShortName();
}

char const *tnoodle_getLongPuzzleName(int puzzleId) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    return puzzles[puzzleId]->getLongName();
}

unsigned int tnoodle_getWcaNotSolvableInLtFilter(int puzzleId) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    return puzzles[puzzleId]->getWcaNotSolvableInLtFilter();
}

char *tnoodle_generateFilteredSeededScramble(int puzzleId, unsigned int notSolvableInLt, int64_t seed) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    return puzzles[puzzleId]->generateScramble(notSolvableInLt, seed);
}

char *tnoodle_generateFilteredScramble(int puzzleId, unsigned int notSolvableInLt) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    return tnoodle_generateFilteredSeededScramble(puzzleId, notSolvableInLt, 0);
}

char *tnoodle_generateSeededScramble(int puzzleId, int64_t seed) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    unsigned int filter = tnoodle_getWcaNotSolvableInLtFilter(puzzleId);
    return tnoodle_generateFilteredSeededScramble(puzzleId, filter, seed);
}

char *tnoodle_generateScramble(int puzzleId) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    unsigned int filter = tnoodle_getWcaNotSolvableInLtFilter(puzzleId);
    return tnoodle_generateFilteredSeededScramble(puzzleId, filter, 0);
}

char *tnoodle_drawScramble(int puzzleId, char *scramble, char *colorScheme) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    return puzzles[puzzleId]->drawScramble(scramble, colorScheme);
}

char const *tnoodle_getDefaultColorScheme(int puzzleId) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    return puzzles[puzzleId]->getDefaultColorSchemeStr();
}

char const *tnoodle_getColorSchemeNames(int puzzleId) {
    assert(tnoodle_isValidPuzzleId(puzzleId));
    return puzzles[puzzleId]->getColorSchemeNamesStr();
}
