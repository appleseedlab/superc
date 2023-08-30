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

import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.HashSet;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

import superc.core.Syntax.LanguageTag;
import superc.core.Syntax.Layout;
import superc.core.Syntax.Language;
import superc.core.Syntax.Text;
import superc.core.Syntax.Directive;
import superc.core.Syntax.Conditional;

import superc.core.PresenceConditionManager.PresenceCondition;

/** The conditional macro table.
 *
 * A few properties:
 * (1) no entry means the macro is free,
 * (2) the union of all entry's conditions is TRUE,
 * (3) each entry's definitions' conditions are disjoint,
 * (4) there is at most one free and one undefined element
 * (5) the table is optimized by having no duplicate definitions
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.63 $
 */
public class MacroTable {
  /** The token creator. */
  TokenCreator tokenCreator;

  /** The mapping from names to lists of (condition, definition) pairs */
  Map<String, List<Entry>> table;
  
  /** Track enabled/disabled macro names */
  Set<String> disabled;

  /** Whether to collect configuration variable names or not. */
  private boolean getConfigurationVariables = false;
  
  /** Records unique configuration variable names. */
  public Set<String> configurationVariables = null;

  /** Whether to collect header guard names or not. */
  private boolean getHeaderGuards = false;

  /** Records unique header guard names. */
  public Set<String> headerGuards = null;

  /** Only allow macros with a given prefix to be free macros. */
  private boolean restrictPrefix = false;

  /** The restricted prefix. */
  private String prefix = null;

  private boolean enableRestrictWhitelist = false;
  
  private List<String> restrictWhitelist = null;

  
  /** Make a new empty macro table */
  public MacroTable(TokenCreator tokenCreator) {
    this.tokenCreator = tokenCreator;

    table = new HashMap<String, List<Entry>>();
    disabled = new HashSet<String>();
  }

  public void getConfigurationVariables(boolean b) {
    getConfigurationVariables = b;

    if (getConfigurationVariables && null == configurationVariables) {
      configurationVariables = new HashSet<String>();
      getHeaderGuards(true);
    }
  }

  public boolean getConfigurationVariables() {
    return getConfigurationVariables;
  }

  public void getHeaderGuards(boolean b) {
    getHeaderGuards = b;

    if (getHeaderGuards && null == headerGuards) {
      headerGuards = new HashSet<String>();
    }
  }

  public boolean getHeaderGuards() {
    return getHeaderGuards;
  }

  /**
   * Only allow macros with a given prefix to be free macros.  Pass
   * null to turn this feature off.  It is off by default.
   *
   * @param prefix Give a string to turn restricted prefix on.  Give
   * null to turn it off.
   */
  public void restrictPrefix(String prefix) {
    if (null == prefix) {
      restrictPrefix = false;
      this.prefix = null;
    } else {
      restrictPrefix = true;
      this.prefix = prefix;
    }
  }
  
  /**
   * Get the current macro prefix restriction.
   *
   * @return The macro prefix restriction or null if none.
   */
  public String getRestrictPrefix() {
    return prefix;
  }

    /** 
   * Restrict free macros to the given whitelist.
   *
   * @param File with whitelisted macros
   */
  public void restrictWhitelist(String whitelistFile) {
    if (null == whitelistFile) {
      enableRestrictWhitelist = false;
      this.restrictWhitelist = null;
    } else {
      enableRestrictWhitelist = true;
      this.restrictWhitelist = new LinkedList<String>();
      try {
        BufferedReader reader = new BufferedReader(new FileReader(whitelistFile));
        String line = reader.readLine();
        while (line != null) {
          this.restrictWhitelist.add(line);
          line = reader.readLine();
        }
      } catch (IOException e) {
        System.err.println("Whitelist unable to be read");
        enableRestrictWhitelist = false;
        this.restrictWhitelist = null;
      }
    }
  }

  public boolean whitelisted(String param) {
    return this.restrictWhitelist.contains(param);
  }


