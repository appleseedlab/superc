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

import xtc.Constants;

import xtc.tree.Location;

import superc.core.ForkMergeParser;

import superc.core.Syntax;
import superc.core.Syntax.Kind;
import superc.core.Syntax.LanguageTag;
import superc.core.Syntax.ConditionalTag;
import superc.core.Syntax.DirectiveTag;
import superc.core.Syntax.Layout;
import superc.core.Syntax.Language;
import superc.core.Syntax.Text;
import superc.core.Syntax.Directive;
import superc.core.Syntax.Conditional;

import superc.cdesugarer.Declaration;

import xtc.type.Type;
import xtc.type.StructT;
import xtc.type.UnionT;
import xtc.type.C;

import superc.core.ParsingContext;

import superc.core.PresenceConditionManager.PresenceCondition;
import superc.core.PresenceConditionManager;

import superc.core.Clauses;

import superc.core.ForkMergeParser.OrderedSyntax;
import superc.core.ForkMergeParser.Lookahead;

import superc.cdesugarer.Multiverse.Element;

import xtc.tree.Node;


/**
 * This class maintains just enough type context for parsing.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.8 $
 */
public class CContext implements ParsingContext {

  /** Output bindings and scope changes. */
  protected static boolean DEBUG = false;
    
    private static String output = "";
    public static void addOutput(String s) {
	output = output + s;
    }
    public static String getOutput() {
	return output;
    }
    
  /**
   * Use the desugarer's symbol table to make token reclassfication
   * decisions for typedef names.  When false, it using the previous
   * symbol table from the C parser.
   */
  protected final static boolean USE_DESUGARER_SYMTAB_FOR_RECLASSIFICATION = false;

  /** The symbol table for this parsing context. */
  protected SymbolTable<Type> symtab;

  /**
   * Lookaside tables for struct/union fields.  This field manages the
   * symbol tables for struct/union fields.  This allows structs to
   * have multiply-defined fields without having to hoist the static
   * conditions around the entire struct definition.
   */
  protected Map<String, SymbolTable<Declaration>> taglookasidetable;

  protected static Map<String,Multiverse<String>> prototypeMultiplex = new HashMap<String,Multiverse<String>>();

  /**
   * The forward tag reference accounts for forward references of
   * struct/union, when in a single pass, we won't know yet how many
   * configurations of the struct/union there will be.  See
   * getDeclarations to see how the forward reference is handled.
   */
  protected BiMap<String, String> forwardtagrefs;
  protected BiMap<String, String> forwardEtagrefs;

  /** Renamed enumerators for enums. */
  protected SymbolTable<Map.Entry<String, List<String>>> enumeratortable;
  
  /** The old symbol table. */
  protected OldSymbolTable oldsymtab;

  /**
   * Declarations to put at the top of the scope.  This is used to
   * handle the use of forward references for structs/unions.  All
   * user-defined type declarations (typedefs, structs/unions) are
   * added here in the order in which they appear in the input file.
   * Since declarations are desugared via renaming, there is no need
   * to distinguish between configurations and all declarations can be
   * concatenated.  Forking and merging
   */
  protected StringBuilder declarations;

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

  public static ForkMergeParser parser;
  
  public static PresenceCondition getParseErrorCond() {
    return parser.getErrorCond();
  }

  /** Create a new initial C parsing contex. */
  public CContext() {
    this(new SymbolTable<Type>(),
         new HashMap<String, SymbolTable<Declaration>>(),
         new BiMap<String, String>(),
         new BiMap<String, String>(),
         new SymbolTable<Map.Entry<String, List<String>>>(),
         new OldSymbolTable(), null);
  }

  /**
   * Create a new C parsing context.
   *
   * @param symtab The symbol table for this parsing context and scope.
   * @param parent The parent parsing context and scope.
   */
  public CContext(SymbolTable<Type> symtab,
                  Map<String, SymbolTable<Declaration>> taglookasidetable,
                  BiMap<String, String> forwardtagrefs,
                  BiMap<String, String> forwardEtagrefs,
                  SymbolTable<Map.Entry<String, List<String>>> enumeratortable,
                  OldSymbolTable oldsymtab,
                  CContext parent) {
    this.symtab = symtab;
    this.taglookasidetable = taglookasidetable;
    this.forwardtagrefs = forwardtagrefs;
    this.forwardEtagrefs = forwardEtagrefs;
    this.enumeratortable = enumeratortable;
    this.oldsymtab = oldsymtab;
    this.parent = parent;

    this.reentrant = false;

    this.declarations = new StringBuilder();
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
    this.taglookasidetable = scope.taglookasidetable; for (SymbolTable<Declaration> elem : taglookasidetable.values()) { elem.addRef(); }
    this.forwardtagrefs = scope.forwardtagrefs;
    this.forwardEtagrefs = scope.forwardEtagrefs;
    this.enumeratortable = scope.enumeratortable;
    this.oldsymtab = scope.oldsymtab.addRef();

    if (scope.parent != null) {
      this.parent = new CContext(scope.parent);

    } else {
      this.parent = null;
    }

    this.reentrant = scope.reentrant;

    // forked contexts share the same declarations. renaming is used
    // instead of presence conditions, allowing them to be merged by
    // concatenation.
    this.declarations = scope.declarations;
  }


