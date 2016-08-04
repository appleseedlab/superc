/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007 IBM Corp.
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
package xtc.lang.jeannie;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import xtc.lang.JavaAstSimplifier;
import xtc.tree.LineMarker;
import xtc.tree.Node;
import xtc.tree.Visitor;

/**
 * A visitor that simplifies Jeannie ASTs. Uses JavaAstSimplifier on the Java
 * parts of the AST, while leaving the C part of the AST untouched.
 */
public class AstSimplifier extends Visitor {
  private static final class JavaSimplifier extends JavaAstSimplifier {
    final AstSimplifier _jeannieSimplifier;
    
    JavaSimplifier(final AstSimplifier jeannieSimplifier) {
      _jeannieSimplifier = jeannieSimplifier;
    }
    
    public final Node visit(final Node n) {
      if (GOTO_C.contains(n.getName())) {
        _jeannieSimplifier._inJava = false;
        final Node result = _jeannieSimplifier.genericDispatch(n);
        _jeannieSimplifier._inJava = true;
        return result;
      }
      return super.visit(n);
    }
  }

  private static final Set<String> GOTO_C =
    Collections.unmodifiableSet(new HashSet<String>(Arrays.asList(new String[] {
      "CDeclarations", "CInJavaBlock", "CInJavaExpression", "TranslationUnit" })));

  private static final Set<String> GOTO_JAVA =
    Collections.unmodifiableSet(new HashSet<String>(Arrays.asList(new String[] {
      "CompilationUnit", "JavaImports", "JavaInCBlock", "JavaInCExpression", "JavaInCStatement", "JavaThrows", "JavaType" })));

  private boolean _inJava;

  private final JavaSimplifier _javaSimplifier;

  /** Create a new jeannie.AstSimplifier, and specify the initial language with "Java" or "C". */
  public AstSimplifier(final String language) {
    _inJava = "Java".equals(language);
    _javaSimplifier = new JavaSimplifier(this);
  }

  private final Node genericDispatch(final Node n) {
    for (int i=0; i<n.size(); i++) {
      final Object o = n.get(i);
      if (o instanceof Node)
        n.set(i, dispatch((Node) o));
    }
    return n;
  }
  
  public final LineMarker visit(final LineMarker m) {
    m.setNode((Node) dispatch(m.getNode()));
    return m;
  }

  /** Dispatch the node in C or in Java depending on the current language, and
   * depending on whether the node itself indicates a language transition.
   * Transitions from Java to C are handled indirectly by
   * JeannieJAstSimplifier.visit(GNode).
   */
  public final Node visit(final Node n) {
    final Node result;
    if (_inJava) {
      result = (Node) _javaSimplifier.dispatch(n);
    } else if (GOTO_JAVA.contains(n.getName())) {
      _inJava = true;
      result = genericDispatch(n);
      _inJava = false;
    } else {
      result = genericDispatch(n);
    }
    return result;
  }
}
