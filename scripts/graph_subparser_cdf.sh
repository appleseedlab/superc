#!/bin/bash

# Generate the chart comparing subparser size reductions from
# optimizations.

if [ $# -lt 3 ]; then
    echo "USAGE: `basename $0` outfile file1.csv Name1 file2.csv Name2 ..."
    exit
fi

outfile=$1
shift

# The upper-right-hand coordinates of the legend.
legendx=39
legendy=38.3

# The line types
lts[1]=2
lts[2]=1
lts[3]=3

# The legend spacing
legendspace=9

plot=
legend="set nokey; set object rectangle from 13, 26 to 40, 24 fillstyle noborder; "
delim="plot"

N=0
legendN=0
while [ $# -ne 0 ]; do
    file=$1
    plot="$plot$delim \"$file\" using 1:(\$2*100)"
    shift
    if [ $# -eq 0 ]; then
        echo "error: must specify a \"Name\" for the line too."
        exit
    fi
    N=$((N+1))
    name=$1
    lineattr="lc rgb \"black\" lt ${lts[N]}"
    plot="$plot title \"bob\" with line $lineattr"
    numlines=$((1+`echo -en $name | wc -c`-`echo -en $name | tr -d '\n' | wc -c`))
    xcoord=$legendx
    ycoord="$legendy - $legendspace*($legendN)"
    yarrow="$ycoord - ($numlines-1)*$legendspace/2-.32"
    legend="$legend set label \"$name\" right at $xcoord-5, $ycoord; set arrow from $xcoord-4,$yarrow to $xcoord,$yarrow nohead $lineattr; "
    shift
    legendN=$((legendN+$numlines))
    delim=","
done

echo "
set term pdfcairo monochrome dashed font \"Helvetica,5pt\" size 3.125, 2.0 lw 2
set output \"$outfile\"
set lmargin 9
set rmargin 3.125
set size ratio .618
set ytics 0,25,100 scale 0
set grid ytics
set xtics scale .5

set xlabel \"Number of Subparsers\"
set ylabel \"Cumulative Percentage\"
set yrange [0:100]
set xrange [0:40]

set datafile separator ' '

$legend

$plot
" | gnuplot
