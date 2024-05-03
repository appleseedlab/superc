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
import java.util.AbstractMap;

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
public class SymbolTable<T> implements Iterable<String> {

  private Error<T> ERROR = new Error<T>();

  private Undeclared<T> UNDECLARED = new Undeclared<T>();

  /**
   * Get the UNDECLARED entry, which is used by the scope to lookup a
   * symbol in all scopes.
   */
  public Entry<T> getUndeclared() { return UNDECLARED; }

  public static abstract class Entry<U> {
    /** True if an error entry. */
    public boolean isError() { return false; }

    /** True if an undeclared entry. */
    public boolean isUndeclared() { return false; }

    /** True if a declared entry. */
    public boolean isDeclared() { return false; }

    /**
     * Get the value if the entry has one.
     */
    public abstract U getValue();
  }

  protected static class Error<U> extends Entry<U> {
    protected Error() { }

    public boolean isError() { return true; }

    public U getValue() {
      throw new UnsupportedOperationException("the error symbol table entry has no type");
    }

    public String toString() {
      return "<ERROR>";
    }
  }

  protected static class Undeclared<U> extends Entry<U> {
    private Undeclared() { }

    public boolean isUndeclared() { return true; }

    public U getValue() {
      throw new UnsupportedOperationException("the undeclared symbol table entry has no type");
    }
    
    public String toString() {
      return "<UNDECLARED>";
    }
  }

  public static class Declared<U> extends Entry<U> {
    protected final U value;
    
    public Declared(U value) {
      this.value = value;
    }
    
    public boolean isDeclared() { return true; }

    public U getValue() {
      return this.value;
    }
    
    public String toString() {
      return String.format("(VALUE=%s)", this.value.toString());
    }
  }

  /**
   * The symbol table's core data structure that maps symbols to a
   * multiverse of types.
   */
  protected HashMap<String, Multiverse<Entry<T>>> map;

  /** The reference count for cleaning up the table BDDs */
  public int refs;

  /**
   * Create a new, empty symbol table.
   */
  public SymbolTable() {
    this.refs = 1;
    this.map = new HashMap<String, Multiverse<Entry<T>>>();
  }

