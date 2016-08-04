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

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.Stack;

import xtc.Constants;
import xtc.lang.CAnalyzer;
import xtc.lang.JavaAnalyzer;
import xtc.lang.JavaEntities;
import xtc.lang.JavaTypeConverter;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Visitor;
import xtc.type.C;
import xtc.type.DynamicReference;
import xtc.type.ErrorT;
import xtc.type.FunctionT;
import xtc.type.PointerT;
import xtc.type.Reference;
import xtc.type.Type;
import xtc.type.VariableT;
import xtc.util.Runtime;
import xtc.util.SymbolTable;

/**
 * A visitor that constructs a symbol table for a Jeannie file.
 * Assumes that the AST has been simplified with jeannie.AstSimplifier.
 *
 * @author Martin Hirzel
 */
public final class Analyzer extends Visitor {
  static final class JeannieCAnalyzer extends CAnalyzer {
    private static final class JeannieC extends C {
      public final boolean isConstant(final Type t) {
        if (Utilities.isJavaEntity(t))
          return JavaEntities.isConstantT(t);
        if (t.hasAttribute(Constants.ATT_CONSTANT, false))
          return true;
        switch (t.tag()) {
          case ARRAY: {
            final Type e = t.resolve().toArray().getType();
            return null == e ? false : isConstant(e);
          }
          case STRUCT:
          case UNION: {
            for (final Type e : t.toTagged().getMembers())
              if (isConstant(e))
                return true;
            return false;
          }
        }
        return t.isWrapped() ? isConstant(t.toWrapped().getType()) : false;
      }
    }

    static final class JeannieCContext {
      boolean _hasScope;
      boolean _isTopLevel;
      boolean _localsAreLifted;
      int _loops;
      List<Type> _openArrays;
      List<Boolean> _switches;
    }

    final class JeannieCSpecifiers extends CAnalyzer.Specifiers {
      public JeannieCSpecifiers(final GNode specifiers_, final boolean refIsDecl_) {
        super(specifiers_, refIsDecl_);
      }

      /** Visit a JavaType = Java.TypeName. */
      public final void visitJavaType(final GNode n) {
        if (hasType()) {
          multipleTypes();
          return;
        }
        _jeannieAnalyzer.enterJava();
        final Type result;
        final SymbolTable tab = getTable();
        if (n.getNode(0).hasName("QualifiedIdentifier")) {
          final String qualifiedName = (String) _jeannieAnalyzer.dispatch(n.getNode(0));
          final List<File> paths = JavaEntities.classpath(getRuntime());
          result = JavaEntities.qualifiedNameToType(tab, paths, tab.current().getQualifiedName(), qualifiedName);
        } else {
          assert n.getNode(0).hasName("PrimitiveType");
          final Type jType = (Type) _jeannieAnalyzer.dispatch(n.getNode(0));
          result = Utilities.javaTypeToCType(tab, runtime, n, jType, true);
        }
        _jeannieAnalyzer.exitJava();
        type = JavaAnalyzer.setType(n, result);
      }
    }
    
    /**
     * Descends into a Declarator to find a FunctionDeclarator with a throws clause, if any:<br>
     * FunctionDeclarator = (ParameterTypeList / IdentifierList) JavaThrows.
     */
    protected static GNode getDeclaredExceptions(final GNode declarator) {
      @SuppressWarnings("unused")
      final Visitor v = new Visitor() {
        public final Object visit(final GNode n) {
          return null;
        }
        public final Object visitArrayDeclarator(final GNode n) {
          return dispatch(n.getGeneric(0));
        }
        public final Object visitAttributedDeclarator(final GNode n) {
          return dispatch(n.getGeneric(1));
        }
        public final Object visitFunctionDeclarator(final GNode n) {
          final GNode result = n.getGeneric(2); //TD 05 visitFunctionDeclarator throws clause is at index 1!
          assert null == result || result.hasName("JavaThrows");
          return result;
        }
        public final Object visitPointerDeclarator(final GNode n) {
          return dispatch(n.getGeneric(1));
        }
      };
      return GNode.cast(v.dispatch(declarator));
    }

    final Analyzer _jeannieAnalyzer;
    boolean _localsAreLifted;
    final List<Type> _openArrays;

    JeannieCAnalyzer(final Analyzer jeannieAnalyzer) {
      super(new JeannieC(), null == jeannieAnalyzer ? Utilities.newRuntime() : jeannieAnalyzer._runtime);
      _jeannieAnalyzer = jeannieAnalyzer;
      _openArrays = new ArrayList<Type>();
      this.table = null == jeannieAnalyzer ? null : jeannieAnalyzer._table;
      isTopLevel = true;
      _localsAreLifted = false;
      loops.clear();
      switches.clear();
    }

