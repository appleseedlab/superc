#!/bin/bash

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


# This script finds the top-ten included header files based on the by
# the number of other files that include them.

if [ $# -ne 2 ]; then
    echo "`basename $0` linux_files.txt linux_headers.txt"
    exit
fi

files=$1
headers=$2

echo "Current directory: `basename $PWD`"

dirs=`find . -maxdepth 1 -mindepth 1 -type d | grep -v arch`
dirs="$dirs ./arch/x86"

total=`cat $files $headers | wc -l`
num_c=`cat $files | wc -l`
num_h=`cat $headers | wc -l`

echo "top includes in .c and .h"
cat $files $headers | xargs cat | grep "^#include" | awk '{print $2}' | sort | awk -v total=$total 'BEGIN{count=0; file="";}{if ($0 != file) { print count, count / total file; file = $0; count=1; } else { count++ }}' | sort -nr | head
echo

echo "top includes in .c"
cat $files | xargs cat | grep "^#include" | awk '{print $2}' | sort | awk -v total=$num_c 'BEGIN{count=0; file="";}{if ($0 != file) { print count, count / total, file; file = $0; count=1; } else { count++ }}' | sort -nr | head
echo

echo "top includes in .h"
cat $headers | xargs cat | grep "^#include" | awk '{print $2}' | sort | awk -v total=$num_h 'BEGIN{count=0; file="";}{if ($0 != file) { print count, count / total, file; file = $0; count=1; } else { count++ }}' | sort -nr | head

