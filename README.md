libtnoodle [![Build Status](https://travis-ci.org/jfly/libtnoodle.svg?branch=master)](https://travis-ci.org/jfly/libtnoodle)
==========

An experimental C/C++ replacement for the scrambling guts of
[cubing/tnoodle](https://github.com/cubing/tnoodle).

** NOTHING IN HERE IS SANCTIONED BY THE WCA. THIS MUST NOT
BE USED FOR OFFICIAL WCA COMPETITIONS. **

## How to use

See [jtnoodle-demo](https://github.com/jfly/jtnoodle-demo) for an example
project that uses jtnoodle.

## Compiling

### Requirements

A properly configured Linux machine can compile binaries for Linux, Windows, and OS X.
Here's a (likely incomplete) list of dependencies.

- [Clang](http://clang.llvm.org/) and the JDK are required to compile for Linux.
- [MinGW-w64](http://mingw-w64.sourceforge.net/) is required to compile to
  compile for Windows.
- [https://github.com/tpoechtrager/osxcross](osxcross) needs to be set up to
  compile for OS X. You must set the MACOSX_DEPLOYMENT_TARGET environment
  variable to 10.9 (MACOSX_DEPLOYMENT_TARGET=10.9)!

### Commands

- `./gradlew jar` produces build/libs/jtnoodle-VERSION.jar.
- `./gradlew run` runs main.cpp (this may be removed in the future).

## Testing

### Requirements

- [Swig](http://www.swig.org/) is used to produce a Python wrapper for our C++ code.

### Commands

- `./gradlew test` to run python tests.
- `./gradlew pytnoodle` will produce Swig wrapper code in `build/pytnoodle`.

## Releasing

Travis CI is configured to publish to
http://oss.jfrog.org/oss-snapshot-local/tk/tnoodle/ on each build.

We could investigate manual deployment to `oss-release-local` and promoting
releases to jcenter.

## Components (under src/)

- libtnoodle - A pure C/C++ library for generating scrambles. Produces
  libtnoodle.{so,dll,dylib}
- jtnoodle - A pure Java library that simply wraps tnoodle. It also defines a
  very basic main() to generate scrambles via the cli. Depends on libtnoodle,
  produces jtnoodle.jar.

## TODO

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