    /** Use this for asserting that the input is typed correctly. */
    protected boolean assrt(final GNode n, final boolean cond, final String msgFormat, final Object... msgArgs) {
      return JavaEntities.runtimeAssrt(runtime, n, cond, msgFormat, msgArgs);
    }
    
    final void assrtOpenArray(final GNode n, final Type t) {
      if (t.hasShape()) {
        final Reference tRef = t.getShape();
        for (int i = _openArrays.size() - 1; i >= 0; i--) {
          final Type o = _openArrays.get(i);
          if (o.hasShape()) {
            final Reference oRef = o.getShape();
            if (tRef == oRef) {
              if (i != _openArrays.size() - 1)
                runtime.error("_with statement for '" + n.getGeneric(0).getString(0) + "' not immediately enclosing", n);
              return;
            }
          }
        }
      }
      runtime.error("no enclosing _with statement for '" + n.getGeneric(0).getString(0) + "'", n);
    }
    
    final void contextRestore(final JeannieCContext other) {
      hasScope = other._hasScope;
      isTopLevel = other._isTopLevel;
      _localsAreLifted = other._localsAreLifted;
      assert _openArrays.size() >= other._openArrays.size();
      while (_openArrays.size() > other._openArrays.size())
        _openArrays.remove(loops.size() - 1);
      for (int i=0; i<_openArrays.size(); i++)
        assert _openArrays.get(i) == other._openArrays.get(i);
      assert loops.size() >= other._loops;
      while (loops.size() > other._loops)
        loops.remove(loops.size() - 1);
      for (int i=0; i<other._loops; i++)
        assert loops.get(i).booleanValue();
      assert switches.size() >= other._switches.size();
      while (switches.size() > other._switches.size())
        switches.remove(switches.size() - 1);
      for (int i=0; i<switches.size(); i++)
        assert switches.get(i).booleanValue() == other._switches.get(i);
    }
    
    final JeannieCContext contextSave() {
      final JeannieCContext result = new JeannieCContext();
      result._hasScope = hasScope;
      result._isTopLevel = isTopLevel;
      result._localsAreLifted = _localsAreLifted;
      result._loops = loops.size();
      result._openArrays = new ArrayList<Type>(_openArrays.size());
      for (final Type t : _openArrays)
        result._openArrays.add(t);
      result._switches = new ArrayList<Boolean>(switches.size());
      for (final Boolean b : switches)
        result._switches.add(b);
      return result;
    }

    final boolean getHasScope() { return hasScope; }

    final List<Boolean> getLoops() { return loops; }

    final Runtime getRuntime() { return runtime; }

    final List<Boolean> getSwitches() { return switches; }

    final SymbolTable getTable() { return table; }

    public final Specifiers newSpecifiers(final GNode specifiers, final boolean refIsDecl) {
      return new JeannieCSpecifiers(specifiers, refIsDecl);
    }

    protected final Type processAssignment(final boolean init, final String op, final Node n,
        final Type lhsType, final Type rhsType) {
      final Type lr = Utilities.getJavaClassOrInterfaceT(lhsType);
      if (JavaEntities.isWrappedClassT(lr) || JavaEntities.isWrappedInterfaceT(lr)) {
        final Type rr = Utilities.cTypeToJavaType(table, runtime, n, rhsType);
        if (rr.isError())
          return ErrorT.TYPE;
        final List<File> paths = JavaEntities.classpath(runtime);
        if (JavaTypeConverter.isAssignable(table, paths, lr, rr))
          return lr;
        runtime.error("illegal C assignment to Java type '" + JavaEntities.javaTypeToString(table, lr) + "'", n);
        return ErrorT.TYPE;
      }
      Type rr = Utilities.getJavaClassOrInterfaceT(rhsType);
      if (JavaEntities.isWrappedClassT(rr) || JavaEntities.isWrappedInterfaceT(rr))
        rr = Utilities.javaTypeToCType(table, runtime, n, rr, false);
      return super.processAssignment(init, op, n, lhsType, rr);
    }
    
    protected final void processParameters(final GNode n, final FunctionT function) {
      function.setExceptions(_jeannieAnalyzer._jAnalyzer._context._handledExceptions);
      super.processParameters(n, function);
    }

    final void setHasScope(final boolean x) { hasScope = x; }

    final void setIsTopLevel(final boolean x) { isTopLevel = x; }
    
    /** Visit a CancelStatement = JeannieC.PrimaryIdentifier. */
    public final void visitCancelStatement(final GNode n) {
      final Type t = (Type) _jeannieAnalyzer.dispatch(n.getGeneric(0));
      assrtOpenArray(n, t);
    }
    
