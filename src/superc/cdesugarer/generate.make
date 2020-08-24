# Rules to generate the lexer and parser.

include $(JAVA_DEV_ROOT)/Makebase

SRC := CParseTables.java CTag.java CLexer.java CValues.java CActions.java

.PHONY: all clean

all: $(SRC)

CParseTables.java: desugarer.y ../parsergen/gen_tables.c
	bison -o desugarer.tab.c desugarer.y
	# extract prologue, epilogue, and inline actions for inclusion in
	# CActions
	../parsergen/extract_bison_java.sh desugarer.y
	$(CC) $(CFLAGS) -I./ -DBISON_PARSER_FILE=desugarer.bison_content -DPACKAGE_NAME=superc.cdesugarer -DCLASS_NAME=CParseTables -o gen_c_tables ../parsergen/gen_tables.c
	./gen_c_tables > CParseTables.java
	$(RM) gen_c_tables
	$(MAKE) CParseTables.class

CValues.java: desugarer.y
	../parsergen/extract_annotations.pl < desugarer.y | $(JAVA) superc.core.GenerateValuesClass superc.cdesugarer CValues superc.cdesugarer.CParseTables > CValues.java

CActions.java: desugarer.y
	../parsergen/extract_annotations.pl < desugarer.y | $(JAVA) superc.core.GenerateActionsClass superc.cdesugarer CActions superc.cdesugarer.CParseTables desugarer.action_switches desugarer.prologue desugarer.epilogue > CActions.java

CTag.java: ../cparser/lexer.l
	$(CPP) $(CPPFLAGS) -DPACKAGE_NAME=superc.cdesugarer -DLANGUAGE_TAGS - < $< | grep -v "^#" > CTag.java

CLexer.java: ../cparser/lexer.l
	#   filter out line directives for java compilation
	$(CPP) $(CPPFLAGS) -DPACKAGE_NAME=superc.cdesugarer - < $< | grep -v "^#" > lexer.l.i
	$(JAVA) -jar $(JAVA_DEV_ROOT)/bin/JFlex.jar lexer.l.i
	$(RM) lexer.l.i

CLexerCreator.java: ../cparser/CLexerCreator.java
	# copy the c parser's lexercreator, but change the package to cdesugarer
	sed 's/superc.cparser/superc.cdesugarer/' ../cparser/CLexerCreator.java > CLexerCreator.java

CTokenCreator.java: ../cparser/CTokenCreator.java
	# copy the c parser's tokencreator, but change the package to cdesugarer
	sed 's/superc.cparser/superc.cdesugarer/' ../cparser/CTokenCreator.java > CTokenCreator.java

clean:
	rm -f $(SRC) desugarer.action_switches desugarer.bison_content desugarer.epilogue desugarer.prologue desugarer.tab.c

