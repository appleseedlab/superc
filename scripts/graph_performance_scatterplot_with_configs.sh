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
cat $breakdown | grep "^performance_breakdown " | awk '{print $3, $4, $5, $2}' | sort -t' ' -k4 > $sorted_breakdown

# Sort sizes and configs data by filename.
sizes_and_configs.awk $sizes_and_configs | awk '{print $2, $3, $1}' | sort -t' ' -k3 > $sorted_sizes_and_configs

join -1 3 -2 4 $sorted_sizes_and_configs $sorted_breakdown | sort -nk$key > $joined

max=`cat $joined | wc -l`

echo "
set term pdf monochrome dashed font \"Helvetica,5pt\" size 3.125, 2.0
set output \"$outfile\"
set lmargin 9
set rmargin 3.125
set size ratio .618
set ytics scale 0
set grid ytics
set xtics scale .5

set xlabel \"Size in Millions of Bytes\"
set ylabel \"Latency in Seconds\"

set key top left Left samplen 1 width -5 reverse

set datafile separator ' '

# plot \
# \"$joined\" using 2:4 with points pt 6 ps 0.60 lc rgb \"#000000\" title \"Lex, Preprocess, and Parse\", \
# \"$joined\" using 2:5 with points pt 4 ps 0.50 lc rgb \"#606060\" title \"Lex and Preprocess\", \
# \"$joined\" using 2:6 with points pt 8 ps 0.70 lc rgb \"#B0B0B0\" title \"Lex\"

set ytics nomirror
set y2tics 0, 50

plot \
\"$joined\" using (\$2/1000000):4 axis x1y1 with points pt 3 ps 0.65 lc rgb \"#000000\" title \"Parse, Preprocess, and Lex\", \
\"$joined\" using (\$2/1000000):5 axis x1y1 with points pt 1 ps 0.70 lc rgb \"#606060\" title \"Preprocess and Lex\", \
\"$joined\" using (\$2/1000000):6 axis x1y1 with points pt 2 ps 0.60 lc rgb \"#B0B0B0\" title \"Lex\", \
\"$joined\" using (\$2/1000000):3 axis x1y2 with dots lc rgb \"blue\" title \"Configs\"


" | gnuplot
