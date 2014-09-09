libtnoodle
==========

An experimental c/c++ replacement for the scrambling guts of
[cubing/tnoodle](https://github.com/cubing/tnoodle).

** NOTHING IN HERE IS SANCITONED BY THE WCA. NONE OF THIS MAY
BE USED FOR OFFICIAL WCA COMPETITIONS **

## Compiling

I'm trying out gradle for building, rather than a conventional
Makefile. Run `./gradlew tasks` to see a list of commands you
can run. Try out `./gradlew installmymainExecutable` followed
by `build/install/mainExecutable/my/main`.

Current objective is to be able to cross-compile for the big
three operating systems, all from Linux or Travis CI. Right
now, compilation to Windows works with MinGW, but the file
extensions are wrong (no .exe and .so instead of .dll).
