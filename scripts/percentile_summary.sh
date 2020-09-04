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


# Finds specific percentiles from a data file.

while getopts :p:q: opt; do
    case $opt in
        p)
            pctls=$OPTARG
            ;;
        q)
            quietmode=$OPTARG
            ;;
        \?)
            echo "(`basename $0`)" "Invalid argument: -$OPTARG"
            ;;
        :)
            echo "(`basename $0`)" "-$OPTARG requires an argument."
            ;;
    esac
done

shift $(($OPTIND - 1))

if [[ $# -lt 3 ]]; then
    echo "USAGE"
    echo "  `basename $0` [-q percentile] [-p \"percentiles\"] file row_name col_number"
    echo ""
    echo -e "  -p percentiles\tspecifies the (p)ercentiles to find"
    echo -e "  -q percentile\t\t(q)uiet mode only prints a single percentile without any other text"
    echo ""
    echo "EXAMPLES"
    echo "  `basename $0` -p \".5 .8 .9 1\" performance.txt performance 3"
    echo "  `basename $0` -q .5 performance.txt performance 3"
    echo ""
    echo "DETAILS"
    echo "  The file format expected are rows of data with the columns separated by spaces."
    echo "  The first column, col_number 1, is a row_name identifying the type of data.  The"
    echo "  percentile is specified as a decimal number."
    exit
fi

file=$1
item=$2
field=$3

count=`cat $file | grep $item | wc -l`

function get_percentile {
    pctl=$1
    n=`perl -w -e "use POSIX; print ceil($count * $pctl), qq{\n}"`  # ugh
    echo `cat $file | grep $item | awk -v col=$field '{ print $col }' \
        | sort -n | head -n $n | tail -n 1`
}

if [[ "$quietmode" != "" ]]; then
    if [[ "$pctls" != "" ]]; then
        echo "error: only -p or -q may be used, not both"
        exit 1
    fi
    get_percentile $quietmode
else
    if [[ "$pctls" == "" ]]; then
        pctls=".5 .9 1" # the default list of percentiles to find
    fi
    echo "Out of $count rows."
    for pctl in $pctls; do
        echo "Percentile $pctl ($n rows)"
        get_percentile $pctl
        echo
    done
fi
