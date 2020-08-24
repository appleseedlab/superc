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

import java.util.Iterator;

import superc.core.Syntax.Kind;
import superc.core.Syntax.ErrorType;

/**
 * A stream that filters out all tokens except for regular and
 * compound tokens.
 *
 * @author Paul Gazzillo
 */
public class TokenFilter implements Iterator<Syntax> {
  /** The stream to read syntax from. */
  Iterator<Syntax> stream;

  /** Whether to keep errors or filter them. */
  boolean keep_errors;  

  /**
   * Create a new token filter stream.
   *
   * @param stream The stream to filter.
   * @param keep_errors Whether to keep error tokens or filter them.
   */
  public TokenFilter(Iterator<Syntax> stream, boolean keep_errors) {
    this.stream = stream;
    this.keep_errors = keep_errors;
  }

  /**
   * Create a new token filter stream.
   *
   * @param stream The stream to filter.
   */
  public TokenFilter(Iterator<Syntax> stream) {
    this(stream, false);
  }

  public Syntax next() {
    Syntax syntax = this.stream.next();

    // consume tokens until we get a parseable one
    while (true) {
      boolean keep_token;
      switch (syntax.kind()) {
      case LANGUAGE:
      case EOF:
      case CONDITIONAL:
        keep_token = true;
        break;
      case ERROR:
        if (keep_errors) {
          if (syntax.toError().type == ErrorType.FATAL ||
              syntax.toError().type == ErrorType.ERROR) {
            keep_token = true;
            break;
          }
        }
        // fall through
      default:
        keep_token = false;
        break;
      }

      if (keep_token) {
        break;
      }

      syntax = this.stream.next();
    }

    // while (syntax.kind() != Kind.LANGUAGE
    //        && syntax.kind() != Kind.EOF
    //        && syntax.kind() != Kind.CONDITIONAL) {
    //   syntax = this.stream.next();
    // }

    return syntax;
  }

  public boolean hasNext() {
    return this.stream.hasNext();
  }

  public void remove() {
    throw new RuntimeException();
  }
}
