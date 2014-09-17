#include "tnoodlejni.h"
#include "tnoodle.h"

JNIEXPORT jint JNICALL Java_JTNoodle_summer
  (JNIEnv *jenv, jclass clz) {
    printf("a scramble!: %s\n", tnoodle_generateScramble(0));//<<<
    return 2*summer();//<<<
}
