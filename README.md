# SuperC and xtc

SuperC is a parsing framework that preserves preprocessor conditionals
during C preprocessing and parsing.  SuperC is bundled with the xtc
framework, from which it uses the AST and Type libraries.  The
original project homepage for both can be found at
http://www.cs.nyu.edu/xtc/, where past versions and links to
publications can be found.

## Dependencies and environment variables

Building SuperC requires `bison` and `sat4j`.  For debian and ubuntu run

    apt-get install bison sat4j

The following environment variables are expected by SuperC/xtc.

    JAVA_DEV_ROOT=~/src/superc  # or wherever your git repo is cloned
    CLASSPATH=$CLASSPATH:$JAVA_DEV_ROOT/classes:$JAVA_DEV_ROOT/bin/junit.jar:$JAVA_DEV_ROOT/bin/antlr.jar:$JAVA_DEV_ROOT/bin/javabdd.jar:/usr/share/java/org.sat4j.core.jar
    JAVA_ARGS="-Xms2048m -Xmx4048m -Xss128m" # JVM settings
    JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/  # Location of java jdk
    SUPERC_SCRATCH=~/tmp/superc # Temporary files during regression testing
    export JAVA_DEV_ROOT CLASSPATH JAVA_ARGS JAVA_HOME

## Building SuperC and xtc

From the root of the xtc source tree, run the following:

    make configure
    make

## Running the SuperC parser

    java xtc.lang.cpp.SuperC -silent -printAST file_to_transform.c

## Running the SuperC desugarer

    java xtc.lang.cpp.SugarC -silent file_to_desugarer.c > desugared_file.c

## Testing SuperC's parser

Configure SuperC to do parsing only.  From the root of the source tree, run

    make check-cpp  # run SuperC tests

## Using SuperC with Linux source code

Use the script [`scripts/superc_linux.sh`](scripts/superc_linux.sh).  See [`scripts/data.sh`](scripts/data.sh) for example usage.  Linux versions past 2013 have not been tested.

## SuperC Manual

Run `make manual` in src/superc/manual.  Requires `pdflatex`.

## Kmax

Kmax is now in its own repository: <https://github.com/paulgazz/kmax>
