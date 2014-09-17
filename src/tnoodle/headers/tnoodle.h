#ifndef TNOODLE_H
#define TNOODLE_H

#include <stdint.h>

extern "C" {

int summer();

// TODO - initialization? thread safety?
// TODO - color schemes?
// TODO - get a list of all puzzles? maybe not that useful...

/* 
 * Returns the short puzzle name for puzzleId.
 * This is "333" instead of "Rubik's Cube".
 */
char const *tnoodle_getShortPuzzleName(int puzzleId);

/* 
 * Returns the "long" (human friendly) puzzle name for puzzleId.
 * This is "Rubik's Cube" instead of "333".
 */
char const *tnoodle_getLongPuzzleName(int puzzleId);

/*
 * Returns a filter limit that could be passed into tnoodle_generateFilteredScramble().
 *         See https://www.worldcubeassociation.org/regulations/#4b3.
 */
int tnoodle_getWcaNotSolvableInLtFilter(int puzzleId);

/*
 * puzzleId - see tnoodle_getShortPuzzleNames()
 * notSolvableInLt - Require that the generated scramble 
 *                   produces a state that is not solvable in less
 *                   than notSolvableInLt moves. Therefore, a value
 *                   of 0 means no filtering. The smaller this number,
 *                   the faster this function will run.
 * seed - If nonzero, seed the random number generator for a 
 *        reproducible scramble.
 *
 * Returns a string containing a scramble for the given puzzle that
 *         could be passed to drawScramble() to generate an SVG
 */
char const *tnoodle_generateFilteredSeededScramble(int puzzleId, int notSolvableInLt, int64_t seed);

/*
 * Delegates to tnoodle_generateFilteredSeededScramble()
 */
char const *tnoodle_generateFilteredScramble(int puzzleId, int notSolvableInLt);

/*
 * Delegates to tnoodle_generateFilteredSeededScramble()
 */
char const *tnoodle_generateSeededScramble(int puzzleId, int64_t seed);

/*
 * Delegates to tnoodle_generateFilteredSeededScramble()
 */
char const *tnoodle_generateScramble(int puzzleId);

/*
 * puzzleId - see tnoodle_getShortPuzzleNames()
 * scramble - turns to apply to solved puzzle
 *
 * Returns a string containing an SVG image.
 */
char const *tnoodle_drawScramble(int puzzleId, char *scramble);

}

#endif // TNOODLE_H
