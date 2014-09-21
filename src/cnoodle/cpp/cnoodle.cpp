#include "tnoodle.h"
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
    if(seed == 0) {
        static std::mt19937 rand; // TODO - seed from something truly random, such as random_device
        return puzzles[puzzleId]->generateScramble(notSolvableInLt, rand);
    } else {
        std::mt19937 rand(seed);
        return puzzles[puzzleId]->generateScramble(notSolvableInLt, rand);
    }
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

char *tnoodle_drawScramble(int puzzleId, char *scramble) {
    return puzzles[puzzleId]->drawScramble(scramble);
}
