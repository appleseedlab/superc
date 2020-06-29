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

import xtc.lang.cpp.Syntax.Kind;
import xtc.lang.cpp.Syntax.LanguageTag;
import xtc.lang.cpp.Syntax.ConditionalTag;
import xtc.lang.cpp.Syntax.DirectiveTag;
import xtc.lang.cpp.Syntax.Layout;
import xtc.lang.cpp.Syntax.Language;
import xtc.lang.cpp.Syntax.Text;
import xtc.lang.cpp.Syntax.Directive;
import xtc.lang.cpp.Syntax.Conditional;

import xtc.type.Type;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;
import xtc.lang.cpp.Multiverse.Element;

import xtc.lang.cpp.ForkMergeParser.OrderedSyntax;
import xtc.lang.cpp.ForkMergeParser.Lookahead;

/**
 * The symbol table that stores a scope's symbol bindings.
*/
public class SymbolTable {

  public static final Entry UNDEFINED = new Entry(null, null) {
      public String toString() {
        return "UNDEFINED_ENTRY";
      }
    };

  /**
   * A symbol table entry that holds a multiverse of types and
   * renamings.
   */
  public static class Entry {
    /**
     * The renaming of the variable for a given set of
     * configurations.
     */
    protected final String renaming;

    /**
     * The type under a given set of configurations.
     */
    protected final Type type;

    /** Create a new symbol table entry. */
    public Entry(String renaming, Type type) {
      this.renaming = renaming;
      this.type = type;
    }

    /**
     * Get the renaming field.
     *
     * @returns The renaming field.
     */
    public String getRenaming() {
      return renaming;
    }

    /**
     * Get the type field.
     *
     * @returns The type field.
     */
    public Type getType() {
      return type;
    }

    public String toString() {
      return renaming + " " + type.toString();
    }
  }

  public enum STField {
    TYPEDEF, IDENT, INIT, USED, VAR, GLOBAL_FUNDEF, STATIC_FUNDEF, FUNCALL,
  }

  /**
   * The symbol table's core data structure that maps symbols to a
   * multiverse of types and renamings.
   */
  protected HashMap<String, Multiverse<Entry>> map;

  /** The reference count for cleaning up the table BDDs */
  public int refs;

  /**
   * Create a new, empty symbol table.
   */
  public SymbolTable() {
    this.refs = 1;
    this.map = new HashMap<String, Multiverse<Entry>>();
    this.bools = new HashMap<String, EnumMap<STField, ConditionedBool>>();
  }

