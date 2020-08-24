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


# Sums one column of one SuperC statistics row.

item=$1
field=$2

if [[ -z $item || -z $field ]]; then
    echo "USAGE"
    echo "  `basename $0` item_name field"
    echo ""
    echo "DESCRIPTION"
    echo "  Computes the sum of a given data item and field from standard in."
    echo ""
    echo "EXAMPLE:"
    echo "  Given a list of fields"
    echo "    item_name  first field  second field"
    echo "    summary             20            25"
    echo "    summary              3           325"
    echo ""
    echo "  Running \"`basename $0` summary 1\" yields 23"
    echo "  Running \"`basename $0` summary 2\" yields 325"
    exit 1
fi

cat $file | grep $item | awk -v field=$field '
BEGIN{sum=0; col=field + 1;}
{ sum += $col }
END{print sum}
'