    /** Visit a CInCBlock = LocalLabelDeclaration* JeannieC.DeclarationOrStatement* Annotations. */
    public final Type visitCInCBlock(final GNode n) {
      return super.visitCompoundStatement(n);
    }

    /** Visit a CommitStatement = JeannieC.PrimaryIdentifier. */
    public final void visitCommitStatement(final GNode n) {
      final Type t = (Type) _jeannieAnalyzer.dispatch(n.getGeneric(0));
      assrtOpenArray(n, t);
    }
    
    static class MiniVisitor_liftableDeclaration extends Visitor {
      private boolean _hasCompoundInitializer = false;
      private boolean _hasVariableArray = false;
      public final Boolean visit(final Node n) {
        for (final Object o : n)
          if (o instanceof Node) {
            dispatch((Node)o);
            if (_hasCompoundInitializer && _hasVariableArray)
              return false;
          }
        return true;
      }
      public final Boolean visitInitializerList(final GNode n) {
        _hasCompoundInitializer = true;
        if (_hasVariableArray)
          return false;
        return visit(n);
      }
      public final Boolean visitArrayDeclarator(final GNode n) {
        if (n.getGeneric(2).hasName("VariableLength"))
          _hasVariableArray = true;
        if (_hasCompoundInitializer)
          return false;
        return visit(n);
      }
    }
    
    /** Visit a Declaration = ["__extension__"] DeclarationSpecifiers [InitializedDeclaratorList]. */
    public final void visitDeclaration(final GNode n) {
      super.visitDeclaration(n);
      if (_localsAreLifted) {
        final MiniVisitor_liftableDeclaration v = new MiniVisitor_liftableDeclaration();
        final boolean liftable = ((Boolean)v.dispatch(n)).booleanValue();
        assrt(n, liftable, "compound initializer with variable-sized array");
      }
    }
    
    /** Visit a FunctionCall = (PrimaryIdentifier / JeannieC.PostfixExpression) JeannieC.ExpressionList. */
    public final Type visitFunctionCall(final GNode n) {
      final GNode callee = n.getGeneric(0);
      if (callee.hasName("PrimaryIdentifier") && Analyzer.BUILTINS.contains(callee.getString(0)))
        return JavaAnalyzer.setType(n, _jeannieAnalyzer.processBuiltin(n));
      final Type result = super.visitFunctionCall(n);
      FunctionT function = null;
      {
        final Type t1;
        if (callee.hasName("PrimaryIdentifier"))
          t1 = (Type) table.lookup(callee.getString(0));
        else
          t1 = (Type) callee.getProperty(Constants.TYPE);
        if (null != t1) {
          final Type r1 = Utilities.c().pointerize(t1);
          if (!r1.isError() && r1.isPointer()) {
            final Type f1 = ((PointerT)r1).getType().resolve();
            if (f1.isFunction())
              function = (FunctionT)f1;
          }
        }
      }
      if (null != function) {
        final List<Type> exc = function.getExceptions();
        if (null != exc) {
          final List<File> paths = JavaEntities.classpath(runtime);
          for (final Type tThrown : exc)
            if (JavaEntities.isCheckedException(table, paths, tThrown))
              if (!_jeannieAnalyzer._jAnalyzer.isHandled(tThrown))
                runtime.error("uncaught exception", n);
        }
      }
      return result;
    }

    /** Visit a FunctionDeclarator = (ParameterTypeList / IdentifierList) JavaThrows.
     * This method should never be called; look at visitFunctionDefinition(). */
    public final void visitFunctionDeclarator(final GNode n) {
      assert false && null == n;
    }
  
    /** Visit a FunctionDefinition = ["__extension__"] [DeclarationSpecifiers] Declarator [DeclarationList] CompoundStatement.<br> */
    public final void visitFunctionDefinition(final GNode n) {
      final GNode javaThrows = getDeclaredExceptions(n.getGeneric(2));
      _jeannieAnalyzer.enterJava();
      _jeannieAnalyzer.dispatch(javaThrows);
      _jeannieAnalyzer.enterC();
      assert !_localsAreLifted;
      _localsAreLifted = Utilities.containsCToJavaTransition(n);
      super.visitFunctionDefinition(n);
      _localsAreLifted = false;
      final String functionName = SymbolTable.fromNameSpace(xtc.util.Utilities.unqualify((String) n.getProperty(Constants.SCOPE)));
      final FunctionT function = ((Type) table.current().lookupLocally(functionName)).resolve().toFunction();
      _jeannieAnalyzer.exitC();
      _jeannieAnalyzer.exitJava();
      if (Utilities.containsCToJavaTransition(n)) {
        VariableT jniEnv = null;
        for (final Type param : function.getParameters())
          if ("env".equals(param.toVariable().getName())) {
            jniEnv = param.toVariable();
            break;
          }
        if (assrt(n, null != jniEnv, "C function %s contains Java snippet but lacks explicit formal JNIEnv* env", functionName))
          assrt(n, jniEnv.getType().isPointer() && Utilities.hasTypedefName(jniEnv.getType().toPointer().getType(), "JNIEnv"), "expected formal env to be of type JNIEnv");
      }
      JavaAnalyzer.setType(n, function);
    }

