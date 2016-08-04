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


# This script sets up SuperC environment variables.

JAVA_DEV_ROOT=~/work/java  # Location of xtc suite.

JAVA_ARGS="-Xms2048m -Xmx4048m -Xss128m" # JVM settings.

# Java classpath and scripts path settings

PATH_SEP=:

CLASSPATH=$CLASSPATH:$JAVA_DEV_ROOT/classes:$JAVA_DEV_ROOT/bin/junit.jar\
:$JAVA_DEV_ROOT/bin/antlr.jar:$JAVA_DEV_ROOT/bin/javabdd.jar

PATH=$PATH:$JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts

#Export the environment vars.
export JAVA_DEV_ROOT JAVA_ARGS PATH_SEP CLASSPATH PATH