  /** Define a macro under a given presenceCondition.  This function will
   * ensure that all conditions are disjoint and that there are no more
   * than one of each unique definition.
   */
  public void define(String name, Macro macro, PresenceConditionManager presenceConditionManager) {
    PresenceCondition presenceCondition;

    if (presenceConditionManager.isFalse()) return; //invalid configuration

    /* If this is a boolean variable already, then remove FREE and
     * replace with equivalent defined M and ! defined M
     */
    if (contains(name)
        && presenceConditionManager.hasDefinedVariable(name)) {
      PresenceCondition var;
      PresenceCondition not;
      List<Entry> entries;
      
      var = presenceConditionManager.getDefinedVariable(name);
      not = var.not();
      
      entries = table.get(name);
      
      for (int i = 0; i < entries.size(); i++) {
        Entry e;
        
        e = entries.get(i);
        
        if (Macro.State.FREE == e.macro.state) {
          List<Syntax> definition;
          PresenceCondition andvar, andnot;
          
          andvar = e.presenceCondition.and(var);
          andnot = e.presenceCondition.and(not);

          definition = new LinkedList<Syntax>();
          {  // Mark an unknown definition.
            Language<?> deftoken;
            
            deftoken = tokenCreator.createIdentifier(name);
            deftoken.setFlag(Preprocessor.NO_EXPAND);
            deftoken.setFlag(Preprocessor.UNKNOWN_DEF);
            definition.add(deftoken);
          }
          _define(name, new Macro.Object(definition), andvar);
          
          _define(name, Macro.undefined, andnot);

          andvar.delRef();
          andnot.delRef();
        }
      }
    }

    presenceCondition = presenceConditionManager.reference();

    _define(name, macro, presenceCondition);
    
    presenceCondition.delRef();
  }
  
  /** Update the symbol table with a new entry.  The presenceCondition passed
   * will gain a reference, so dereference it yourself if you no
   * longer need it.
   */
  protected void _define(String name, Macro macro, PresenceCondition presenceCondition) {
    if (presenceCondition.isFalse()) return;
    
    if (! contains(name)) {  //new macro
      List<Entry> defs;
      
      defs = new LinkedList<Entry>();
      table.put(name, defs);

      if (! presenceCondition.isTrue()) {
        PresenceCondition negation;
        
        negation = presenceCondition.not();
        if (enableRestrictWhitelist && ! whitelisted(name)) {
          // Assume the macro is undefined.
          defs.add(new Entry(Macro.undefined, negation));
        } else if (restrictPrefix && !name.startsWith(prefix)) {
          // Assume the macro is undefined.
          defs.add(new Entry(Macro.undefined, negation));
        } else {
          // Let the macro be free.
          defs.add(new Entry(Macro.free, negation));
        }
        negation.delRef();
      }

      defs.add(new Entry(macro, presenceCondition));
      
    } else {  //update macro entries
      Entry duplicate;
      List<Entry> defs;
      
      duplicate = null;
      defs = table.get(name);
      
      //make entries disjoint
      for (int d = 0; d < defs.size(); d++) {
        Entry entry = defs.get(d);
        PresenceCondition newPresenceCondition;
        
        newPresenceCondition = entry.presenceCondition.andNot(presenceCondition);
        entry.presenceCondition.delRef();
        entry.presenceCondition = newPresenceCondition;
        
        if (newPresenceCondition.isFalse()) {
          newPresenceCondition.delRef();
          defs.remove(d);
          d--;
        }
      }
      
      // Deduplication macro entries.  First find the duplicate entry
      // if there is one.
      for (Entry e : defs) {
        if (e.macro.state != macro.state) continue;

        switch (macro.state) {
        case UNDEFINED:
          // Fall through.
        case FREE:
          // Only allow one entry for UNDEFINED and FREE.
          duplicate = e;
          break;

        case DEFINED:
          if (null == macro.definition && null == e.macro.definition) {
            duplicate = e;
          } else if (null != macro.definition && null != e.macro.definition) {
            if (macro.definition.size() == e.macro.definition.size()) {
              boolean isdup;
                
              isdup = true;
              for (int i = 0; i < macro.definition.size(); i++) {
                Syntax a, b;
                  
                a = macro.definition.get(i);
                b = e.macro.definition.get(i);
                  
                if (! a.getTokenText().equals(b.getTokenText())
                    || ! a.flagsEqual(b)) {
                  isdup = false;
                }
              }
                
              if (isdup) {
                duplicate = e;
                break;
              }
            }
          }
          break;
        }
      }

      if (null == duplicate) {
        // Add new entry if there is no duplicate entry.
        table.get(name).add(new Entry(macro, presenceCondition));
      } else {
        // Instead of adding a new entry, update the presence
        // condition of the existing duplicate entry.
        PresenceCondition oldc = duplicate.presenceCondition;
        PresenceCondition newc = oldc.or(presenceCondition);
        oldc.delRef();
        duplicate.presenceCondition = newc;
      }
    }
  }
  
