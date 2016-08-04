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

import java.lang.StringBuilder;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;

import xtc.lang.cpp.Syntax.Kind;
import xtc.lang.cpp.Syntax.LanguageTag;
import xtc.lang.cpp.Syntax.PreprocessorTag;
import xtc.lang.cpp.Syntax.ConditionalTag;
import xtc.lang.cpp.Syntax.DirectiveTag;
import xtc.lang.cpp.Syntax.Layout;
import xtc.lang.cpp.Syntax.Language;
import xtc.lang.cpp.Syntax.Text;
import xtc.lang.cpp.Syntax.Directive;
import xtc.lang.cpp.Syntax.Conditional;

import xtc.tree.Location;

/**
 * Parses directives into compound tokens.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.17 $
 */
public class DirectiveParser implements Iterator<Syntax> {
  /** The input stream of tokens. */
  Iterator<Syntax> stream;
    
  /** We are at the beginning of a newline. */
  protected boolean newline;
   
  /** Create a new directive parser stream. */
  public DirectiveParser(Iterator<Syntax> stream, String filename) {
    this.stream = stream;
    this.newline = true;
  }
    
  /**
   * This function parses preprocessor directives.  The directive must
   * occur at the beginning of the new line, which is why we must keep
   * a flag indicating whether this is so.
   *
   * The function returns either the next Yytoken
   * from the lexer or a Directive which the function has parsed.
   *
   * The directive's location is taken from the location of the hash
   * symbol.
   *
   * @return the next token or compound token.
   */
  public Syntax next() {
    Syntax syntax = stream.next();
      
    // Parse the directive.
    if (newline && syntax.kind() == Kind.LANGUAGE
        && syntax.toLanguage().tag().ppTag() == PreprocessorTag.HASH) {
      List<Language<?>> list;
      String directiveName;
      DirectiveTag tag;
      boolean prevWhite = false;  // Flag for preserving whitespace.
      Location location = syntax.getLocation();
        
      list = new ArrayList<Language<?>>();
        
      do { // Skip the whitespace after the #.
        syntax = stream.next();

        if (syntax.kind() == Kind.LAYOUT
            && ((Layout) syntax).hasNewline()) {
          break;

        } else if (syntax.kind() == Kind.LANGUAGE) {
          break;
        }
      } while (true);

      if (syntax.kind() == Kind.LAYOUT && ((Layout) syntax).hasNewline()
          || syntax.kind() == Kind.EOF) {
        // It's an empty line marker.
        Directive empty = new Directive(DirectiveTag.LINEMARKER, list);
        empty.setLocation(location);

        return empty;
      }

      directiveName = syntax.toLanguage().getTokenText();

      if (tagMap.containsKey(directiveName)) {
        tag = tagMap.get(directiveName);

      } else if (syntax.toLanguage().tag().ppTag() == PreprocessorTag.NUMBER) {
        tag = DirectiveTag.LINEMARKER;
        list.add(syntax.toLanguage());
      } else {
        tag = DirectiveTag.INVALID;
        list.add(syntax.toLanguage());
      }

      do { // Skip the whitespace after the directive name.
        syntax = stream.next();

        if (syntax.kind() == Kind.LAYOUT
            && ((Layout) syntax).hasNewline()) {
          break;

        } else if (syntax.kind() == Kind.LANGUAGE) {
          break;
        }
      } while (true);

      if (syntax.kind() == Kind.LAYOUT && ((Layout) syntax).hasNewline()
          || syntax.kind() == Kind.EOF) {
        // It's an empty directive.
        Directive empty = new Directive(tag, list);
        empty.setLocation(location);

        return empty;
      }

      list.add(syntax.toLanguage());

      do { // Collect the tokens in the directive.
        syntax = stream.next();

        if (syntax.kind() == Kind.EOF) {
          // Don't swallow the EOF.
          break;

        } else if (syntax.kind() == Kind.LANGUAGE) {
          if (prevWhite) {
            syntax.setFlag(Preprocessor.PREV_WHITE);
            prevWhite = false;
          }
          list.add(syntax.toLanguage());

        } else if (syntax.kind() == Kind.LAYOUT
            && ((Layout) syntax).hasNewline()) {
          break;

        } else if (syntax.kind() == Kind.LAYOUT) {
          // Set the PREV_WHITE flag when a token is preceded by
          // whitespace.  This is used to preserve spacing in expanded
          // macros.
          if (syntax.getTokenText().length() > 0) {
            prevWhite = true;
          }
        }
      } while (true);

      newline = true;

      Directive directive = new Directive(tag, list);
      directive.setLocation(location);

      return directive;

    } else {
      // Check whether there is a newline.
      newline = (syntax.kind() == Kind.LAYOUT)
        && ((Layout) syntax).hasNewline();

      return syntax;
    }
  }
    
  public boolean hasNext() {
    return stream.hasNext();
  }

  private static final HashMap<String, DirectiveTag> tagMap
    = new HashMap<String, DirectiveTag>();

  static {
    tagMap.put("if", DirectiveTag.IF);
    tagMap.put("ifdef", DirectiveTag.IFDEF);
    tagMap.put("ifndef", DirectiveTag.IFNDEF);
    tagMap.put("elif", DirectiveTag.ELIF);
    tagMap.put("else", DirectiveTag.ELSE);
    tagMap.put("endif", DirectiveTag.ENDIF);
    tagMap.put("include", DirectiveTag.INCLUDE);
    tagMap.put("include_next", DirectiveTag.INCLUDE_NEXT);
    tagMap.put("define", DirectiveTag.DEFINE);
    tagMap.put("undef", DirectiveTag.UNDEF);
    tagMap.put("line", DirectiveTag.LINE);
    tagMap.put("error", DirectiveTag.ERROR);
    tagMap.put("warning", DirectiveTag.WARNING);
    tagMap.put("pragma", DirectiveTag.PRAGMA);
  }

  public void remove() {
    throw new UnsupportedOperationException();
  }
}
