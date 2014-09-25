#include <stdlib.h>

#include "jnitnoodle.h"
#include "cnoodle.h"

JNIEXPORT jstring JNICALL Java_JTNoodle_getShortPuzzleName
  (JNIEnv *jenv, jclass clz, jint puzzleId) {
    char const *shortName = tnoodle_getShortPuzzleName(puzzleId);
    return jenv->NewStringUTF(shortName);
}

JNIEXPORT jstring JNICALL Java_JTNoodle_generateScramble
  (JNIEnv *jenv, jclass clz, jint puzzleId) {
    char const *scramble = tnoodle_generateScramble(puzzleId);
    return jenv->NewStringUTF(scramble);
}
