#!/usr/bin/awk -f

# xtc - The eXTensible Compiler
# Copyright (C) 2009-2012 New York University
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
# USA.

# This script takes the output from two SuperC flags,
# -configurationVariables and -size, and reports for each file
# "filename size num_configs".  It is used in conjunction with
# graph_performance_breakdown.sh to generate performance breakdown
# charts.

BEGIN {
  filename=""
  configs=0
  size=0
}

{
  if ($1 == "Processing") {
    if (filename != "") {
      print filename, size, configs
    }
    filename=$2
    configs=0
    size=0
  } else if ($1 == "config_var") {
    configs++
  } else if ($1 == "size") {
    size=$2
  }
}

END {
  print filename, size, configs
}
