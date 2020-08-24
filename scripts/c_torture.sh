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


# Test the SuperC C parser on the gcc C torture test suite.  Only
# checks whether the parsing passed or failed.

if [ -z "$JAVA_DEV_ROOT" ]
then
    "please run env.sh first"
fi

outfile=c_torture.txt
tmp=tmpfile.c
rm $outfile
touch $outfile
for i in `find $JAVA_DEV_ROOT/fonda/xtc_testsuite/gcc.c-torture/ -name "*.c" -type f | sort`
do
    echo "Processing $i" 1>&2
    gcc -E $i > $tmp

    java -ea xtc.lang.cpp.SuperC -silent -showAccepts $tmp 2>&1 | grep "ACCEPT"

    if [ $? -ne 0 ]; then
        echo $i >> $outfile
    fi
done
rm $tmp

if [ ! -s $outfile ]
then
    echo "Passed c torture test."
else
    echo "Failed.  Check $outfile for which files it failed on."
fi
