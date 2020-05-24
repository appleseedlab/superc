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
import java.util.Map;
import java.util.Set;
import java.util.Random;

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

import xtc.lang.cpp.ForkMergeParser.OrderedSyntax;
import xtc.lang.cpp.ForkMergeParser.Lookahead;

/**
 * This class maintains just enough type context for parsing.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.8 $
 */
public class CContext implements ParsingContext {

  /** Output bindings and scope changes. */
  protected static boolean DEBUG = false;

  /** The symbol table for this parsing context. */
  protected SymbolTable symtab;

  /**
   * The parent parsing context, corresponding to the parent
   * scope.
   */
  protected CContext parent;

  /**
   * Whether the scope this parsing context is associated with is
   * reentrant.  This is used to parse function definitions.
   */
  protected boolean reentrant;

  /**
   * Store last seen base type from specifiers.  Used to build type
   * from a declarator's abstract type.
   */
  public Type lastSeenType;

  /** Whether to display language statistics. */
  boolean languageStatistics;

  /**
   * A three-bit digit.  This is used to capture typedef/var ambiguity
   * when one token can be both.
   */
  public static enum trit {
    TRUE,
    FALSE,
    TRUEFALSE
  }

  /** Create a new initial C parsing contex. */
  public CContext() {
    this(new SymbolTable(), null);
  }

  /**
   * Create a new C parsing context.
   *
   * @param symtab The symbol table for this parsing context and scope.
   * @param parent The parent parsing context and scope.
   */
  public CContext(SymbolTable symtab, CContext parent) {
    this.symtab = symtab;
    this.parent = parent;

    this.reentrant = false;
  }

  /**
   * Turn language statistics collection on.  Default is off.
   *
   * @param b True is on.
   */
  public void collectStatistics(boolean b) {
    languageStatistics = b;
  }

  /**
   * Copy a C parsing context.  Used for forking the parsing context.
   *
   * @param scope The parsing context to copy.
   */
  public CContext(CContext scope) {
    this.symtab = scope.symtab.addRef();

    if (scope.parent != null) {
      this.parent = new CContext(scope.parent);

    } else {
      this.parent = null;
    }

    this.reentrant = scope.reentrant;
  }

  public ParsingContext fork() {
    return new CContext(this);
  }

  /**
   * Check whether a syntax token is an identifier.
   *
   * @return true if syntax is an identifier.
   */
  @SuppressWarnings("unchecked")
  private boolean isIdentifier(Syntax syntax) {
    return syntax.kind() == Kind.LANGUAGE
      && ((Language<CTag>)syntax).toLanguage().tag() == CTag.IDENTIFIER;
  }


  // get around capture of ? to CTag warning
  public boolean shouldReclassify(Collection<Lookahead> set) {
    // Check whether any tokens need reclassification, i.e. they are
    // an identifier and have an entry in the symbol.
    for (Lookahead n : set) {
      if (isIdentifier(n.token.syntax)) {
        String ident = n.token.syntax.getTokenText();

        // Check the stack of symbol tables for a typedef entry.
        CContext scope = this;
        while (true) {
          while (scope.reentrant) scope = scope.parent;

          // if ( scope.symtab.map.containsKey(ident)
          //      && scope.symtab.map.get(ident).typedefCond != null
          //      ) {
          if ( scope.symtab.bools.containsKey(ident)
               && scope.symtab.bools.get(ident).containsKey(SymbolTable.STField.TYPEDEF)
               && ! scope.symtab.bools.get(ident).get(SymbolTable.STField.TYPEDEF).trueCond.isFalse()
               ) {

            // The identifier has a typedef entry some presence
            // condition in the symbol table.  Therefore the parser
            // needs to call reclassify.

            return true;
          }

          if (null == scope.parent) {
            break;
          }

          scope = scope.parent;
        }
      }
    }

    return false;
  }