  /**
   * Update the presenceConditions of macros that use a guard macro.  We assume
   * that guard macros for headers are undefined, not free.
   *
   * This method assumes that there is no entry in the macro table for
   * the guard macro.  Since it is only called by
   * HeaderFileManager.openHeader right now, that method checks this
   * condition.
   *
   * @param guardMacro The name of the guard macro.
   * @param presenceConditionManager The presenceCondition manager.
   */
  public void rectifyGuard(String guardMacro, PresenceConditionManager presenceConditionManager) {
    PresenceCondition var, not;
    PresenceCondition presenceCondition;
    
    // presenceCondition = presenceConditionManager.reference();
    // var = presenceConditionManager.new PresenceCondition(presenceConditionManager.getVariableManager()
    //                                  .getDefinedVariable(guardMacro));
    // not = var.not();
    
    // for (String name : table.keySet()) {
    //   List<Entry> entries;
      
    //   entries = table.get(name);
    //   for (int i = 0; i < entries.size(); i++) {
    //     Entry e;
    //     PresenceCondition restrictnot;
        
    //     PresenceCondition c;
        
    //     e = entries.get(i);
        
    //     c = presenceCondition.and(e.presenceCondition);


    //     // Check whether the macro entry's presence condition
    //     // (e.presenceCondition) depends on the guard macro (! (defined var)).

    //     restrictnot = e.presenceCondition.restrict(not);
        
    //     if (! restrictnot.is(e.presenceCondition)) {
    //       e.presenceCondition.delRef();
          
    //       if (restrictnot.isFalse()) {
    //         entries.remove(i);
    //         i--;

    //       } else {
    //         e.presenceCondition = restrictnot;
    //         e.presenceCondition.addRef();
    //       }
    //     }
        
    //     restrictnot.delRef();
    //   }
    // }
    
    // presenceCondition.delRef();
    // var.delRef();
    // not.delRef();
    

    // This following line doesn't check whether the header macro is
    // already defined!  In openHeader, we make sure the header guard
    // is not already contained in the macro table.

    if (getHeaderGuards) {
      headerGuards.add(guardMacro);
    }

    _define(guardMacro, Macro.undefined, presenceConditionManager.newTrue());
  }
  
  /**
   * Undefine a macro under the given presenceCondition.
   *
   * @param name The name of the macro to undefine.
   * @param presenceConditionManager The presenceCondition manager holding the current
   * presence condition in which the macro should be undefined.
   */
  public void undefine(String name, PresenceConditionManager presenceConditionManager) {
    define(name, Macro.undefined, presenceConditionManager);
  }
  
  /**
   * Gets the macro table entries of the given macro under the given
   * presenceCondition.  Any entries not valid in the presenceCondition will not be
   * returned.  This creates new Entry objects for the entries with
   * the presence conditions ANDed with the current presence
   * condition.
   *
   * @param name The name of the macro.
   * @param presenceConditionManager The manager containing the current presence
   * condition.
   * @return The list of entries valid under the current presence
   * condition or null if there are none.
   */
  public List<Entry> get(String name, PresenceConditionManager presenceConditionManager) {
    List<Entry> all;
    List<Entry> valid;
    PresenceCondition presenceCondition;
    
    if (! contains(name)) return null;
    
    presenceCondition = presenceConditionManager.reference();
    
    all = table.get(name);
    valid = null;
    
    for (Entry e : all) {
      PresenceCondition and;
      
      and = presenceCondition.and(e.presenceCondition);
      
      if (! and.isFalse()) {
        if (null == valid) {
          valid = new LinkedList<Entry>();
        }
        valid.add(new Entry(e.macro, e.presenceCondition));
      }
      
      and.delRef();
    }
    
    presenceCondition.delRef();
    
    return valid;
  }
  
