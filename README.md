# xtc

A clone of the xtc project including SuperC and Kmax.  The main homepage for xtc is http://www.cs.nyu.edu/xtc/, where past versions and links to publications can be found.

## Dependencies and environment variables

Building SuperC requires `bison` and `sat4j`.  For debian and ubuntu run

    apt-get install bison sat4j

The following environment variables are expected by xtc.

    JAVA_DEV_ROOT=~/src/xtc  # or wherever your git repo is cloned
    CLASSPATH=$CLASSPATH:$JAVA_DEV_ROOT/classes:$JAVA_DEV_ROOT/bin/junit.jar:$JAVA_DEV_ROOT/bin/antlr.jar:$JAVA_DEV_ROOT/bin/javabdd.jar:/usr/share/java/org.sat4j.core.jar
    JAVA_ARGS="-Xms2048m -Xmx4048m -Xss128m" # JVM settings
    JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/  # Location of java jdk
    SUPERC_SCRATCH=~/tmp/superc # Temporary files during regression testing
    export JAVA_DEV_ROOT CLASSPATH JAVA_ARGS JAVA_HOME

## Building xtc and SuperC

From the root of the xtc source tree, run the following:

    # build xtc
    make configure
    make
    
    # build SuperC
    (cd src/xtc/lang/cpp/; make configure)
    (cd src/xtc/lang/cpp/; make parsers)
    (cd src/xtc/lang/cpp/; make)

## Running SuperC's Desugarer

    java xtc.lang.cpp.SuperC -silent <file_to_transform>.c > <output_destination>.c

## Testing SuperC

Configure SuperC to do parsing only.  From the root of the source tree, run

    cd src/xtc/lang/cpp/  # go to the SuperC directory
    make select-typechecker  # configure SuperC for parsing (typechecker is a bit of a misnomer)
    make # recompile SuperC
    cd -  # go back to the source root
    make check-cpp  # run SuperC tests

## Using SuperC with Linux source code

Use the script [`src/xtc/lang/cpp/scripts/superc_linux.sh`](src/xtc/lang/cpp/scripts/superc_linux.sh).  See [`src/xtc/lang/cpp/scripts/data.sh`](src/xtc/lang/cpp/scripts/data.sh) for example usage.  Linux versions past 2013 have not been tested.

## SuperC Manual

Run `make manual` in src/xtc/lang/cpp.  Requires `pdflatex`.

## Kmax

Kmax is now in its own repository: <https://github.com/paulgazz/kmax>