  /**
   * Update the number of references to this symbol table.
   */
  public SymbolTable addRef() {
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

      for (Multiverse<Entry> m : map.values()) {
        m.destruct();
      }
    }
  }

  /**
   * This is deprecated pending refactoring of the type-checker to
   * use the new API.
   */
  public void addMapping(String ident, Multiverse<Entry> unis)
  {
    Multiverse<Entry> value = map.get(ident);
    if (value == null)
      {
        Multiverse<Entry> newEntry = new Multiverse<Entry>();
        for (Element<Entry> x : unis)
          newEntry.add(x);
        map.put(ident, newEntry);
      }
    else
      {
        for (Element<Entry> x : unis)
          {
            boolean noCollision = true;
            for (Element<Entry> u : value)
              {
                noCollision = noCollision && u.getCondition().isMutuallyExclusive(x.getCondition());
              }
            if (!noCollision)
              {
                System.out.println("MultipleDef");
                //System.exit(1);
              }
            value.add(x);
          }
      }
    System.err.println(map.toString());
  }

  private static long varcount = 0;
  private final static char[] charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789".toCharArray();
  private final static Random random = new Random();
  private final static int RAND_SIZE = 5;

  protected String randomString(int string_size) {
    StringBuilder randomstring = new StringBuilder();
    for (int i = 0; i < string_size; i++) {
      randomstring.append(charset[random.nextInt(charset.length)]);
    }
    return randomstring.toString();
  }

  protected String mangleRenaming(String prefix, String ident) {
    // don't want to exceed c identifier length limit (31)
    if (ident.length() > 22) {
      // shorten ident to be at max, 22 chars
      StringBuilder sb = new StringBuilder(ident);
      sb = sb.delete(23, ident.length());
      ident = sb.toString();
    }
    return String.format("_%s%d%s_%s", prefix, varcount++, randomString(RAND_SIZE), ident);
  }

  
  /*******************************************************************
   The fields below are the original symbol table implementation that
   only tracks the kind of symbol in order to support C's
   context-sensitive parsing.
   *******************************************************************/

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


  // public void add(String ident, boolean typedef, PresenceCondition presenceCondition) {
  //   if (! map.containsKey(ident)) {
  //     map.put(ident,
  //             new TypedefVarEntry(typedef ? presenceCondition : null, typedef ? null : presenceCondition));
  //     presenceCondition.addRef();
  //   }
  //   else {
  //     TypedefVarEntry e;

  //     e = map.get(ident);

  //     if (typedef) {
  //       if (null == e.typedefCond) {
  //         e.typedefCond = presenceCondition;
  //         presenceCondition.addRef();
  //       }
  //       else {
  //         PresenceCondition or;

  //         or = e.typedefCond.or(presenceCondition);
  //         e.typedefCond.delRef();
  //         e.typedefCond = or;
  //       }
  //     }
  //     else {
  //       if (null == e.varCond) {
  //         e.varCond = presenceCondition;
  //         presenceCondition.addRef();
  //       }
  //       else {
  //         PresenceCondition or;

  //         or = e.varCond.or(presenceCondition);
  //         e.varCond.delRef();
  //         e.varCond = or;
  //       }
  //     }
  //   }
  // }

  public void copyBools(SymbolTable symtab) {
    for (String name : symtab.bools.keySet()) {
      for (STField field : symtab.bools.get(name).keySet()) {
        this.setbool(name, field, true, symtab.bools.get(name).get(field).trueCond);
      }
    }
  }

  //   public void addAll(SymbolTable symtab) {
  //     for (String str : symtab.map.keySet()) {
  //       if (! map.containsKey(str)) {
  //         TypedefVarEntry e = symtab.map.get(str);

  //         map.put(str, new TypedefVarEntry(e.typedefCond, e.varCond));

  //         if (null != e.typedefCond) {
  //           e.typedefCond.addRef();
  //         }

  //         if (null != e.varCond) {
  //           e.varCond.addRef();
  //         }
  //       }
  //       else {
  //         TypedefVarEntry d = map.get(str);
  //         TypedefVarEntry e = symtab.map.get(str);

  //         if (null != e.typedefCond) {
  //           if (null == d.typedefCond) {
  //             d.typedefCond = e.typedefCond;
  //             e.typedefCond.addRef();
  //           }
  //           else {
  //             PresenceCondition or;

  //             or = d.typedefCond.or(e.typedefCond);
  //             d.typedefCond.delRef();
  //             d.typedefCond = or;
  //           }
  //         }

  //         if (null != e.varCond) {
  //           if (null == d.varCond) {
  //             d.varCond = e.varCond;
  //             e.varCond.addRef();
  //           }
  //           else {
  //             PresenceCondition or;

  //             or = d.varCond.or(e.varCond);
  //             d.varCond.delRef();
  //             d.varCond = or;
  //           }
  //         }
  //       }
  //     }
  //   }
  // }

  // /** An entry in the symbol table. */
  // private static class TypedefVarEntry {
  //   /** The presence condition when the symbol is a typedef name. */
  //   PresenceCondition typedefCond;

  //   /** The presence condition when the symbol is a var name. */
  //   PresenceCondition varCond;

  //   /** Create a new entry.
  //    *
  //    * @param t The typedef name presence condition.
  //    * @param f The var name presence condition.
  //    */
  //   public TypedefVarEntry(PresenceCondition typedefCond, PresenceCondition varCond) {
  //     this.typedefCond = typedefCond;
  //     this.varCond = varCond;
  //   }

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

