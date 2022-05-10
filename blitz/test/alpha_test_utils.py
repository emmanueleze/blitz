
import unittest, os, sys



def load(filename):
  #load source code
  source = open(filename + '.cc').read()
  