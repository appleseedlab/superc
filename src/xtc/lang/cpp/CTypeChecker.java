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

import java.util.List;
import java.util.LinkedList;

import xtc.Constants;
import xtc.Limits;

import xtc.tree.Attribute;
import xtc.tree.GNode;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.Token;
import xtc.tree.Visitor;

import xtc.type.AliasT;
import xtc.type.ArrayT;
import xtc.type.BooleanT;
import xtc.type.C;
import xtc.type.CastReference;
import xtc.type.Constant;
import xtc.type.DynamicReference;
import xtc.type.EnumT;
import xtc.type.EnumeratorT;
import xtc.type.ErrorT;
import xtc.type.FieldReference;
import xtc.type.FunctionT;
import xtc.type.InternalT;
import xtc.type.LabelT;
import xtc.type.NullReference;
import xtc.type.NumberT;
import xtc.type.PointerT;
import xtc.type.Reference;
import xtc.type.StaticReference;
import xtc.type.StringReference;
import xtc.type.StructOrUnionT;
import xtc.type.StructT;
import xtc.type.Tagged;
import xtc.type.Type;
import xtc.type.Type.Tag;
import xtc.type.UnionT;
import xtc.type.VariableT;
import xtc.type.VoidT;

import xtc.util.Pair;

import xtc.lang.cpp.Syntax.Kind;
import xtc.lang.cpp.Syntax.LanguageTag;
import xtc.lang.cpp.Syntax.ConditionalTag;
import xtc.lang.cpp.Syntax.DirectiveTag;
import xtc.lang.cpp.Syntax.Layout;
import xtc.lang.cpp.Syntax.Language;
import xtc.lang.cpp.Syntax.Text;
import xtc.lang.cpp.Syntax.Directive;
import xtc.lang.cpp.Syntax.Conditional;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

import xtc.lang.cpp.ForkMergeParser.StackFrame;
import xtc.lang.cpp.ForkMergeParser.Subparser;

/**
 * This class implements the generated CActionsInterface.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.3 $
 */
public class CTypeChecker extends CActionsInterface {
  /** True when statistics should be output. */
  private boolean languageStatistics;

  /** Construct a new C semantic actions plugin. */
  private CTypeChecker() {
  }

  /** The instance of this class */
  private static CTypeChecker ref;

  /** Get the instance of this class */
  public static CTypeChecker getInstance() {
    if (null == ref) {
      ref = new CTypeChecker();
    }
    return ref;
  }

  /**
   * Turn language statistics collection on.  Default is off.
   *
   * @param b True is on.
   */
  public void collectStatistics(boolean b) {
    languageStatistics = b;
  }

  protected static class Specifiers {
    /** Presence condition. */
    public PresenceCondition pc;

    /** True if there is a type error. */
    public boolean error;

    /** The type-error message. */
    public String error_message;

    /** The flag for whether a tag reference is a declaration. */
    public boolean refIsDecl;

    /** The type, if any. */
    public Type type;

    /** The storage class attribute, if any. */
    public Attribute storage;

    /** The thread-local attribute, if any. */
    public Attribute threadlocal;

    /** The inline attribute, if any. */
    public Attribute function;

    /** Any other attributes. */
    public List<Attribute> attributes;

    // The internal state for tracking type specifiers.
    public boolean seenSigned;
    public boolean seenUnsigned;
    public boolean seenBool;
    public boolean seenChar;
    public boolean seenShort;
    public boolean seenInt;
    public int     longCount;
    public boolean seenFloat;
    public boolean seenDouble;
    public boolean seenComplex;

    public Specifiers(PresenceCondition pc) {
      this.pc = pc;
    }

