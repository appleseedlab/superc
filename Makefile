# Makefile
#***************************************************************************
#
# Master Makefile
#
# (C) 1999 Jacob Dreyer - Geotechnical Software Services
# jacob.dreyer@geosoft.no - http://geosoft.no
#
# Modifications Copyright (C) 2001-2012 Robert Grimm
# rgrimm@alum.mit.edu
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#***************************************************************************

ifdef JAVA_DEV_ROOT
include $(JAVA_DEV_ROOT)/Makebase
endif

#***************************************************************************
#
# Packages
#
# Use fully qualified package names for the list of packages.
#
#***************************************************************************

PACKAGES = \
	xtc \
	xtc.util \
	xtc.tree \
	xtc.type \
	xtc.parser \
	xtc.lang \
	xtc.lang.cpp \
	xtc.lang.jeannie \
	xtc.lang.blink \
	xtc.lang.blink.agent

#***************************************************************************
#
# Javadoc
#
# These variables define some of the layout of the javadoc HTML
# output. See javadoc manual for details.
#
#***************************************************************************

WINDOWTITLE     = 'xtc - the eXTensible Compiler'
DOCTITLE        = 'Java Class Documentation for xtc'
BOTTOM          = '<center>(C) Copyright 2004-2011 Robert Grimm, New York University, IBM, and Princeton</center>'
JAVADOC         = javadoc
SUN_JAVADOCS    = http://java.sun.com/j2se/1.5.0/docs/api

JAVADOC_OPTIONS = \
	-J-Xmx1024m \
	-source 1.5 \
	-protected \
	-d $(DOC_DIR) \
	-sourcepath $(SOURCE_DIR) \
	-use \
	-version \
	-splitIndex \
	-windowtitle $(WINDOWTITLE) \
	-doctitle $(DOCTITLE) \
	-bottom $(BOTTOM) \
	-overview overview.html \
	-linkoffline $(SUN_JAVADOCS) $(THE_ROOT)

#***************************************************************************
#
# Rules and dependencies.
#
# The following commands are valid:
#
#  1. make printenv        - Print local system's C compilers
#  2. make configure       - Configure local system's xtc.Limits
#  3. make classes         - Make all class files for all packages
#  4. make                 - Same as (3)
#  5. make parsers         - Make all parsers
#  6. make factories       - Make all AST factories
#  7. make doc             - Make all documentation
#  8. make jars            - Make binary distribution
#  9. make dist            - Make source distribution
# 10. make stats           - Print source code statistics
# 11. make check           - Run all regression tests
# 12. make clean           - Clean classes
# 13. make clobber         - Clean classes, documentation, distributions
# 14. make clobber-parsers - Clean parser sources
#
#
# For the CLASS, JNI, JAR, and CLEAN variables, all backslashes are
# replaced by forward slashes. This substitution is only important
# when using this makefile on Windows. When building in an MS-DOS
# shell, make treats both backslash and forward slash as a path
# segment delimiter. However, Unix shells, such as bash, require
# forward slashes. File names passed to the Java tools may have a mix
# of backslash and forward slash, because they treat both as a path
# segment delimiter.
#
#***************************************************************************

PACK_PATHS  = $(subst .,/,$(PACKAGES))
CLASS       = $(subst \,/,$(PACK_PATHS:%=$(SOURCE_DIR)/%.class))
PARSER      = $(subst \,/,$(PACK_PATHS:%=$(SOURCE_DIR)/%.parser))
FACTORY     = $(subst \,/,$(PACK_PATHS:%=$(SOURCE_DIR)/%.factory))
CLEAN       = $(subst \,/,$(PACK_PATHS:%=$(SOURCE_DIR)/%.clean))

.PHONY  : default classes parsers factories
.PHONY  : printenv configure
.PHONY  : clean clobber clobber-parsers
.PHONY  : all doc jars dist stats

default : classes

classes : $(CLASS)
%.class :
	$(MAKE) -C $* classes

parsers  : $(PARSER)
%.parser :
	$(MAKE) -C $* parsers