    /** Visit a JavaImports = ImportDeclaration*. */
    public final void visitJavaImports(final GNode n) {
      _jeannieAnalyzer.enterJava();
      _jeannieAnalyzer.dispatch(n.getGeneric(0));
      _jeannieAnalyzer.exitJava();
    }

    /** Visit a JavaInCBlock = JavaInJavaBlock. */
    public final void visitJavaInCBlock(final GNode n) {
      _jeannieAnalyzer.enterJava();
      _jeannieAnalyzer.dispatch(n.getGeneric(0));
      _jeannieAnalyzer.exitJava();
    }
  
    /** Visit a JavaInCExpression = JeannieJava.UnaryExpression. */
    public final Type visitJavaInCExpression(final GNode n) {
      _jeannieAnalyzer.enterJava();
      final Type jType = _jeannieAnalyzer.dispatchRValue(n.getGeneric(0));
      _jeannieAnalyzer.exitJava();
      final Type cType = Utilities.javaTypeToCType(table, runtime, n, jType, true);
      return JavaAnalyzer.setType(n, cType);
    }
  
    /** Visit a JavaInCStatement = TryStatement / SynchronizedStatement / ThrowStatement. */
    public final void visitJavaInCStatement(final GNode n) {
      _jeannieAnalyzer.enterJava();
      _jeannieAnalyzer.dispatch(n.getNode(0));
      _jeannieAnalyzer.exitJava();
    }

    /** Visit a JavaThrows = [ThrowsClause].
     * This method should be called on JeannieJavaAnalyzer, not on JeannieCAnalyzer; look at visitFunctionDefinition(). */
    public final void visitJavaThrows(final GNode n) {
      assert false && null == n;
    }

    /** Visit a JeannieC.PrimaryIdentifier = Identifier. */
    public final Type visitPrimaryIdentifier(final GNode n) {
      final String name = n.getString(0);
      Type result = (Type)table.lookup(name);
      if (null == result) {
        runtime.error("'" + name + "' undeclared", n);
        result = ErrorT.TYPE;
      } else if (Utilities.isJavaEntity(result)) {
        runtime.error("cannot use Java entity '" + name + "' in C context", n);
        result = ErrorT.TYPE;
      }
      mark(n, result);
      return result;
    }

    /** Visit a JeannieC.ReturnStatement = [CommaExpression]. */
    public final Type visitReturnStatement(final GNode n) {
      final Type functionOrMethod = Utilities.currentFunctionOrMethod(table);
      if (!functionOrMethod.isMethod())
        return super.visitReturnStatement(n);
      final Type t1 = (Type) _jeannieAnalyzer.dispatch(n.getNode(0));
      final Type result = functionOrMethod.toMethod().getResult();
      if (result.isVoid()) {
        if (null != t1)
          runtime.error("'return' with a value, in method returning void", n);
      } else {
        if (null == t1) {
          runtime.error("'return' with no value, in method returning non-void", n);
        } else {
          final Type jResult = Utilities.cTypeToJavaType(table, runtime, n, t1);
          assrt(n, JavaTypeConverter.isAssignable(table, JavaEntities.classpath(runtime), result, jResult), "return type mismatch");
        }
      }
      return JavaAnalyzer.setType(n, result);
    }

    /** Visit a TranslationUnit = [JavaImports] ExternalDeclaration* Annotations. */
    public final void visitTranslationUnit(final GNode n) {
      super.visitTranslationUnit(n);
    }

