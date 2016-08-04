/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004 Robert Grimm
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package xtc.util;

import java.io.IOException;
import java.io.Reader;
import java.io.Writer;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import java.util.regex.Pattern;

import xtc.tree.Location;

/**
 * Implmentation of utilities for language processors, focusing on
 * handling of I/O.
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public final class Utilities {

  /** Hide constructor. */
  private Utilities() { }

  /** The buffer size for pumping data. */
  private static final int BUFFER_SIZE = 4096;

  /** The buffer for pumping data. */
  private static char[] charBuffer = null;

  /**
   * The regular expression pattern used to split source code along
   * newlines.
   */
  public static final Pattern SPLIT = Pattern.compile("\r\n|\r|\n");

  /**
   * Flag for using doubled escape sequences.  Doubled escape
   * sequences will still read as an escape sequence, even if they are
   * included in a program source character or string.
   */
  public static final int ESCAPE_DOUBLE = 0x01;

  /**
   * Flag for escaping the '<code>[</code>', '<code>-</code>', and
   * '<code>]</code>' characters.
   */
  public static final int ESCAPE_REGEX = 0x02;

  /**
   * Flag for escaping non-printable ASCII characters using Unicode
   * escapes.
   */
  public static final int ESCAPE_UNICODE = 0x04;

  /** The escape flags for C/C++ escapes. */
  public static final int C_ESCAPES = 0x00;

  /** The escape flags for Java escapes. */
  public static final int JAVA_ESCAPES = ESCAPE_UNICODE;

  /** The escape flags for Java and regex escapes. */
  public static final int FULL_ESCAPES = ESCAPE_UNICODE | ESCAPE_REGEX;

  /**
   * Pump all data from the specified reader to the specified writer.
   *
   * @param in The reader.
   * @param out The writer.
   * @throws IOException Signals an exceptinal condition during I/O.
   */
  public static void pump(Reader in, Writer out) throws IOException {
    if (null == charBuffer) charBuffer = new char[BUFFER_SIZE];

    int number = in.read(charBuffer);
    while (-1 != number) {
      out.write(charBuffer, 0, number);
      number = in.read(charBuffer);
    }
  }

  /**
   * Determine whether the double escapes flag is set.
   *
   * @see #ESCAPE_DOUBLE
   *
   * @param flags The escape flags.
   * @return  <code>true</code> if the double escapes flag is set.
   */
  public static boolean useDoubleEscapes(int flags) {
    return (0 != (ESCAPE_DOUBLE & flags));
  }

  /**
   * Determine whether the regex escapes flag is set.
   *
   * @see #ESCAPE_REGEX
   *
   * @param flags The escape flags.
   * @return <code>true</code> if the regex escape flag is set.
   */
  public static boolean useRegexEscapes(int flags) {
    return (0 != (ESCAPE_REGEX & flags));
  }

  /**
   * Determine whether the Unicode escapes flag is set.
   *
   * @see #ESCAPE_UNICODE
   *
   * @param flags The escape flags.
   * @return <code>true</code> if the Unicode escapes flag is set.
   */
  public static boolean useUnicodeEscapes(int flags) {
    return (0 != (ESCAPE_UNICODE & flags));
  }

  /**
   * Escape the specified character into the specified string buffer.
   *
   * @param c The character.
   * @param buf The string buffer.
   * @param flags The escape flags.
   */
  public static void escape(char c, StringBuffer buf, int flags) {
    boolean useDouble  = useDoubleEscapes(flags);
    boolean useRegex   = useRegexEscapes(flags);
    boolean useUnicode = useUnicodeEscapes(flags);

    switch (c) {
    case '\b':
      if (useDouble) {
        buf.append("\\\\b");
      } else {
        buf.append("\\b");
      }
      break;
    case '\t':
      if (useDouble) {
        buf.append("\\\\t");
      } else {
        buf.append("\\t");
      }
      break;
    case '\n':
      if (useDouble) {
        buf.append("\\\\n");
      } else {
        buf.append("\\n");
      }
      break;
    case '\f':
      if (useDouble) {
        buf.append("\\\\f");
      } else {
        buf.append("\\f");
      }
      break;
    case '\r':
      if (useDouble) {
        buf.append("\\\\r");
      } else {
        buf.append("\\r");
      }
      break;
    case '\"':
      if (useDouble) {
        buf.append("\\\\\\\"");
      } else {
        buf.append("\\\"");
      }
      break;
    case '\'':
      if (useDouble) {
        buf.append("\\\\\\\'");
      } else {
        buf.append("\\\'");
      }
      break;
    case '-':
      if (useRegex) {
        if (useDouble) {
          buf.append("\\\\-");
        } else {
          buf.append("\\-");
        }
      } else {
        buf.append('-');
      }
      break;
    case '[':
      if (useRegex) {
        if (useDouble) {
          buf.append("\\\\[");
        } else {
          buf.append("\\[");
        }
      } else {
        buf.append('[');
      }
      break;
    case '\\':
      if (useDouble) {
        buf.append("\\\\\\\\");
      } else {
        buf.append("\\\\");
      }
      break;
    case ']':
      if (useRegex) {
        if (useDouble) {
          buf.append("\\\\]");
        } else {
          buf.append("\\]");
        }
      } else {
        buf.append(']');
      }
      break;
    default:
      if (useUnicode && ((' ' > c) || ('~' < c))) {
        String hex = Integer.toHexString(c);
        String padding;
        switch (hex.length()) {
        case 1:
          padding = "000";
          break;
        case 2:
          padding = "00";
          break;
        case 3:
          padding = "0";
          break;
        default:
          padding = "";
        }
        if (useDouble) {
          buf.append("\\\\");
        } else {
          buf.append("\\");
        }
        buf.append('u');
        buf.append(padding);
        buf.append(hex);

      } else {
        buf.append(c);
      }
    }
  }

  /**
   * Escape the specified string into the specified string buffer.
   *
   * @param s The string.
   * @param buf The string buffer.
   * @param flags The escape flags.
   */
  public static void escape(String s, StringBuffer buf, int flags) {
    final int length = s.length();
    for (int i=0; i<length; i++) {
      escape(s.charAt(i), buf, flags);
    }
  }

  /**
   * Escape the specified character.
   *
   * @param c The character.
   * @param flags The escape flags.
   * @return The escape character as a string.
   */
  public static String escape(char c, int flags) {
    StringBuffer buf = new StringBuffer(1);
    escape(c, buf, flags);
    return buf.toString();
  }

  /**
   * Escape the specified string.
   *
   * @param s The string.
   * @param flags The escape flags.
   * @return The escaped string.
   */
  public static String escape(String s, int flags) {
    StringBuffer buf = new StringBuffer(s.length());
    escape(s, buf, flags);
    return buf.toString();
  }

  /**
   * Unescape the specified string. This method unescapes standard
   * C-style escapes ('<code>\b</code>', '<code>\t</code>',
   * '<code>\n</code>', '<code>\f</code>', <code>'\r</code>',
   * '<code>\"</code>', '<code>\'</code>', and '<code>\\</code>') as
   * well as Java Unicode escapes.  To support regex-like character
   * classes, it also unescapes '<code>\-</code>', '<code>\[</code>',
   * and '<code>\]</code>'.
   *
   * @param s The string to unescape.
   * @return The unescaped string.
   */
  public static String unescape(String s) {
    if (-1 == s.indexOf('\\')) {
      return s;
    }

    final int    length = s.length();
    StringBuffer buf    = new StringBuffer(length);

    for (int i=0; i<length; i++) {
      char c = s.charAt(i);
      if ('\\' != c) {
        buf.append(c);
      } else {
        i++;
        c = s.charAt(i);

        switch (c) {
        case 'b':
          buf.append('\b');
          break;
        case 't':
          buf.append('\t');
          break;
        case 'n':
          buf.append('\n');
          break;
        case 'f':
          buf.append('\f');
          break;
        case 'r':
          buf.append('\r');
          break;
        case '"':
          buf.append('"');
          break;
        case '\'':
          buf.append('\'');
          break;
        case '-':
          buf.append('-');
          break;
        case '[':
          buf.append('[');
          break;
        case '\\':
          buf.append('\\');
          break;
        case ']':
          buf.append(']');
          break;
        case 'u':
          i += 4;
          int n;

          try {
            n = Integer.parseInt(s.substring(i-3, i+1), 16);
          } catch (NumberFormatException x) {
            throw new IllegalArgumentException("Illegal Unicode escape (\'\\u"
                                               + s.substring(i-3, i+1) + "\')");
          }
          buf.append((char)n);
          break;
        default:
          throw new IllegalArgumentException("Illegal escaped character (\'\\"
                                             + c + "\')");
        }
      }
    }
    return buf.toString();
  }

  /**
   * Convert the specified list to a human-readable representation.
   * This method uses <code>toString()</code> for each element in the
   * specified list to generate a human-readable representation.
   *
   * @param l The list.
   * @return The human-readable representation.
   */
  public static String format(List l) {
    final int length = l.size();

    if (0 == length) {
      return "";
    }

    StringBuffer buf = new StringBuffer();

    if (2 == length) {
      buf.append(l.get(0));
      buf.append(" and ");
      buf.append(l.get(1));

    } else {
      boolean  first = true;
      Iterator iter  = l.iterator();
      while (iter.hasNext()) {
        Object el    = iter.next();
        if (first) {
          first      = false;
        } else if (iter.hasNext()) {
          buf.append(", ");
        } else {
          buf.append(", and ");
        }
        buf.append(el);
      }
    }

    return buf.toString();
  }

  /**
   * Convert the specified identifier into a human-readable
   * description.  This method breaks identifiers using an upper case
   * character for each word component into a string of space
   * separated lower case words.
   *
   * @param id The identifier.
   * @return The corresponding description.
   */
  public static String toDescription(String id) {
    // Drop any suffixes.
    int idx = id.indexOf('$');
    if (-1 != idx) {
      id = id.substring(0, idx);
    }

    // Count the number of upper case characters.
    final int length     = id.length();
    int       upperCount = 0;

    for (int i=0; i<length; i++) {
      if (Character.isUpperCase(id.charAt(i))) {
        upperCount++;
      }
    }

    // No conversion is necessary if all characters are either lower
    // or upper case.
    if ((0 == upperCount) || (length == upperCount)) {
      return id;
    }

    // Do the actual conversion.
    StringBuffer buf = new StringBuffer(length + upperCount);

    for (int i=0; i<length; i++) {
      char c = id.charAt(i);

      if (Character.isUpperCase(c)) {
        if (0 != i) {
          buf.append(' ');
        }
        buf.append(Character.toLowerCase(c));
      } else {
        buf.append(c);
      }
    }

    return buf.toString();
  }


  /**
   * Print the specified (error or warning) message to the error
   * console.  The message is prefixed with the specified location
   * information and followed by the corresponding source line, with a
   * caret ('<code>^</code>') indicating the column.
   *
   * @see #msg(String,Location,String,String[])
   *
   * @param msg The message.
   * @param loc The source location.
   * @param source The source file, one line per array entry.
   */
  public static void msg(String msg, Location loc, String[] source) {
    msg(msg, loc, null, source);
  }

  /**
   * Print the specified (error or warning) message to the error
   * console.  If the specified location is non-null, the message is
   * prefixed with the location information.  Otherwise, if the
   * specified context is non-null, the message is prefixed with the
   * context.  If both the specified location and source are non-null,
   * the message is followed by the corresponding source line and a
   * caret ('<code>^</code>') to indicate the column.
   *
   * @param msg The message.
   * @param loc The source location.
   * @param context The alternative context.
   * @param source The source file, one line per array entry.
   */
  public static void msg(String msg, Location loc, String context,
                         String[] source) {
    if (null != loc) {
      System.err.print(loc.toString());
      System.err.print(": ");
    } else if (null != context) {
      System.err.print(context);
      System.err.print(": ");
    }

    System.err.println(msg);

    if ((null != loc) && (null != source)) {
      String line;
      try {
        line = source[loc.line - 1];
      } catch (ArrayIndexOutOfBoundsException x) {
        line = "";
      }
      System.err.println(line);
      for (int i=0; i<loc.column; i++) {
        System.err.print(' ');
      }
      System.err.println('^');
    }
  }

}
