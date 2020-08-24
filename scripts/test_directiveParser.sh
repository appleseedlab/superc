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


# Test the SuperC directive parser by processing the files from the
# linux kernel and comparing the output against the original.

if [ -z "$JAVA_DEV_ROOT" ]
then
    "please run env.sh first"
fi

outfile=test_directiveParser.txt

if [[ -f $outfile && -s $outfile ]]
then
    while true
    do
        echo "Results from a previous test found."
        read -p "Only parse the files that failed? [Y/n] " yn
        case $yn in
            [Nn]* )
                files=
                break
                ;;
            * )
                files=`cat $outfile | sort`
                break
                ;;
        esac
    done
fi

if [[ -f $outfile && ! -s $outfile ]]
then
    while true
    do
        echo "The last test appears to have no failures."
        read -p "Run again? [y/N] " yn
        case $yn in
            [Yy]* )
                break
                ;;
            * )
                exit
                ;;
        esac
    done
fi

echo "Testing the directive parser on the linux kernel."

if [ -f $outfile ]
then
    rm $outfile
fi

touch $outfile

for i in $files
do
    echo "Lexing, directive parsing, and testing $i"

    # Lex the file with SuperC's lexer
    java xtc.lang.cpp.SuperC -silent -directiveParsing $i > $i.tmp 2>/dev/null

    java xtc.lang.cpp.cdiff $i $i.tmp >/dev/null 2>/dev/null

    if [ $? -ne 0 ]; then
        echo "Failed"
        echo $i >> $outfile
    fi

    # Clean-up temp file.
    rm $i.tmp
done