  // get around capture of ? to CTag warning
  public Collection<Lookahead> reclassify(Collection<Lookahead> set) {
    // Reclassify any tokens that are typedef names and also create a
    // new token when there is a typedef/var ambiguity so the FMLR
    // parser will fork.
    Collection<Lookahead> newTokens = null;
    for (Lookahead n : set) {
      // Get the symbol table entry for the token.
      trit isTypedef = trit.FALSE;
      if (isIdentifier(n.token.syntax)) {
        isTypedef = isType(n.token.syntax.getTokenText(),
                           n.presenceCondition, n.token.syntax.getLocation());
      }

      switch (isTypedef) {
      case TRUEFALSE:
        // A typedef ambiguity.  Find the presence condition for both
        // the variable entry and for the typedef entry.  Reclassify
        // the current token as a typedef name and update its presence
        // condition.  Then add a new token for the variable entry.
        PresenceCondition typedefPresenceCondition
          = this.typedefPresenceCondition(n.token.syntax.getTokenText(), n.presenceCondition);
        n.presenceCondition.delRef();
        n.presenceCondition = typedefPresenceCondition;

        // Add a new token for the variable entry.
        PresenceCondition varPresenceCondition = typedefPresenceCondition.not();
        Lookahead identifier = new Lookahead(n.token, varPresenceCondition);
        if (null == newTokens) {
          newTokens = new LinkedList<Lookahead>();
        }
        newTokens.add(identifier);

        // Fall through to reclassify the token as a TYPEDEFname.

      case TRUE:
        // A typedef name.  Reclassify the token replacing the
        // IDENTIFIER token with a TYPEDEFname token.
        Language<CTag> newToken = new Text<CTag>(CTag.TYPEDEFname,
                                                 n.token.syntax.getTokenText());

        // Copy the location.
        newToken.setLocation(n.token.syntax.getLocation());

        // Copy the ordering wrapper for the token.
        n.token = n.token.copy(newToken);
        break;

      case FALSE:
        // No reclassification necessary.
        break;
      }
    }

    return newTokens;
  }