    /** Visit a WithStatement = (JeannieC.Declaration / JeannieC.AssignmentExpression) CInCBlock. */
    public final void visitWithStatement(final GNode n) {
      final boolean oldHasScope = hasScope;
      hasScope = false;
      table.enter(table.freshName("withStatement"));
      table.mark(n);
      final GNode initNode = n.getGeneric(0);
      final GNode cNode, jNode;
      final Type cType, jType;
      if (initNode.hasName("Declaration")) {        
        final GNode initDtorList = initNode.getGeneric(2);
        if (assrt(n, null != initDtorList && 1 == initDtorList.size(), "expected exactly one initializer")) {
          final GNode dtor = initDtorList.getGeneric(0);
          cNode = dtor.getGeneric(1);
          jNode = dtor.getGeneric(4);
          dtor.set(4, null);
          _jeannieAnalyzer.dispatch(initNode);
          dtor.set(4, jNode);
          final String id = CAnalyzer.getDeclaredId(cNode).getString(0);
          cType = (Type) table.current().lookupLocally(id);
          if (assrt(jNode, null != jNode, "initializer expected"))
            jType = (Type) _jeannieAnalyzer.dispatch(jNode);
          else
            jType = ErrorT.TYPE;
        } else {
          cType = jType = ErrorT.TYPE;
          cNode = jNode = null;
        }
      } else {
        assert initNode.hasName("AssignmentExpression");
        cNode = initNode.getGeneric(0);
        jNode = initNode.getGeneric(2);
        final GNode lhsNode = cNode;
        if (assrt(lhsNode, lhsNode.hasName("PrimaryIdentifier"), "primary identifier expected")) {
          final Type t = (Type) _jeannieAnalyzer.dispatch(lhsNode);
          cType = ensureLValue(lhsNode, t) ? t : ErrorT.TYPE;
        } else {
          cType = ErrorT.TYPE;
        }
        assrt(n, "=".equals(initNode.getString(1)), "expected operator '=', not %s", initNode.getString(1));
        jType = (Type) _jeannieAnalyzer.dispatch(jNode);
      }
      mark(initNode, cType);
      _jeannieAnalyzer.assrtCorrectArrayConversion(cNode, cType, jNode, jType);
      final int nOpenArrays = _openArrays.size();
      _openArrays.add(cType);
      _jeannieAnalyzer.dispatch(n.getNode(1));
      assert nOpenArrays + 1 == _openArrays.size();
      _openArrays.remove(nOpenArrays);
      table.exit(n);
      hasScope = oldHasScope;
    }
  }

  private static final class JeannieContext {
    final Visitor _analyzer;
    final Object _savedContext;
    JeannieContext(final Visitor analyzer, final Object savedContext) {
      _analyzer = analyzer;
      _savedContext = savedContext;
    }
  }

  private static final class JeannieJavaAnalyzer extends JavaAnalyzer {
    final Analyzer _jeannieAnalyzer;

    JeannieJavaAnalyzer(final Analyzer jeannieAnalyzer) {
      super(jeannieAnalyzer._runtime, jeannieAnalyzer._table);
      _jeannieAnalyzer = jeannieAnalyzer;
    }

    protected void assrtLegalMethodBody(final GNode n, final Type method) {
      final boolean isAbstract = JavaAnalyzer.hasModifier(method, "abstract");
      assrt(n, isAbstract == (null == n.get(7)), "methods should be abstract iff they have no body");
      if (null != n.get(7)) {
        final boolean isNative = JavaAnalyzer.hasModifier(method, "native");
        assrt(n, isNative == n.getGeneric(7).hasName("CInJavaBlock"), "methods should be native iff their body is in C");
      }
      final Type jniEnv = (Type) _table.root().lookup("JNIEnv");
      if (null == jniEnv) {
        _runtime.error("C typedef for 'JNIEnv' missing; did you forget to #include <jni.h>?", n);
      } else if (null != _table.current().lookupLocally("env")) {
        _runtime.error("formal parameter declaration of 'env' conflicts with implicit JNIEnv pointer");
      } else {
        final Type rval = new PointerT(jniEnv).attribute(Constants.ATT_CONSTANT);
        final VariableT param = VariableT.newParam(rval, "env");
        final DynamicReference ref = new DynamicReference("env", rval);
        final Type lval = Utilities.c().qualify(rval, param).annotate().shape(ref);
        _table.current().define("env", lval);
        lval.scope(_table.current().getQualifiedName());
      }
    }
    
    /** Visit a CDeclarations = ExternalDeclaration*. */
    public final void visitCDeclarations(final GNode n) {
      _jeannieAnalyzer.enterC();
      assert _table.current().isRoot();
      for (int i = 0; i < n.size(); i++)
        _jeannieAnalyzer.dispatch(n.getNode(i));
      _jeannieAnalyzer.exitC();
    }
    
    /** Visit a CInJavaBlock = CInCBlock. */
    public final void visitCInJavaBlock(final GNode n) {
      _jeannieAnalyzer.enterC();
      for (int i = 0; i < n.size(); i++)
        _jeannieAnalyzer.dispatch(n.getNode(i));
      _jeannieAnalyzer.exitC();
    }

    /** Visit a CInJavaExpression = JeannieC.UnaryExpression. */
    public final Type visitCInJavaExpression(final GNode n) {
      _jeannieAnalyzer.enterC();
      final Type cType = (Type)_jeannieAnalyzer.dispatch(n.getNode(0));
      _jeannieAnalyzer.exitC();
      final Type result = Utilities.cTypeToJavaType(_table, _runtime, n, cType);
      return JavaAnalyzer.setType(n, result);
    }

