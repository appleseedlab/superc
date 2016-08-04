/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2008 Robert Grimm
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
package xtc.lang;

import xtc.Constants;

import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Token;
import xtc.tree.Visitor;

import xtc.type.ArrayT;
import xtc.type.StringReference;
import xtc.type.Tagged;
import xtc.type.Type;

import xtc.util.Runtime;
import xtc.util.SymbolTable;
import xtc.util.Utilities;

/**
 * A visitor to extract C features.  This visitor assumes that the AST
 * is well-typed and annotated with the correct types.
 *
 * @author Robert Grimm
 * @version $Revision: 1.6 $
 */
public class CFeatureExtractor extends Visitor {

  /** The runtime. */
  protected final Runtime runtime;

  /** The symbol table. */
  protected SymbolTable table;

  /** The type of the current construct. */
  protected Type type;

  /** The name of the variable being declared. */
  protected String name;

  /**
   * Create a new C feature extractor.
   *
   * @param runtime The runtime.
   */
  public CFeatureExtractor(Runtime runtime) {
    this.runtime = runtime;
  }

  /**
   * Process the specified AST.
   *
   * @param node The type-checked and marked AST.
   * @param table The corresponding symbol table.
   */
  public void process(Node node, SymbolTable table) {
    this.table = table;
    type       = null;
    name       = null;

    runtime.console().sep();
    dispatch(node);
    runtime.console().sep().flush();
  }

  /**
   * Start processing the specified node.
   *
   * @param node The node to process.
   * @return The type of the surrounding construct.
   */
  public Type enter(GNode node) {
    Type old = type;
    type     = toType(node);
    return old;
  }

  /**
   * Stop processing the current node.
   *
   * @param old The type of the surrounding construct.
   */
  public void exit(Type old) {
    type = old;
  }

  /** Visit the specified initialized declarator. */
  public void visitInitializedDeclarator(GNode n) {
    final String oldName    = name;
    final Type   oldType    = type;

    name = CAnalyzer.getDeclaredId(n.getGeneric(1)).getString(0);
    type = (Type)table.lookup(name);

    visit(n);

    if (isZeroLength(type)) {
      runtime.console().loc(n).p(": zero length array '").p(name).pln("'");
    }

    if (null != n.get(2)) {
      final String alt = toText(n.getGeneric(2).getGeneric(0));
      runtime.console().loc(n).p(": assembly name '").p(name).p("' -> '").
        p(alt).pln("'");
    }

    name = oldName;
    type = oldType;
  }

  /** Visit the specified thread specifier. */
  public void visitThreadSpecifier(GNode n) {
    runtime.console().loc(n).pln(": thread-local");
  }

  /** Visit the specified enumertion type definition. */
  public void visitEnumerationTypeDefinition(GNode n) {
    final Type old = enter(n);
    visit(n);
    exit(old);
  }

  /** Visit the specified enumeration type reference. */
  public void visitEnumerationTypeReference(GNode n) {
    final Type old = enter(n);
    visit(n);
    exit(old);
  }

  /** Visit the specified structure type definition. */
  public void visitStructureTypeDefinition(GNode n) {
    final Type old = enter(n);
    visit(n);

    if (0 == type.toTagged().getMemberCount()) {
      runtime.console().loc(n).p(": empty ").pln(toDescription(type));
    }

    exit(old);
  }

  /** Visit the specified structure type reference. */
  public void visitStructureTypeReference(GNode n) {
    final Type old = enter(n);
    visit(n);
    exit(old);
  }

  /** Visit the specified union type definition. */
  public void visitUnionTypeDefinition(GNode n) {
    final Type old = enter(n);
    visit(n);

    if (0 == type.toTagged().getMemberCount()) {
      runtime.console().loc(n).p(": empty ").pln(toDescription(type));
    }

    exit(old);
  }

  /** Visit the specified union type reference. */
  public void visitUnionTypeReference(GNode n) {
    final Type old = enter(n);
    visit(n);
    exit(old);
  }

  /** Visit the specified structure declaration. */
  public void visitStructureDeclaration(GNode n) {
    if (null == n.get(2)) runtime.console().loc(n).pln(": unnamed field");
    visit(n);
  }

  /** Visit the specified structure declarator. */
  public void visitStructureDeclarator(GNode n) {
    final GNode id = CAnalyzer.getDeclaredId(n);

    if (null != id) {
      final String s = id.getString(0);
      final Type   t = type.toTagged().lookup(s);

      if (isZeroLength(t)) {
        runtime.console().loc(n).p(": zero length array '").p(s).pln("'");
      }
    }
  }

  /** Visit the specified parameter type list. */
  public void visitParameterTypeList(GNode n) {
    final Type old = type;
    type           = null;

    visit(n);

    type = old;
  }

  /** Visit the specified parameter declaration. */
  public void visitParameterDeclaration(GNode n) {
    final String oldName = name;
    final GNode  id      = CAnalyzer.getDeclaredId(n.getGeneric(1));
    name                 = null == id ? null : id.getString(0);

    visit(n);

    name = oldName;
  }

  /** Visit the specified typeof specifier. */
  public void visitTypeofSpecifier(GNode n) {
    runtime.console().loc(n).pln(": typeof");
    visit(n);
  }

  /** Visit the specified var-arg list specifier. */
  public void visitVarArgListSpecifier(GNode n) {
    runtime.console().loc(n).pln(": var-arg list");
  }

