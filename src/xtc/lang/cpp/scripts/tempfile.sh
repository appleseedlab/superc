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


# Create a temporary file with a unique name.  Uses the tempfile
# command if the system has it.

if [[ ! -d ${SUPERC_SCRATCH} ]]; then
  echo "Please 'export SUPERC_SCRATCH=~/path/to/some/tmp' for holding output during regression testing.  Output files will not be removed." >&2
  exit 1
fi
tmpdir=${SUPERC_SCRATCH}

which tempfile >/dev/null 2>&1

if [ $? -eq 0 ]; then
    tempfile -d $tmpdir $@
else
    prefix="file"
    suffix=
    while getopts :p:s: opt; do
        case $opt in
            p)
                prefix=$OPTARG
                ;;
            s)
                suffix=$OPTARG
                ;;
            \?)
                echo "(`basename $0`)" "Invalid argument: -$OPTARG"
                ;;
            :)
                echo "(`basename $0`)" "-$OPTARG requires an argument."
                ;;
        esac
    done

    file="$tmpdir/$prefix`date +%s`$suffix"

    i=0
    while [ -f $file ]; do
        i=$((i+1))
        file="$tmpdir/$prefix`date +%s`.$i$suffix"
    done

    touch $file
    echo $file
fi