  public ParsingContext fork()
  {
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
    if (USE_DESUGARER_SYMTAB_FOR_RECLASSIFICATION) {
      // If there is any lookahead token that has some presence
      // condition where it is declared to be a typedef name, i.e.,
      // AliasT, then the parser needs to call reclassify (return true).
      for (Lookahead n : set) {
        if (isIdentifier(n.token.syntax)) {
          String ident = n.token.syntax.getTokenText();
          PresenceCondition pc = n.presenceCondition;
          Multiverse<SymbolTable.Entry<Type>> entries = this.getInAnyScope(ident, pc);
          for (Element<SymbolTable.Entry<Type>> entry : entries) {
            if (entry.getData().isDeclared()
                && entry.getData().getValue().isAlias()) {
              return true;
            }
          }
        }
      }
      return false;
    } else {
      // TODO: use the new symboltable to do this
      // Check whether any tokens need reclassification, i.e. they are
      // an identifier and have an entry in the symbol.
      for (Lookahead n : set) {
        if (isIdentifier(n.token.syntax)) {
          String ident = n.token.syntax.getTokenText();
          // Check the stack of symbol tables for a typedef entry.
          CContext scope = this;
          while (true) {
            while (scope.reentrant) scope = scope.parent;
            
            if ( scope.oldsymtab.bools.containsKey(ident)
                 && scope.oldsymtab.bools.get(ident).containsKey(OldSymbolTable.STField.TYPEDEF)
                 && ! scope.oldsymtab.bools.get(ident).get(OldSymbolTable.STField.TYPEDEF).trueCond.isFalse()
                 ) {

              // if ( scope.oldsymtab.bools.containsKey(ident)
              //      && scope.oldsymtab.bools.get(ident).containsKey(OldSymbolTable.STField.TYPEDEF)
              //      && ! scope.oldsymtab.bools.get(ident).get(OldSymbolTable.STField.TYPEDEF).trueCond.isFalse()
              //      ) {

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
  }

  // get around capture of ? to CTag warning
  public Collection<Lookahead> reclassify(Collection<Lookahead> set) {
    if (USE_DESUGARER_SYMTAB_FOR_RECLASSIFICATION) {
      Collection<Lookahead> newTokens = null;
      for (Lookahead n : set) {
        if (isIdentifier(n.token.syntax)) {
          String ident = n.token.syntax.getTokenText();
          PresenceCondition pc = n.presenceCondition;

          // determine the conditions of a typedef declaration and just a regular ident
          Multiverse<SymbolTable.Entry<Type>> entries = this.getInAnyScope(ident, pc);
          PresenceCondition typedefCond = pc.presenceConditionManager().newFalse();
          PresenceCondition identCond = pc.presenceConditionManager().newFalse();
          for (Element<SymbolTable.Entry<Type>> entry : entries) {
            if (entry.getData().isDeclared()
                && entry.getData().getValue().isAlias()) {
              PresenceCondition newtypedefCond = typedefCond.or(entry.getCondition());
              typedefCond.delRef(); typedefCond = newtypedefCond;
            } else {
              // not a typedef in this configuration
              PresenceCondition newidentCond = identCond.or(entry.getCondition());
              identCond.delRef(); identCond = newidentCond;
            }
          }


          if (typedefCond.isNotFalse()) {
            // the n token will become the typedef token, and we'll add
            // a new identifier token if needed.
            if (identCond.isNotFalse()) {
              // A typedef ambiguity.  Find the presence condition for both
              // the variable entry and for the typedef entry.  Reclassify
              // the current token as a typedef name and update its presence
              // condition.  Then add a new token for the variable entry.

              // update the presence condition of the typedef entry
              n.presenceCondition.delRef();
              n.presenceCondition = typedefCond; typedefCond.addRef();

              // Add a new token for the variable entry.
              PresenceCondition varPresenceCondition = typedefCond.not();
              Lookahead identifier = new Lookahead(n.token, identCond); identCond.addRef();
              if (null == newTokens) {
                newTokens = new LinkedList<Lookahead>();
              }
              newTokens.add(identifier);
            
            } else {
              // do nothing when there's no ident condition, which means
              // n.presenceCondition should already be equal to
              // typedefCond at this point, given the behavior of the
              // loop that computes it above.
            }

            // A typedef name.  Reclassify the token replacing the
            // IDENTIFIER token with a TYPEDEFname token.
            Language<CTag> newToken = new Text<CTag>(CTag.TYPEDEFname,
                                                     n.token.syntax.getTokenText());

            // Copy the location.
            newToken.setLocation(n.token.syntax.getLocation());

            // Copy the ordering wrapper for the token.
            n.token = n.token.copy(newToken);
            
          } else {
            // no configurations are a typedef, so do nothing
          }
          typedefCond.delRef();
          identCond.delRef();
        }
      }

      return newTokens;
    } else {
      // TODO: use the new symboltable to do this
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

        // TODO: do a lookup and check in which configurations it's an
        // alias type

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
  }

  /**
   * This method determines whether an identifier is a typedef name,
   * var name, or both by inspecting the symbol table in this scope
   * and any parent scopes.  (Legacy type checking).
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
      if (scope.oldsymtab.bools.containsKey(ident)
          && scope.oldsymtab.bools.get(ident).containsKey(OldSymbolTable.STField.TYPEDEF)
          && ! scope.oldsymtab.bools.get(ident).get(OldSymbolTable.STField.TYPEDEF).trueCond.isFalse()) {
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

      if (scope.oldsymtab.bools.containsKey(ident) &&
          (scope.oldsymtab.bools.get(ident).containsKey(OldSymbolTable.STField.TYPEDEF)
           || scope.oldsymtab.bools.get(ident).containsKey(OldSymbolTable.STField.IDENT))) {
        // Set the flags for typedef (2) and var (1).
        int flags = 0;
        if (scope.oldsymtab.bools.get(ident).containsKey(OldSymbolTable.STField.TYPEDEF) &&
            ! scope.oldsymtab.bools.get(ident).get(OldSymbolTable.STField.TYPEDEF).trueCond.isFalse()) {
          PresenceCondition and = scope.oldsymtab.bools.get(ident).get(OldSymbolTable.STField.TYPEDEF).trueCond.and(presenceCondition);
          if (! and.isFalse()) flags |= 2;
          and.delRef();
        }
        if (scope.oldsymtab.bools.get(ident).containsKey(OldSymbolTable.STField.IDENT) &&
            ! scope.oldsymtab.bools.get(ident).get(OldSymbolTable.STField.IDENT).trueCond.isFalse()) {
          PresenceCondition and = scope.oldsymtab.bools.get(ident).get(OldSymbolTable.STField.IDENT).trueCond.and(presenceCondition);
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
      assert s.oldsymtab == t.oldsymtab;
      assert s.taglookasidetable == t.taglookasidetable;
      assert s.forwardtagrefs == t.forwardtagrefs;
      assert s.forwardEtagrefs == t.forwardEtagrefs;
      assert s.enumeratortable == t.enumeratortable;
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
      assert oldsymtab == scope.oldsymtab;
      assert taglookasidetable == scope.taglookasidetable;
      assert forwardtagrefs == scope.forwardtagrefs;
      assert forwardEtagrefs == scope.forwardEtagrefs;
      assert enumeratortable == scope.enumeratortable;
      return this;
    } else {
      // symtab.addAll(scope.symtab);
      oldsymtab.copyBools(scope.oldsymtab);
      
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
    // taglookasidetable.delRef();  // trace issue with this
    oldsymtab.delRef();

    if (null != parent) {
      parent.free();
    }
  }

  /**
   * Get a reference to the context's symbol table.
   *
   * @return The context's symbol table.
   */
  public SymbolTable<Type> getSymbolTable() {
    CContext scope = this;
    while (scope.reentrant) scope = scope.parent;

    return scope.symtab;
  }

  /**
   * Get a reference to the context's old symbol table.
   *
   * @return The context's old symbol table.
   */
  public OldSymbolTable getOldSymbolTable() {
    CContext scope = this;
    while (scope.reentrant) scope = scope.parent;

    return scope.oldsymtab;
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
   * typedef name.  (Legacy type checking).
   *
   * @param ident The identifier.
   * @param presenceCondition The current presence condition.
   */
  public PresenceCondition typedefPresenceCondition(String ident, PresenceCondition presenceCondition) {
    CContext scope;

    scope = this;

    do {  //find the symbol in local scope or parent scope

      while (scope.reentrant) scope = scope.parent;

      if (scope.oldsymtab.bools.containsKey(ident) &&
          scope.oldsymtab.bools.get(ident).containsKey(OldSymbolTable.STField.TYPEDEF)) {
        PresenceCondition and = scope.oldsymtab.bools.get(ident).get(OldSymbolTable.STField.TYPEDEF).trueCond.and(presenceCondition);

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
   * typedef name.  (Legacy type checking).
   *
   * @param ident The identifier.
   * @param presenceCondition The current presence condition.
   */
  public PresenceCondition symbolPresenceCond(String ident, OldSymbolTable.STField field) {
    CContext scope;

    scope = this;

    do {  //find the symbol in local scope or parent scope

      while (scope.reentrant) scope = scope.parent;

      if (scope.oldsymtab.bools.containsKey(ident) &&
          scope.oldsymtab.bools.get(ident).containsKey(field)) {
        return scope.oldsymtab.bools.get(ident).get(field).trueCond;
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
      for (SymbolTable<Declaration> elem : taglookasidetable.values()) { elem.delRef(); }
      scope.taglookasidetable = null;
      scope.forwardtagrefs = null;
      scope.forwardEtagrefs = null;
      scope.enumeratortable = null;
      scope.oldsymtab.delRef();
      scope.oldsymtab = null;
      scope = scope.parent;
    }

    scope = new CContext(new SymbolTable<Type>(),
                         new HashMap<String, SymbolTable<Declaration>>(),
                         new BiMap<String, String>(),
                         new BiMap<String, String>(),
                         new SymbolTable<Map.Entry<String, List<String>>>(),
                         new OldSymbolTable(),
                         new CContext(scope));

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
      if (scope.taglookasidetable != null) {
        for (SymbolTable<Declaration> elem : scope.taglookasidetable.values()) {
          elem.delRef();
        }
      }
      scope.taglookasidetable = null;
      scope.forwardtagrefs = null;
      scope.forwardEtagrefs = null;
      scope.enumeratortable = null;
      scope.oldsymtab.delRef();
      scope.oldsymtab = null;
      scope = scope.parent;
    }

    scope.symtab.delRef();
    scope.symtab = null;
    if (scope.taglookasidetable != null) {
	for (SymbolTable<Declaration> elem : scope.taglookasidetable.values()) {
	    elem.delRef();
	}
    }
    scope.taglookasidetable = null;
    scope.forwardtagrefs = null;
    scope.forwardEtagrefs = null;
    scope.enumeratortable = null;
    scope.oldsymtab.delRef();
    scope.oldsymtab = null;
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
      for (SymbolTable<Declaration> elem : taglookasidetable.values()) { elem.delRef(); }
      scope.taglookasidetable = null;
      scope.forwardtagrefs = null;
      scope.forwardEtagrefs = null;
      scope.enumeratortable = null;
      scope.oldsymtab.delRef();
      scope.oldsymtab = null;
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
      for (SymbolTable<Declaration> elem : taglookasidetable.values()) { elem.delRef(); }
      scope.taglookasidetable = null;
      scope.forwardtagrefs = null;
      scope.forwardEtagrefs = null;
      scope.enumeratortable = null;
      scope.oldsymtab.delRef();
      scope.oldsymtab = null;
      scope = scope.parent;
    }
    return scope;
  }

  /**
   * Get the symbol table entries for the given identifier under the
   * given presence conditions, following the chain of nested scopes.
   * This accounts for symbols only obscured in some configurations.
   * This filters the Multiverse by trimming entries infeasible under
   * the given condition.
   *
   * @param ident The identifier to look up.
   * @param cond The presence condition.
   * @returns A new Multiverse instance containing the entries under
   * the given condition.
   */
  public Multiverse<SymbolTable.Entry<Type>> getInAnyScope(String ident, PresenceCondition cond) {
    Multiverse<SymbolTable.Entry<Type>> result = new Multiverse<SymbolTable.Entry<Type>>();

    if (! cond.isFalse()) {
      get(result, this, ident, cond);
    }
    return result;
  }

  /**
   * Get only the local symbol table entries for the given identifier under the
   * given presence conditions.
   *
   * @param ident The identifier to look up.
   * @param cond The presence condition.
   * @returns A new Multiverse instance containing the entries under
   * the given condition, including UNDECLARED.
   */
  public Multiverse<SymbolTable.Entry<Type>> getInCurrentScope(String ident, PresenceCondition cond) {
    return getSymbolTable().get(ident, cond);
  }

  /**
   * Put a symbol into the current symbol table.
   *
   * @param ident The identifier to enter.
   * @param type The type.
   * @param putCond The presence condition.
   * @returns A new Multiverse instance containing the entries under
   * the given condition or null if the symbol is not defined.
   */
  public void put(String ident, Type type, PresenceCondition putCond) {
    getSymbolTable().put(ident, type, putCond);
  }
  
  /**
   * Add an entry representing a type error to the current symbol
   * table.
   *
   * @param ident The identifier to enter.
   * @param putCond The presence condition.
   */
  public void putError(String ident, PresenceCondition putCond) {
    getSymbolTable().putError(ident, putCond);
  }
  
  /**
   * Returns if the current scope is in global space.
   *
   * @returns boolean describing if the current scope is global
   */
  public boolean isGlobal()
  {
    CContext scope = this;
    while(scope.reentrant) {
      scope = scope.parent;
    }
    return scope.parent == null;
  }
  
  /**
   * One step of the recursive walk of the nested symbol tables.  The
   * base cases are when we have already reached the global scope or
   * there are no more configurations with an undeclared entry.
   *
   * @param result The current list of resulting entries.  If there
   * are none, then the only entry will be UNDECLARED.
   * @param scope The current scope to look up.
   * @param ident The identifier to look up.
   * @param cond The current presence condition.
   */
  private void get(Multiverse<SymbolTable.Entry<Type>> result, CContext scope, String ident, PresenceCondition cond) {
    SymbolTable<Type> symtab = scope.getSymbolTable();
    Multiverse<SymbolTable.Entry<Type>> local = symtab.get(ident, cond);
    // add any declarations to the result, and continue looking in
    // the parent if this scope has any undeclared presence
    // condition.
    PresenceCondition undefinedCondition = null;

    // if undefinedCondition remains null, it means there was no
    // presence condition under which the identifier is undeclared.
    for (Element<SymbolTable.Entry<Type>> entry : local) {
      if (entry.getData().isUndeclared()) {
        if (null != undefinedCondition) {
          System.err.println("FATAL: there should only one entry for UNDECLARED");
          System.exit(1);
        }
        undefinedCondition = entry.getCondition();
        entry.getCondition().addRef();
      } else {
        result.add(entry.getData(), entry.getCondition());
        entry.getCondition().addRef();
      }
    }

    local.destruct();

    // use the UNDECLARED presence condition to continue looking in
    // the parent for definitions.
    if (null != undefinedCondition) {
      if (null != scope.parent) {
        // continue search in the global scope
        get(result, scope.parent, ident, undefinedCondition);  // TODO: can we move scope past reentrant? does it matter?
        undefinedCondition.delRef();
      } else {
        // we've reached the global scope, so add the remaining
        // condition as an UNDECLARED entry.
        result.add(symtab.getUndeclared(), undefinedCondition);
        undefinedCondition.delRef();
      }
    }

    if (DEBUG) System.err.println(String.format("context.get: %s -> %s", ident, result));
  }

  /**
   * Add a new tag lookaside table.
   */
  public SymbolTable<Declaration> addLookasideTable(String tag) {
    CContext scope = this;
    while (scope.reentrant) scope = scope.parent;
    if (scope.taglookasidetable.containsKey(tag)) {
      throw new AssertionError("the type checker should never be adding duplicate struct tags");
    }
    SymbolTable<Declaration> tagtab = new SymbolTable<Declaration>();
    scope.taglookasidetable.put(tag, tagtab);
    return tagtab;
  }

  /**
   * Get the lookaside table, following parent scopes as needed.
   */
  public SymbolTable<Declaration> getLookasideTableAnyScope(String tag) {
    if (this.reentrant) {
      if (null != this.parent) {
        return this.parent.getLookasideTableAnyScope(tag);
      } else {
        throw new AssertionError("reentrant scopes should always have a parent");
      }
    } else {
      // not a reentrant scope.  look for the tag
      if (taglookasidetable.containsKey(tag)) {
        return taglookasidetable.get(tag);
      } else {
        if (null != this.parent) {
          return this.parent.getLookasideTableAnyScope(tag);
        } else {
          //With parse errors, this might not always be true
          //throw new AssertionError("the type checker should always be using a defined struct tag name");
          //just try returning an empty table
          return new SymbolTable();
        }
      }
    }
  }

  /**
   * Get the forward reference to a struct tag.  Check each scope and
   * return the associated forward reference.  Otherwise, return null.
   *
   * @param The original name of a tag.
   * @returns null If no forward tag exists for the given tag.
   */
  public String getForwardTagForTag(String tag) {
    if (this.reentrant) {
      if (null != this.parent) {
        return this.parent.getForwardTagForTag(tag);
      } else {
        throw new AssertionError("reentrant scopes should always have a parent");
      }
    } else {
      // not a reentrant scope.  look for the tag
      if (forwardtagrefs.containsValue(tag)) {
        return forwardtagrefs.getKey(tag);
      } else {
        if (null != this.parent) {
          return this.parent.getForwardTagForTag(tag);
        } else {
          return null;
        }
      }
    }
  }

  public boolean hasForwardTagForTag(String tag) {
    return null != getForwardTagForTag(tag);
  }
  
  /**
   * Add new forward reference to a tag.
   */
  public void putForwardTagReference(String forwardTag, String referencedTag) {
    CContext scope = this;
    
    while (scope.reentrant) scope = scope.parent;

    if (scope.forwardtagrefs.containsKey(forwardTag)) {
      throw new AssertionError("invariant violation: forward tag refs should never get remapped");
    }
    
    scope.forwardtagrefs.put(forwardTag, referencedTag);
  }

  /**
   * Get a forward reference to a tag.
   */
  public String getForwardTagReferenceAnyScope(String forwardTag) {
    if (this.reentrant) {
      if (null != this.parent) {
        return this.parent.getForwardTagReferenceAnyScope(forwardTag);
      } else {
        throw new AssertionError("reentrant scopes should always have a parent");
      }
    } else {
      // not a reentrant scope.  look for the tag
      if (forwardtagrefs.containsKey(forwardTag)) {
        return forwardtagrefs.getValue(forwardTag);
      } else {
        if (null != this.parent) {
          return this.parent.getForwardTagReferenceAnyScope(forwardTag);
        } else {
          throw new AssertionError("the type checker should always be using a defined struct tag name");
        }
      }
    }
  }

    /**
   * Get the forward reference to a struct tag.  Check each scope and
   * return the associated forward reference.  Otherwise, return null.
   *
   * @param The original name of a tag.
   * @returns null If no forward tag exists for the given tag.
   */
  public String getForwardETagForTag(String tag) {
    if (this.reentrant) {
      if (null != this.parent) {
        return this.parent.getForwardETagForTag(tag);
      } else {
        throw new AssertionError("reentrant scopes should always have a parent");
      }
    } else {
      // not a reentrant scope.  look for the tag
      if (forwardEtagrefs.containsValue(tag)) {
        return forwardEtagrefs.getKey(tag);
      } else {
        if (null != this.parent) {
          return this.parent.getForwardETagForTag(tag);
        } else {
          return null;
        }
      }
    }
  }

  public boolean hasForwardETagForTag(String tag) {
    return null != getForwardETagForTag(tag);
  }
  
  /**
   * Add new forward reference to a tag.
   */
  public void putForwardETagReference(String forwardTag, String referencedTag) {
    CContext scope = this;
    
    while (scope.reentrant) scope = scope.parent;

    if (scope.forwardEtagrefs.containsKey(forwardTag)) {
      throw new AssertionError("invariant violation: forward tag refs should never get remapped");
    }
    
    scope.forwardEtagrefs.put(forwardTag, referencedTag);
  }

  /**
   * Get a forward reference to a tag.
   */
  public String getForwardETagReferenceAnyScope(String forwardTag) {
    if (this.reentrant) {
      if (null != this.parent) {
        return this.parent.getForwardETagReferenceAnyScope(forwardTag);
      } else {
        throw new AssertionError("reentrant scopes should always have a parent");
      }
    } else {
      // not a reentrant scope.  look for the tag
      if (forwardEtagrefs.containsKey(forwardTag)) {
        return forwardEtagrefs.getValue(forwardTag);
      } else {
        if (null != this.parent) {
          return this.parent.getForwardETagReferenceAnyScope(forwardTag);
        } else {
          throw new AssertionError("the type checker should always be using a defined struct tag name");
        }
      }
    }
  }
  

  /**
   * Add a new (renamed) enumerator to the given enum tag.
   */
  public void putEnumerator(String enumTag, String renamedtag, List<String> enumerators, PresenceCondition p) {
    CContext scope = this;
    
    while (scope.reentrant) scope = scope.parent;
    scope.enumeratortable.put(enumTag,new AbstractMap.SimpleImmutableEntry<String,List<String>>(renamedtag,enumerators),p);

    StringBuilder sb = new StringBuilder();
    
    // create an enum for each enum specifier
    sb.append("enum ");
    sb.append(renamedtag);
    sb.append(" {\n");
    for (String enumerator : enumerators) {
      sb.append(enumerator);
      sb.append(",\n");
    }
    sb.append("};\n");
    addDeclaration(sb.toString());
    
  }

  public Multiverse<String> getEnumMultiverse(String enumTag, PresenceCondition pc) {
    CContext scope = this;
    
    while (scope.reentrant) scope = scope.parent;
    
    Multiverse<SymbolTable.Entry<Map.Entry<String,List<String>>>> m = scope.enumeratortable.get(enumTag,pc);
      Multiverse<String> res = new Multiverse<String>();
      for (Element<SymbolTable.Entry<Map.Entry<String,List<String>>>> s : m) {
        if (s.getData().isDeclared()) {
          res.add(s.getData().getValue().getKey(),s.getCondition());
        } else if (s.getData().isUndeclared()) {
          if (scope.isGlobal()) {
            res.add("<undeclared>",s.getCondition());
          } else {
            res.addAll(scope.parent.getEnumMultiverse(enumTag,pc));
          }
        }else {
          if (scope.isGlobal()) {
            res.add("<error>",s.getCondition());
          } else {
            res.addAll(scope.parent.getEnumMultiverse(enumTag,pc));
          }
        }
      }
      return res;
  }
 

  public static void addMultiplex(String original, String rename, PresenceCondition cond) {
    Multiverse<String> plexes;
    if(prototypeMultiplex.containsKey(original)) {
      plexes = prototypeMultiplex.get(original).filter(cond.not());
      plexes.add(rename,cond);
      
    } else {
      plexes = new Multiverse<String>(rename,cond);
    }
    prototypeMultiplex.put(original,plexes);   
  }

  public static Map<String,Multiverse<String>> getMultiplexes() {
    return prototypeMultiplex;
  }
  
  /**
   * Add to the declarations to be put at the top of the scope.
   *
   * @param sb The string builder of the declaration to add.
   */
  public void addDeclaration(String sb) {
    CContext scope = this;
    
    while (scope.reentrant) scope = scope.parent;
    
    scope.declarations.append(sb);
  }

  /**
   * Get the declarations to be put at the top of the scope.
   *
   * @returns The string
   */
  public String getDeclarations(PresenceCondition presenceCondition) {
    StringBuilder sb = new StringBuilder();
    
    // emit the user-defined type declarations, which are renamed
    CContext scope = this;
    while (scope.reentrant) scope = scope.parent;
        
    sb.append(scope.declarations);
    sb.append("\n");

    // create a struct for each forward tag reference that is a union
    // containing each configuration of the struct.
    SymbolTable<Type> symtab = scope.getSymbolTable();
    CActions.todoReminder("account for bitfield sizes in forward refs");
    for (String tag : forwardtagrefs.keySet()) {
      sb.append(String.format("struct %s {", tag));
      sb.append(" // generated union of struct variations");
      sb.append("\nunion {\n");
      String originalTag = forwardtagrefs.getValue(tag);
      Multiverse<SymbolTable.Entry<Type>> originalTagEntries
        = symtab.get(CContext.toTagName(originalTag), presenceCondition);
      for (Element<SymbolTable.Entry<Type>> tagentry : originalTagEntries) {
        if (tagentry.getData().isError()) {
          // error tagentry
        } else if (tagentry.getData().isUndeclared()) {
          // no declaration in this configuration
        } else {
          if (tagentry.getData().getValue().isStruct()) {
            StructT type = tagentry.getData().getValue().toStruct();
            String renamedTag = type.getName();
            sb.append(String.format("struct %s %s;", renamedTag, renamedTag));
            sb.append("\n");
          } else if (tagentry.getData().getValue().isUnion()) {
            UnionT type = tagentry.getData().getValue().toUnion();
            String renamedTag = type.getName();
            sb.append(String.format("union %s %s;", renamedTag, renamedTag));
            sb.append("\n");
          } else {
            throw new IllegalStateException("invariant violation: type should only be struct or union");
          }
        }
      }
      sb.append("};\n};\n\n");
    }
    for (String tag : forwardEtagrefs.keySet()) {
      String name = forwardEtagrefs.getValue(tag);
      sb.append(String.format("union %s {", tag));
      sb.append(" // generated union of enum variations\n");
      Multiverse<SymbolTable.Entry<Map.Entry<String,List<String>>>>  originalTagEntries
        = enumeratortable.get(name, presenceCondition);
      
      for (Element<SymbolTable.Entry<Map.Entry<String,List<String>>>> tagentry : originalTagEntries) {
        if (tagentry.getData().isError()) {
          // error tagentry
        } else if (tagentry.getData().isUndeclared()) {
          // no declaration in this configuration
        } else {
          sb.append(String.format("enum %s %s;", tagentry.getData().getValue().getKey(), tagentry.getData().getValue().getKey()));
          sb.append("\n");
        }
      }
      sb.append("};\n\n");
    }
    return sb.toString();
  }


  /***************************************************************************
   **** The following naming and namespacing functionality is taken
   **** directly from xtc.util.SymbolTable.
   ***************************************************************************/

  /** The end of opaqueness marker as a string. */
  private static final String END_OPAQUE =
    Character.toString(Constants.END_OPAQUE);

  /**
   * Determine whether the specified symbol is in the specified name
   * space.
   *
   * @param symbol The symbol.
   * @param space The name space.
   * @return <code>true</code> if the symbol is mangled symbol in the
   *   name space.
   */
  public static boolean isInNameSpace(String symbol, String space) {
    try {
      return (symbol.startsWith(space) &&
              (Constants.START_OPAQUE == symbol.charAt(space.length())) &&
              symbol.endsWith(END_OPAQUE));
    } catch (IndexOutOfBoundsException x) {
      return false;
    }
  }

  /**
   * Convert the specified unqualified symbol to a symbol in the
   * specified name space.
   *
   * @param symbol The symbol
   * @param space The name space.
   * @return The mangled symbol.
   */
  public static String toNameSpace(String symbol, String space) {
    return space + Constants.START_OPAQUE + symbol + Constants.END_OPAQUE;
  }

  /**
   * Convert the specified unqualified symbol within a name space to a
   * symbol without a name space.
   *
   * @param symbol The mangled symbol within a name space.
   * @return The corresponding symbol without a name space.
   */
  public static String fromNameSpace(String symbol) {
    int start = symbol.indexOf(Constants.START_OPAQUE);
    int end   = symbol.length() - 1;
    if ((0 < start) && (Constants.END_OPAQUE == symbol.charAt(end))) {
      return symbol.substring(start + 1, end);
    } else {
      throw new IllegalArgumentException("Not a mangled symbol '"+symbol+"'");
    }
  }

  // /**
  //  * Convert the specified C struct, union, or enum tag into a symbol
  //  * table name.  This is used for forward references to struct/union
  //  * tags.
  //  *
  //  * @param tag The tag.
  //  * @return The corresponding symbol table name.
  //  */
  // public static String toTagRefName(String tagref) {
  //   return toNameSpace(tagref, "tagref");
  // }

  /**
   * Convert the specified C struct, union, or enum tag into a symbol
   * table name.
   *
   * @param tag The tag.
   * @return The corresponding symbol table name.
   */
  public static String toTagName(String tag) {
    return toNameSpace(tag, "tag");
  }

  /**
   * Convert the specified label identifier into a symbol table name.
   *
   * @param id The identifier.
   * @return The corresponding symbol table name.
   */
  public static String toLabelName(String id) {
    return toNameSpace(id, "label");
  }

  protected static class BiMap<T, U> {
    Map<T, U> map1;
    Map<U, T> map2;
    
    public BiMap() {
      map1 = new HashMap<T, U>();
      map2 = new HashMap<U, T>();
    }

    public boolean containsKey(T key) {
      return map1.containsKey(key);
    }

    public boolean containsValue(U value) {
      return map2.containsKey(value);
    }

    public Set<T> keySet() {
      return map1.keySet();
    }

    public Set<U> valueSet() {
      return map2.keySet();
    }

    public U getValue(T key) {
      return map1.get(key);
    }

    public T getKey(U value) {
      return map2.get(value);
    }

    public void put(T key, U value) {
      map1.put(key, value);
      map2.put(value, key);
    }
  }
}