factories : $(FACTORY)
%.factory :
	$(MAKE) -C $* factories

printenv :
	@echo "=============================================================================="
	@echo "OSTYPE        = $(OSTYPE)"
	@echo "CC            = $(CC)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "CPP           = $(CPP)"
	@echo "CPPFLAGS      = $(CPPFLAGS)"
	@echo "JAVA_HOME     = $(JAVA_HOME)"
	@echo "JAVA_DEV_ROOT = $(JAVA_DEV_ROOT)"
	@echo "JAVA          = $(JAVA)"
	@echo "which java    = `which java`"
	@$(JAVA) -version
	@echo "JAVAC         = $(JAVAC)"
	@echo "which javac   = `which javac`"
	@echo "JAVAC_OPTIONS = $(JAVAC_OPTIONS)"
	@echo "CLASSPATH     = $(CLASSPATH)"
	@echo "=============================================================================="

configure :
	$(MAKE) -C $(SOURCE_DIR)/xtc configure
	$(MAKE) -C $(SOURCE_DIR)/xtc/lang/cpp configure

clean   : $(CLEAN)
%.clean :
	$(MAKE) -C $* clean

clobber :
ifdef JAVA_DEV_ROOT
	$(RM) $(SOURCE_DIR)/xtc/limitgen
	$(RMDIR) $(CLASS_DIR)/xtc
	$(RMDIR) $(CLASS_DIR)/edu
	$(RM) $(DOC_DIR)/allclasses-frame.html
	$(RM) $(DOC_DIR)/allclasses-noframe.html
	$(RM) $(DOC_DIR)/constant-values.html
	$(RM) $(DOC_DIR)/deprecated-list.html
	$(RM) $(DOC_DIR)/help-doc.html
	$(RM) $(DOC_DIR)/index.html
	$(RM) $(DOC_DIR)/overview-frame.html
	$(RM) $(DOC_DIR)/overview-summary.html
	$(RM) $(DOC_DIR)/overview-tree.html
	$(RM) $(DOC_DIR)/packages.html
	$(RM) $(DOC_DIR)/package-list
	$(RM) $(DOC_DIR)/serialized-form.html
	$(RM) $(DOC_DIR)/stylesheet.css
	$(RMDIR) $(DOC_DIR)/index-files
	$(RMDIR) $(DOC_DIR)/xtc
	$(RMDIR) $(DOC_DIR)/edu
	$(RM) $(BIN_DIR)/xtc.jar
	$(RM) $(BIN_DIR)/rats.jar
	$(RM) $(BIN_DIR)/rats-runtime.jar
	$(RM) $(GLR_DIR)/Java14.dep
	$(RM) $(GLR_DIR)/Java14.tbl
	$(RM) $(GLR_DIR)/Java15.dep
	$(RM) $(GLR_DIR)/Java15.tbl
	$(RM) xtc-core.zip xtc-testsuite.zip
	$(RM) rats.log rats.sum
	$(RM) xtc.log xtc.sum
	$(RM) typical.log typical.sum
	$(RM) overlog.log overlog.sum
	$(MAKE) -C $(SOURCE_DIR)/xtc/lang/jeannie/doc cleanall
	$(MAKE) -C $(SOURCE_DIR)/xtc/lang/blink/doc cleanall
	$(RM) $(FONDA_DIR)/xtc_testsuite/layout/headergen
	$(RM) $(FONDA_DIR)/xtc_testsuite/layout/metadata.h
	$(RM) $(FONDA_DIR)/xtc_testsuite/layout/test.E
	$(RMDIR) $(FONDA_DIR)/jeannie_testsuite/tmp
	$(FIND) $(FONDA_DIR) -name '*.tmp' -exec $(RM) \{\} \;
	$(FIND) $(FONDA_DIR) -name '*.E'   -exec $(RM) \{\} \;
	$(FIND) $(FONDA_DIR)/cpp_testsuite/ | \
		egrep "\.test$$|\.diff$$|\.gcc$$" | \
		xargs rm -f
endif

