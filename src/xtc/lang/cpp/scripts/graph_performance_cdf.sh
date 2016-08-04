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


# This script generates the performance cdf graph.

if [[ $# -lt 3 ]]; then
    echo "USAGE: `basename $0` outfile superc typechef"
    exit 1
fi

outfile=$1
superc=$2
typechef=$3

# Generate a multi-line chart.

superc_cdf=$(tempfile -p superc) || exit
typechef_cdf=$(tempfile -p typechef) || exit

superc_max=`cat $superc | grep "^performance " | sort -nk3 | tail -n1 | cut -d' ' -f3 | awk '{printf("%.2f", $0)}'`
superc_max_position=`echo $superc_max | awk '{print $0 + 1}'`
typechef_max=`cat $typechef | grep "^performance " | sort -nk3 | tail -n1 | cut -d' ' -f3 | awk '{printf("%.2f", $0)}'`

superc_total=`performance_sum.sh $superc | awk '{ printf("%.2f", $0/3600)}'`
typechef_total=`performance_sum.sh $typechef | awk '{ printf("%.2f", $0/3600)}'`

performance_cdf.sh $superc > $superc_cdf
performance_cdf.sh $typechef > $typechef_cdf

echo "SuperC summary"
percentile_summary.sh -p ".5 .8 .9 1" $superc performance 3

seconds=`performance_sum.sh $superc`

echo "Total time (seconds): $seconds" 
echo "Total time (hours):" `echo "$seconds / 3600" | bc -lq`

echo ""

echo "TypeChef summary"
percentile_summary.sh -p ".5 .8 .9 1" $typechef performance 3

seconds=`performance_sum.sh $typechef`

echo "Total time (seconds): $seconds" 
echo "Total time (hours):" `echo "$seconds / 3600" | bc -lq`

echo ""

# The center of the legend.
legendx=30.25
legendy=21

echo "
set term pdfcairo monochrome dashed font \"Helvetica,5pt\" size 3.125, 2.0 lw 2
set output \"$outfile\"
set lmargin 9
set rmargin 3.125
set size ratio .618
set ytics 0,25,100 scale 0
set grid ytics
set xtics scale .5

set xlabel \"Latency in Seconds\"
set ylabel \"Cumulative Percentage\"
set yrange [0:100]
set xrange [0:40]

set datafile separator ' '

set nokey
# set label \"SuperC\" at 6.2, 87 right
set obj rect center 9.5, 62.5 size char(6), 1.5 front fillstyle solid 1.0 border
set label \"SuperC\" at 9.5, 62.5 center front
set label \"TypeChef\" at 24, 62.5 left
# set label \"TypeChef\" at 30, 92 right
# set label \"SuperC's\\nMaximum\\nis $superc_max\s\" at $superc_max_position, 94 left
# set label \"TypeChef's\\nMaximum\\nis $typechef_max\s\" at 39.4, 79 right
set label \"Max: $superc_max\s\" at $superc_max_position, 93 left
set label \"Max: $typechef_max\s\" at 39.4, 84 right

set obj rect center $legendx, $legendy+.32 size 15, 25
set label \"Total Time\" at $legendx, $legendy+8 center
set label \"SuperC\" at $legendx-7, $legendy left
set label \"TypeChef\" at $legendx-7, $legendy-7 left
set label \"$superc_total\hrs\" at $legendx+7, $legendy right
set label \"$typechef_total\hrs\" at $legendx+7, $legendy-7 right

# set key bottom right Right #samplen 1 width -5 reverse

plot \"$superc_cdf\" using 1:(\$2*100) title 'SuperC' with line lc rgb \"black\" lt 1 , \
\"$typechef_cdf\" using 1:(\$2*100) title 'TypeChef' with line lc rgb \"black\" lt 1 , \
\"< echo '$superc_max 100'\" with impulses lt 2
" | gnuplot