    public Specifiers(PresenceCondition pc, Specifiers s) {
      this(pc);
      this.error = s.error;
      this.error_message = s.error_message;
      this.refIsDecl = s.refIsDecl;
      this.type = s.type;
      this.storage = s.storage;
      this.threadlocal = s.threadlocal;
      this.function = s.function;
      this.attributes = s.attributes;
      this.seenSigned = s.seenSigned;
      this.seenUnsigned = s.seenUnsigned;
      this.seenBool = s.seenBool;
      this.seenChar = s.seenChar;
      this.seenShort = s.seenShort;
      this.seenInt = s.seenInt;
      this.longCount = s.longCount;
      this.seenFloat = s.seenFloat;
      this.seenDouble = s.seenDouble;
      this.seenComplex = s.seenComplex;
    }

    /** Test for previous type. */
    protected boolean hasType() {
      return
        (seenBool || seenChar || seenShort || seenInt || (0 < longCount) ||
         seenFloat || seenDouble || seenComplex ||
         (null != type));
    }

    /** Report error indicating multiple types. */
    protected void multipleTypes() {
      this.error = true;
      this.error_message = "multiple data types in declaration specifiers";
      type = ErrorT.TYPE;
    }

    public void setError(String msg) {
      this.error = true;
      this.error_message = msg;
      System.err.println("error in specifiers: " + msg);
    }

    // Get specs.  Gets list of specifiers, checking for type errors.
    // Also need to hoist conditionals around complete type
    // specifiers.  Is it possible to make a hoisting tree-walker?
    // Walk tree, when encountering conditional, fork the spec state
    // and walk both.  No need for merge, since there are two
    // different declarations.
  }

  protected void typeDispatch(Visitor v, Object o) {
    if (o instanceof Syntax) {
      v.dispatch((Syntax) o);
    } else if (o instanceof GNode) {
      v.dispatch((GNode) o);
    } else {
      System.err.println("internal error: invalid AST type.  shouldn't happen. " + o.getClass());
    }
  }

