#include "tnoodlejni.h"
#include "tnoodle.h"

JNIEXPORT jint JNICALL Java_JTNoodle_summer
  (JNIEnv *jenv, jclass clz) {
    return 2*summer();//<<<
}