    /** Visit a CompilationUnit = [PackageDeclaration] JavaImports CDeclarations JeannieJava.Declaration*. */
    public final void visitCompilationUnit(final GNode n) {
      if (null == n.get(0))
        visitPackageDeclaration(null);
      else
        dispatch(n.getNode(0));
      _table.enter(JavaEntities.fileNameToScopeName(n.getLocation().file));
      _table.mark(n);
      for (final Object o : n.getGeneric(1))
        _externalAnalyzer.dispatch((Node)o);
      for (int i=3; i<n.size(); i++)
        _externalAnalyzer.dispatch(n.getNode(i));
      dispatch(n.getNode(1)); //in package:file scope, for normal Java code ...
      final String fileScope = JavaEntities.enterScopeByQualifiedName(_table, "");
      dispatch(n.getNode(1)); //... ALSO in top-level scope, for Java in top-level C code
      dispatch(n.getNode(2));
      JavaEntities.enterScopeByQualifiedName(_table, fileScope);
      for (int i = 3; i < n.size(); i++)
        dispatch(n.getNode(i));
      _table.setScope(_table.root());
    }

    /** Visit a JavaImports = ImportDeclaration*. */
    public final List<Type> visitJavaImports(final GNode n) {
      final List<Type> types = new ArrayList<Type>(n.size());
      for (final Object o : n)
        types.add((Type)dispatch((Node)o));
      return types;
    }
    
    /** Visit a JavaInJavaBlock = JeannieJava.DeclarationOrStatement*. */
    public final Type visitJavaInJavaBlock(final GNode n) {
      return super.visitBlock(n);
    }

    /** Visit a JavaThrows = [ThrowsClause]. */
    public final List<Type> visitJavaThrows(final GNode n) {
      if (null == n || null == n.get(0))
        _context._handledExceptions = new ArrayList<Type>();
      else
        _context._handledExceptions = JavaEntities.typeList((List)_externalAnalyzer.dispatch(n.getNode(0)));
      assrtLegalHandledExceptions(n.getGeneric(0));
      return _context._handledExceptions;
    }

    /** Visit a MethodDeclaration = Modifiers null Type Identifier FormalParameters [Dimensions] [ThrowsClause] [Block]. */
    public final Type visitMethodDeclaration(final GNode n) {
      assert !_jeannieAnalyzer._cAnalyzer._localsAreLifted;
      _jeannieAnalyzer._cAnalyzer._localsAreLifted = Utilities.containsJavaToCTransition(n);
      final Type result = super.visitMethodDeclaration(n);
      _jeannieAnalyzer._cAnalyzer._localsAreLifted = false;
      return result;
    }
      
    /** Visit a JeannieJava.PrimaryIdentifier = Identifier. */
    public final Type visitPrimaryIdentifier(final GNode n) {
      final String name = n.getString(0);
      final Type result = (Type)_table.lookup(name);
      if (null != result && !result.hasError() && !Utilities.isJavaEntity(result)) {
        _runtime.error("cannot use C entity '" + name + "' in Java context", n);
        return JavaAnalyzer.setType(n, ErrorT.TYPE);
      }
      return super.visitPrimaryIdentifier(n);
    }

    /**
     * Visit a ReturnStatement = [Expression] (gosling_et_al_2000 <a
     * href="http://java.sun.com/docs/books/jls/second_edition/html/statements.doc.html#6767">&sect;14.16</a>).
     */
    public final void visitReturnStatement(final GNode n) {
      final Type function = Utilities.currentFunctionOrMethod(_table);
      if (function.isMethod()) {
        super.visitReturnStatement(n);
        return;
      }
      Type t1 = null;
      if (null != n.get(0)) {
        final Type jType = _jeannieAnalyzer.dispatchRValue(n.getGeneric(0));
        t1 = Utilities.javaTypeToCType(_table, _runtime, n, jType, false);
      }
      final Type result = Utilities.returnType(function);
      if (result.resolve().isVoid()) {
        if (null != t1)
          _runtime.error("'return' with a value, in function returning void", n);
      } else {
        if (null != t1)
          _jeannieAnalyzer._cAnalyzer.processAssignment(false, "return", n, result, t1);
        else
          _runtime.error("'return' with no value, in function returning non-void", n);
      }
    }
  }
  
  static final Set<String> BUILTINS = Collections.unmodifiableSet(new HashSet<String>(Arrays.asList(new String[] {
    "_copyFromJava", "_copyToJava", "_newJavaString", "_stringUTFLength" })));
  final JeannieCAnalyzer _cAnalyzer;
  final JeannieJavaAnalyzer _jAnalyzer;
  final Runtime _runtime;
  private final Stack<JeannieContext> _stack;
  public final SymbolTable _table;
  