  /**
   * For a given tree node containing declaration specificers, return
   * a list of Specifiers classes hoisted around conditionals.
   *
   * @param spec_tree Type specifier subtree, potentially with
   * conditional nodes.
   * @param specs The current Specifiers object to continue analyzing
   * from.
   * @return A list of Specifier objects.
   */
  protected List<Specifiers> getSpecifiers(Object spec_tree, final Specifiers specs) {
    final List<Specifiers> hoisted_specs = new LinkedList<Specifiers>();
    final Visitor v = new Visitor() {
        public void visit(GNode n) {
          for (Object o : n) {
            typeDispatch(this, o);
          }
        }

        public void visitConditional(GNode n) {
          // stop if there is a type error

          // filter out infeasible configurations

          // update pc of spec object, create new spec object

          // recursively call getSpecifiers on both objects, passing
          // the child

          System.err.println("TODO, fork");
          typeDispatch(this, n.get(1));
        }

        public void visitStorageClass(GNode n) {
          LanguageTag tag = (((Syntax) n.get(0)).toLanguage()).tag();
          String token = CParseTables.getInstance().yytname[tag.getID()];
          String name = tag.getText();
          Attribute storage;
          
          if (token.equals("AUTO")) {
            storage = Constants.ATT_STORAGE_AUTO;
          } else if (token.equals("EXTERN")) {
            storage = Constants.ATT_STORAGE_EXTERN;
          } else if (token.equals("REGISTER")) {
            storage = Constants.ATT_STORAGE_REGISTER;
          } else if (token.equals("STATIC")) {
            storage = Constants.ATT_STORAGE_STATIC;
          } else if (token.equals("TYPEDEF")) {
            storage = Constants.ATT_STORAGE_TYPEDEF;
          } else {
            storage = null;
            error("unsupported storage class found " + name);
          }

          if (null == specs.storage) {
            specs.storage = storage;
          } else if (specs.storage == storage) {
            specs.setError("duplicate '" + name + "'");
          } else {
            specs.setError("multiple storage classes in declaration specifiers");
          }

          System.err.println(specs.storage);
        }

        public void visitBasicType(GNode n) {
          LanguageTag tag = (((Syntax) n.get(0)).toLanguage()).tag();
          String token = CParseTables.getInstance().yytname[tag.getID()];
          String name = tag.getText();

          if (token.equals("VOID")) {
            if (specs.hasType()) {
              specs.multipleTypes();
            } else {
              specs.type = VoidT.TYPE;
            }
          } else if (token.equals("CHAR")) {
            if (specs.hasType()) {
              specs.multipleTypes();
            } else {
              specs.seenChar = true;
            }
          } else if (token.equals("SHORT")) {
            if (specs.seenBool || specs.seenChar || specs.seenShort || (0 < specs.longCount) ||
                specs.seenFloat || specs.seenDouble || specs.seenComplex ||
                (null != specs.type)) {
              specs.multipleTypes();
            } else {
              specs.seenShort = true;
            }
          } else if (token.equals("INT")) {
            if (specs.seenBool || specs.seenChar || specs.seenInt ||
                specs.seenFloat || specs.seenDouble || specs.seenComplex ||
                (null != specs.type)) {
              specs.multipleTypes();
            } else {
              specs.seenInt = true;
            }
          } else if (token.equals("LONG")) {
            if (specs.seenBool || specs.seenChar || specs.seenShort || (1 < specs.longCount) ||
                specs.seenFloat ||
                ((specs.seenDouble || specs.seenComplex) &&
                 (0 < specs.longCount)) ||
                (null != specs.type)) {
              specs.multipleTypes();
            } else {
              specs.longCount++;
            }
          } else if (token.equals("FLOAT")) {
            if (specs.seenBool || specs.seenChar || specs.seenShort || specs.seenInt || (0 < specs.longCount) ||
                specs.seenDouble ||
                (null != specs.type)) {
              specs.multipleTypes();
            } else {
              specs.seenFloat = true;
            }
          } else if (token.equals("DOUBLE")) {
            if (specs.seenBool || specs.seenChar || specs.seenShort || specs.seenInt || (1 < specs.longCount) ||
                specs.seenFloat ||
                (null != specs.type)) {
              specs.multipleTypes();
            } else {
              specs.seenDouble = true;
            }
          } else if (token.equals("UNSIGNED")) {
            if (specs.seenSigned) {
              specs.seenUnsigned = true;
              specs.setError("both 'signed' and 'unsigned' in declaration specifiers");
            } else if (specs.seenUnsigned) {
              specs.setError("duplicate 'unsigned'");
            } else {
              specs.seenUnsigned = true;
            }
          } else if (token.equals("_BOOL")) {
            if (specs.hasType()) {
              specs.multipleTypes();
            } else {
              specs.seenBool = true;
            }
          } else {
            error("unsupported basic type found " + name);
          }
        }

        public void visitComplexKeyword(GNode n) {
          if (specs.seenBool || specs.seenChar || specs.seenShort || specs.seenInt || (1 < specs.longCount) ||
              (null != specs.type)) {
            specs.multipleTypes();
          } else {
            specs.seenComplex = true;
          }
        }

        public void visitSignedKeyword(GNode n) {
          if (specs.seenUnsigned) {
            specs.seenSigned = true;
            specs.setError("both 'signed' and 'unsigned' in declaration specifiers");
          } else if (specs.seenSigned) {
            specs.setError("duplicate 'signed'");
          } else {
            specs.seenSigned = true;
          }
        }

        public void visit(Syntax s) {
          System.err.println("TODO unchecked syntax object: " + s);
        }
      };

    typeDispatch(v, spec_tree);

    // if (spec_tree instanceof Syntax) {
    //   if (((Syntax) spec_tree).kind() == Syntax.Kind.LANGUAGE) {
    //     System.err.println(spec_tree);
    //   } else {
    //     System.err.println("internal error: invalid Syntax type.  shouldn't happen");
    //   }
    // } else if (spec_tree instanceof GNode) {
    //   Visitor v = new Visitor() {
    //       public void visit(GNode n) {
    //         dispatch(n.getGeneric(0));
    //       }
    //     };

    //   v.dispatch((GNode) spec_tree);
    // } else {
    //   System.err.println("internal error: invalid AST type.  shouldn't happen");
    // }

    // for each configuration, verify that it has a valid set of
    // specifiers

    return null;
  }