  public void free(List<Entry> entries) {
    for (Entry e : entries) {
      e.presenceCondition.delRef();
    }
  }
  
  /** Whether the table already contains the macro name. */
  public boolean contains(String name) {
    return table.containsKey(name);
  }
  
  /** String representation */
  public String toString() {
    StringBuilder sb;
    
    sb = new StringBuilder();
    for (String name : table.keySet()) {
      sb.append(name);
      sb.append("\n");
      sb.append("-------------------------------------------");
      sb.append("\n");
      for (Entry e : table.get(name)) {
        sb.append(e);
        sb.append("\n");
      }
      sb.append("\n");
    }
    
    return sb.toString();
  }
  
  /** Disable a macro */
  public void disable(String macro) {
    disabled.add(macro);
  }
  
  /** Enable a macro */
  public void enable(String macro) {
    disabled.remove(macro);
  }
  
  /** Test whether a macro is enabled */
  public boolean isEnabled(String macro) {
    return ! disabled.contains(macro);
  }

  /**
   * Count the number of definitions a given macro has.  Does not
   * include FREE or UNDEFINED entries in the macro table.
   *
   * @param name The macro name.
   * @return The number of definitions of the macro.
   */
  public int countDefinitions(String name) {
    if (! table.containsKey(name)) return 0;

    int count = 0;

    for (Entry e : table.get(name)) {
      if (Macro.State.DEFINED == e.macro.state) {
        count++;
      }
    }

    return count;
  }
  

  /** A macro definition */
  public static class Macro {
    /** The macro definition */
    protected List<Syntax> definition;
    
    /** The state of the macro */
    protected State state;
    
    /** An undefined macro */
    public static Macro undefined = new Macro(State.UNDEFINED);
    
    /** A free macro */
    public static Macro free = new Macro(State.FREE);
    
    public enum State {
      FREE, UNDEFINED, DEFINED
    }
    
    /** Only subclasses are instantiable */
    protected Macro(List<Syntax> definition, State state) {
      this.definition = definition;
      this.state = state;
    }
    
    protected Macro(State state) {
      this(null, state);
    }
    
    public boolean isObject() {
      return false;
    }
    
    public boolean isFunction() {
      return false;
    }
    
    public static class Object extends Macro {
      public Object(List<Syntax> definition) {
        super(definition, State.DEFINED);
      }

      public boolean isObject() {
        return true;
      }
    }
    
    public static class Function extends Macro {
      protected List<String> formals;
      protected String variadic;

      public Function(List<String> formals, List<Syntax> definition,
                      String variadic) {
        super(definition, State.DEFINED);
        this.formals = formals;
        this.variadic = variadic;
      }

      public boolean isFunction() {
        return true;
      }
      
      public boolean isVariadic() {
        return null != variadic;
      }
    }
  }

  /** A macro table entry. */
  public static class Entry {
    protected Macro macro;
    protected PresenceCondition presenceCondition;
    
    public Entry(Macro macro, PresenceCondition presenceCondition) {
      this.macro = macro;
      this.presenceCondition = presenceCondition;
      this.presenceCondition.addRef();
    }
    
    public String toString() {
      StringBuilder sb;
      
      sb = new StringBuilder();
      sb.append(macro.state);
      if (Macro.State.DEFINED == macro.state && null != macro.definition) {
        sb.append("(");
        for (Syntax t : macro.definition) {
          if (t.testFlag(Preprocessor.PREV_WHITE)) {
            sb.append(" ");
          }
          sb.append(t.getTokenText());
        }
        sb.append(")");
      }
      sb.append("\n");
      sb.append(presenceCondition);
      sb.append("\n");
      
      return sb.toString();
    }
  }
}

