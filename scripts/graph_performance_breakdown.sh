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


# This script generates the performance breakdown graph.

if [[ $# -lt 4 ]]; then
    echo "USAGE: `basename $0` size|configs outfile breakdown sizes_and_configs"
    exit 1
fi

type=$1
outfile=$2
breakdown=$3
sizes_and_configs=$4

if [[ "$type" == "size" ]]; then
    key=2 #size
    xaxislabel="Compilation Units (Sorted by Size)"
elif [[ "$type" == "configs" ]]; then
    key=3
    xaxislabel="Compilation Units (Sorted by Number of Configuration Variables)"
else
    echo "Please specify size or configs."
    exit
fi

tempfile=$(tempfile -p graph) || exit
joined=$tempfile.joined.txt
sorted_breakdown=$tempfile.sorted_breakdown.txt
sorted_sizes_and_configs=$tempfile.sorted_sizes_and_configs.txt
# trap "rm -f -- $tempfile $joined $sorted_breakdown $sorted_sizes_and_configs" EXIT

# Sort performance breakdown data by file name.
cat $breakdown | grep "^performance_breakdown " | sort -k2 > $sorted_breakdown

# Sort sizes and configs data by filename.
sizes_and_configs.awk $sizes_and_configs | sort -k1 > $sorted_sizes_and_configs

join -1 1 -2 2 $sorted_sizes_and_configs $sorted_breakdown | sort -nk$key > $joined

max=`cat $joined | wc -l`

echo "
set term pdf monochrome dashed font \"Helvetica,5pt\" size 3.125, 1.9
set output \"$outfile\"

set lmargin 8
set rmargin 3.125

set size ratio .618
set xlabel \"$xaxislabel\"
set ylabel \"Latency in Seconds\"

set xrange [0:$max+1]
set noxtics

set ytics scale .25
set y2tics mirror offset -.6 scale .25
set grid ytics

set key top left Left samplen 1 width -5 reverse

set datafile separator ' '
plot \"$joined\" using 5:xtic(1) with filledcurves y1=0 lt 1 lc rgb \"#B8B8B8\" title \"Parser, Preprocessor, Lexer\", \
\"$joined\" using 6:xtic(1) with filledcurves y1=0 lt 1 lc rgb \"#808080\" title \"Preprocessor and Lexer\", \
\"$joined\" using 7:xtic(1) with filledcurves y1=0 lt 1 lc rgb \"#404040\" title \"Lexer\"

" | gnuplot
