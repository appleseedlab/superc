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

import xtc.type.Type;
import xtc.type.UnitT;

import superc.cdesugarer.Multiverse.Element;

import superc.core.PresenceConditionManager;
import superc.core.PresenceConditionManager.PresenceCondition;

import superc.core.ForkMergeParser.OrderedSyntax;
import superc.core.ForkMergeParser.Lookahead;

/**
 * The symbol table that stores a scope's symbol bindings.
 */
public class SymbolTable implements Iterable<String> {

  public static final Entry UNDECLARED = new Entry(null) {
      public Type getType() {
        throw new UnsupportedOperationException("the undeclared symbol table entry has no type");
      }

      public String toString() {
        return "<UNDECLARED>";
      }
    };
    
  public static final Entry ERROR = new Entry(null) {
      public Type getType() {
        throw new UnsupportedOperationException("the error symbol table entry has no type");
      }

      public String toString() {
        return "<ERROR>";
      }
    };
    
  /**
   * A symbol table entry that holds a type.
   */
  public static class Entry {
    // TODO: make this abstract and have type for VALID entries, have an error message for other kinds

    /**
     * The type under a given set of configurations.  This type should
     * be a VariableT, AliasT, or NamedFunctionT, all of which store
     * the renaming of the symbol.
     */
    protected final Type type;

    /** Create a new symbol table entry. */
    public Entry(Type type) {
      this.type = type;
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
      return String.format("(TYPE=%s)", getType().toString());
    }
  }

  /**
   * The symbol table's core data structure that maps symbols to a
   * multiverse of types.
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
   * Get the symbol table entries for the given identifier under the
   * given presence conditions.  This filters the Multiverse by
   * trimming entries infeasible under the given condition.
   *
   * @param ident The identifier to look up.
   * @param cond The presence condition.
   * @returns A new Multiverse instance containing the entries under
   * the given condition.  If the symbol was never seen before, it
   * returns a Multiverse that contains only the UNDECLARED entry.
   */
  public Multiverse<Entry> get(String ident, PresenceCondition cond) {
    Multiverse<Entry> newmv;
    if (! this.map.containsKey(ident)) {
      // Create a new multiverse for the symbol that has only the
      // UNDECLARED entry under the True condition
      newmv = new Multiverse<Entry>();

      PresenceCondition trueCond = cond.presenceConditionManager().newTrue();
      newmv.add(UNDECLARED, trueCond);
      trueCond.delRef();

      PresenceCondition falseCond = cond.presenceConditionManager().newFalse();
      newmv.add(ERROR, falseCond);
      falseCond.delRef();
      
      Multiverse<Entry> filtered = newmv.filter(cond);
      newmv.destruct();
      return filtered;
    } else {
      return this.map.get(ident).filter(cond);
    }
  }

