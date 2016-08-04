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
package xtc.util;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.NoSuchElementException;

/**
 * Implementation of a pair.  Pairs are used to construct immutable
 * singly-linked lists, not unlike cons cells in Scheme (with the
 * differences that pairs are immutable and that the second pointer
 * always references another pair).
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public class Pair {

  /**
   * The pair representing the empty list.  This object serves as a
   * sentinel to avoid special-casing <code>null</code>.
   */
  public static final Pair EMPTY = new Pair();

  /** The value. */
  private final Object value;

  /** The next pair. */
  private final Pair   next;

  /** Create a new pair. */
  private Pair() {
    value = null;
    next  = null;
  }

  /**
   * Create a new pair.  The newly created pair represents a singleton
   * list.
   *
   * @param value The value.
   */
  public Pair(Object value) {
    this(value, EMPTY);
  }

  /**
   * Create a new pair.
   *
   * @param value The value.
   * @param next  The next pair.
   * @throws NullPointerException
   *    Signals that <code>next</code> is <code>null</code>.
   */
  public Pair(Object value, Pair next) {
    if (null == next) {
      throw new NullPointerException();
    }

    this.value = value;
    this.next  = next;
  }

  /**
   * Determine whether the list starting at this pair is empty.
   *
   * @return <code>true</code> if the list is empty.
   */
  public boolean isEmpty() {
    return (this == EMPTY);
  }

  /**
   * Get this pair's value.
   *
   * @return This pair's value.
   * @throws IllegalStateException
   *    Signals that this pair represents the empty list.
   */
  public Object value() {
    if (this == EMPTY) {
      throw new IllegalStateException();
    }

    return value;
  }

  /**
   * Get the next pair.
   *
   * @return The next pair.
   * @throws IllegalStateException
   *    Signals that this pair represents the empty list.
   */
  public Pair next() {
    if (this == EMPTY) {
      throw new IllegalStateException();
    }

    return next;
  }

  /**
   * Get the size of the list starting at this pair.
   *
   * @return The size.
   */
  public int size() {
    Pair pair = this;
    int  size = 0;

    while (pair != EMPTY) {
      size++;
      pair = pair.next;
    }

    return size;
  }

  /**
   * Get an iterator over the values of the list starting at this
   * pair.
   *
   * @return The iterator.
   */
  public Iterator iterator() {
    return new Iterator() {
        private Pair pair = Pair.this;

        public boolean hasNext() {
          return (EMPTY != pair);
        }

        public Object next() {
          if (EMPTY == pair) {
            throw new NoSuchElementException();
          } else {
            Object v = pair.value;
            pair     = pair.next;
            return v;
          }
        }

        public void remove() {
          throw new UnsupportedOperationException();
        }
      };
  }

  /**
   * Get a Java Collections list with the values of the list starting
   * at this pair.
   *
   * @return The Java Collections list.
   */
  public List list() {
    ArrayList list = new ArrayList(size());
    Pair      pair = this;

    while (EMPTY != pair) {
      list.add(pair.value);
      pair = pair.next;
    }

    return list;
  }

}
