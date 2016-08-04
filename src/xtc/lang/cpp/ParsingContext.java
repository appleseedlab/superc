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

import java.util.Collection;

import xtc.lang.cpp.ForkMergeParser.Lookahead;

/**
 * The interface for the parsing context plugin.
 *
 * @author Robert Grimm, Paul Gazzillo
 * @version $Revision: 1.1 $
 */
public interface ParsingContext {
  /**
   * Fork this context.  This method is invoked on regular fork
   * operations but not on fork operations due to context.
   *
   * @return The forked context.
   */
  public ParsingContext fork();

  /**
   * Determine whether the follow-set needs reclassification.  The
   * parser only class reclassify if this method returns true.
   * Therefore, this method should be faster than reclassify, which
   * will improve parser performance.
   *
   * @param set The follow-set.
   * @return true If the follow-set needs reclassification.
   */
  public boolean shouldReclassify(Collection<Lookahead> set);

  /**
   * Given the follow-set, reclassify tokens in the set and return
   * any new tokens that result from implicit conditionals, e.g. the
   * typedef/var name ambiguity in C.  Do not add tokens the
   * follow-set.
   *
   * @param set The follow-set.
   * @return Any new tokens or null if there are none.
   */
  public Collection<Lookahead> reclassify(Collection<Lookahead> set);

  /**
   * Determine whether this context can merge with another.  This
   * method is invoked on merge candidates that already observe the
   * merge discipline (modulo context).
   *
   * @param other The other context.
   * @return true if the contexts may merge.
   */
  public boolean mayMerge(ParsingContext other);

  /**
   * Merge this context with another.
   *
   * @param other The other context.
   * @return The merged context.
   */
  public ParsingContext merge(ParsingContext other);

  /**
   * Free any memory this context may be using.
   */
  public void free();
}