  /**
   * This method determines whether an identifier is a typedef name,
   * var name, or both by inspecting the symbol table in this scope
   * and any parent scopes.
   *
   * @param ident The identifier.
   * @param presenceCondition The presence condition.
   */
  public trit isType(String ident, PresenceCondition presenceCondition,
                     Location location) {
    CContext scope;

    scope = this;

    while (true) {
      while (scope.reentrant) scope = scope.parent;

      // if ( scope.symtab.map.containsKey(ident)
      //      && scope.symtab.map.get(ident).typedefCond != null
      //      ) {
      if (scope.symtab.bools.containsKey(ident)
          && scope.symtab.bools.get(ident).containsKey(SymbolTable.STField.TYPEDEF)
          && ! scope.symtab.bools.get(ident).get(SymbolTable.STField.TYPEDEF).trueCond.isFalse()) {
  break;
      }

      if (null == scope.parent) {
        return trit.FALSE;
      }

      scope = scope.parent;
    }

    scope = this;

    do {  //find the symbol in local scope or parent scope

      while (scope.reentrant) scope = scope.parent;

      if (scope.symtab.bools.containsKey(ident) &&
          (scope.symtab.bools.get(ident).containsKey(SymbolTable.STField.TYPEDEF)
           || scope.symtab.bools.get(ident).containsKey(SymbolTable.STField.IDENT))) {
        // Set the flags for typedef (2) and var (1).
        int flags = 0;
        if (scope.symtab.bools.get(ident).containsKey(SymbolTable.STField.TYPEDEF) &&
            ! scope.symtab.bools.get(ident).get(SymbolTable.STField.TYPEDEF).trueCond.isFalse()) {
          PresenceCondition and = scope.symtab.bools.get(ident).get(SymbolTable.STField.TYPEDEF).trueCond.and(presenceCondition);
          if (! and.isFalse()) flags |= 2;
          and.delRef();
        }
        if (scope.symtab.bools.get(ident).containsKey(SymbolTable.STField.IDENT) &&
            ! scope.symtab.bools.get(ident).get(SymbolTable.STField.IDENT).trueCond.isFalse()) {
          PresenceCondition and = scope.symtab.bools.get(ident).get(SymbolTable.STField.IDENT).trueCond.and(presenceCondition);
          if (! and.isFalse()) flags |= 1;
          and.delRef();
        }
        switch (flags) {
        case 3:
          if (DEBUG) System.err.println("isType: " + ident
                                        + " true/false in " /*+ presenceCondition*/);
          if (languageStatistics) {
            System.err.println(String.format("typedef_ambiguity %s %s",
                                             ident, location));
          }
          return trit.TRUEFALSE;

        case 2:
          if (DEBUG) System.err.println("isType: " + ident
                                        + " true in " /*+ presenceCondition*/);
          return trit.TRUE;

        case 1:
          if (DEBUG) System.err.println("isType: " + ident
                                        + " false in " /*+ presenceCondition*/);
          return trit.FALSE;
        }
      }

      // if (scope.symtab.map.containsKey(ident)) {
      //   TypedefVarEntry e = scope.symtab.map.get(ident);

      //   // Set the flags for typedef (2) and var (1).
      //   int flags = 0;
      //   if (null != e.typedefCond) {
      //     PresenceCondition and;

      //     and = e.typedefCond.and(presenceCondition);
      //     if (! and.isFalse()) {
      //       flags |= 2;
      //     }
      //     and.delRef();
      //   }

      //   if (null != e.varCond) {
      //     PresenceCondition and;

      //     and = e.varCond.and(presenceCondition);
      //     if (! and.isFalse()) {
      //       flags |= 1;
      //     }
      //     and.delRef();
      //   }

      //   switch (flags) {
      //   case 3:
      //     if (DEBUG) System.err.println("isType: " + ident
      //                                   + " true/false in " /*+ presenceCondition*/);
      //     if (languageStatistics) {
      //       System.err.println(String.format("typedef_ambiguity %s %s",
      //                                        ident, location));
      //     }
      //     return trit.TRUEFALSE;

      //   case 2:
      //     if (DEBUG) System.err.println("isType: " + ident
      //                                   + " true in " /*+ presenceCondition*/);
      //     return trit.TRUE;

      //   case 1:
      //     if (DEBUG) System.err.println("isType: " + ident
      //                                   + " false in " /*+ presenceCondition*/);
      //     return trit.FALSE;
      //   }
      // }

      if (null == scope.parent) {
        break;
      }

      scope = scope.parent;
    } while (true);

    if (DEBUG) System.err.println("isType: " + ident
                                  + " false in " /*+ presenceCondition*/);

    return trit.FALSE;
  }

  public boolean mayMerge(ParsingContext other) {
    if (! (other instanceof CContext)) return false;

    return mergeable(this, (CContext) other);
  }

  /**
   * A helper method for testing mergeability.
   *
   * @param s The first parsing context.
   * @param t The second parsing context.
   */
  private static boolean mergeable(CContext s, CContext t) {
    if ((null == s) && (null == t)) {
      return true;
    } else if ((null == s) || (null == t)) {
      return false;
    } else if (s.symtab == t.symtab) {
      return true;
    } else if (s.reentrant != t.reentrant) {
      return false;
    } else {
      return mergeable(s.parent, t.parent);
    }
  }

  public ParsingContext merge(ParsingContext other) {
    CContext scope = (CContext) other;

    if (this.symtab == scope.symtab) {
      return this;
    } else {
      // symtab.addAll(scope.symtab);
      symtab.copyBools(scope.symtab);

      if (null != parent) {
        return parent.merge(scope.parent);

      } else {
        return null;
      }
    }
  }

  /** Free BDDs in the symbol table and those of the parent scopes. */
  public void free() {
    symtab.delRef();

    if (null != parent) {
      parent.free();
    }
  }

  /**
   * Get a reference to the context's symbol table.
   *
   * @return The context's symbol table.
   */
  public SymbolTable getSymbolTable() {
    CContext scope = this;
    while (scope.reentrant) scope = scope.parent;

    return scope.symtab;
  }

