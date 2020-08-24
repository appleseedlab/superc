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

version = "4.0"
arch = "x86"

# superc_args += "-include %s/kmax/checkers/defs.h -TypeChef-x CONFIG_ -keepErrors" % (kmaxdata.kmax_root)
superc_args = ""
superc_args += linuxinstance.get_superc_args(version)

if len(superc_args) > 0:
  superc_args = '-S"%s"' % (superc_args)

instance = linuxinstance.LinuxInstance()
instance.enter(version)
instance.init_arch(arch)

compilation_unit = "init/main.c"
command = 'superc_linux.sh -A -c -K 600 %s %s' % (superc_args,
                                                compilation_unit)
print command
# popen = subprocess.call(command, shell=True, stderr=tmp, stdout=tmp)
popen = subprocess.call(command, shell=True)

instance.exit()

#git checkout v3.7; make allyesconfig; check_dep --autoconf-free arch/x86/Kconfig > autoconf-free.h; grep -v "autoconf" include/linux/kconfig.h > kconfig.h; superc_linux.sh -S"-include autoconf-free.h -include kconfig.h -D CONFIG_KASAN_SHADOW_OFFSETUL=0xdffffc0000000000UL -TypeChef-x CONFIG_ -keepError" -A -c -K 300 init/main.c 2>&1 | tee /tmp/out