  /**
   * Update the number of references to this symbol table.
   */
  public SymbolTable<T> addRef() {
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
      for (Multiverse<Entry<T>> m : map.values()) {
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
  public Multiverse<Entry<T>> get(String ident, PresenceCondition cond) {
    Multiverse<Entry<T>> newmv = new Multiverse<Entry<T>>();
    if (! this.map.containsKey(ident)) {
      // Create a new multiverse for the symbol that has only the
      // UNDECLARED entry under the True condition
      PresenceCondition trueCond = cond.presenceConditionManager().newTrue();
      newmv.add(UNDECLARED, trueCond);
      trueCond.delRef();

      PresenceCondition falseCond = cond.presenceConditionManager().newFalse();
      newmv.add(ERROR, falseCond);
      falseCond.delRef();
      Multiverse<Entry<T>> filtered = newmv.filter(cond);
      return filtered;
    } else {
      Multiverse<Entry<T>> cur = this.map.get(ident);
      for (Element<Entry<T>> e : cur) {
        if (!e.getCondition().and(CContext.getParseErrorCond()).is(e.getCondition())) {
          newmv.add(e);
        } else {
          newmv.add(ERROR, e.getCondition());
        }
      }
      return newmv.filter(cond);
    }
  }

  /**
   * returns a Multiverse of a List of all elements under a presence condition
   * 
   */
  public Multiverse<List<Map.Entry<String,T>>> getLists(PresenceCondition cond) {
    Multiverse<List<Map.Entry<String,T>>> lists = new Multiverse<List<Map.Entry<String,T>>>();
    lists.add(new LinkedList<Map.Entry<String,T>>(), cond);
    for (Map.Entry<String,Multiverse<Entry<T>>> m : map.entrySet()) {
      for (Element<Entry<T>> e : m.getValue()) {
        if (e.getData().isUndeclared() || e.getData().isError()) {
          continue;
        }
        //for each value, check to see if any 'and's does not result
        //in not. If it doesn't split the list.
        boolean remade;
        do {
          remade = false;
          for (Element<List<Map.Entry<String,T>>> el : lists) {
            PresenceCondition p = el.getCondition().and(e.getCondition());
            //if the presencondition is a subset, but isn't 0
            //issue is, that we also add if e is strictly greater than.
            if (el.getCondition().is(p)) {
              el.getData().add(new AbstractMap.SimpleImmutableEntry<String,T>(m.getKey(),e.getData().getValue()));
            } else if (!p.isFalse()) {
              Multiverse<List<Map.Entry<String,T>>> newLists = new Multiverse<List<Map.Entry<String,T>>>();
              for (Element<List<Map.Entry<String,T>>> elN : lists) {
                if (elN != el) {
                  newLists.add(elN.getData(), elN.getCondition());
                }
              }
              List<Map.Entry<String,T>> tL = new LinkedList<Map.Entry<String,T>>(el.getData());
              newLists.add(el.getData(), p);
              newLists.add(tL, el.getCondition().and(p.not()));
              lists.destruct();
              lists = newLists;
              remade = true;
              p.delRef();
              break;
            }
          }
        } while (remade);
      } 
    }
    return lists;
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
  protected void put(String ident, SymbolTable.Entry<T> putEntry, PresenceCondition putCond) {
    if (! putCond.isFalse()) {
      if (! this.map.containsKey(ident)) {
        // Create a new multiverse for the symbol that has only the
        // UNDECLARED entry under the True condition
        Multiverse<Entry<T>> newmv = new Multiverse<Entry<T>>();

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

      Multiverse<Entry<T>> oldmv = this.map.get(ident);
      Multiverse<Entry<T>> newmv = new Multiverse<Entry<T>>();

      /* lifetime for presence conditions */ {
        PresenceCondition undeclaredCond = null;
        PresenceCondition errorCond = null;
        PresenceCondition notPutCond = putCond.not();
        PresenceCondition collectErrors = putCond.presenceConditionManager().newFalse();

        for (Element<Entry<T>> entry : oldmv) {
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
        for (Element<Entry<T>> entry_i : newmv) {
          PresenceCondition newUnion = union.or(entry_i.getCondition());
          union.delRef();
          union = newUnion;
          
          for (Element<Entry<T>> entry_j : newmv) {
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
    // System.err.println(toString());
  }

  /**
   * Add a new symbol table entry for the given identifier.
   *
   * @param ident The identifier to enter.
   * @param type The value.
   * @param putCond The presence condition.
   */
  public void put(String ident, T value, PresenceCondition putCond) {
    Entry<T> entry = new Declared<T>(value);
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

  public void replaceType(String renamed, T newValue, PresenceCondition cond) {
    String originalName = renamed;
    while (originalName.charAt(originalName.length()-1) >= '0' && originalName.charAt(originalName.length()-1) <= '9') {
      originalName = originalName.substring(0,originalName.length()-1);
    }
    originalName = originalName.substring(2,originalName.length()-1);
    Multiverse<Entry<T>> values = map.get(originalName);
    Multiverse<Entry<T>> onlyDeclared = values.filter(cond);
    for (Element<Entry<T>> e : onlyDeclared) {
      if (!e.getData().isDeclared()) {
        System.err.println("Error: trying to redefine type for erroneous or undeclared entry");
        System.exit(1);
      }
    }
    onlyDeclared.destruct();
    Multiverse<Entry<T>> newmv = values.filter(cond.not());
    newmv.add(new Declared(newValue),cond);
    map.replace(originalName,newmv);
  }
  
  /**
   * returns a list of all anonymous ids that exist in the
   * symbol table.
   */
  public List<String> getAnonIds() {
    List<String> res = new LinkedList<String>();
    for (String k : map.keySet()) {
      if (k.startsWith("anon_id_")) {
        res.add(k);
      }
    }
    return res;
  }
  
  public String toString() {
    StringBuilder sb  = new StringBuilder();

    sb.append(String.format("SymbolTable: %d entries", this.map.size()));
    sb.append("\n");
    for (String ident : this.map.keySet()) {
      sb.append(String.format("%s -> %s", ident, this.map.get(ident)));
    }
    
    return sb.toString();
  }


  public static void main(String args[]) {
    PresenceConditionManager presenceConditionManager = new PresenceConditionManager();
    PresenceCondition A = presenceConditionManager.getVariable("A");
    PresenceCondition B = presenceConditionManager.getVariable("B");
    PresenceCondition C = presenceConditionManager.getVariable("C");
    PresenceCondition and = A.and(B);
    PresenceCondition or = and.or(C);
    SymbolTable<xtc.type.Type> symtab = new SymbolTable<xtc.type.Type>();
    System.err.println(symtab);
    symtab.put("x", UnitT.TYPE, or);
    System.err.println(symtab);
    symtab.putError("x", and.not());
    System.err.println(symtab);
  }
}
