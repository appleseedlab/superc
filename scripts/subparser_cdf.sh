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


# This takes the SuperC -parserStatistics output from processing
# several compilation units and creates a cumulative distribution of
# subparser sizes by percentage of parser loop iterations.

files=$@

if [[ -z $files ]]; then
    echo "USAGE: `basename $0` file file ..."
    exit 1
fi

iterations=`cat $files | grep "iterations" \
    | awk 'BEGIN{sum = 0} {sum += $2} END{print sum}'`

cat $files | grep "^subparsers" \
    | awk -v iterations=$iterations '{print $2, ($3 / iterations) }' | sort -n \
    | awk '\
BEGIN{ subparsers=0; sum=0 } \
{if ($1 == subparsers) {
sum += $2;
} else {
print subparsers, sum;
subparsers=$1; sum=$2;
}} \
END{print subparsers, sum;} \
' \
    | awk 'BEGIN{sum = 0} {sum += $2; print $1, sum}'

