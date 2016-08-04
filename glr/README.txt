This directory contains the files necessary for building Java parsers
with SDF2 and Elkhound.

The SDF2 grammars for Java 1.4 and 1.5 are contained in the Java14.sdf
and Java15.sdf modules, which depend on several other SDF modules
contained in the languages subdirectory.  The Java 1.5 grammar
corresponds to the java-front 0.8 grammar, with JavaCompilationUnit-15
as the top-level module.  The Java 1.4 grammar has been manually
derrived from the former by removing all constructs new to Java 1.5
(i.e., generics, the enhanced for loop, typesafe enums, varargs,
annotations, and static imports).  The buildsdf.sh script utilizes
pack-sdf and sdf2table to build the corresponding parse tables, which
in turn are utilized by ../data/sdf.sh to evaluate the performance of
SDF2-generated parsers.  Note that the tables must be moved/copied
from this directory to the data directory.

The ella subdirectory contains all code necessary for building an
Elkhound-based Java 1.4 parser, which, ahem, is called ella.  The
configure script and Makefile in this directory are used to build the
parser.  Both assume that the ast, smbase, elkhound, and elsa
directories from the elsa and elkhound distribution have been moved
into this directory.