clobber-parsers :
ifdef JAVA_DEV_ROOT
	$(RM) $(SOURCE_DIR)/xtc/parser/PParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/CParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/CReader.java
	$(RM) $(SOURCE_DIR)/xtc/lang/CFactoryParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/JavaRecognizer.java
	$(RM) $(SOURCE_DIR)/xtc/lang/JavaParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/JavaReader.java
	$(RM) $(SOURCE_DIR)/xtc/lang/JavaFiveParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/JavaFiveReader.java
	$(RM) $(SOURCE_DIR)/xtc/lang/JavaFactoryParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/TypedLambdaParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/jeannie/JeannieParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/jeannie/PreJeannieParser.java
	$(RM) $(SOURCE_DIR)/xtc/lang/blink/CommandParser.java
	$(MAKE) -C $(SOURCE_DIR)/xtc/lang/cpp clobber-parsers
endif

jars    : classes
ifdef JAVA_DEV_ROOT
	$(RMDIR) $(JAR_TMP)
	$(CPDIR) $(CLASS_DIR) $(JAR_TMP)
	$(RMDIR) $(JAR_TMP)/CVS
	$(RM)    $(JAR_TMP)/.cvsignore
	$(RM)    $(JAR_TMP)/.anchor
	$(JAR) cmf xtc.manifest $(BIN_DIR)/xtc.jar -C $(JAR_TMP) xtc
	$(RMDIR) $(JAR_TMP)
	$(MKDIR) $(JAR_TMP)
	$(MKDIR) $(JAR_TMP)/xtc
	$(MKDIR) $(JAR_TMP)/xtc/util
	$(MKDIR) $(JAR_TMP)/xtc/tree
	$(MKDIR) $(JAR_TMP)/xtc/type
	$(MKDIR) $(JAR_TMP)/xtc/parser
	$(CP) $(CLASS_DIR)/xtc/*.class $(JAR_TMP)/xtc
	$(CP) $(CLASS_DIR)/xtc/util/*.class $(JAR_TMP)/xtc/util
	$(CP) $(CLASS_DIR)/xtc/tree/*.class $(JAR_TMP)/xtc/tree
	$(CP) $(CLASS_DIR)/xtc/type/*.class $(JAR_TMP)/xtc/type
	$(CP) $(CLASS_DIR)/xtc/parser/*.class $(JAR_TMP)/xtc/parser
	$(JAR) cmf rats.manifest $(BIN_DIR)/rats.jar -C $(JAR_TMP) xtc
	$(RMDIR) $(JAR_TMP)
	$(MKDIR) $(JAR_TMP)
	$(MKDIR) $(JAR_TMP)/xtc
	$(MKDIR) $(JAR_TMP)/xtc/util
	$(MKDIR) $(JAR_TMP)/xtc/tree
	$(MKDIR) $(JAR_TMP)/xtc/parser
	$(CP) $(CLASS_DIR)/xtc/util/Pair*.class \
              $(CLASS_DIR)/xtc/util/Action.class \
              $(CLASS_DIR)/xtc/util/State.class \
              $(CLASS_DIR)/xtc/util/Utilities.class \
              $(JAR_TMP)/xtc/util
	$(CP) $(CLASS_DIR)/xtc/tree/Location.class \
              $(CLASS_DIR)/xtc/tree/Locatable.class \
              $(CLASS_DIR)/xtc/tree/Node*.class \
              $(CLASS_DIR)/xtc/tree/Token.class \
              $(CLASS_DIR)/xtc/tree/Annotation.class \
              $(CLASS_DIR)/xtc/tree/Formatting*.class \
              $(CLASS_DIR)/xtc/tree/GNode*.class \
              $(JAR_TMP)/xtc/tree
	$(CP) $(CLASS_DIR)/xtc/parser/ParserBase.class \
	      $(CLASS_DIR)/xtc/parser/Column.class \
	      $(CLASS_DIR)/xtc/parser/Result.class \
	      $(CLASS_DIR)/xtc/parser/SemanticValue.class \
	      $(CLASS_DIR)/xtc/parser/ParseError.class \
              $(CLASS_DIR)/xtc/parser/ParseException.class \
              $(JAR_TMP)/xtc/parser
	$(JAR) cf $(BIN_DIR)/rats-runtime.jar -C $(JAR_TMP) xtc
	$(RMDIR) $(JAR_TMP)
endif

dist    :
ifdef JAVA_DEV_ROOT
	$(RMDIR) $(DIST_TMP)
	$(MKDIR) $(DIST_TMP)
	$(MKDIR) $(DIST_TMP)/classes
	$(CP)    $(CLASS_DIR)/.anchor $(DIST_TMP)/classes
	$(MKDIR) $(DIST_TMP)/doc
	$(CP)    $(DOC_DIR)/.anchor   $(DIST_TMP)/doc
	$(MKDIR) $(DIST_TMP)/bin
	$(CP)    $(BIN_DIR)/.anchor   $(DIST_TMP)/bin
	$(MKDIR) $(DIST_TMP)/src
	$(CPDIR) $(SOURCE_DIR)/xtc    $(DIST_TMP)/src
	$(MKDIR) $(DIST_TMP)/glr
	$(CP)    $(GLR_DIR)/README.txt   $(DIST_TMP)/glr
	$(CPDIR) $(GLR_DIR)/languages $(DIST_TMP)/glr
	$(CP)    $(GLR_DIR)/*.sdf     $(DIST_TMP)/glr
	$(CP)    $(GLR_DIR)/buildsdf.sh  $(DIST_TMP)/glr
	$(CPDIR) $(GLR_DIR)/ella      $(DIST_TMP)/glr
	$(CP)    $(GLR_DIR)/configure $(DIST_TMP)/glr
	$(CP)    $(GLR_DIR)/Makefile  $(DIST_TMP)/glr
	$(CP)    Makebase             $(DIST_TMP)
	$(CP)    Makefile             $(DIST_TMP)
	$(CP)    Makerules            $(DIST_TMP)
	$(CP)    xtc.manifest         $(DIST_TMP)
	$(CP)    rats.manifest        $(DIST_TMP)
	$(CP)    package-list         $(DIST_TMP)
	$(CP)    overview.html        $(DIST_TMP)
	$(CP)    history.html         $(DIST_TMP)
	$(CP)    grammar.css          $(DIST_TMP)
	$(CP)    development.html     $(DIST_TMP)
	$(CP)    setup.sh             $(DIST_TMP)
	$(CP)    site.exp             $(DIST_TMP)
	$(FIND) $(DIST_TMP) -name .DS_Store  -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -name .cvsignore -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -name '.#*'      -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -name '*#*'      -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -name '*~'       -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -depth -name CVS -exec $(RMDIR) \{\} \;
	$(RMDIR) $(DIST_TMP)/src/xtc/crt
	$(RMDIR) $(DIST_TMP)/src/xtc/il
	$(RMDIR) $(DIST_TMP)/src/xtc/lang/antlr
	$(RMDIR) $(DIST_TMP)/src/xtc/lang/blink/doc
	$(RMDIR) $(DIST_TMP)/src/xtc/lang/c
	$(RMDIR) $(DIST_TMP)/src/xtc/lang/c4
	$(RMDIR) $(DIST_TMP)/src/xtc/lang/javacc
	$(RMDIR) $(DIST_TMP)/src/xtc/lang/jeannie/doc
	$(RMDIR) $(DIST_TMP)/src/xtc/lang/overlog
	$(RMDIR) $(DIST_TMP)/src/xtc/lang/babble
	$(RMDIR) $(DIST_TMP)/src/xtc/oop
	$(RMDIR) $(DIST_TMP)/src/xtc/playground
	$(RMDIR) $(DIST_TMP)/src/xtc/typical
	$(RMDIR) $(DIST_TMP)/src/xtc/xform
	$(ZIP) -r xtc-core xtc
	$(RMDIR) $(DIST_TMP)
	$(MKDIR) $(DIST_TMP)
	$(CPDIR) $(FONDA_DIR)         $(DIST_TMP)/fonda
	$(MKDIR) $(DIST_TMP)/data
	$(CP)    $(DATA_DIR)/README.txt  $(DIST_TMP)/data
	$(CP)    $(DATA_DIR)/*.java   $(DIST_TMP)/data
	$(CP)    $(DATA_DIR)/check-parsetree.sh $(DIST_TMP)/data
	$(CP)    $(DATA_DIR)/sdf.sh   $(DIST_TMP)/data
	$(CP)    $(DATA_DIR)/ella.sh  $(DIST_TMP)/data
	$(MKDIR) $(DIST_TMP)/data/cpp
	$(CP)    $(DATA_DIR)/cpp/0001-remove-printlns.patch \
		 $(DIST_TMP)/data/cpp
	$(CP)    $(DATA_DIR)/cpp/nonbooleans.h \
		 $(DIST_TMP)/data/cpp
	$(CP)    $(DATA_DIR)/cpp/typechef_system_headers.tar \
		 $(DIST_TMP)/data/cpp
	$(FIND) $(DIST_TMP) -name .DS_Store  -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -name .cvsignore -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -name '.#*'      -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -name '*#*'      -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -name '*~'       -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP)/fonda -name '*.E'   -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP)/fonda -name '*.tmp' -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP)/fonda -name '*.proc2' -exec $(RM) \{\} \;
	$(FIND) $(DIST_TMP) -depth -name CVS -exec $(RMDIR) \{\} \;
	$(FIND) $(DIST_TMP)/fonda/cpp_testsuite/ | \
		egrep "\.test$$|\.diff$$|\.gcc$$" | \
		xargs rm -f
	$(RMDIR) $(DIST_TMP)/fonda/jeannie_testsuite/input/JavaBDD
	$(RMDIR) $(DIST_TMP)/fonda/typical_testsuite
	$(RMDIR) $(DIST_TMP)/fonda/overlog_testsuite
	$(RMDIR) $(DIST_TMP)/fonda/babble_testsuite
	$(ZIP) -r xtc-testsuite xtc
	$(RMDIR) $(DIST_TMP)
endif

SOURCE_LIST = $(THE_ROOT)/source-list.txt

stats   :
	@$(FIND) $(SOURCE_DIR)/xtc -name *.java -maxdepth 1 -print \
		> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/util -name *.java -print \
		>> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/tree -name *.java -print \
		>> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/type -name *.java -print \
		>> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/parser -name *.java -print \
		>> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/lang -name *.java -maxdepth 1 -print \
		>> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/lang/cpp -name *.java -maxdepth 1 -print \
		>> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/lang/jeannie -name *.java -maxdepth 1 -print \
		>> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/lang/blink -name *.java -maxdepth 1 -print \
		>> $(SOURCE_LIST)
	@$(FIND) $(SOURCE_DIR)/xtc/lang/blink/agent -name *.java -maxdepth 1 \
		-print >> $(SOURCE_LIST)
	@$(JAVANCSS) -package -object @$(SOURCE_LIST)
	@$(RM) $(SOURCE_LIST)

all     : classes jni

doc     :
	$(JAVADOC) $(JAVADOC_OPTIONS) $(PACKAGES)

#***************************************************************************
# Testing
#
# The following commands are valid:
#
#  1. make check-unit      : run unit tests for xtc
#  2. make check-rats      : run tests for Rats!
#  3. make check-c         : run tests for Java-based C analyzer
#  4. make check-c-layout  : run tests for C struct layout
#  5. make check-java      : run tests for the Java analyzer
#  6. make check-jeannie   : run tests for the Jeannie compiler
#  7. make check-cpp       : run tests for SuperC
#  8. make check           : run all tests
#
# RUNTESTFLAGS is a variable used to choose which files (.exp) to check
# Example: make check-parser RUNTESTFLAGS="compile.exp ..." 
#***************************************************************************

.PHONY	: pre-check check check-unit check-rats check-c check-c-layout
.PHONY  : check-java check-jeannie check-cpp check-babble

pre-check:
	@if [ ! -f $(CLASS_DIR)/xtc/util/UtilitiesTest.class ] || \
	    [ ! -f $(CLASS_DIR)/xtc/parser/Rats.class ] || \
	    [ ! -f $(CLASS_DIR)/xtc/lang/Java.class ] || \
	    [ ! -f $(CLASS_DIR)/xtc/lang/C.class ] || \
	    [ ! -f $(CLASS_DIR)/xtc/lang/JavaUnitTests.class ] || \
	    [ ! -f $(CLASS_DIR)/xtc/lang/jeannie/UnitTests.class ] ; then\
		echo ; \
		echo "*** Build xtc before running tests! ***" ; \
		echo ; \
		exit 1 ; \
	fi

check-unit: pre-check
	$(JUNIT) xtc.util.UtilitiesTest

check-rats: pre-check
	runtest --tool rats SUBTOOL=rats $(RUNTESTFLAGS)
	$(RM) rats.log rats.sum
	cd data ; ./check-parsetree.sh ; cd ..

check-c: pre-check
	runtest --tool xtc SUBTOOL=c-parser $(RUNTESTFLAGS)
	runtest --tool xtc SUBTOOL=c-analyzer $(RUNTESTFLAGS)
	$(RM) xtc.log xtc.sum

check-c-layout: pre-check
	$(MAKE) -C $(FONDA_DIR)/xtc_testsuite/layout test

check-java: pre-check
	$(JUNIT) xtc.lang.JavaUnitTests

check-jeannie: pre-check
	$(JUNIT) xtc.lang.jeannie.UnitTests
	$(MAKE) -C $(FONDA_DIR)/jeannie_testsuite cleanall
	$(MAKE) -C $(FONDA_DIR)/jeannie_testsuite test
	$(RMDIR) $(FONDA_DIR)/jeannie_testsuite/tmp

check-cpp: pre-check
	$(JAVA_DEV_ROOT)/src/xtc/lang/cpp/scripts/regression.sh -a \
		-C "$(CPP) $(CPPFLAGS)" \
		-S"-E -I $(FONDA_DIR)/cpp_testsuite/cpp/include1 \
					-I $(FONDA_DIR)/cpp_testsuite/cpp/include2 \
					-I $(FONDA_DIR)/cpp_testsuite/cpp/sys" \
		-G"   -I $(FONDA_DIR)/cpp_testsuite/cpp/include1 \
					-I $(FONDA_DIR)/cpp_testsuite/cpp/include2 \
					-I $(FONDA_DIR)/cpp_testsuite/cpp/sys" \
		$(FONDA_DIR)/cpp_testsuite/cpp/*.c \
		$(FONDA_DIR)/cpp_testsuite/preprocessor/*.c \
		$(FONDA_DIR)/cpp_testsuite/new_interactions/*.c
	# $(JAVA_DEV_ROOT)/src/xtc/lang/cpp/scripts/regression.sh -k .ast \
	# 	-C "$(CPP) $(CPPFLAGS)" \
	# 	$(FONDA_DIR)/cpp_testsuite/grammar/*.c \
	# 	$(FONDA_DIR)/cpp_testsuite/parser/*.c
	$(JAVA_DEV_ROOT)/src/xtc/lang/cpp/scripts/regression.sh \
		-C "$(CPP) $(CPPFLAGS)" \
		-a -S-E $(FONDA_DIR)/cpp_testsuite/new_interactions/*.c
	$(JAVA_DEV_ROOT)/src/xtc/lang/cpp/scripts/regression.sh -a -S-printSource \
		-C "$(CPP) $(CPPFLAGS)" \
		$(FONDA_DIR)/cpp_testsuite/grammar/*.c \
		$(FONDA_DIR)/cpp_testsuite/parser/*.c \
		$(FONDA_DIR)/cpp_testsuite/new_interactions/*.c

check-babble: pre-check
	runtest --tool babble $(RUNTESTFLAGS)	
	$(RM) babble.log babble.sum

check: pre-check check-unit check-rats check-c check-c-layout check-java \
       check-jeannie check-cpp
	@echo
	@echo "*** Happy happy joy joy! ***"
