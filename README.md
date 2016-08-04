# xtc

A clone of the xtc project including SuperC and Kmax.  The main homepage for xtc is http://www.cs.nyu.edu/xtc/, where past versions and links to publications can be found.

## Dependencies and environment variables

Building SuperC may require `bison`, for debian and ubuntu run

    apt-get install bison

The following environment variables are expected by xtc.

    JAVA_DEV_ROOT=~/src/xtc  # or wherever your git repo is cloned
    CLASSPATH=$CLASSPATH:$JAVA_DEV_ROOT/classes:$JAVA_DEV_ROOT/bin/junit.jar:$JAVA_DEV_ROOT/bin/antlr.jar:$JAVA_DEV_ROOT/bin/javabdd.jar:/usr/share/java/org.sat4j.core.jar
    JAVA_ARGS="-Xms2048m -Xmx4048m -Xss128m" # JVM settings
    JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/  # Location of java jdk
    export JAVA_DEV_ROOT CLASSPATH JAVA_ARGS JAVA_HOME

## Building SuperC

Starting from the root of the xtc source tree, run the following:

    cd src/xtc/lang/cpp/  # go to the SuperC directory
    make configure  # configure SuperC
    cd -  # go back to the source root
    make  # build all of xtc

## Testing SuperC

From the root of the source tree, run

    make check-cpp

## Using SuperC with Linux

Use the script [`src/xtc/lang/cpp/scripts/superc_linux.sh`](src/xtc/lang/cpp/scripts/superc_linux.sh).  See [`src/xtc/lang/cpp/scripts/data.sh`](src/xtc/lang/cpp/scripts/data.sh) for example usage.  Linux versions past 2013 have not been tested.

## SuperC Manual

Run `make manual` in src/xtc/lang/cpp.  Requires `pdflatex`.

## Kmax

See Kmax's [README](src/xtc/lang/cpp/kmax/README) for build and use instructions.
