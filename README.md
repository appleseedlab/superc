# SuperC and xtc

SuperC is a parsing framework that preserves preprocessor conditionals
during C preprocessing and parsing.  SuperC is bundled with the xtc
framework, from which it uses the AST and Type libraries.  The
original project homepage for both can be found at
http://www.cs.nyu.edu/xtc/, where past versions and links to
publications can be found.

## Dependencies and environment variables

Building SuperC requires `bison` and `sat4j`.  For debian and ubuntu run

    apt-get install bison libz3-java sat4j

The following environment variables are expected by SuperC/xtc.

    JAVA_DEV_ROOT=~/src/superc  # or wherever your git repo is cloned
    CLASSPATH=$CLASSPATH:$JAVA_DEV_ROOT/classes:$JAVA_DEV_ROOT/bin/junit.jar:$JAVA_DEV_ROOT/bin/antlr.jar:$JAVA_DEV_ROOT/bin/javabdd.jar:/usr/share/java/org.sat4j.core.jar:/usr/share/java/com.microsoft.z3.jar
    JAVA_ARGS="-Xms2048m -Xmx4048m -Xss128m" # JVM settings
    JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/  # Location of java jdk
    export JAVA_DEV_ROOT CLASSPATH JAVA_ARGS JAVA_HOME

## Building SuperC and xtc

From the root of the xtc source tree, run the following:

    make configure
    make

## Running the SuperC parser

    java superc.SuperC -silent -printAST file_to_transform.c

## Running the SuperC desugarer

    java superc.SugarC file_to_desugarer.c > desugared_file.c

## Using preprocessed headers

Preprocessing the headers only needs to be done once:

    bash scripts/preprocess_system_headers.sh ~/src/preprocessed_sysdirs/
    
Use the headers with SuperC/SugarC like this:

    java superc.SugarC $(cat ~/src/preprocessed_sysdirs/supercargs.txt) helloworld.c

## Testing SuperC's parser

### Requirements

- A python 2 interpreter for some tests
- Setting `SUPERC_SCRATCH=~/tmp/superc` to some existing directory for holding temp files.

### Running the tests

From the root of the source tree, run

    make check-cpp  # run SuperC tests

## Using SuperC with Linux source code

Use the script [`scripts/superc_linux.sh`](scripts/superc_linux.sh).  See [`scripts/data.sh`](scripts/data.sh) for example usage.  Linux versions past 2013 have not been tested.

## Regenerating SuperC's parsers for development

SuperC comes shippped with prebuilt parsers.  To modify then generate

    make -C src/superc parsers
    make

## SuperC Manual

Run `make manual` in src/superc/manual.  Requires `pdflatex`.

## Kmax

Kmax is now in its own repository: <https://github.com/paulgazz/kmax>