  public void BindIdentifier(Subparser subparser) {
    StackFrame stack = subparser.stack;
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
    CTypeContext scope = (CTypeContext) subparser.scope;
    boolean typedef;
    Language ident;
      
    // Get the AST nodes that contain the type specifier and the
    // declarator.
    Object a = stack.get(3).value;
    Object b = stack.get(2).value;
    List<Specifiers> hoisted_specs = getSpecifiers(a, new Specifiers(presenceCondition));
    System.err.println("decl: " + b);

    // c-decl.c, grokdeclarator and decl_context

    // Check whether the declaration is a typedef.  This assumes that
    // the typedef keyword is the first token of the declaration.
    Language t;
    while (true) {
      if (a instanceof Node && ! (a instanceof Syntax)) {
        Node n = (Node) a;
        if (n.hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
          // When it's a conditional node, the first child is a
          // presence condition, the second is the first AST child.
          a = n.get(1);
        } else {
          a = n.get(0);
        }
      } else if (a instanceof Pair) {
        a = ((Pair) a).head();
      } else {
        break;
      }
    }
    t = (Language) a;

    // Get the identifier in the declarator.
    ident = getident(b);

    if (CTag.TYPEDEF == t.tag()) {
      // Bind a typedef name.
      typedef = true;

      if (languageStatistics) {
        if (typedef) {
          Location location = subparser.lookahead.token.syntax.getLocation();
          System.err.println(String.format("typedef %s %s", ident, location));
        }
      }
    } else {
      // Binding a variable name.
      typedef = false;
    }
      
    scope.bind(ident.getTokenText(), typedef, presenceCondition);
  }
    
  public void BindIdentifierInList(Subparser subparser) {
    StackFrame stack = subparser.stack;
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
    CTypeContext scope = (CTypeContext) subparser.scope;
      
    boolean typedef;
    Language ident;
      
    // Get the AST nodes that contain the type specifier and the
    // declarator.
    Object a = stack.get(5).value;
    Object b = stack.get(2).value;
      
    // Check whether the declaration is a typedef.  This assumes that
    // the typedef keyword is the first token of the declaration.
    Language t;
    while (true) {
      if (a instanceof Node && ! (a instanceof Syntax)) {
        Node n = (Node) a;
        if (n.hasName(ForkMergeParser.CHOICE_NODE_NAME)) {
          // When it's a conditional node, the first child is a
          // presence condition, the second is the first AST child.
          a = n.get(1);
        } else {
          a = n.get(0);
        }
      } else if (a instanceof Pair) {
        a = ((Pair) a).head();
      } else {
        break;
      }
    }
    t = (Language) a;

    // Get the identifier in the declarator.
    ident = getident(b);

    if (CTag.TYPEDEF == t.tag()) {
      // Bind a typedef name.
      typedef = true;

      if (languageStatistics) {
        if (typedef) {
          Location location = subparser.lookahead.token.syntax.getLocation();
          System.err.println(String.format("typedef %s %s", ident, location));
        }
      }
    } else {
      // Bind a variable name.
      typedef = false;
    }
      
    scope.bind(ident.getTokenText(), typedef, presenceCondition);
  }
    
  public void BindVar(Subparser subparser) {
    StackFrame stack = subparser.stack;
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
    CTypeContext scope = (CTypeContext) subparser.scope;
      
    // Get the identifier in the declarator.
    Object b = stack.get(2).value;
    Language<?> ident = getident(b);

    // Bind variable name.
    scope.bind(ident.getTokenText(), false, presenceCondition);
  }
    
