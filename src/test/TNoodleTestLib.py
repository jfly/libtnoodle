import os
import sys

testDir = os.path.dirname(os.path.realpath(__file__))
pytnoodleDir = os.path.join(testDir, os.pardir, os.pardir, 'build', 'pytnoodle')
sys.path.append(pytnoodleDir)
