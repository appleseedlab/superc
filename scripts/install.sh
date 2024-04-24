#!/bin/bash

set -x

# this script installs SuperC (https://github.com/appleseedlab/superc/

# set this to the prefix you would like to install superc to
user_prefix=

# uninstall by removing ${prefix}/share/superc/, ${prefix}/bin/superc_linux.sh, and ${prefix}/bin/make.cross

# setup colors
RED=
GREEN=
ENDCOLOR=
if test -t 1; then
  ncolors=$(tput colors)
  if test -n "$ncolors" && test $ncolors -ge 8; then
    RED="\e[31m"
    GREEN="\e[32m"
    ENDCOLOR="\e[0m"
  fi
fi

prefix="${user_prefix:-${HOME}/.local}"

echo -e "${GREEN}Installing to prefix ${prefix}${ENDCOLOR}"
echo -e ""

jarpath="${prefix}/share/superc"
binpath="${prefix}/bin"

mkdir -p "${jarpath}"
mkdir -p "${binpath}"

# SuperC depends on several libraries, some of which need to be downloaded manually.
cd "${jarpath}"
wget -O - --content-disposition -c https://sourceforge.net/projects/javabdd/files/javabdd-linux/1.0b2%20Linux%20binary/javabdd_1.0b2.tar.gz/download?use_mirror=master > javabdd.tar.bz
tar -xvf javabdd.tar.bz JavaBDD/javabdd-1.0b2.jar
wget -O z3-4.8.12-x64-glibc-2.31.zip https://github.com/Z3Prover/z3/releases/download/z3-4.8.12/z3-4.8.12-x64-glibc-2.31.zip
unzip -o z3-4.8.12-x64-glibc-2.31.zip z3-4.8.12-x64-glibc-2.31/bin/com.microsoft.z3.jar
wget -O xtc.jar https://github.com/appleseedlab/superc/releases/download/v2.0-rc4/xtc.jar
wget -O superc.jar https://github.com/appleseedlab/superc/releases/download/v2.0-rc4/superc.jar

# Download and install the SuperC Linux runner script.
cd "${binpath}"
wget -O superc_linux.sh https://raw.githubusercontent.com/appleseedlab/superc/master/scripts/superc_linux.sh
chmod 755 superc_linux.sh

# Download and install `make.cross` for cross-compiling Linux source code.
wget -O make.cross https://raw.githubusercontent.com/intel/lkp-tests/master/kbuild/make.cross
wget -O kbuild.sh https://raw.githubusercontent.com/intel/lkp-tests/master/kbuild/kbuild.sh
chmod 755 make.cross

echo -e ""
echo -e "${GREEN}Update your java CLASSPATH to contain all the requisite jarfiles for SuperC.${ENDCOLOR}"
echo -e "export CLASSPATH="'${CLASSPATH}'":/usr/share/java/org.sat4j.core.jar:/usr/share/java/json-lib.jar:${jarpath}/z3-4.8.12-x64-glibc-2.31/bin/com.microsoft.z3.jar:${jarpath}/JavaBDD/javabdd-1.0b2.jar:${jarpath}/xtc.jar:${jarpath}/superc.jar"
echo -e ""

echo -e "${GREEN}Update your PATH to include ${binpath}${ENDCOLOR}"
echo -e "export PATH="'${PATH}'":${binpath}"
echo -e ""
