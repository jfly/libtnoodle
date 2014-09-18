#include <stdlib.h>

#include "tnoodlejni.h"
#include "tnoodle.h"

JNIEXPORT jint JNICALL Java_JTNoodle_summer
  (JNIEnv *jenv, jclass clz) {
    char *scramble = tnoodle_generateScramble(0);
    printf("a scramble!: %s\n", scramble);//<<<
    free(scramble);
    return 2*summer();//<<<
}
