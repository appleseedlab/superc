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

# Computes static preprocesor usage statistics for a Linux kernel.

# Get the set of subdirectories from the Linux source to use.
dirs=`find . -maxdepth 1 -mindepth 1 -type d | grep -v arch`

# Get command-line arguments
subdirs=`mktemp`
trap "rm $subdirs" EXIT
if [[ $# -eq 1 && ("$1" == "-a" || "$1" == "-x") ]]; then
    # -a uses all .c and .h files in the current arch's source.
    if [ "$1" == "-x" ]; then
        dirs="$dirs ./arch/x86 ./arch/x86_64 ./arch/i386"
    else
        dirs="$dirs ./arch"
    fi
    files=`mktemp`
    headers=`mktemp`
    trap "rm $files $headers" EXIT

    find $dirs -type f -name "*.c" > $files
    find $dirs -type f -name "*.h" > $headers
elif [ $# -ne 2 ]; then
    # Show usage.
    echo "`basename $0` linux_files.txt linux_headers.txt"
    echo "`basename $0` -a"
    exit
else
    # Use the file lists given by the user for .c and .h files.
    dirs="$dirs ./arch/x86 ./arch/x86_64 ./arch/i386"
    files=$1
    headers=$2

fi
find $dirs -type d > $subdirs

# Check for cloc which is used to count source lines of code.  Warn
# the user if they don't have it installed or it's not in the path.
which cloc >/dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "warning: \"cloc\" not found.  It is needed for counting source" 1>&2
    echo "lines of code.  Continuing without it" 1>&1
fi

which bc >/dev/null 2>&1

if [ $? -ne 0 ]; then
    echo "warning: \"bc\" not found.  It is needed for computing percentages." 1>&2
    echo "Continuing without it" 1>&1
fi

# Print linux version and subdirectories included in stats.
echo "current_dir `basename $PWD`"
# for subdir in $dirs; do
#     echo "subdirectory $subdir"
# done

# File counts
c_h_file_count=`cat $files $headers | wc -l`
c_file_count=`cat $files | wc -l`
h_file_count=`cat $headers | wc -l`
subdir_count=`cat $subdirs | wc -l`

echo "c_h_file_count $c_h_file_count"
echo "c_file_count $c_file_count"
echo "h_file_count $h_file_count"
echo "c_file_pct "$( echo "$c_file_count / $c_h_file_count" | bc -lq )
echo "h_file_pct "$( echo "$h_file_count / $c_h_file_count" | bc -lq )
echo "subdir_count $subdir_count"

# Config var counts (using Kconfig files)
if [ `pwd | awk -F/ '{print$NF}'` == "linux-0.01" ]; then
    echo "config_var_count" `cat include/linux/config.h \
        | grep -o "# *define.*$" | awk '{print$2}' \
        | grep -v "_H$" | sort | uniq | wc -l` #"linux-0.01"
elif [ `pwd | awk -F/ '{print$NF}'` == "linux-0.99.2" ]; then
    cat .config | grep -v "#" | grep "..*" | awk '{print$1}' > tmp
    cat include/linux/config.h \
        | grep -o "# *define.*$" | awk '{print$2}' \
        | grep -v "_H$" >> tmp
    echo "config_var_count" `cat tmp | sort | uniq | wc -l` #"linux-0.99.2"
elif [ `ls arch/*/Kconfig | wc -l` -gt 0 ]; then
    echo "config_var_count " `find $dirs -name Kconfig | xargs cat \
        | grep "^config" | awk '{print }' | sort | uniq | wc -l` #"kconfig"
elif [ -f config.in ]; then
    echo "config_var_count " `ls config.in \
        | xargs grep -o "CONFIG_[A-Za-z0-9_]*" \
        | sort | uniq | wc -l` #"configure"
elif [ `ls arch/*/config.in | wc -l` -gt 0 ]; then
    echo "config_var_count " `find $dirs | grep -i config.in \
        | xargs grep -o "CONFIG_[A-Za-z0-9_]*" | awk -F: '{print$NF}' \
        | sort | uniq | wc -l` #"configure"
else
    echo "config_var_count 0" #"none"
fi

# Macro definition
alldefines=`cat $files $headers | xargs cat | grep "^# *define" | wc -l`
defines_c_files=`cat $files | xargs cat \
    | grep "^# *define" | wc -l`
defines_h_files=`cat $headers | xargs cat \
    | grep "^# *define" | wc -l`

echo "defines_total $alldefines"
echo "defines_c_files $defines_c_files"
echo "defines_h_files $defines_h_files"
echo "defines_c_files_pct "$( echo "$defines_c_files / $alldefines" | bc -lq )
echo "defines_h_files_pct "$( echo "$defines_h_files / $alldefines" | bc -lq )

# Macro usage
cat $files $headers | xargs cat | grep "^# *define" | awk '{print $2}' \
    | awk -F'(' '{print $1}' | sort | uniq > uniquemacros.txt

macros=`cat uniquemacros.txt | wc -l`
macros_c_files=`cat $files | xargs cat \
    | grep "^# *define" | awk '{print $2}' | awk -F'(' '{print $1}' \
    | sort | uniq | wc -l`
macros_h_files=`cat $headers | xargs cat \
    | grep "^# *define" | awk '{print $2}' | awk -F'(' '{print $1}' \
    | sort | uniq | wc -l`

echo "macros_total $macros"
echo "macros_c_files $macros_c_files"
echo "macros_h_files $macros_h_files"
echo "macros_c_files_pct "$( echo "$macros_c_files / $macros" | bc -lq )
echo "macros_h_files_pct "$( echo "$macros_h_files / $macros" | bc -lq )
echo "avg_defs_per_macro " `echo "$alldefines / $macros" | bc -lq`

# Conditionals
start_conditionals_total=`cat $files $headers | xargs cat \
    | grep "^# *if" | wc -l`
start_conditionals_c_files=`cat $files | xargs cat \
    | grep "^# *if" | wc -l`
start_conditionals_h_files=`cat $headers | xargs cat \
    | grep "^# *if" | wc -l`
echo "start_conditionals_total $start_conditionals_total"
echo "start_conditionals_c_files $start_conditionals_c_files"
echo "start_conditionals_h_files $start_conditionals_h_files"
echo "start_conditionals_c_files_pct "$( echo "$start_conditionals_c_files / $start_conditionals_total" | bc -lq )
echo "start_conditionals_h_files_pct "$( echo "$start_conditionals_h_files / $start_conditionals_total" | bc -lq )

# Includes
includes_total=`cat $files $headers | xargs cat \
    | grep "^# *include" | wc -l`
includes_c_files=`cat $files | xargs cat \
    | grep "^# *include" | wc -l`
includes_h_files=`cat $headers | xargs cat \
    | grep "^# *include" | wc -l`

echo "includes_total $includes_total"
echo "includes_c_files $includes_c_files"
echo "includes_h_files $includes_h_files"
echo "includes_c_files_pct "$( echo "$includes_c_files / $includes_total" | bc -lq )
echo "includes_h_files_pct "$( echo "$includes_h_files / $includes_total" | bc -lq )

# All directives
directives_total=`cat $files $headers | xargs cat | egrep \
    "^# *(if|elif|endif|include|define|undef|error|line|warning|pragma)" \
    | wc -l`

directives_c_files=`cat $files | xargs cat | egrep \
    "^# *(if|elif|endif|include|define|undef|error|line|warning|pragma)" \
    | wc -l`

directives_h_files=`cat $headers | xargs cat | egrep \
    "^# *(if|elif|endif|include|define|undef|error|line|warning|pragma)" \
    | wc -l`

echo "directives_total $directives_total"
echo "directives_c_files $directives_c_files"
echo "directives_h_files $directives_h_files"
echo "directives_c_files_pct "$( echo "$directives_c_files / $directives_total" | bc -lq )
echo "directives_h_files_pct "$( echo "$directives_h_files / $directives_total" | bc -lq )

echo ""
echo "[Source Lines of Code]"

cat $files $headers > linux_all.txt
cloc --list-file=linux_all.txt