  /**
   * Add a new entry to the symbol table.  This maintains two
   * invariants: (1) all entries are mutually-exclusive and (2) all
   * entries together union to True.  This ensures that the UNDECLARED
   * entry is always present in the Multiverse, even if its presence
   * condition is False.  This method will error out if a symbol is
   * redeclared in some presence condition.  To ensure this does not
   * happen, use get() under the putCond first and see if there are
   * any mapped symbols.  For type-checking, emit errors for these
   * redeclarations and revise the presence condition.
   *
   * @param putEntry The entry to add, either a regular entry or the
   * canonical UNDECLARED or ERROR entries
   * @param putCond The presence condition under which to update the
   * table.
   */
  protected void put(String ident, SymbolTable.Entry putEntry, PresenceCondition putCond) {
    if (! putCond.isFalse()) {
      if (! this.map.containsKey(ident)) {
        // Create a new multiverse for the symbol that has only the
        // UNDECLARED entry under the True condition
        Multiverse<Entry> newmv = new Multiverse<Entry>();

        PresenceCondition trueCond = putCond.presenceConditionManager().newTrue();
        newmv.add(UNDECLARED, trueCond);
        trueCond.delRef();

        PresenceCondition falseCond = putCond.presenceConditionManager().newFalse();
        newmv.add(ERROR, falseCond);
        falseCond.delRef();

        this.map.put(ident, newmv);
      }

      // TODO: include way to check for invalid type redeclaration and
      // convert it to a type error

      Multiverse<Entry> oldmv = this.map.get(ident);
      Multiverse<Entry> newmv = new Multiverse<Entry>();

      /* lifetime for presence conditions */ {
        PresenceCondition undeclaredCond = null;
        PresenceCondition errorCond = null;
        PresenceCondition notPutCond = putCond.not();
        PresenceCondition collectErrors = putCond.presenceConditionManager().newFalse();

        for (Element<Entry> entry : oldmv) {
          if (UNDECLARED == entry.getData()) {
            if (null != undeclaredCond) {
              throw new AssertionError("there should only be one UNDECLARED entry in the symbol table");
            }
            undeclaredCond = entry.getCondition();
            undeclaredCond.addRef();
          } else if (ERROR == entry.getData()) {
            if (null != errorCond) {
              throw new AssertionError("there should only be one ERROR entry in the symbol table");
            }
            errorCond = entry.getCondition();
            errorCond.addRef();
          } else { // lifetime for andNotNewCond and andNewCond
            // update old declarations' conditions and check for redeclarations
            PresenceCondition andNotNewCond = entry.getCondition().and(notPutCond);
            PresenceCondition andNewCond = entry.getCondition().and(putCond);
              
            if (! andNewCond.isFalse() && putEntry != ERROR) {
              throw new IllegalStateException("only updates to the ERROR entry can be used to updated an existing entry");
              // // redeclarations cause the symbol to be undeclared
              // /*PresenceCondition updateCollectErrors = collectErrors.or(andNewCond);
              // collectErrors.delRef();
              // collectErrors = updateCollectErrors;
              // if (putEntry != ERROR) {*/
              //   System.err.println(String.format("FATAL: redeclaration of %s turned into an error entry.  use xtc.type.C.equal to check for legal redeclaration to same type.", ident));
              //   System.exit(1);
              //   //}
            }
                
            if (! andNotNewCond.isFalse()) {
              // update the presence conditions of prior declarations
              newmv.add(entry.getData(), andNotNewCond);
            }
              
            andNotNewCond.delRef();
            andNewCond.delRef();
          } // end lifetime (and for loop)
        }

        if (null == undeclaredCond) {
          throw new AssertionError("the undeclared entry should always be present in the symbol table");
        }

        if (null == errorCond) {
          throw new AssertionError("the error entry should always be present in the symbol table");
        }

        // add a new declaration
        if (UNDECLARED != putEntry && ERROR != putEntry) {
          PresenceCondition newCond = undeclaredCond.and(putCond);
          // putCond's lifetime managed by caller
          if (! newCond.isFalse()) {
            newmv.add(putEntry, newCond);  // cond's lifetime managed by caller
          } else {
            System.err.println("WARNING: entry was infeasible due to redeclarations");
          }
          newCond.delRef();  // add calls addRef()
        }

        // update the errors to include the remapping errors
        PresenceCondition newError = collectErrors.or(errorCond);
        if (ERROR == putEntry) {
          PresenceCondition updatedError = newError.or(putCond);
          newError.delRef();
          newError = updatedError;
        }
        newmv.add(ERROR, newError);
        
        // update the undeclared conditions to include the new entry
        // if it's an undeclared entry or to exclude the new entry
        // otherwise
        PresenceCondition newUndeclared;
        if (UNDECLARED == putEntry) {
          newUndeclared = undeclaredCond.or(putCond);
        } else {
          newUndeclared = undeclaredCond.and(notPutCond);
        }
        newmv.add(UNDECLARED, newUndeclared);

        newUndeclared.delRef();
        newError.delRef();

        collectErrors.delRef();
        notPutCond.delRef();
        undeclaredCond.delRef();
        errorCond.delRef();
      } // end lifetime for presence conditions

      // check invariants
      {
        PresenceCondition union = putCond.presenceConditionManager().newFalse();

        // has redundant checks
        for (Element<Entry> entry_i : newmv) {
          PresenceCondition newUnion = union.or(entry_i.getCondition());
          union.delRef();
          union = newUnion;
          
          for (Element<Entry> entry_j : newmv) {
            if (entry_i != entry_j) {
              if (! entry_i.getCondition().isMutuallyExclusive(entry_j.getCondition())) {
                throw new AssertionError("symbol table invariant violation: entries should be in mutually-exclusive configurations");
              }
            }
          }
        }

        PresenceCondition notUnion = union.not();
        if (! notUnion.isFalse()) {
          throw new AssertionError("symbol table invariant violation: entries should cover all possible configurations, i.e., union to true");
        }
        notUnion.delRef();
        
        union.delRef();
      }
    
      
      this.map.put(ident, newmv);
      oldmv.destruct();
    } else {
      // nothing to add, since the given presence condition is False
    }

    // System.err.println(String.format("after put: %s -> %s", ident, map.get(ident)));
    System.err.println(toString());
  }

