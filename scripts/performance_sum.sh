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


# This takes the performance statistics output from linux_test.sh or
# typechef_test.sh and produces a CDF of per-file times.

files=$@

if [[ -z $files ]]; then
    echo "Please pass a list of files."
    exit 1
fi

total=`cat $files | grep "^performance" \
    | awk 'BEGIN{sum = 0} {sum += 1} END{print sum}'`

cat $files | grep "^performance " | awk '{print $3, $2}' | sort -n \
    | awk -v total=$total 'BEGIN{sum=0} {sum+=$1} END{print sum}'