  public Analyzer(final Runtime runtime, final SymbolTable table, final String language) {
    _stack = new Stack<JeannieContext>();
    _table = table;
    _runtime = runtime;
    _cAnalyzer = new JeannieCAnalyzer(this);
    _jAnalyzer = new JeannieJavaAnalyzer(this);
    if ("C".equals(language))
      enterC();
    if ("Java".equals(language))
      enterJava();
  }

  private Visitor activeAnalyzer() {
    return _stack.isEmpty() ? null : _stack.peek()._analyzer;
  }
  
  final Type dispatchRValue(final GNode n) {
    final JeannieJavaAnalyzer a = (JeannieJavaAnalyzer) activeAnalyzer();
    return a.dispatchRValue(n);
  }
  
  final void enterC() {
    assert _cAnalyzer != activeAnalyzer();
    _stack.push(new JeannieContext(_cAnalyzer, _cAnalyzer.contextSave()));
    _cAnalyzer.setHasScope(_jAnalyzer._context._hasScope);
    _cAnalyzer.setIsTopLevel(JavaEntities.isScopeTopLevel(_table.current().getQualifiedName()));
    if (_jAnalyzer._context._loop)
      _cAnalyzer.getLoops().add(Boolean.TRUE);
    if (_jAnalyzer._context._switch)
      _cAnalyzer.getSwitches().add(Boolean.TRUE);
  }
  
  final void enterJava() {
    assert _jAnalyzer != activeAnalyzer();
    _stack.push(new JeannieContext(_jAnalyzer, _jAnalyzer._context.save()));
    _jAnalyzer._context._hasScope = _cAnalyzer.getHasScope();
    _jAnalyzer._context._loop = !_cAnalyzer.getLoops().isEmpty();
    _jAnalyzer._context._switch = !_cAnalyzer.getSwitches().isEmpty();
  }
  
  final void exitC() {
    assert _cAnalyzer == activeAnalyzer();
    _cAnalyzer.contextRestore(savedContextC());
    _stack.pop();
  }
  
  final void exitJava() {
    assert _jAnalyzer == activeAnalyzer();
    _jAnalyzer._context.restore(savedContextJ());
    _stack.pop();
  }
  
  private Type processBuiltin(final GNode n) {
    final String name = n.getGeneric(0).getString(0);
    final GNode argsNode = n.getGeneric(1);
    @SuppressWarnings("unchecked")
    final List<Type> argTypes = (List<Type>) dispatch(argsNode);
    for (final Type t : argTypes)
      if (t.isError())
        return JavaAnalyzer.setType(n, ErrorT.TYPE);
    if ("_copyFromJava".equals(name)) {
      if (!_cAnalyzer.assrt(n, 5 == argsNode.size(), "invalid call to builtin function: `int _copyFromJava(cArray, cArrayStart, javaArray, javaArrayStart, length)"))
        return ErrorT.TYPE;
      _cAnalyzer.ensureInteger(argsNode.getNode(1), argTypes.get(1));
      _cAnalyzer.ensureInteger(argsNode.getNode(3), argTypes.get(3));
      _cAnalyzer.ensureInteger(argsNode.getNode(4), argTypes.get(4));
      assrtCorrectArrayConversion(argsNode.getGeneric(0), argTypes.get(0), argsNode.getGeneric(2), argTypes.get(2));
      return Utilities.javaTypeToCType(_table, _runtime, n, JavaEntities.nameToBaseType("int"), false);
    } else if ("_copyToJava".equals(name)) {
      if (!_cAnalyzer.assrt(n, 5 == argTypes.size(), "invalid call to builtin function: `int _copyToJava(javaArray, javaArrayStart, cArray, cArrayStart, length)"))
        return ErrorT.TYPE;
      _cAnalyzer.ensureInteger(argsNode.getNode(1), argTypes.get(1));
      _cAnalyzer.ensureInteger(argsNode.getNode(3), argTypes.get(3));
      _cAnalyzer.ensureInteger(argsNode.getNode(4), argTypes.get(4));
      if (!_cAnalyzer.assrt(argsNode.getGeneric(0), !Utilities.hasTypedefName(argTypes.get(0), "jstring"), "_copyToJava target must not be String"))
        return ErrorT.TYPE;
      assrtCorrectArrayConversion(argsNode.getGeneric(2), argTypes.get(2), argsNode.getGeneric(0), argTypes.get(0));
      return Utilities.javaTypeToCType(_table, _runtime, n, JavaEntities.nameToBaseType("int"), false);
    } else if ("_newJavaString".equals(name)) {
      if (!_cAnalyzer.assrt(argsNode, 1 == argsNode.size(), "invalid call to builtin function: `String _newJavaString(cArray)"))
        return JavaAnalyzer.setType(n, ErrorT.TYPE);
      final Type t = argTypes.get(0);
      final boolean typeOk = Utilities.isPtrChar(t) || Utilities.isPtrTypedef(t, "`char") || Utilities.isPtrTypedef(t, "jbyte");
      if (!_cAnalyzer.assrt(argsNode.getGeneric(0), typeOk, "expected pointer to char, `byte, or `char"))
        return JavaAnalyzer.setType(n, ErrorT.TYPE);
      return Utilities.pureCType(_table, _runtime, JavaEntities.tString(_table));
    } else if ("_stringUTFLength".equals(name)) {
      if (!_cAnalyzer.assrt(argsNode, 1 == argsNode.size() || 3 == argsNode.size(), "invalid call to builtin function: `int _stringUTFLength(jstring [, jStart, jLen])"))
        return JavaAnalyzer.setType(n, ErrorT.TYPE);
      final Type t = Utilities.pureCType(_table, _runtime, argTypes.get(0));
      if (!_cAnalyzer.assrt(argsNode.getGeneric(0), Utilities.hasTypedefName(t, "jstring"), "expected `String"))
        return JavaAnalyzer.setType(n, ErrorT.TYPE);
      if (3 == argsNode.size()) {
        _cAnalyzer.ensureInteger(argsNode.getNode(1), argTypes.get(1));
        _cAnalyzer.ensureInteger(argsNode.getNode(2), argTypes.get(2));
      }
      return Utilities.javaTypeToCType(_table, _runtime, n, JavaEntities.nameToBaseType("int"), false);
    } else {
      throw new Error("builtin " + name + " not yet implemented");
    }
  }
  
