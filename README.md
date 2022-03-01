# SuperC and xtc

SuperC is a parsing framework that preserves preprocessor conditionals
during C preprocessing and parsing.  SuperC is bundled with the xtc
framework, from which it uses the AST and Type libraries.  The
original project homepage for both can be found at
http://www.cs.nyu.edu/xtc/, where past versions and links to
publications can be found.

## Dependencies and environment variables

Building SuperC requires `bison`, `libz3-java`, `libjson-java`, and `sat4j`.  For debian and ubuntu run

    apt-get install bison libz3-java=4.8.7-4build1 libjson-java sat4j

The following environment variables are expected by SuperC/xtc, changing `/path/to/repository/` to the root of the repository.

    JAVA_DEV_ROOT=/path/to/repository/  # wherever your git repo is cloned
    # add included libraries to the classpath
    CLASSPATH=$CLASSPATH:$JAVA_DEV_ROOT/classes:$JAVA_DEV_ROOT/bin/junit.jar:$JAVA_DEV_ROOT/bin/antlr.jar:$JAVA_DEV_ROOT/bin/javabdd.jar:$JAVA_DEV_ROOT/bin/json-simple-1.1.1.jar
    # add system-installed libraries to the classpath
    CLASSPATH=$CLASSPATH:/usr/share/java/org.sat4j.core.jar:/usr/share/java/com.microsoft.z3.jar:/usr/share/java/json-lib.jar
    JAVA_ARGS="-Xms2048m -Xmx4048m -Xss128m" # JVM settings
    JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/  # Location of java jdk
    export JAVA_DEV_ROOT CLASSPATH JAVA_ARGS JAVA_HOME

## Building SuperC and xtc

From the root of the xtc source tree, run the following:

    make configure
    make

## Running the SuperC parser

    java superc.SuperC -silent -printAST file_to_transform.c

## Running the SugarC preprocessor desugarer

    java superc.SugarC file_to_desugarer.c > desugared_file.c

## Running the SuperP4 parser

    java superc.SuperP4 -silent -printAST file_to_transform.p4

## Testing SuperC's parser

First set `SUPERC_SCRATCH=~/tmp/superc` to some existing directory for holding temp files.

The, from the root of the source tree, run

    make check-cpp  # run SuperC tests

## Using SuperC with Linux source code

Use the script [`scripts/superc_linux.sh`](scripts/superc_linux.sh).  See [`scripts/data.sh`](scripts/data.sh) for example usage.  (Linux versions past 2013 have not been tested.)

## Regenerating SuperC's parsers for development

SuperC comes shippped with prebuilt parsers.  To modify then generate

    make -C src/superc parsers
    make

## SuperC Manual

Run `make manual` in src/superc/manual.  Requires `pdflatex`.
SuperP4 is similar to SuperC, so the manual applies to SuperP4 as well.

## Kmax

Kmax is now in its own repository: <https://github.com/paulgazz/kmax>

