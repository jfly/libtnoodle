libtnoodle [![Build Status](https://travis-ci.org/jfly/libtnoodle.svg?branch=master)](https://travis-ci.org/jfly/libtnoodle)
==========

An experimental C/C++ replacement for the scrambling guts of
[cubing/tnoodle](https://github.com/cubing/tnoodle).

** NOTHING IN HERE IS SANCTIONED BY THE WCA. THIS MUST NOT
BE USED FOR OFFICIAL WCA COMPETITIONS. **

## How to use

See [jtnoodle-demo](https://github.com/jfly/jtnoodle-demo) for an example
project that uses jtnoodle.

## How to develop

### Requirements

- [Swig](http://www.swig.org/) is used to produce the Java (JNI) and Python
  wrappers for our C++ code.
- [Clang](http://clang.llvm.org/) and the JDK are required to compile for Linux.
    - Make sure you install the python libclang bindings. On Fedora 18 with
clang 3.3, I had to run `sudo pip install clang==3.3` ([Read
this](http://stackoverflow.com/questions/9510474/removing-pips-cache) if you
think you installed the wrong version.)

A properly configured Linux machine can cross-compile binaries for Windows and
OS X as well.

- [MinGW-w64](http://mingw-w64.sourceforge.net/) is required to compile to
  compile for Windows.
- [https://github.com/tpoechtrager/osxcross](osxcross) needs to be set up to
  compile for OS X. You must set the MACOSX_DEPLOYMENT_TARGET environment
  variable to 10.9 (MACOSX_DEPLOYMENT_TARGET=10.9)!

If you have trouble setting up a development environment, it might be worth
checking out `.travis.yml`, which has all the commands to set things up for
Travis CI's 64 bit Ubuntu 12.04 environment.

### Building

- `./gradlew jar` produces build/libs/jtnoodle-VERSION.jar.
- `./gradlew run` runs main.cpp (this may be removed in the future).

### Testing

- `./gradlew test` to run python tests.
- If you want to run tests in `src/test/` directly, you need to run `./gradlew
  pytnoodle` first to produce the Swig wrapper code in `build/pytnoodle`.

### Releasing

Travis CI is configured to publish to
http://oss.jfrog.org/oss-snapshot-local/tk/tnoodle/ on each build.

We could investigate manual deployment to `oss-release-local` and promoting
releases to jcenter.

## Components (under src/)

- cnoodle - A pure C/C++ library for generating scrambles. Produces
  `libcnoodle.{so,dll,dylib}`
- jtnoodle - A Java Native Interface (JNI) wrapper for cnoodle. It also
  defines a very basic main() to generate scrambles via the cli. Produces
  `jtnoodle-VERSION.jar`.
- pytnoodle - A Python wrapper for cnoodle. Produces `pytnoodle.py` and
  `_pytnoodle.so` in `build/pytnoodle`. We could investigate publishing this to
  [PyPI](https://pypi.python.org/pypi).
- test - Python tests for cnoodle. Depends on pytnoodle.

## Random musings...

This is an experiment. It remains to be seen how we're going to include a
version of libtnoodle for every major operating system + architecture pair in
jtnoodle.jar so that it *just works* (like the current pure Java tnoodle).

If we succeed at producing a Java desktop app that can work everywhere, then
we can declare this experiment a success, and start porting the Java scrambling code
in tnoodle to libtnoodle. As this port is occurring, we can change tnoodle to depend
on jtnoodle. This way we can reuse the existing webserver/pdf/zip/json generation
infrastructure that we've already written in Java in tnoodle.

## Why?

TNoodle evolved strangly. Generating random turn scrambles for an event like
7x7x7 takes seconds, when it should be instantaneous. This is due to a lot of
infrastructure that was added to aid in scramble filtering. Porting the
scrambling code to C++ gives us a needed excuse to revisit and rewrite.

In addition to needing a rewrite, C++ code gives us the option to run libtnoodle in
as many places as possible.

- Javascript (via Emscripten) - Emscripten does a much better job of producing
efficient Javascript than GWT (the Java to Javascript compiler currently used
by tnoodle).
- Android (via the Android NDK) - This is harder with C++ code than with Java,
but I experimented with the NDK in
[jfly/fskube](https://github.com/jfly/fskube), and determined that it does work well.
- iOS (natively via Objective-C++) - Running Java in iOS is impossible. It
should be easy to compile and run libtnoodle because it is written entirely in
C++.
