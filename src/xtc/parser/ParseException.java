/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2005, 2007, 2012 Robert Grimm
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */
package xtc.parser;

/**
 * An exception representing a {@link ParseError parse error}.
 *
 * @author Robert Grimm
 * @version $Revision: 1.7 $
 */
public class ParseException extends RuntimeException {

  /**
   * Create a new parse exception.
   *
   * @param msg The message.
   */
  public ParseException(String msg) {
    super(msg);
  }

  /**
   * Create a new parse exception.
   *
   * @param msg The message.
   * @param cause The cause.
   */
  public ParseException(String msg, Throwable cause) {
    super(msg, cause);
  }

  /**
   * Create a new parse exception.
   *
   * @param cause The cause.
   */
  public ParseException(Throwable cause) {
    super(cause);
  }

}
