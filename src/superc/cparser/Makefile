# Makefile 2
#***************************************************************************
#
# Java development root directory.
#
# (C) 1999 Jacob Dreyer - Geotechnical Software Services
# jacob.dreyer@geosoft.no - http://geosoft.no
#
# Modifications Copyright (C) 2001, 2004 Robert Grimm
# rgrimm@alum.mit.edu
#
# Modifications Copyright (C) 2007 New York University
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




#***************************************************************************
#
# This section describes the current package.
#
# o PACKAGE     - The complete package name.
# o PACKAGE_LOC - Same as PACKAGE but with "/"s instead of "."s.
# o SOURCE      - List of the source files. Remember extension.
# o JNI_SOURCE  - Files from SOURCE that are to be built with the JAVAH
#                 compiler.
# o JAR_EXTRAS  - None-class files and directories that are to be bundled
#                 into the jar archive.
#
#***************************************************************************

PACKAGE     = superc.cparser
PACKAGE_LOC = superc/cparser

SOURCE = \
	CParseTables.java \
	CTag.java \
	CLexer.java \
	CLexerCreator.java \
	CTokenCreator.java \
	CValues.java \
	CActions.java \
	CContext.java


JNI_SOURCE =

JAR_EXTRAS =


#***************************************************************************
#
# Include common part of makefile
#
#***************************************************************************

ifdef JAVA_DEV_ROOT
include $(JAVA_DEV_ROOT)/Makerules

CParseTables.java: parser.y ../parsergen/gen_tables.c
	bison -o parser.tab.c parser.y
	# extract prologue, epilogue, and inline actions for inclusion in
	# CActions
	../parsergen/extract_bison_java.sh parser.y
	$(CC) $(CFLAGS) -I./ -DBISON_PARSER_FILE=parser.bison_content -DPACKAGE_NAME=superc.cparser -DCLASS_NAME=CParseTables -o gen_c_tables ../parsergen/gen_tables.c
	./gen_c_tables > CParseTables.java
	$(RM) gen_c_tables
	$(MAKE) CParseTables.class

CTag.java: lexer.l
	$(CPP) $(CPPFLAGS) -DPACKAGE_NAME=superc.cparser -DLANGUAGE_TAGS - < lexer.l | grep -v "^#" > CTag.java

CLexer.java: lexer.l
	#   filter out line directives for java compilation
	$(CPP) $(CPPFLAGS) -DPACKAGE_NAME=superc.cparser - < lexer.l | grep -v "^#" > lexer.l.i
	$(JAVA) -jar $(JAVA_DEV_ROOT)/bin/JFlex.jar lexer.l.i
	$(RM) lexer.l.i

CValues.java: parser.y
	../parsergen/extract_annotations.pl < parser.y | $(JAVA) superc.core.GenerateValuesClass superc.cparser CValues superc.cparser.CParseTables > CValues.java

CActions.java: parser.y
	../parsergen/extract_annotations.pl < parser.y | $(JAVA) superc.core.GenerateActionsClass superc.cparser CActions superc.cparser.CParseTables parser.action_switches parser.prologue parser.epilogue > CActions.java

clobber:
	rm -f CParseTables.java CTag.java CLexer.java CValues.java CActions.java parser.action_switches parser.bison_content parser.epilogue parser.prologue parser.tab.c


endif
