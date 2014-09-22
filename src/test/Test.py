#!/usr/bin/env python3

import unittest

import TNoodleTestLib
import pytnoodle

class TestSequenceFunctions(unittest.TestCase):
    def test_sanity(self):
        self.assertEqual(pytnoodle.summer(), 42)

        cube = pytnoodle.Cube()
        self.assertEqual(cube.getShortName(), '333')

if __name__ == '__main__':
    unittest.main()
