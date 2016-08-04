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
package xtc.lang.cpp;

import java.io.StringReader;
import java.io.IOException;

import xtc.lang.cpp.Syntax.Kind;
import xtc.lang.cpp.Syntax.Language;
import xtc.lang.cpp.Syntax.Text;

/**
 * A token creator implementation for C.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.6 $
 */
class CTokenCreator implements TokenCreator {

  public Language<?> createStringLiteral(String str) {
    return new Text<CTag>(CTag.STRINGliteral, str);
  }

  public Language<?> createIntegerConstant(int i) {
    return new Text<CTag>(CTag.INTEGERconstant, ((Integer) i).toString());
  }

  public Language<?> createIdentifier(String ident) {
    return new Text<CTag>(CTag.IDENTIFIER, ident);
  }

  public Language<?> pasteTokens(Language<?> t1, Language<?> t2) {
    // Paste the tokens and run the resulting string through the
    // lexer.
    String str = t1.getTokenText() + t2.getTokenText();
    StringReader sr = new StringReader(str);
    CLexer lexer = new CLexer(sr);
    Syntax pasted;
    Syntax next;

    try {
      pasted = lexer.yylex();
      next = lexer.yylex();
    } catch (IOException e) {
      e.printStackTrace();
      throw new RuntimeException();
    }

    // If the token-paste was successful, the next token will be an
    // EOF.
    if (next.kind() == Kind.EOF) {
      return pasted.toLanguage();
    } else {
      return null;
    }
  }
}
