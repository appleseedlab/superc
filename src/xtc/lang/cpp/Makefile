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

PACKAGE     = xtc.lang.cpp
PACKAGE_LOC = xtc/lang/cpp

c_parse_tables = c.tab.c c.prologue c.action_switches c.epilogue	\
c.bison_content CParseTables.java

c_lexer = CTag.java CLexer.java

c_actions = CValues.java CActions.java

c_expression_parsers = expression.tab.c expression.prologue						\
expression.action_switches expression.epilogue												\
ExpressionParseTables.java ExpressionValues.java ExpressionRats.java

SOURCE = \
	BuiltinsGenerator.java \
	Builtins.java \
	GenerateValuesClass.java \
	GenerateActionsClass.java \
	ParseTables.java \
	SemanticValues.java \
	SemanticActions.java \
	CContext.java \
	$(c_parse_tables) \
	$(c_lexer) \
	$(c_actions) \
	$(c_expression_parsers) \
	Syntax.java \
	PresenceConditionManager.java \
	ParsingContext.java \
	DirectiveParser.java \
	HeaderFileManager.java \
	MacroTable.java \
	Preprocessor.java \
	ForkMergeParser.java \
	Clauses.java \
	TokenFilter.java \
	FilenameService.java \
	StreamTimer.java \
	StopWatch.java \
	TreeComparator.java \
	ExpressionParser.java \
	ConditionEvaluator.java \
	CTokenCreator.java \
	GCCShunt.java \
	cdiff.java \
	FunctionChecker.java \
	Desugarer.java \
	TypeBuilder.java \
	SuperC.java


JNI_SOURCE =

JAR_EXTRAS =


#***************************************************************************
#
# Include common part of makefile
#
#***************************************************************************

ifdef JAVA_DEV_ROOT
include $(JAVA_DEV_ROOT)/Makerules

manual: manual.pdf

manual.pdf: manual.tex
	pdflatex manual.tex
	pdflatex manual.tex
	pdflatex manual.tex

configure:
	if [ -f Builtins.java ]; then $(RM) Builtins.java; fi
	$(MAKE) BuiltinsGenerator.class
	$(MAKE) Builtins.java
	$(MAKE) Builtins.class
	if [ -f ${JAVA_DEV_ROOT}/classes/xtc/lang/cpp/SuperC.class ]; then $(RM) ${JAVA_DEV_ROOT}/classes/xtc/lang/cpp/SuperC.class; $(MAKE) SuperC.class; fi
	$(MAKE) select-typechecker

Builtins.java:
	$(CPP) $(CPPFLAGS) -v empty.c 2> sysdirs > /dev/null
	$(CPP) $(CPPFLAGS) -dM empty.c > builtins 2> /dev/null
	$(JAVA) xtc.lang.cpp.BuiltinsGenerator sysdirs builtins > Builtins.java
	$(RM) sysdirs
	$(RM) builtins

$(c_parse_tables): c.y gen_tables.c
	bison -o c.tab.c c.y

	# extract prologue, epilogue, and inline actions for inclusion in
	# CActions
	./extract_bison_java.sh c.y

	$(CC) $(CFLAGS) -DBISON_PARSER_FILE=c.bison_content -DCLASS_NAME=CParseTables -o gen_c_tables gen_tables.c
	./gen_c_tables > CParseTables.java
	$(RM) gen_c_tables
	$(MAKE) CParseTables.class

$(c_lexer): c.l Syntax.java $(c_parse_tables)
	$(CPP) $(CPPFLAGS) -DLANGUAGE_TAGS - < c.l | grep -v "^#" > CTag.java

	#   filter out line directives for java compilation
	$(CPP) $(CPPFLAGS) - < c.l | grep -v "^#" > c.l.lexer
	$(JAVA) -jar $(JAVA_DEV_ROOT)/bin/JFlex.jar c.l.lexer
	$(RM) c.l.lexer

$(c_actions): $(c_parse_tables)
	$(MAKE) GenerateValuesClass.class
	$(MAKE) GenerateActionsClass.class
	./extract_annotations.pl < c.y | $(JAVA) xtc.lang.cpp.GenerateValuesClass CValues xtc.lang.cpp.CParseTables > CValues.java
	./extract_annotations.pl < c.y | $(JAVA) xtc.lang.cpp.GenerateActionsClass CActions xtc.lang.cpp.CParseTables c.action_switches c.prologue c.epilogue > CActions.java

$(c_expression_parsers): expression.y gen_tables.c Condition.rats
	bison -o expression.tab.c expression.y

	./extract_bison_java.sh expression.y

	$(CC) $(CFLAGS) -DBISON_PARSER_FILE=expression.bison_content -DCLASS_NAME=ExpressionParseTables -o gen_expression_tables gen_tables.c
	./gen_expression_tables > ExpressionParseTables.java
	$(RM) gen_expression_tables
	$(MAKE) ExpressionParseTables.class

	$(MAKE) GenerateValuesClass.class
	$(MAKE) GenerateActionsClass.class
	./extract_annotations.pl < expression.y | $(JAVA) xtc.lang.cpp.GenerateValuesClass ExpressionValues xtc.lang.cpp.ExpressionParseTables > ExpressionValues.java
	./extract_annotations.pl < expression.y | $(JAVA) xtc.lang.cpp.GenerateActionsClass ExpressionActions xtc.lang.cpp.ExpressionParseTables expression.action_switches expression.prologue expression.epilogue > ExpressionActions.java

	# expression parser (rats)
	$(RATS) -option 'parser(xtc.lang.cpp.ExpressionRats)' Condition.rats
	$(MAKE) ExpressionRats.class

	# force rebuild of fml parser to use newly built expression parsers
	$(RM) ${JAVA_DEV_ROOT}/classes/xtc/lang/cpp/ForkMergeParser.class
	$(MAKE) ForkMergeParser.class

parsers:
	$(MAKE) $(c_parse_tables)
	$(MAKE) $(c_lexer)
	$(MAKE) $(c_actions)
	$(MAKE) $(c_expression_parsers)

# update c.y based on hidden link to selected grammar file
c.y: .c.y
	$(RM) -f $@
	echo -e " /* COPIED FROM SYMLINKED $< BY MAKE.  DO NOT EDIT. */\n" > $@
	cat $< >> $@
	chmod a-w $@

# update CContext.java based on hidden link to selected grammar file
CContext.java: .CContext.java
	$(RM) -f $@
	echo -e " /* COPIED FROM SYMLINKED $< BY MAKE.  DO NOT EDIT. */\n" > $@
	cat $< >> $@
	chmod a-w $@

select-parsingonly:
	$(RM) -f .c.y c.y .CContext.java CContext.java
	ln -s $(PWD)/c_parsingonly.y .c.y
	ln -s $(PWD)/CContext_parsingonly.java .CContext.java

select-typechecker:
	$(RM) -f .c.y c.y .CContext.java CContext.java
	ln -s $(PWD)/c_typechecker.y .c.y
	ln -s $(PWD)/CContext_typechecker.java .CContext.java

select-desugarer:
	$(RM) -f .c.y c.y .CContext.java CContext.java
	ln -s $(PWD)/c_desugarer.y .c.y
	ln -s $(PWD)/CContext_desugarer.java .CContext.java

which-grammar:
	@readlink .c.y | xargs basename
	@readlink .CContext.java | xargs basename

clobber-parsers :
	$(RM) $(c_parse_tables) $(c_lexer) $(c_actions) $(c_expression_parsers)

endif
