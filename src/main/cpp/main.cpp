#include <stdio.h>
#include "cnoodle.h"

int main() {
    printf("%s scramble: %s\n", tnoodle_getShortPuzzleName(0), tnoodle_generateScramble(0));
}
