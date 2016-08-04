# Kmax
# Copyright (C) 2012-2015 Paul Gazzillo
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import os
import sys
import fnmatch
import subprocess
import cPickle as pickle
import kmaxdata
import linuxinstance
from enum import Enum  # requires enum34: pip install enum34
import random
import argparse

# Validate SuperC's preprocessor and parser by comparing their output
# to gcc -E for all compilation units under the Linux configuration.

argparser = argparse.ArgumentParser(
    formatter_class=argparse.RawDescriptionHelpFormatter,
    description="""\
Collect preprocessor and parser statistics and perform dynamic analysis
    """,
    epilog="""\
    """
    )
argparser.add_argument('version',
                       type=str,
                       help="""the git tag name of the Linux version""")
argparser.add_argument('arch',
                       type=str,
                       help="""the arch subdirectory name of the architecture.  passing 'x86' will
automatically switch to i386 for pre-2.6.24 kernels.""")
argparser.add_argument('--preprocessor',
                       action='store_true',
                       help="""test the preprocessor only.""")
argparser.add_argument('--parser',
                       action='store_true',
                       help="""test the parser only.""")
argparser.add_argument('-a',
                       '--all-units',
                       action='store_true',
                       help="""don't skip tests that already passed.""")
argparser.add_argument('-r',
                       '--randomize',
                       action='store_true',
                       help="""randomize the list of compilation units.""")
args = argparser.parse_args()

version = args.version
arch = args.arch
skip_passed = not args.all_units
test_components = []
test_both = not args.preprocessor and not args.parser
if args.preprocessor or test_both:
  test_components.append("preprocessor")
if args.parser or test_both:
  test_components.append("parser")
randomize_list = args.randomize

# print version
# print arch
# print skip_passed
# print test_components
# print randomize_list
# exit(1)

TestStatus = Enum("TestStatus", "succeeded failed terminated")

def has_passed(cu):
  return False

instance = linuxinstance.LinuxInstance()
instance.enter(version)
instance.init_arch(arch)

# Read pickled data object
with open(kmaxdata.compilation_units_datafile(version, arch), "rb") as f:
  compilation_units = f.readlines()

if randomize_list:
  random.shuffle(compilation_units)

compilation_units_status = {}

superc_args = linuxinstance.get_superc_args(version)

for cu in compilation_units:
  if has_passed(cu) and skip_passed:
    sys.stderr.write("Skipping " + cu + "\n")
  else:
    for process in test_components:
      flag = "-E" if process == "preprocessor" else "-A"
      sys.stderr.write("Testing " + process + " " + cu + "\n")
      command = ["superc_linux.sh", flag, "-c", "-K", "300", superc_args, cu]
      popen = subprocess.Popen(" ".join(command), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
      stdout_, stderr_ = popen.communicate()
      if "comparison_succeeded" in stdout_:
        status = TestStatus.succeeded
      elif "comparison_failed" in stdout_:
        status = TestStatus.failed
      else:
        status = TestStatus.terminated
      print process, status, cu
      compilation_units_status[cu] = status

instance.exit()
