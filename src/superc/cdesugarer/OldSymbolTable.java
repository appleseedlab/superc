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
package superc.cdesugarer;

import java.util.ArrayList;
import java.util.Collection;
import java.util.EnumMap;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.List;
import java.util.Random;
import java.util.Iterator;

import xtc.tree.Location;

import superc.core.Syntax.Kind;
import superc.core.Syntax.LanguageTag;
import superc.core.Syntax.ConditionalTag;
import superc.core.Syntax.DirectiveTag;
import superc.core.Syntax.Layout;
import superc.core.Syntax.Language;
import superc.core.Syntax.Text;
import superc.core.Syntax.Directive;
import superc.core.Syntax.Conditional;

import xtc.type.UnitT;

import superc.cdesugarer.Multiverse.Element;

import superc.core.PresenceConditionManager;
import superc.core.PresenceConditionManager.PresenceCondition;

import superc.core.ForkMergeParser.OrderedSyntax;
import superc.core.ForkMergeParser.Lookahead;

/**
 * The symbol table that stores a scope's symbol bindings.
 */
public class OldSymbolTable {
  /** The reference count for cleaning up the table BDDs */
  public int refs;

  /**
   * Create a new, empty symbol table.
   */
  public OldSymbolTable() {
    this.refs = 1;
    this.bools = new HashMap<String, EnumMap<STField, ConditionedBool>>();
  }

  /**
   * Update the number of references to this symbol table.
   */
  public OldSymbolTable addRef() {
    refs++;

    return this;
  }

  /**
   * Decrement the number of references to this symbol table,
   * freeing BDDs once we reach zero.
   */
  public void delRef() {
    refs--;
      
    if (0 == refs) {  //clean up symbol table
      for (String name : this.bools.keySet()) {
        for (STField field : this.bools.get(name).keySet()) {
          ConditionedBool cb = this.bools.get(name).get(field);
          cb.trueCond.delRef();
        }
      }
    }
  }
  
  /*******************************************************************
   ***** The fields below are the original symbol table implementation
   ***** that only tracks the kind of symbol in order to support C's
   ***** context-sensitive parsing.
   *******************************************************************/

  public enum STField {
    TYPEDEF, IDENT, INIT, USED, VAR, GLOBAL_FUNDEF, STATIC_FUNDEF, FUNCALL,
  }

  /**
   * Simple symbol table tracking kind of symbol.
   */
  public HashMap<String, EnumMap<STField, ConditionedBool>> bools;

  /**
   * Set the presence condition of the boolean value of the given
   * field.
   *
   * @param name The name of the symbol.
   * @param field The field of the symbol table entry to update.
   * @param value The boolean value to set.
   * @param condition The condition of the boolean value.
   */
  public void setbool(String name,
                      STField field,
                      boolean value,
                      PresenceCondition condition) {
    if (! bools.containsKey(name)) {
      // create a new symbol table entry
      bools.put(name, new EnumMap<STField, ConditionedBool>(STField.class));
    }

    if (! bools.get(name).containsKey(field)) {
      // create a new field for the symbol table entry
      PresenceCondition trueCond;
      if (value) {
        trueCond = condition.addRef();
      } else {
        trueCond = condition.not();
      }
      bools.get(name).put(field, new ConditionedBool(trueCond));
    } else {
      // update the existing field's presence conditions
      ConditionedBool cb = bools.get(name).get(field);
      if (value) {
        PresenceCondition union = cb.trueCond.or(condition);
        cb.trueCond.delRef();
        cb.trueCond = union;
      } else {
        PresenceCondition not = condition.not();
        PresenceCondition union = cb.trueCond.and(not);
        cb.trueCond.delRef();
        cb.trueCond = union;
        not.delRef();
      }
    }
  }

  /**
   * Get all names given a field.
   *
   * @param field The given field.
   * @return A list of names.
   */
  public Set<String> getNames(STField field) {
    Set<String> a = new HashSet<String>();

    for (String s : bools.keySet()) {
      if (bools.get(s).containsKey(field)) {
        a.add(s);
      }
    }

    return a;
  }

  /**
   * Get the presence condition of a given name and field
   * combination.
   *
   * @param name The symbol name.
   * @param field The symbol field.
   * @return The presence condition.
   */
  public PresenceCondition getPresenceCond(String name,
                                           STField field) {
    if (bools.containsKey(name) &&
        bools.get(name).containsKey(field)) {
      return bools.get(name).get(field).trueCond;
    }
    return null;
  }

  public void copyBools(OldSymbolTable symtab) {
    for (String name : symtab.bools.keySet()) {
      for (STField field : symtab.bools.get(name).keySet()) {
        this.setbool(name, field, true, symtab.bools.get(name).get(field).trueCond);
      }
    }
  }

  /**
   * A boolean that maintain a boolean expression for when the
   * variable can be true.
   */
  protected static class ConditionedBool {
    /** The presence condition when true. */
    public PresenceCondition trueCond;

    /** Create a new entry.
     *
     * @param trueCond Condition when true.
     */
    public ConditionedBool(PresenceCondition trueCond) {
      this.trueCond = trueCond;
    }
  }
}
