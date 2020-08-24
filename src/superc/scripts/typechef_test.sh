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


# This script runs the TypeChef Linux test case with either SuperC or
# TypeChef.  It produces total and per-file timing data.


TYPECHEF_LINUXVER=linux-2.6.33.3

# Save the command-line to record it in the outfile.

commandline=$@

# Get options.

# Defaults
default_file_list=linux_files.lst

# Get options.

# Defaults
args= #empty
out= #default is empty pending system name
file_list=
host= #empty
port= #empty
unconstrained= #empty

while getopts :a:f:o:h:p:u opt; do
    case $opt in
        a)
            args=$OPTARG
            ;;
        f)
            file_list=$OPTARG
            ;;
        o)
            out=$OPTARG
            ;;
        h)
            host=$OPTARG
            ;;
        p)
            port=$OPTARG
            ;;
        u)
            unconstrained="-u"
            ;;
        \?)
            echo "Invalid argument: -$OPTARG"
            exit;
            ;;
        :)
            echo "-$OPTARG requires an argument."
            exit;
            ;;
    esac
done

shift $(($OPTIND - 1))

system=$1

if [[ -z $system || "$system" != "SuperC" && "$system" != "TypeChef" ]]; then
    echo "USAGE: `basename $0` [-a args] SuperC|TypeChef"
    echo ""
    echo "OPTIONS:"
    echo "  -a args            Pass extra arguments when running the tool"
    echo "  -u                 Run on unconstrained linux kernel"
    echo "  -f file_list.txt   Optionally specify a custom list of Linux files."
    echo "                     to run.  Defaults to $default_file_list."
    echo "  -o output_filename The name of the output file. Defaults to"
    echo "                     performance.system_name.date_and_time.txt"
    echo "  -h file_host       Optionally specify a filename server to get the"
    echo "                     Linux files to run on.  Cannot be used with -f."
    echo "  -p file_host_port  The port for the filename server."
    exit 0
fi

if [ -z $out ]; then
    out="performance.$system.`date +%Y-%m-%d_%H-%M-%S`.txt"
fi

if [ -f $out ]; then
    echo "Exiting. The outfile \"$out\" already exists."
    exit 0;
fi

# Make sure the SuperC environment is set up.

if [ -z "$JAVA_DEV_ROOT" ]
then
    "please run env.sh first"
fi


# Make sure the linux directory exists.

if [ ! -d "$TYPECHEF_LINUXVER" ]
then
    echo "Please run ./prepareLinuxTestCase.sh from the TypeChef directory " \
        "first"
    exit 1
fi

if [[ ! -z $file_list && ! -z $host ]]; then
    echo "Cannot specify both a file and a server for the filename list."
    exit;
fi

if [[ ! -z $host && -z $port ]]; then
    echo "Please specify a port (-p port) to connect to at host \"$host\"."
    exit;
fi


# Get the source of the filename list, from a file or from a server

if [[ -z $host ]]; then
    if [ -z $file_list ]; then
        file_list=$default_file_list
    fi

    if [ ! -f $file_list ]; then
        echo "The file list \"$file_list\" is not a valid file."
        exit 0
    fi

    length=0;
    for file in `cat $file_list`; do
        files[length]=$file
        length=$length+1
    done
fi

# if [ "$system" == "TypeChef" ]; then
#     java -jar sbt-launch-0.7.5.jar compile
# fi

# Check for the calculator program.

which bc >/dev/null 2>&1

if [ $? -eq 0 ]; then
    calc="bc -lq"
else
    calc= #empty
    echo "warning: calculator program \"bc\" not found on system, reporting \
start and"
    echo "         end times instead of run-times"
fi

echo "Writing output to \"$out\""

echo "# start `date`" >> $out

finalize() {
    echo "# finish `date`" >> $out
    exit
}

echo "# Command-line: $commandline" >> $out

i=0
while :; do
    before=`date +%s.%N`

    if [ -z $host ]; then
        if [[ $i -eq $length ]]; then
            echo "done";
            finalize;
            exit;
        fi
        file=${files[$i]}
        i=$i+1
    else
        file=`java xtc.lang.cpp.FilenameService -client $host $port`
        errcode=$?
        if [[ $errcode -eq 3 ]]; then
            echo "No more files."
            finalize;
            exit
        elif [[ $errcode -eq 4 ]]; then
            echo "No server available."
            finalize;
            exit
        elif [[ $errcode -ne 0 || -z $file ]]; then
            echo "Unknown file server error."
            finalize;
            exit
        fi
    fi

    if [[ $file_list == $default_file_list ]]; then
        # TypeChef's file list omits the linux directory and the
        # file's .c extension.  Normal file lists will have the actual
        # file name.
        file=$TYPECHEF_LINUXVER/$file.c
    fi

    typechef_run_file.sh -t $system $unconstrained -a "$args" $file >> $out 2>&1 $out

    after=`date +%s.%N`

    if [[ ! -z $calc ]]; then
        time=`echo "$after - $before" | $calc`
        echo "performance $file $time" >> $out
    else
        # If there is no calculator program on the system, just output
        # the before and after times.
        echo "performance_raw $file $before $after" >> $out
    fi
done
echo "# finish `date`" >> $out
