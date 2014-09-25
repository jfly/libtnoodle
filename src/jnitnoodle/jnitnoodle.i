%module jtnoodle

%{
#include "cnoodle.h"
%}

%include "stdint.i"

%include "cnoodle.h"

%pragma(java) jniclasscode=%{
  static {
System.out.println("hello world!");//<<<
    try {
        NativeUtils.loadLibrary("jnitnoodle");
    } catch(java.io.IOException e) {
        System.err.println("Native code library failed to load. \n" + e);
        System.exit(1);
    }
  }
%}