  // /**
  //  * Bind an identifier to a typedef or var name for a given presence
  //  * condition.
  //  *
  //  * @param ident The identifier.
  //  * @param typedef Whether its a typedef name or a var name.
  //  * @param presenceCondition The presence condition.
  //  */
  // public void bind(String ident, boolean typedef, PresenceCondition presenceCondition) {
  //   CContext scope;

  //   if (DEBUG) {
  //     System.err.println("bind: " + ident + " " + typedef);
  //   }

  //   scope = this;
  //   while (scope.reentrant) scope = scope.parent;

  //   scope.symtab.add(ident, typedef, presenceCondition);
  // }

  /**
   * Return the presence condition under which an identifier is a
   * typedef name.
   *
   * @param ident The identifier.
   * @param presenceCondition The current presence condition.
   */
  public PresenceCondition typedefPresenceCondition(String ident, PresenceCondition presenceCondition) {
    CContext scope;

    scope = this;

    do {  //find the symbol in local scope or parent scope

      while (scope.reentrant) scope = scope.parent;

      if (scope.symtab.bools.containsKey(ident) &&
          scope.symtab.bools.get(ident).containsKey(SymbolTable.STField.TYPEDEF)) {
        PresenceCondition and = scope.symtab.bools.get(ident).get(SymbolTable.STField.TYPEDEF).trueCond.and(presenceCondition);

        if (! and.isFalse()) {
          return and;
        }

        and.delRef();
      }

      // if (scope.symtab.map.containsKey(ident)) {
      //   TypedefVarEntry e;
      //   boolean typedef;
      //   boolean var;
      //   PresenceCondition and;

      //   e = scope.symtab.map.get(ident);

      //   and = e.typedefCond.and(presenceCondition);

      //   if (! and.isFalse()) {
      //     return and;
      //   }
      //   and.delRef();
      // }

      if (null == scope.parent) {
        break;
      }
      scope = scope.parent;
    } while (true);

    return null;
  }

  /**
   * Return the presence condition under which an identifier is a
   * typedef name.
   *
   * @param ident The identifier.
   * @param presenceCondition The current presence condition.
   */
  public PresenceCondition symbolPresenceCond(String ident, SymbolTable.STField field) {
    CContext scope;

    scope = this;

    do {  //find the symbol in local scope or parent scope

      while (scope.reentrant) scope = scope.parent;

      if (scope.symtab.bools.containsKey(ident) &&
          scope.symtab.bools.get(ident).containsKey(field)) {
        return scope.symtab.bools.get(ident).get(field).trueCond;
      }

      if (null == scope.parent) {
        break;
      }
      scope = scope.parent;
    } while (true);

    return null;
  }

  /**
   * Enter a new scope.
   *
   * @param presenceCondition The current presence condition.
   * @return The parsing context of the new scope.
   */
  public CContext enterScope(PresenceCondition presenceCondition) {
    CContext scope;

    if (DEBUG) System.err.println("enter scope");

    scope = this;
    while (scope.reentrant) {
      scope.symtab.delRef();
      scope.symtab = null;
      scope = scope.parent;
    }

    scope = new CContext(new SymbolTable(), new CContext(scope));

    return scope;
  }

  /**
   * Exit the scope.
   *
   * @param presenceCondition The current presence condition.
   * @return The parsing context of the parent scope.
   */
  public CContext exitScope(PresenceCondition presenceCondition) {
    CContext scope;

    if (DEBUG) System.err.println("exit scope");

    scope = this;
    while (scope.reentrant) {
      scope.symtab.delRef();
      scope.symtab = null;
      scope = scope.parent;
    }

    scope.symtab.delRef();
    scope.symtab = null;
    scope = scope.parent;

    return scope;
  }

