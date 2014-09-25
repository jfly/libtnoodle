#ifndef CNOODLE_H
#define CNOODLE_H

#include <stdint.h>

extern "C" {

// TODO - get a list of all puzzles? maybe not that useful...
// TODO - can swig generate java constants for us?

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
unsigned int tnoodle_getWcaNotSolvableInLtFilter(int puzzleId);

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
 *         could be passed to drawScramble() to generate an SVG.
 *         The returned pointer can be passed to free().
 */
char *tnoodle_generateFilteredSeededScramble(int puzzleId, unsigned int notSolvableInLt, int64_t seed);

/*
 * Delegates to tnoodle_generateFilteredSeededScramble()
 */
char *tnoodle_generateFilteredScramble(int puzzleId, unsigned int notSolvableInLt);

/*
 * Delegates to tnoodle_generateFilteredSeededScramble()
 */
char *tnoodle_generateSeededScramble(int puzzleId, int64_t seed);

/*
 * Delegates to tnoodle_generateFilteredSeededScramble()
 */
char *tnoodle_generateScramble(int puzzleId);

/*
 * puzzleId - see tnoodle_getShortPuzzleNames()
 * scramble - turns to apply to solved puzzle. If longer than
 *            MAX_SCRAMBLE_LENGTH, this function must not crash, but
 *            its behavior is undefined.
 * colorScheme - the color scheme to use, see tnoodle_getDefaultColorScheme(). If this
 *               contains the wrong number of colors, invalid color names, or
 *               is longer than MAX_COLORSCHEME_LENGTH, this function must not
 *               crash, but its behavior is undefined.
 *
 * Returns a string containing an SVG image. The returned pointer can be passed
 *         to free().
 */
char *tnoodle_drawScramble(int puzzleId, char *scramble, char *colorScheme);

/*
 * Returns the default color scheme for the given puzzle. The color scheme is
 * represented as a comma separated string of colors. Each color must be a valid
 * SVG color, see http://www.w3.org/TR/SVG/types.html#DataTypeColor.
 */
char const *tnoodle_getDefaultColorScheme(int puzzleId);

/*
 * Returns the names of the various colorable parts of this puzzle (on most
 * puzzles, "parts" means "faces"). This is a comma separated
 * string that must contain the same number of commas as the string returned by
 * tnoodle_getDefaultColorScheme(). Consequently, none of the names may contain
 * commas.
 */
char const *tnoodle_getColorSchemeNames(int puzzleId);

}

#endif // CNOODLE_H