  private JeannieCAnalyzer.JeannieCContext savedContextC() {
    return (JeannieCAnalyzer.JeannieCContext)_stack.peek()._savedContext;
  }

  private JavaAnalyzer.JavaContext savedContextJ() {
    return (JavaAnalyzer.JavaContext)_stack.peek()._savedContext;
  }

  public final Object visit(final Node n) {
    return activeAnalyzer().dispatch(n);
  }

  private void assrtCorrectArrayConversion(final GNode cNode, final Type cType, final GNode jNode, final Type cjType) {
    if (cType.isError() || cjType.isError())
      return;
    final Type cResolved = Utilities.c().pointerize(cType);
    if (!_cAnalyzer.assrt(cNode, cResolved.isPointer(), "pointer or array type expected"))
      return;
    final Type cElem = ((PointerT)cResolved).getType();
    assert !cElem.isError();
    final Type jType = Utilities.cTypeToJavaType(_table, _runtime, jNode, cjType);
    assert !jType.isError() && JavaEntities.isGeneralRValueT(jType);
    if (jType.isArray()) {
      final Type jElem = JavaEntities.resolveToRawRValue(JavaEntities.arrayElementType(jType.toArray()));
      if (JavaEntities.isPrimitiveT(jElem)) {
        final String expectedName = "j" + JavaEntities.baseTypeToName(jElem);
        _cAnalyzer.assrt(cNode, Utilities.hasTypedefName(cElem, expectedName), "type '%s*' expected", expectedName);
      } else {
        final Type jcElem = Utilities.cTypeToJavaType(_table, _runtime, cNode, cElem);
        final boolean ok = JavaTypeConverter.isAssignable(_table, JavaEntities.classpath(_runtime), jcElem, jElem);
        _cAnalyzer.assrt(cNode, ok, "type 'jobject*' expected");
      }
    } else if (JavaTypeConverter.isIdentical(jType, JavaEntities.tString(_table))) {
      final boolean isChar = Utilities.hasTypedefName(cElem, "jchar");
      _cAnalyzer.assrt(cNode, isChar || Utilities.hasTypedefName(cElem, "jbyte"), "type 'jchar*' or 'jbyte*' expected");
    } else {
      _cAnalyzer.assrt(jNode, false, "string or primitive array expected");
    }
  }

  /** Visit a CompilationUnit = CDeclarations [PackageDeclaration] ImportDeclaration* JeannieJava.Declaration*. */
  public final void visitCompilationUnit(final GNode n) {
    assert null == activeAnalyzer();
    enterJava();
    activeAnalyzer().dispatch(n);
    exitJava();
  }

  /** Visit a TranslationUnit = [JavaImports] ExternalDeclaration* Annotations. */
  public final void visitTranslationUnit(final GNode n) {
    assert null == activeAnalyzer();
    enterC();
    activeAnalyzer().dispatch(n);
    exitC();
  }
  
  //TD 41 jeannie.Analyzer should disallow break, continue, and goto from crossing language boundary or _with boundary
}