  /**
   * Exit a reentrant scope.
   *
   * @param presenceCondition The current presence condition.
   * @return The parsing context of the parent scope.
   */
  public CContext exitReentrantScope(PresenceCondition presenceCondition) {
    CContext scope;

    if (DEBUG) System.err.println("exit reentrant scope");

    scope = this;
    while (scope.reentrant) {
      scope.symtab.delRef();
      scope.symtab = null;
      scope = scope.parent;
    }

    scope.reentrant = true;

    return scope;
  }

  /**
   * Reenter a reentrant scope.
   *
   * @param presenceCondition The current presence condition.
   * @return The parsing context of the reentered scope.
   */
  public CContext reenterScope(PresenceCondition presenceCondition) {
    if (DEBUG) System.err.println("reenter scope");

    if (! reentrant) {
      // This may happen for functions without a postfix declarator.
      // See cpp_testsuite/grammar/scope.c.  The parameter list
      // nonterminal enters and exits a reentrant scope.  Then the
      // function nonterminal reenters the scope.  If there is no
      // list, there is no reentrant scope, and at the end of the
      // function nonterminal, exitScope is called, returning null.
      if (DEBUG) System.err.println("not reentrant");
      return enterScope(presenceCondition);
    } else {
      reentrant = false;
      return this;
    }
  }

  /**
   * Kill a reentrant scope.
   *
   * @param presenceCondition The current presence condition.
   * @return The parsing context of the non-reentrant parent scope.
   */
  public CContext killReentrantScope(PresenceCondition presenceCondition) {
    CContext scope;

    if (DEBUG) System.err.println("kill reentrant scope");

    scope = this;
    while (scope.reentrant) {
      scope.symtab.delRef();
      scope.symtab = null;
      scope = scope.parent;
    }

    return scope;
  }

  /** The symbol table that stores a scope's symbol bindings. */
  public static class SymbolTable {
    public enum STField {
      TYPEDEF, IDENT, INIT, USED, VAR, GLOBAL_FUNDEF, STATIC_FUNDEF, FUNCALL,
    }

      private static int count = 0;
    // /** The symbol table data structure. */
    // public HashMap<String, TypedefVarEntry> map;

    /** The symbol table data structure. */
    public HashMap<String, EnumMap<STField, ConditionedBool>> bools;

      public Multiverse multiverse;

    /** The reference count for cleaning up the table BDDs */
    public int refs;

    /** New table */
    public SymbolTable() {
      // this.map = new HashMap<String, TypedefVarEntry>();
      this.bools = new HashMap<String, EnumMap<STField, ConditionedBool>>();
      this.refs = 1;
      multiverse = new Multiverse();
    }

    public SymbolTable addRef() {
      refs++;

      return this;
    }
      public void addMapping(String ident, Type type, PresenceCondition p)
      {
	  if (!multiverse.addMapping(ident, mangleRenaming("", ident), type, p))
	      {
		  System.out.println("Redefinition of identifier: " + ident);
		  System.exit(1);
	      }
	  System.out.println(multiverse.toString());
      }

    public void delRef() {
      refs--;
      if (0 == refs) {  //clean up symbol table
        for (String name : this.bools.keySet()) {
          for (STField field : this.bools.get(name).keySet()) {
            ConditionedBool cb = this.bools.get(name).get(field);
            cb.trueCond.delRef();
          }
        }
        // for (String str : this.map.keySet()) {
        //   TypedefVarEntry e = this.map.get(str);

        //   if (null != e.typedefCond) {
        //     e.typedefCond.delRef();
        //   }
        //   if (null != e.varCond) {
        //     e.varCond.delRef();
        //   }
        // }
      }
      multiverse.delRefs();
    }

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

  }

  /**
   * A boolean that maintain a boolean expression for when the
   * variable can be true.
   */
  private static class ConditionedBool {
    /** The presence condition when true. */
    PresenceCondition trueCond;

    /** Create a new entry.
     *
     * @param trueCond Condition when true.
     */
    public ConditionedBool(PresenceCondition trueCond) {
      this.trueCond = trueCond;
    }
  }
}
