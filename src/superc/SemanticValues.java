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

import xtc.util.Pair;

/**
 * Support for semantic actions and parser context. *
 * @author Robert Grimm, Paul Gazzillo
 * @version $Revision: 1.4 $
 */
public interface SemanticValues {

  /**
   * Determine whether a production represents a complete semantic
   * unit.  The default implementation returns <code>true</code>.
   *
   * @param id The production ID.
   * @return <code>true</code> if the production is a complete semantc
   *   unit.
   */
  public boolean isComplete(int id);

  /** The types of semantic values. */
  public static enum ValueType {
    /** Create a regular node. */
    NODE,
    /** Create a node with all list elements. */
    LIST,
    /** Treat as layout, i.e., not having a value. */
    LAYOUT,
    /** Pass through the single value of an alternative. */
    PASS_THROUGH,
    /** Invoke arbitrary semantic action. */
    ACTION,
    /** The production has no semantic value. */
    VOID
  }

  /**
   * Determine a production's value type.  The default implementation
   * simply returns {@link ValueType#NODE}.
   *
   * @param id The production ID.
   * @return The corresponding value type.
   */
  public ValueType getValueType(int id);

  /**
   * Get the semantic value for the specific production.  The default
   * implementation signals an invalid state.
   *
   * @param id The production's symbol ID.
   * @param name The production's name.
   * @param values The values that make up the production.
   * @return The value of the production.
   */
  public Object getValue(int id, String name, Pair<Object> values);

  /**
   * Determine whether a production's AST should have a different name
   * than the original symbol name.
   *
   * @param id The production's symbol ID.
   * @return true if the name should be changed.
   */
  public boolean changeName(int id);

  /**
   * Get the new name for the production's AST node only if changeName
   * is true.
   *
   * @param id The production's symbol ID.
   * @return The new name of the production's AST or null if its name
   * shouldn't be changed.
   */
  public String newName(int id);
}