  /** Visit the specified designator. */
  public void visitDesignator(GNode n) {
    if (3 == n.size()) runtime.console().loc(n).pln(": array range");
    visit(n);
  }

  /** Visit the specified obsolete array designation. */
  public void visitObsoleteArrayDesignation(GNode n) {
    if (3 == n.size()) runtime.console().loc(n).pln(": array range");
    visit(n);
  }

  /** Visit the specified attribute list entry. */
  public void visitAttributeListEntry(GNode n) {
    runtime.console().loc(n).p(": ");

    if (null != type && type.resolve().isFunction()) {
      runtime.console().p("function attribute '").p(name).p("' -> ");
    } else if (null != type && type.hasTagged()) {
      runtime.console().p("type attribute '").p(toDescription(type)).p("' -> ");
    } else {
      runtime.console().p("variable attribute ");
      if (null != name) runtime.console().p("'").p(name).p("' -> ");
    }
    runtime.console().p("'").p(n.getString(0)).pln("'");

    dispatch(n.getNode(1));
  }

  /** Visit the specified local label declaration. */
  public void visitLocalLabelDeclaration(GNode n) {
    runtime.console().loc(n).p(": local label");
    if (1 == n.size()) {
      runtime.console().p(' ');
    } else {
      runtime.console().p("s ");
    }
    boolean first = true;
    for (Object o : n) {
      if (first) {
        first = false;
      } else {
        runtime.console().p(", ");
      }
      runtime.console().p("'").p((String)o).p("'");
    }
    runtime.console().pln();
  }

  /** Visit the specified case label. */
  public void visitCaseLabel(GNode n) {
    if (2 == n.size()) runtime.console().loc(n).pln(": case range");
    visit(n);
  }

  /** Visit the specified goto statement. */
  public void visitGotoStatement(GNode n) {
    if (null != n.get(0)) runtime.console().loc(n).pln(": computed goto");
    visit(n);
  }

  /** Visit the specified alignof expression. */
  public void visitAlignofExpression(GNode n) {
    runtime.console().loc(n).pln(": alignof");
    visit(n);
  }

  /** Visit the specified offsetof expression. */
  public void visitOffsetofExpression(GNode n) {
    runtime.console().loc(n).pln(": offsetof");
    visit(n);
  }

  /** Visit the specified type compatibility expression. */
  public void visitTypeCompatibilityExpression(GNode n) {
    runtime.console().loc(n).pln(": types_compatible_p");
    visit(n);
  }

  /** Visit the specified label address expression. */
  public void visitLabelAddressExpression(GNode n) {
    runtime.console().loc(n).pln(": label address");
    visit(n);
  }

  /** Visit the specified function call. */
  public void visitFunctionCall(GNode n) {
    if (n.getGeneric(0).hasName("PrimaryIdentifier")) {
      final String s = n.getGeneric(0).getString(0);

      if (s.startsWith("__builtin_") || s.startsWith("__sync_")) {
        runtime.console().loc(n).p(": call to built-in function '").p(s).
          pln("'");
      }
    }
    visit(n);
  }

  /** Visit the specified statement as expression. */
  public void visitStatementAsExpression(GNode n) {
    runtime.console().loc(n).pln(": statement expression");
    visit(n);
  }

  /** Visit the specified variable argument access. */
  public void visitVariableArgumentAccess(GNode n) {
    runtime.console().loc(n).
      pln(": call to built-in function '__builtin_va_arg'");
    visit(n);
  }

  /** Visit the specified assembly argument. */
  public void visitAssemblyArgument(GNode n) {
    if (1 < n.size()) runtime.console().loc(n).pln(": extended asm");
    visit(n);
  }

  /** Visit the specified node. */
  public void visit(Node n) {
    table.enter(n);
    for (Object o :  n) {
      if (o instanceof Node) dispatch((Node)o);
    }
    table.exit(n);
  }
  
  /**
   * Get the specified node's type from the corresponding property.
   *
   * @param node The node.
   * @return The corresponding type.
   */
  public static final Type toType(Node node) {
    Type t = (Type)node.getProperty(Constants.TYPE);
    assert null != t;
    return t;
  }

  /**
   * Determine whether the specified type represents a zero-length
   * array.
   *
   * @param type The type.
   * @return <code>true</code> if the type is a zero-length array.
   */
  public static boolean isZeroLength(Type type) {
    type = type.resolve();
    if (! type.isArray()) return false;
    ArrayT array = type.toArray();
    return array.hasLength() && 0 == array.getLength();
  }

  /**
   * Get the specified type's description.
   *
   * @param type The type.
   * @return The corresponding description or <code>null</code> if
   *   there is no description.
   */
  public static String toDescription(Type type) {
    String s = null;

    if (type.hasTagged()) {
      Tagged tagged = type.toTagged();

      if (tagged.isEnum()) {
        s = "enum";
      } else if (tagged.isStruct()) {
        s = "struct";
      } else {
        s = "union";
      }

      if (! tagged.isUnnamed()) {
        s = s + ' ' + tagged.getName();
      }
    }

    return s;
  }

  /**
   * Get the specified string constant's text.
   *
   * @param node The string constant node.
   * @return The corresponding text.
   */
  public final String toText(GNode node) {
    assert node.hasName("StringConstant");

    return ((StringReference)toType(node).getShape()).getLiteral();
  }

}
