/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004 Robert Grimm
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
package xtc.parser;

import java.io.IOException;
import java.io.Reader;

import xtc.tree.Location;

/**
 * The superclass of all packrat parsers.  Note that packrat parsers
 * also are {@link Result results}.  However, this is purely a
 * performance optimization and a packrat parser may only be treated
 * as a result if it is returned from the {@link #character()} method.
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public abstract class PackratParser extends Result {

  /**
   * The dummy packrat parser.  The dummy packrat parser must
   * <i>not</i> be used for parsing anything.  Its sole purpose is to
   * enable the creation of a {@link ParseError#DUMMY dummy parse
   * error}.
   */
  public static final PackratParser DUMMY = new PackratParser() {
      public PackratParser next() {
        throw new IllegalStateException("Dummy packrat parser");
      }
    };

  /** The reader for the character stream to be parsed. */
  protected final Reader  yyReader;

  /** The current index into the character stream. */
  protected final int     yyCount;

  /**
   * The file name.  This field is not final as to allow parsers, such
   * as the C preprocessor, to adjust the file name while parsing.
   */
  protected String        yyFile;

  /**
   * The flag for whether the previous character was a carriage
   * return.  This flag is needed to correctly track line and column
   * numbers.
   */
  protected boolean       yySeenCR;

  /**
   * The current line.  This field is not final as to allow parsers,
   * such as the C preprocessor, to adjust the line number while
   * parsing.
   */
  protected int           yyLine;

  /**
   * The current column.  This field is not final as to allow parsers,
   * such as the C preprocessor, to adjust the column number while
   * parsing.
   */
  protected int           yyColumn;

  /**
   * The field for this parser's character.  Note that -2 indicates
   * that the character has not yet been parsed and -1 that the
   * end-of-file has been reached.
   */
  private   int           yyChar;

  /** 
   * Create a new, empty packrat parser. This constructor is used only
   * for creating the {@link #DUMMY dummy packrat parser}.
   */
  private PackratParser() {
    yyReader = null;
    yyCount  = -1;
    yyFile   = "*** Not a file! ***";
    yySeenCR = false;
    yyLine   = -1;
    yyColumn = -1;
    yyChar   = -2;
  }

  /**
   * Create a new packrat parser.
   *
   * @param reader The reader for the character stream to be parsed.
   * @param file The name of the file backing the character stream.
   */
  public PackratParser(Reader reader, String file) {
    yyReader = reader;
    yyCount  = 0;
    yyFile   = file;
    yySeenCR = false;
    yyLine   = 1;
    yyColumn = 0;
    yyChar   = -2;
  }

  /**
   * Create a new packrat parser, moving ahead one character.  The
   * specified packrat parser must represent a valid character; i.e.,
   * its {@link #hasValue()} method must return <code>true</code>.
   * 
   * @param previous The previous packrat parser.
   */
  protected PackratParser(PackratParser previous) {
    yyReader = previous.yyReader;
    yyCount  = previous.yyCount + 1;
    yyChar   = -2;
  }

  /**
   * Get the parser for the next character.  A concrete implementation
   * of this method should simply return the parser object created by
   * using the {@link #PackratParser(PackratParser)} constructor with
   * <code>this</code> as the argument.
   *
   * @return The parser for the next character.
   */
  protected abstract PackratParser next();
  
  /**
   * Update the location information for this parser.  This method
   * correctly sets this parser's {@link #yyFile}, {@link #yySeenCR},
   * {@link #yyLine}, and {@link #yyColumn} fields.  It must be
   * invoked right after setting the previous parser's {@link #yyChar}
   * field to its character value.
   *
   * @param previous The previous packrat parser.
   */
  private void updateLocation(PackratParser previous) {
    yyFile       = previous.yyFile;

    switch (previous.yyChar) {
    case '\t':
      yySeenCR   = false;
      yyLine     = previous.yyLine;
      yyColumn   = ((previous.yyColumn >> 3) + 1) << 3;
      return;
    case '\n':
      yySeenCR   = false;
      if (previous.yySeenCR) {
        yyLine   = previous.yyLine;
        yyColumn = previous.yyColumn;
      } else {
        yyLine   = previous.yyLine + 1;
        yyColumn = 0;
      }
      return;
    case '\r':
      yySeenCR   = true;
      yyLine     = previous.yyLine + 1;
      yyColumn   = 0;
      return;
    default:
      yySeenCR   = false;
      yyLine     = previous.yyLine;
      yyColumn   = previous.yyColumn + 1;
      return;
    }
  }

  /**
   * Parse a character.  This method returns the result of parsing the
   * next character offered by this parser's character stream.  If
   * there is another character, the result is this parser; otherwise,
   * it is a {@link ParseError}.
   *
   * @return The corresponding result.
   * @throws IOException Signals an exceptional condition while
   *   accessing the character stream.
   */
  protected final Result character() throws IOException {
    switch (yyChar) {
    case -2:
      yyChar = yyReader.read();
      if (0 <= yyChar) {
        parser = next();
        parser.updateLocation(this);
        return this;
      }
      /* Fall through. */

    case -1:
      return new ParseError("End-of-file", this);
      
    default:
      return this;
    }
  }

  public boolean hasValue() {
    return (0 <= yyChar);
  }

  public char charValue() {
    if (0 <= yyChar) {
      return (char)yyChar;
    } else {
      throw new IllegalStateException("No character value available");
    }
  }

  public Object semanticValue() {
    throw new IllegalStateException("No semantic value available");
  }

  public ParseError parseError() {
    return ParseError.DUMMY;
  }

  public SemanticValue createValue(Object value, ParseError error) {
    return new SemanticValue(value, parser, error);
  }

  /**
   * Get the difference between this parser and the specified parser.
   * Both parsers must parse the same character stream.
   *
   * @param o The other parser.
   * @return The difference as a string.
   */
  protected final String getDifference(PackratParser o) {
    PackratParser p;
    int           n;

    if (yyCount < o.yyCount) {
      p = this;
      n = o.yyCount - yyCount;
    } else if (yyCount > o.yyCount) {
      p = o;
      n = yyCount - o.yyCount;
    } else {
      return "";
    }

    StringBuffer buf = new StringBuffer(n);

    int i = 0;
    do {
      buf.append((char)p.yyChar);
      p = p.parser;
      i++;
    } while (i < n);

    return buf.toString();
  }

  /**
   * Get the current file name.
   *
   * @return The file name.
   */
  public final String file() {
    return yyFile;
  }

  /**
   * Get the current line number.
   *
   * @return The line number.
   */
  public final int line() {
    return yyLine;
  }

  /**
   * Get the current column number.
   *
   * @return The column number.
   */
  public final int column() {
    return yyColumn;
  }

  /**
   * Get the current location.
   *
   * @return The location.
   */
  public final Location location() {
    return new Location(yyFile, yyLine, yyColumn);
  }

  public String toString() {
    StringBuffer buf = new StringBuffer();

    buf.append(yyFile);
    buf.append(':');
    buf.append(Integer.toString(yyLine));
    buf.append(',');
    buf.append(Integer.toString(yyColumn));
    buf.append(": ");

    PackratParser p = this;
    int           i = 0;

    do {
      if (0 <= p.yyChar) {
        buf.append((char)p.yyChar);
        p = p.parser;
        i++;

        if ((20 <= i) && (0 <= p.yyChar)) {
          buf.append(" ...");
        }
      } else {
        break;
      }
    } while (i < 20);

    return buf.toString();
  }

}

