# Rules to generate the lexer and parser.

include $(JAVA_DEV_ROOT)/Makebase

SRC := CParseTables.java CTag.java CLexer.java CValues.java CActions.java

.PHONY: all clean

all: $(SRC)

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

clean:
	rm -f $(SRC) parser.action_switches parser.bison_content parser.epilogue parser.prologue parser.tab.c
