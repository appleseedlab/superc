/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2009-2012 New York University
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */

#include <stdio.h>

#ifndef BISON_PARSER_FILE
#error "Set BISON_PARSER_FILE to be the header file containing the Bison parse tables."
#endif

#ifndef CLASS_NAME
#error "Set CLASS_NAME to be the name of the output Java class implementing the ParseTables interface."
#else
#endif

// Stringification of macro values
#define _str(x) #x
#define str(x) _str(x)

// Turn on YYDEBUG to get the Bison tables containing symbol information
#define YYDEBUG 1

// Empty definitions to avoid errors from c.tab.c.
#define YYPRINT(a,b,c)
int yylex() {}
int yyerror() {}
int l() {}

// Set all table types to 16-bit integers.
#define YYTYPE_UINT8 unsigned short int
#define YYTYPE_INT8 short int
#define YYTYPE_UINT16 unsigned short int
#define YYTYPE_INT16 short int

// Include the Bison parse tables
#include str(BISON_PARSER_FILE)

int main() {
  int i;
  
  printf("/*\n");
  printf(" * xtc - The eXTensible Compiler\n");
  printf(" * Copyright (C) 2009-2012 New York University\n");
  printf(" *\n");
  printf(" * This program is free software; you can redistribute it and/or\n");
  printf(" * modify it under the terms of the GNU General Public License\n");
  printf(" * version 2 as published by the Free Software Foundation.\n");
  printf(" *\n");
  printf(" * This program is distributed in the hope that it will be useful,\n");
  printf(" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
  printf(" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
  printf(" * GNU General Public License for more details.\n");
  printf(" *\n");
  printf(" * You should have received a copy of the GNU General Public License\n");
  printf(" * along with this program; if not, write to the Free Software\n");
  printf(" * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,\n");
  printf(" * USA.\n");
  printf(" */\n");
  printf("package xtc.lang.cpp;\n");
  printf("\n");

  printf("public class %s extends ParseTables {\n", str(CLASS_NAME));

  printf("  protected %s() {\n", str(CLASS_NAME));
  printf("    super(\n");
# define constructor_entry(x)  do { printf("          %d, // %s\n", x, #x); } while (0)
  constructor_entry(YYFINAL);
  constructor_entry(YYLAST);
  constructor_entry(YYNTOKENS);
  constructor_entry(YYNNTS);
  constructor_entry(YYNRULES);
  constructor_entry(YYNSTATES);
  constructor_entry(YYUNDEFTOK);
  constructor_entry(YYMAXUTOK);
  constructor_entry(YYEOF);
  constructor_entry(YYPACT_NINF);
  constructor_entry(YYTABLE_NINF);
# define constructor_entry_table(x)  do { printf("          %s_wrapper.%s,\n", #x, #x); } while (0)
# define constructor_entry_table_last(x)  do { printf("          %s_wrapper.%s);\n", #x, #x); } while (0)
  constructor_entry_table(yytranslate);
  /* constructor_entry_table(yyprhs); */
  /* constructor_entry_table(yyrhs); */
  constructor_entry_table(yytname);
  constructor_entry_table(yytoknum);
  constructor_entry_table(yyr1);
  constructor_entry_table(yyr2);
  constructor_entry_table(yydefact);
  constructor_entry_table(yydefgoto);
  constructor_entry_table(yypact);
  constructor_entry_table(yypgoto);
  constructor_entry_table(yytable);
  constructor_entry_table(yycheck);
  constructor_entry_table_last(yystos);
  printf("  }\n");

  printf("\n");

  printf("  public static %s getInstance() {\n", str(CLASS_NAME));
  printf("    if (ref == null)\n");
  printf("        ref = new %s();		\n", str(CLASS_NAME));
  printf("    return ref;\n");
  printf("  }\n");
  printf("\n");
  printf("  public Object clone()	throws CloneNotSupportedException {\n");
  printf("    throw new CloneNotSupportedException(); \n");
  printf("  }\n");
  printf("\n");
  printf("  private static %s ref;\n", str(CLASS_NAME));

  printf("\n");

  print_uint16("yytranslate", yytranslate, YYMAXUTOK);
  /* print_uint16("yyprhs", yyprhs, YYNRULES); */
  /* print_int16("yyrhs", yyrhs, yyprhs[YYNRULES] + yyr2[YYNRULES]); */
  print_char("yytname", yytname, YYNTOKENS + YYNNTS - 1);
  print_uint16("yytoknum", yytoknum, YYNTOKENS - 1);
  print_uint16("yyr1", yyr1, YYNRULES);
  print_uint16("yyr2", yyr2, YYNRULES);
  print_uint16("yydefact", yydefact, YYNSTATES - 1);
  print_int16("yydefgoto", yydefgoto, YYNNTS - 1);
  print_int16("yypact", yypact, YYNSTATES - 1);
  print_int16("yypgoto", yypgoto, YYNNTS - 1);
  print_int16("yytable", yytable, YYLAST);
  print_int16("yycheck", yycheck, YYLAST);
  print_uint16("yystos", yystos, YYNSTATES - 1);

  printf("}\n");

  return 0;
}

#define TABLEPRINTER(fname, ctype, pftype, jtype, limit) \
int print_ ## fname(char *name, ctype table[], int max) { \
  int i; \
   \
  /*printf("  public static final " #jtype "[] %s = {", name);*/ \
  printf("  public static class %s_wrapper {\n", name); \
  printf("    public static final " #jtype "[] %s = {", name); \
  for (i = 0; i <= max; i++) { \
    if (i > 0) printf(","); \
    if ((i % limit) == 0) printf("\n    "); \
    else printf(" "); \
    printf(pftype, table[i]); \
  } \
  printf("\n    };\n"); \
  printf("  }\n\n"); \
}

TABLEPRINTER(uint16, yytype_uint16, "%d", int, 10)

TABLEPRINTER(int16, yytype_int16, "%d", int, 10)

TABLEPRINTER(char, char *const, "\"%s\"", String, 1)

