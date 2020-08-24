# Rules to generate the lexer and parser.

include $(JAVA_DEV_ROOT)/Makebase

SRC := ExpressionRats.java

.PHONY: all clean

all: $(SRC)

ExpressionRats.java: Condition.rats Constant.rats Expression.rats Identifier.rats Reserved.rats Spacing.rats Symbol.rats
	$(RATS) -option 'parser(superc.expression.ExpressionRats)' Condition.rats

# $(c_expression_parser_superc): expression.y gen_tables.c Condition.rats
# 	bison -o expression.tab.c expression.y

# 	../generators/extract_bison_java.sh expression.y

# 	$(CC) $(CFLAGS) -DBISON_PARSER_FILE=expression.bison_content -DCLASS_NAME=ExpressionParseTables -o gen_expression_tables ../generators/gen_tables.c
# 	./gen_expression_tables > ExpressionParseTables.java
# 	$(RM) gen_expression_tables
# 	$(MAKE) ExpressionParseTables.class

# 	../generators/extract_annotations.pl < expression.y | $(JAVA) superc.generators.GenerateValuesClass ExpressionValues superc.expression.ExpressionParseTables > ExpressionValues.java
# 	../generators/extract_annotations.pl < expression.y | $(JAVA) superc.generators.GenerateActionsClass ExpressionActions superc.generators.ExpressionParseTables expression.action_switches expression.prologue expression.epilogue > ExpressionActions.java

clean:
	$(RM) $(SRC) # $(c_expression_superc_parser)
