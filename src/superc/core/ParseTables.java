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
package superc.core;

public class ParseTables {
  public final int YYFINAL;
  public final int YYLAST;
  public final int YYNTOKENS;
  public final int YYNNTS;
  public final int YYNRULES;
  public final int YYNSTATES;
  public final int YYUNDEFTOK;
  public final int YYMAXUTOK;
  public final int YYEOF;
  public final int YYPACT_NINF;
  public final int YYTABLE_NINF;

  public final int[] yytranslate;
  // public final int[] yyprhs;
  // public final int[] yyrhs;
  public final String[] yytname;
  public final int[] yytoknum;
  public final int[] yyr1;
  public final int[] yyr2;
  public final int[] yydefact;
  public final int[] yydefgoto;
  public final int[] yypact;
  public final int[] yypgoto;
  public final int[] yytable;
  public final int[] yycheck;
  public final int[] yystos;

  protected ParseTables(int YYFINAL, int YYLAST, int YYNTOKENS, int YYNNTS,
                        int YYNRULES, int YYNSTATES, int YYUNDEFTOK,
                        int YYMAXUTOK, int YYEOF, int YYPACT_NINF,
                        int YYTABLE_NINF, int[] yytranslate,
                        // int[] yyprhs, int[] yyrhs,
                        String[] yytname, int[] yytoknum,
                        int[] yyr1, int[] yyr2, int[] yydefact, int[] yydefgoto,
                        int[] yypact, int[] yypgoto, int[] yytable,
                        int[] yycheck, int[] yystos) {
    this.YYFINAL = YYFINAL;
    this.YYLAST = YYLAST;
    this.YYNTOKENS = YYNTOKENS;
    this.YYNNTS = YYNNTS;
    this.YYNRULES = YYNRULES;
    this.YYNSTATES = YYNSTATES;
    this.YYUNDEFTOK = YYUNDEFTOK;
    this.YYMAXUTOK = YYMAXUTOK;
    this.YYEOF = YYEOF;
    this.YYPACT_NINF = YYPACT_NINF;
    this.YYTABLE_NINF = YYTABLE_NINF;
    this.yytranslate = yytranslate;
    // this.yyprhs = yyprhs;
    // this.yyrhs = yyrhs;
    this.yytname = yytname;
    this.yytoknum = yytoknum;
    this.yyr1 = yyr1;
    this.yyr2 = yyr2;
    this.yydefact = yydefact;
    this.yydefgoto = yydefgoto;
    this.yypact = yypact;
    this.yypgoto = yypgoto;
    this.yytable = yytable;
    this.yycheck = yycheck;
    this.yystos = yystos;
  }
}
