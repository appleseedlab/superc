#!/bin/bash

# Generate the table comparing subparser size reductions from
# optimizations.

if [ $# -lt 1 ]; then
    echo "USAGE: `basename $0` file1.csv file2.csv ..."
    exit
fi

plot=
delim="plot"

lt=0
while [ $# -ne 0 ]; do
    file=$1
    if [ -f $file ]; then
        echo "`basename $file` summary"
        tac $file | awk 'BEGIN{fifty = 0; nn = 0; max = 0;} {if (NR == 1) { max=$1 } pctl=$2; if (pctl >= .5) {fifty=$1} if (pctl >= .99) {nn=$1}} END{print "summary_subparsers", fifty, nn, max}'
    else
        echo "$file not found"
    fi
    echo
    shift
done
