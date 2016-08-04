# Match up undefined functions to other compilation units.

import os
import sys
import fnmatch
import subprocess
import cPickle as pickle
import linuxinstance
import kmaxdata
import lockfile # pip install lockfile or install from
                # https://github.com/smontanaro/pylockfile.git
import tempfile
import csv
import zlib
import threading
import Queue
import argparse
from collections import namedtuple

version = "4.0"
arch = "x86"

functions_datafile = kmaxdata.functions_datafile(version, arch)
functions_pc_datafile = kmaxdata.functions_pc_datafile(version, arch)

functions = {}

class Links:
  def __init__(self, bdd, links):
    self.bdd = bdd
    self.links = links

class Fields:
  def __init__(self):
    self.global_fundefs = {}
    self.undef_funcalls = {}

unit = ""
i = 0

sys.stderr.write("analyzing functions\n")
for line in open(functions_datafile):
  with open(functions_pc_datafile, 'rb') as pcf:
    i += 1
    if line.startswith("compilation_unit "):
      unit = line.split(" ", 1)[1].strip()
      functions[unit] = Fields()
    elif line.startswith("global_fundef") or line.startswith("undef_funcall"):
      a = line.strip().split(' ')
      field = a[0]
      funname = a[1]
      pc_start = int(a[2])
      pc_len = int(a[3])
      pcf.seek(pc_start, os.SEEK_SET)
      pc_decompressed = zlib.decompress(pcf.read(pc_len))
      # sys.stdout.write('%s %s %s\n' % (field, funname, pc_decompressed))
      if line.startswith("global_fundef "):
        functions[unit].global_fundefs[funname] = pc_decompressed
      elif line.startswith("undef_funcall "):
        functions[unit].undef_funcalls[funname] = pc_decompressed
    if i == 500000:
      break

sys.stderr.write("finding links\n")
links = {}
for unit in functions.keys():
  linked = set()
  for undef_funcall in functions[unit].undef_funcalls.keys():
    for linked_unit in functions.keys():
      if undef_funcall in functions[linked_unit].global_fundefs.keys():
        linked.add(linked_unit, undef_funcall)
    links[unit] = Links("", linked)
  print "links %s %s" % (unit, ",".join(linked))
