%module jtnoodle

%{
#include "cnoodle.h"
%}

# Remove all "tnoodle_" prefixes.
%rename("%(strip:[tnoodle_])s") "";

# Generate compiler constants, rather than runtime constants.
%javaconst(1);


%include "stdint.i"

%include "cnoodle.h"

%pragma(java) jniclasscode=%{
  static {
    try {
        NativeUtils.loadLibrary("jnitnoodle");
    } catch(java.io.IOException e) {
        System.err.println("Native code library failed to load. \n" + e);
        System.exit(1);
    }
  }
%}
