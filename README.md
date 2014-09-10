libtnoodle
==========

An experimental c/c++ replacement for the scrambling guts of
[cubing/tnoodle](https://github.com/cubing/tnoodle).

** NOTHING IN HERE IS SANCTIONED BY THE WCA. THIS MUST NOT
BE USED FOR OFFICIAL WCA COMPETITIONS. **

## Compiling

I'm trying out gradle for building, rather than a conventional
Makefile. Run `./gradlew tasks` to see a list of commands you
can run. Try out `./gradlew installmymainExecutable` followed
by `build/install/mainExecutable/my/main`.

Current objective is to be able to cross-compile for the big
three operating systems, all from Linux or Travis CI. Right
now, compilation to Windows works with MinGW, but the file
extensions are wrong (no .exe and .so instead of .dll).

- `./gradlew jtnoodleClasses` - compile jtnoodle
- `./gradlew linux_x64tnoodlejniSharedLibrary` - compile shared library libjtnoodle.

## Components (under src/)

- libtnoodle - A pure C/C++ library for generating scrambles. Produces
  libtnoodle.{so,dll,dylib}
- jtnoodle - A pure Java library that simply wraps tnoodle. It also defines a
  very basic main() to generate scrambles via the cli. Depends on libtnoodle,
  produces jtnoodle.jar.

## TODO

This is an experiment. It remains to be seen how we're going to include a
version of libtnoodle for every major operating system + architecture pair in
jtnoodle.jar so that it *just works* (like the current pure Java TNoodle).

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

LD_LIBRARY_PATH=build/binaries/tnoodlejniSharedLibrary/linux_x64 java -cp build/classes/jtnoodle Main
