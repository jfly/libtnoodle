#include <stdlib.h>

#include "jnitnoodle.h"
#include "cnoodle.h"

JNIEXPORT jint JNICALL Java_JTNoodle_summer
  (JNIEnv *jenv, jclass clz) {
    char *scramble = tnoodle_generateScramble(0);
    printf("a scramble!: %s\n", scramble);//<<<
    free(scramble);
    return 2*summer();//<<<
}
