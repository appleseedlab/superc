# Rules to generate the lexer and parser.

include $(JAVA_DEV_ROOT)/Makebase

SRC := P4ParseTables.java P4Tag.java P4Lexer.java P4Values.java P4Actions.java

.PHONY: all clean

all: $(SRC)

P4ParseTables.java: p4parser.y ../parsergen/gen_tables.c
	bison -o p4parser.tab.c p4parser.y
	# extract prologue, epilogue, and inline actions for inclusion in
	# P4Actions
	../parsergen/extract_bison_java.sh p4parser.y
	$(CC) $(CFLAGS) -I./ -DBISON_PARSER_FILE=p4parser.bison_content -DPACKAGE_NAME=superc.p4parser -DCLASS_NAME=P4ParseTables -o gen_c_tables ../parsergen/gen_tables.c
	./gen_c_tables > P4ParseTables.java
	$(RM) gen_c_tables
	$(MAKE) P4ParseTables.class

P4Tag.java: p4lexer.l
	$(CPP) $(CPPFLAGS) -DPACKAGE_NAME=superc.p4parser -DLANGUAGE_TAGS - < p4lexer.l | grep -v "^#" > P4Tag.java

P4Lexer.java: p4lexer.l
	#   filter out line directives for java compilation
	$(CPP) $(CPPFLAGS) -DPACKAGE_NAME=superc.p4parser - < p4lexer.l | grep -v "^#" > p4lexer.l.i
	$(JAVA) -jar $(JAVA_DEV_ROOT)/bin/JFlex.jar p4lexer.l.i
	$(RM) p4lexer.l.i

P4Values.java: p4parser.y
	../parsergen/extract_annotations.pl < p4parser.y | $(JAVA) superc.core.GenerateValuesClass superc.p4parser P4Values superc.p4parser.P4ParseTables > P4Values.java

P4Actions.java: p4parser.y
	../parsergen/extract_annotations.pl < p4parser.y | $(JAVA) superc.core.GenerateActionsClass superc.p4parser P4Actions superc.p4parser.P4ParseTables p4parser.action_switches p4parser.prologue p4parser.epilogue > P4Actions.java

clean:
	rm -f $(SRC) p4parser.action_switches p4parser.bison_content p4parser.epilogue p4parser.prologue p4parser.tab.c