  public void BindEnum(Subparser subparser) {
    StackFrame stack  = subparser.stack;
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
    CTypeContext scope = (CTypeContext) subparser.scope;
      
    // Get the identifier in the declarator.  The identifier must
    // occur after an IdentifierOrTypedefName token.
    Object b = stack.get(2).value;
    String ident = getident(b).getTokenText();

    // Bind variable name.
    scope.bind(ident, false, presenceCondition);
  }
    
  public void EnterScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope = ((CTypeContext) subparser.scope).enterScope(presenceCondition);
  }
    
  public void ExitScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope = ((CTypeContext) subparser.scope).exitScope(presenceCondition);
  }

  public void ExitReentrantScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope
      = ((CTypeContext) subparser.scope).exitReentrantScope(presenceCondition);
  }
    
  public void ReenterScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope
      = ((CTypeContext) subparser.scope).reenterScope(presenceCondition);
  }
    
  public void KillReentrantScope(Subparser subparser) {
    PresenceConditionManager.PresenceCondition presenceCondition = subparser.getPresenceCondition();
      
    subparser.scope
      = ((CTypeContext) subparser.scope).killReentrantScope(presenceCondition);
  }
    
  /**
   * Find the identifier or typedef name in a declarator.  Assume
   * the first identifier in the subtree is the var or typedef name.
   *
   * @param o The semantic value.
   * @return The first identifier in the subtree or null if there is
   * none.
   */
  private static Language getident(Object o) {
    if (o instanceof Language) {
      Language token = ((Language) o);
        
      if (CTag.IDENTIFIER == token.tag()
          || CTag.TYPEDEFname == token.tag()) {
        return token;

      } else {
        return null;
      }

    } else if (o instanceof Pair) {
      Pair<?> b = (Pair<?>) o;
        
      while (b != Pair.empty()) {
        Object child = b.head();
          
        if (null != child) {
          Language ident = getident(child);
            
          if (null != ident) {
            return ident;
          }
        }
          
        b = b.tail();
      }
        
      return null;
    } else if (o instanceof PresenceConditionManager.PresenceCondition) {
      return null;
    } else {
      Node b = (Node) o;
        
      for (int i = 0; i < b.size(); i++) {
        Object child = b.get(i);
          
        if (null != child) {
          Language ident = getident(child);
            
          if (null != ident) {
            return ident;
          }
        }
      }
        
      return null;
    }
  }

  public void Declaration(Subparser parser) {
    System.err.println("encountered declaration");
  }

  public void CompoundStatement(Subparser parser) {
    System.err.println("encountered compoundstatement");
  }

  public void FunctionCompoundStatement(Subparser parser) {
    System.err.println("encountered functioncompoundstatement");
  }

  private void error(String msg) {
    System.err.println("error: " + msg);
    System.exit(1);
  }

  // Temporary
  Specifiers specs = new Specifiers(null);

  public void StorageClass(Subparser parser) {
    GNode n = (GNode) parser.stack.value;
    LanguageTag tag = (((Syntax) n.get(0)).toLanguage()).tag();
    String token = CParseTables.getInstance().yytname[tag.getID()];
    String name = tag.getText();
    Attribute storage;
          
    if (token.equals("AUTO")) {
      storage = Constants.ATT_STORAGE_AUTO;
    } else if (token.equals("EXTERN")) {
      storage = Constants.ATT_STORAGE_EXTERN;
    } else if (token.equals("REGISTER")) {
      storage = Constants.ATT_STORAGE_REGISTER;
    } else if (token.equals("STATIC")) {
      storage = Constants.ATT_STORAGE_STATIC;
    } else if (token.equals("TYPEDEF")) {
      storage = Constants.ATT_STORAGE_TYPEDEF;
    } else {
      storage = null;
      error("unsupported storage class found " + name);
    }

    if (null == specs.storage) {
      specs.storage = storage;
    } else if (specs.storage == storage) {
      specs.setError("duplicate '" + name + "'");
    } else {
      specs.setError("multiple storage classes in declaration specifiers");
    }

    System.err.println(specs.storage);
  }

  public void BasicType(Subparser parser) {
    GNode n = (GNode) parser.stack.value;
    LanguageTag tag = (((Syntax) n.get(0)).toLanguage()).tag();
    String token = CParseTables.getInstance().yytname[tag.getID()];
    String name = tag.getText();

    if (token.equals("VOID")) {
      if (specs.hasType()) {
        specs.multipleTypes();
      } else {
        specs.type = VoidT.TYPE;
      }
    } else if (token.equals("CHAR")) {
      if (specs.hasType()) {
        specs.multipleTypes();
      } else {
        specs.seenChar = true;
      }
    } else if (token.equals("SHORT")) {
      if (specs.seenBool || specs.seenChar || specs.seenShort || (0 < specs.longCount) ||
          specs.seenFloat || specs.seenDouble || specs.seenComplex ||
          (null != specs.type)) {
        specs.multipleTypes();
      } else {
        specs.seenShort = true;
      }
    } else if (token.equals("INT")) {
      if (specs.seenBool || specs.seenChar || specs.seenInt ||
          specs.seenFloat || specs.seenDouble || specs.seenComplex ||
          (null != specs.type)) {
        specs.multipleTypes();
      } else {
        specs.seenInt = true;
      }
    } else if (token.equals("LONG")) {
      if (specs.seenBool || specs.seenChar || specs.seenShort || (1 < specs.longCount) ||
          specs.seenFloat ||
          ((specs.seenDouble || specs.seenComplex) &&
           (0 < specs.longCount)) ||
          (null != specs.type)) {
        specs.multipleTypes();
      } else {
        specs.longCount++;
      }
    } else if (token.equals("FLOAT")) {
      if (specs.seenBool || specs.seenChar || specs.seenShort || specs.seenInt || (0 < specs.longCount) ||
          specs.seenDouble ||
          (null != specs.type)) {
        specs.multipleTypes();
      } else {
        specs.seenFloat = true;
      }
    } else if (token.equals("DOUBLE")) {
      if (specs.seenBool || specs.seenChar || specs.seenShort || specs.seenInt || (1 < specs.longCount) ||
          specs.seenFloat ||
          (null != specs.type)) {
        specs.multipleTypes();
      } else {
        specs.seenDouble = true;
      }
    } else if (token.equals("UNSIGNED")) {
      if (specs.seenSigned) {
        specs.seenUnsigned = true;
        specs.setError("both 'signed' and 'unsigned' in declaration specifiers");
      } else if (specs.seenUnsigned) {
        specs.setError("duplicate 'unsigned'");
      } else {
        specs.seenUnsigned = true;
      }
    } else if (token.equals("_BOOL")) {
      if (specs.hasType()) {
        specs.multipleTypes();
      } else {
        specs.seenBool = true;
      }
    } else {
      error("unsupported basic type found " + name);
    }
  }

  // public void ComplexKeyword(Subparser parser) {
  //   if (specs.seenBool || specs.seenChar || specs.seenShort || specs.seenInt || (1 < specs.longCount) ||
  //       (null != specs.type)) {
  //     specs.multipleTypes();
  //   } else {
  //     specs.seenComplex = true;
  //   }
  // }

  // public void SignedKeyword(Subparser parser) {
  //   if (specs.seenUnsigned) {
  //     specs.seenSigned = true;
  //     specs.setError("both 'signed' and 'unsigned' in declaration specifiers");
  //   } else if (specs.seenSigned) {
  //     specs.setError("duplicate 'signed'");
  //   } else {
  //     specs.seenSigned = true;
  //   }
  // }
}
