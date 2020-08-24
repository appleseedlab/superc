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

PACKAGE     = superc.cdesugarer
PACKAGE_LOC = superc/cdesugarer

SOURCE = \
	CParseTables.java \
	CTag.java \
	CLexer.java \
	CValues.java \
	NamedFunctionT.java \
	SymbolTable.java \
	CActions.java \
	Multiverse.java \
	TypeBuilder.java \
	Declarator.java \
	Declaration.java \
	DesugaringOperators.java \
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

CParseTables.java: desugarer.y ../parsergen/gen_tables.c
	bison -o desugarer.tab.c desugarer.y
	# extract prologue, epilogue, and inline actions for inclusion in
	# CActions
	../parsergen/extract_bison_java.sh desugarer.y
	$(CC) $(CFLAGS) -I./ -DBISON_PARSER_FILE=desugarer.bison_content -DPACKAGE_NAME=superc.cdesugarer -DCLASS_NAME=CParseTables -o gen_c_tables ../parsergen/gen_tables.c
	./gen_c_tables > CParseTables.java
	$(RM) gen_c_tables
	$(MAKE) CParseTables.class

CTag.java: ../cparser/lexer.l
	$(CPP) $(CPPFLAGS) -DPACKAGE_NAME=superc.cdesugarer -DLANGUAGE_TAGS - < $< | grep -v "^#" > CTag.java

CLexer.java: ../cparser/lexer.l
	#   filter out line directives for java compilation
	$(CPP) $(CPPFLAGS) -DPACKAGE_NAME=superc.cdesugarer - < $< | grep -v "^#" > lexer.l.i
	$(JAVA) -jar $(JAVA_DEV_ROOT)/bin/JFlex.jar lexer.l.i
	$(RM) lexer.l.i

CValues.java: desugarer.y
	../parsergen/extract_annotations.pl < desugarer.y | $(JAVA) superc.core.GenerateValuesClass superc.cdesugarer CValues superc.cdesugarer.CParseTables > CValues.java

CActions.java: desugarer.y
	../parsergen/extract_annotations.pl < desugarer.y | $(JAVA) superc.core.GenerateActionsClass superc.cdesugarer CActions superc.cdesugarer.CParseTables desugarer.action_switches desugarer.prologue desugarer.epilogue > CActions.java

clobber:
	rm -f CParseTables.java CTag.java CLexer.java CValues.java CActions.java desugarer.action_switches desugarer.bison_content desugarer.epilogue desugarer.prologue desugarer.tab.c


endif
