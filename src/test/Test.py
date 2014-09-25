#!/usr/bin/env python3

import unittest

import TNoodleTestLib
import pytnoodle

class TestSequenceFunctions(unittest.TestCase):
    def test_sanity(self):
        cube = pytnoodle.Cube()
        self.assertEqual(cube.getShortName(), '333')
        self.assertEqual(cube.getLongName(), "Rubik's Cube")

        faceNames = cube.getColorSchemeNamesStr().split(",")
        defaultColors = cube.getDefaultColorSchemeStr().split(",")

        self.assertEqual(len(defaultColors), cube.getColorSchemeNamesCount())
        self.assertEqual(len(defaultColors), len(faceNames))
        self.assertEqual(set(faceNames), set("FURBLD"))

        # Sanity test drawing the solved state.
        cube.drawScramble(None, None)

        # Sanity test generating a scramble with the default filter level and
        # then drawing it.
        wcaFilter = cube.getWcaNotSolvableInLtFilter()
        scramble = cube.generateScramble(wcaFilter, 0)
        cube.drawScramble(scramble, "")

    def test_colorSchemeParsing(self):
        cube = pytnoodle.Cube()
        
        # Too many colors
        cube.drawScramble(None, "1,2,3,4,5,6,7,8,9")

        # Too few colors
        cube.drawScramble(None, "1")
        cube.drawScramble(None, "1,,")

if __name__ == '__main__':
    unittest.main()