  /**
   * Add a new symbol table entry for the given identifier.
   *
   * @param ident The identifier to enter.
   * @param type The type.
   * @param putCond The presence condition.
   */
  public void put(String ident, Type type, PresenceCondition putCond) {
    Entry entry = new Entry(type);
    put(ident, entry, putCond);
  }

  /**
   * Add an entry representing a type error.
   *
   * @param ident The identifier to enter.
   * @param putCond The presence condition.
   */
  public void putError(String ident, PresenceCondition putCond) {
    put(ident, ERROR, putCond);
  }

  /**
   * Creates an iterator over the symbols.
   *
   * @return the iterator.
   */
  public Iterator<String> iterator() {
    return map.keySet().iterator();
  }

  // private static long varcount = 0;
  // private final static char[] charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789".toCharArray();
  // private final static Random random = new Random();
  // private final static int RAND_SIZE = 5;

  // /**
  //  * Produce a random string of a given size.
  //  *
  //  * @returns The random string.
  //  */
  // protected String randomString(int string_size) {
  //   StringBuilder randomstring = new StringBuilder();
  //   for (int i = 0; i < string_size; i++) {
  //     randomstring.append(charset[random.nextInt(charset.length)]);
  //   }
  //   return randomstring.toString();
  // }

  // /**
  //  * Mangle the given identifier to avoid naming clashes when symbols
  //  * are multiply-declared.
  //  */
  // protected String mangleRenaming(String prefix, String ident) {
  //   // don't want to exceed c identifier length limit (31)
  //   if (ident.length() > 22) {
  //     // shorten ident to be at max, 22 chars
  //     StringBuilder sb = new StringBuilder(ident);
  //     sb = sb.delete(23, ident.length());
  //     ident = sb.toString();
  //   }
    
  //   // return String.format("_%s%d_%s", prefix, varcount++, ident);
  //   // NOTE: when doing regression testing, uncomment the line above, and comment-out the line below
  //   return String.format("_%s%d%s_%s", prefix, varcount++, randomString(RAND_SIZE), ident);
  // }

  public String toString() {
    StringBuilder sb  = new StringBuilder();

    sb.append(String.format("SymbolTable: %d entries", this.map.size()));
    sb.append("\n");
    for (String ident : this.map.keySet()) {
      sb.append(String.format("%s -> %s", ident, this.map.get(ident)));
    }
    
    return sb.toString();
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

  public void copyBools(SymbolTable symtab) {
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

  public static void main(String args[]) {
    PresenceConditionManager presenceConditionManager = new PresenceConditionManager();
    PresenceCondition A = presenceConditionManager.getVariable("A");
    PresenceCondition B = presenceConditionManager.getVariable("B");
    PresenceCondition C = presenceConditionManager.getVariable("C");
    PresenceCondition and = A.and(B);
    PresenceCondition or = and.or(C);
    SymbolTable symtab = new SymbolTable();
    System.err.println(symtab);
    symtab.put("x", UnitT.TYPE, or);
    System.err.println(symtab);
    symtab.putError("x", and.not());
    System.err.println(symtab);
  }
}
