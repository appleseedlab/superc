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


default_times=5
times=$default_times

while getopts :r: opt; do
    case $opt in
        S)
            times=$OPTARG
            ;;
        \?)
            echo "(`basename $0`)" "Invalid argument: -$OPTARG"
            exit;
            ;;
        :)
            echo "(`basename $0`)" "-$OPTARG requires an argument."
            exit;
            ;;
    esac
done

shift $(($OPTIND - 1))


# Get the command to run from the remaining command-line tokens.

command=$@


# Check that a filename was passed.

if [ -z "$command" ]; then
    echo "Runs a command a number of times and finds the average and"
    echo "standard deviation of the running times."
    echo ""
    echo "USAGE: `basename $0` [-r num_runs] command [args_to_command]"
    echo ""
    echo "OPTIONS:"
    echo "  -r num_runs    The number of times to run the command.  Default 5."
    echo ""
    exit 0
fi


nums=`for i in {1..5}; do
    /usr/bin/time -p $command 2>&1 >/dev/null | grep real | awk '{print $2}';
done`

echo $nums | tr ' ' '\n'

avg=`echo $nums | tr ' ' '\n' | awk 'BEGIN{sum = 0; count = 0;}{sum += $1; count++;}END{avg=sum/count; print avg}'`

echo "avg $avg"

stdev=`echo $nums | tr ' ' '\n' | awk -v avg=$avg 'BEGIN{sum = 0; count = 0;}{dev=avg-$1; dev2=dev*dev; sum += dev2; count++;} END{var=sum/count; stdev=sqrt(var); print stdev;}'`

echo "stdev $stdev"

