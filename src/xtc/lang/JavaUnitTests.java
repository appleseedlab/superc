/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2005-2007 IBM Corp.
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

import java.io.CharArrayWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStream;
import java.io.StringReader;
import java.io.StringWriter;
import java.io.Writer;
import java.lang.reflect.Method;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import xtc.Constants;
import xtc.parser.ParseException;
import xtc.parser.Result;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.type.AliasT;
import xtc.type.AnnotatedT;
import xtc.type.ClassT;
import xtc.type.InterfaceT;
import xtc.type.PackageT;
import xtc.type.Type;
import xtc.util.Runtime;
import xtc.util.SymbolTable;

/**
 * JUnit tests for Java-related classes in package xtc.lang.
 * 
 * This class is a good place to quickly try a method on some simple
 * inputs. The test cases also document how to use certain API and
 * what it does.
 * 
 * To run from the console, set your CLASSPATH to include
 * $JAVA_DEV_ROOT/classes and junit.jar, then run
 * 
 *   java -ea junit.textui.TestRunner xtc.lang.JavaUnitTests
 *
 * Or, to run from within eclipse, Run -> Run ... -> JUnit -> New, and
 * specify xtc.lang.JavaUnitTests.
 * 
 * @author Martin Hirzel
 * @version $Revision: 1.38 $
 */
public final class JavaUnitTests extends TestCase {
  public static abstract class IgnorableTest extends TestCase {
    private final boolean _ignore;
    private final StackTraceElement _location;
    public IgnorableTest(final boolean ignore) {
      _ignore = ignore;
      _location = ignore ? null : new Throwable().getStackTrace()[2];
    }
    public final void runTest() throws Throwable {
      if (_ignore && IGNORE_MEANS_SKIP)
        return;
      try {
        runTestIgnorable();
      } catch (final Throwable t) {
        if (_ignore)
          return;
        final StackTraceElement[] oldTrace = t.getStackTrace();
        final StackTraceElement[] newTrace = new StackTraceElement[1 + oldTrace.length];
        newTrace[0] = _location;
        System.arraycopy(oldTrace, 0, newTrace, 1, oldTrace.length);
        t.setStackTrace(newTrace);
        throw t;
      }
    }
    public abstract void runTestIgnorable() throws Throwable;
  }
  
  static class JavaAnalyzerTestConstant extends IgnorableTest {
    private final Object _expected;
    private final String _input;
    JavaAnalyzerTestConstant(final boolean ignore, final String input, final Object expected) {
      super(ignore);
      _expected = expected;
      _input = input;
    }
    public void runTestIgnorable() throws Throwable {
      final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), new SymbolTable());
      enterPackageFile(ana._table, "", "<input>");
      javaAnalyzerTestConstant(_input, _expected, ana);
    }
  }
  
  static class JavaAnalyzerTestError extends IgnorableTest {
    private final String _expected;
    private final String _input;
    private final String _production;
    private final List<TempFile> _tempFiles; 
    JavaAnalyzerTestError(final boolean ignore, final String production, final String input, final String expected) {
//      this(ignore, production, input, expected, new ArrayList<TempFile>());
      super(ignore);
      _production = production;
      _input = input;
      _expected = expected;
      _tempFiles = new ArrayList<TempFile>();
    }
    JavaAnalyzerTestError(final boolean ignore, final String production, final String input, final String expected, final List<TempFile> tempFiles) {
      super(ignore);
      _production = production;
      _input = input;
      _expected = expected;
      _tempFiles = tempFiles;
    }
    public void runTestIgnorable() throws Throwable {
      try {
        TempFile.create(_tempFiles, JavaEntities.TEMP_DIR);
        javaAnalyzerTestError(_production, _input, _expected);
      } finally {
        TempFile.delete(_tempFiles, JavaEntities.TEMP_DIR);
      }
    }
  }

  static class JavaExternalAnalyzerTest extends IgnorableTest {
    private final String _expected;
    private final String _input;
    private final String _production;
    private final boolean _withType;
    JavaExternalAnalyzerTest(final boolean ignore, final String production, final boolean withType, final String input, final String expected) {
      super(ignore);
      _expected = expected;
      _input = input;
      _production = production;
      _withType = withType;
    }
    JavaExternalAnalyzerTest(final boolean ignore, final String production, final String input) {
      this(ignore, production, false, input, input);
    }
    public void runTestIgnorable() throws Throwable {
      final JavaExternalAnalyzer ana = newJavaExternalAnalyzer();
      enterPackageFile(ana._table, "", "<input>");
      if (_withType) {
        final ClassT t = new ClassT("Z", JavaEntities.tObjectAlias(ana._table),
            new ArrayList<Type>(), new ArrayList<Type>(), new ArrayList<Type>());
        ana._table.current().define("tag(Z)", t);
        ana._table.enter("Z");
      }
      final GNode ast = JavaEntities.javaStringToAst(_production, _input, true);
      final Object dispatched = ana.dispatch(ast);
      final String result = JavaEntities.typeDeclString(ana._table, dispatched);
      assertEquals(contractSpace(_expected), contractSpace(result));      
    }
  }
  
  static class JavaParserTest extends IgnorableTest {
    private final String _expected;
    private final String _input;
    private final String _production;
    JavaParserTest(final boolean ignore, final String production, final String input) {
      super(ignore);
      _expected = _input = input;
      _production = production;
    }
    JavaParserTest(final boolean ignore, final String production, final String input, final String expected) {
      super(ignore);
      _expected = expected;
      _input = input;
      _production = production;
    }
    public void runTestIgnorable() throws Exception {
      javaParserTestRoundTrip(_production, _input, _expected, false);
      javaParserTestRoundTrip(_production, _input, _expected, true);
    }
  }
  
  static class TempFile {
    static List<TempFile> cons(final String contents1, final String path1, final List<TempFile> list) {
      assertFalse(path1.contains("."));
      final List<TempFile> result = null == list ? new ArrayList<TempFile>() : list;
      result.add(new TempFile(contents1, path1 + ".java"));
      return result;
    }
    static List<TempFile> cons(final String contents1, final String path11, final String path12, final List<TempFile> list) {
      return cons(contents1, path11 + File.separator + path12, list);
    }
    static List<TempFile> cons(final String contents1, final String path11, final String path12, final String path13, final List<TempFile> list) {
      return cons(contents1, path11 + File.separator + path12 + File.separator + path13, list);
    }
    static void create(final List<TempFile> tempFiles, final File tempDir)
        throws IOException {
      for (final TempFile tf : tempFiles)
        createTempFile(tempDir, tf._path, tf._contents);
    }
    static void delete(final List<TempFile> tempFiles, final File tempDir) {
      for (final TempFile tf : tempFiles)
        new File(tempDir, tf._path).delete();
    }
    private final String _contents;
    private final String _path;
    TempFile(final String contents, final String path) {
      _contents = contents;
      _path = path;
    }
  }
  
  public static class WriterOutputStream extends OutputStream {
    final Writer _writer;

    public WriterOutputStream(final Writer writer) {
      _writer = writer;
    }

    public final void write(final int b) throws IOException {
      _writer.write(b);
    }
  }
  
  public static final boolean IGNORE_MEANS_SKIP = true;
  
  public static String cAstToString(final Node ast) {
    final CharArrayWriter writer = new CharArrayWriter();
    final CPrinter printer = new CPrinter(new Printer(writer));
    printer.dispatch(ast);
    return writer.toString();
  }

  public static String contractSpace(final String string) {
    final StringBuffer result = new StringBuffer();
    char prevChar = '-';
    boolean sawSpace = false;
    for (int i = 0, n = string.length(); i < n; i++) {
      final char currChar = string.charAt(i);
      if (Character.isWhitespace(currChar)) {
        sawSpace = true;
      } else {
        if (sawSpace) {
          if (Character.isJavaIdentifierPart(prevChar)
              && Character.isJavaIdentifierPart(currChar))
            result.append(' ');
          sawSpace = false;
        }
        result.append(currChar);
        prevChar = currChar;
      }
    }
    return result.toString();
  }

  private static void cParserRoundTrip(final String production,
      final String string) throws Exception {
    final GNode ast = cStringToAst(production, string, null);
    final String result = cAstToString(ast);
    assertEquals(contractSpace(string), contractSpace(result));
  }

  static File createTempFile(
      final File tempDir, final String path, final String contents)
      throws IOException {
    final File result = new File(tempDir, path);
    result.getParentFile().mkdirs();
    if (result.exists())
      result.delete();
    assertTrue(result.createNewFile());
    final Writer writer = new FileWriter(result);
    writer.write(contents);
    writer.flush();
    writer.close();
    return result;
  }

  public static GNode cStringToAst(final String production, final String string, final Set<String> typedefs)
      throws Exception {
    final Class[] paramTypes = { Integer.TYPE };
    final Method method = CParser.class.getDeclaredMethod( //
        "p" + production, paramTypes);
    method.setAccessible(true);
    final CParser parser = new CParser(new StringReader(string), "<input>", string.length());
    parser.yyState.start();
    if (null != typedefs) {
      parser.yyState.start();
      for (final String type : typedefs)
        parser.yyState.bind(type, true);
      parser.yyState.commit();
    }
    final Object[] paramValues = { new Integer(0) };
    final Result parseResult = (Result) method.invoke(parser, paramValues);
    return (GNode) parser.value(parseResult);
  }
  
  public static void dumpSymbolTable(final SymbolTable table) {
    final Printer p = new Printer(System.out);
    table.root().dump(p);
    p.flush();
  }

  public static void enterPackageFile(final SymbolTable table,
      final String packageName, final String fileName) {
    JavaEntities.canonicalNameToPackage(table, packageName);
    table.enter(JavaEntities.packageNameToScopeName(packageName));
    table.enter(JavaEntities.fileNameToScopeName(fileName));
  }

  static void javaAnalyzerTestConstant(final String expression,
      final Object expected, final JavaAnalyzer ana) throws Exception {
    final GNode ast = JavaEntities.javaStringToAst("Expression", expression, true);
    final Type type = ana.dispatchRValue(ast);
    assertEquals(expected, type.getConstant().getValue());
  }

  static void javaAnalyzerTestError(final String production,
      final String input, final String expected) throws Exception {
    final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), new SymbolTable());
    if (!"CompilationUnit".equals(production))
      enterPackageFile(ana._table, "", "<input>");
    javaAnalyzerTestError(production, input, expected, ana);
  }

  private static void javaAnalyzerTestError(final String production,
      final String input, final String expected, final JavaAnalyzer ana)
      throws Exception {
    final StringWriter stringWriter = new StringWriter();
    ana._runtime.setErrConsole(new Printer(stringWriter));
    GNode ast = null;
    try {
      ast = JavaEntities.javaStringToAst(production, input, true);
    } catch (final ParseException e) {
      ana._runtime.errConsole().pln(e.toString());
    }
    if (null != ast)
      ana.dispatch(ast);
    String output = stringWriter.toString();
    output = stripPrefix(output, "error:");
    output = stripPrefix(output, "Exception:");
    output = stripSuffix(output, "\n");
    output = output.trim();
    assertEquals(expected, output);
  }

  private static void javaAnalyzerTestUseDef(final JavaAnalyzer ana,
      final String use, final String def) throws Exception {
    final Type u, d;
    {
      final GNode ast = JavaEntities.javaStringToAst("Expression", use, true);
      ana.dispatch(ast);
      if (ast.hasName("CallExpression")) {
        u = (Type)ast.getGeneric(3).getProperty(Constants.TYPE);
      } else {
        final Type cu = (Type)ast.getProperty(Constants.TYPE);
        u = JavaEntities.isConstantT(cu) ? ((AnnotatedT)cu).getType() : cu;
      }
    }
    // must parse use before def, since def gets analyzed on demand
    {
      final int bracket = def.indexOf('[');
      final String baseName = -1 == bracket ? def : def.substring(0, bracket);
      final int nDimensions = -1 == bracket ? 0 : (def.length() - bracket) / 2;
      final Type baseType = (Type) ana._table.lookup(baseName);
      if (null != baseType)
        d = JavaEntities.typeWithDimensions(baseType, nDimensions);
      else
        d = null;
    }
//    System.out.println("def(" + def + ")=d(" + d + "),use(" + use + ")=u(" + u + ")");
    if (null == d) {
      System.out.println("can't find \"" + def + "\" in ");
      dumpSymbolTable(ana._table);
      System.out.println("u(" + JavaEntities.typeDeclString(ana._table, u)
          + ")");
    }
    assertNotNull(d);
    assertEquals(d, u);
  }
  
  static void javaParserTestRoundTrip( // 
      final String production, final String input, final String expected, final boolean simple //
  ) throws Exception {
    final String unescaped = JavaEntities.unicodeUnescape(input);
    final GNode ast = JavaEntities.javaStringToAst(production, unescaped, simple);
    final String result = JavaEntities.javaAstToString(ast);
    assertEquals(contractSpace(JavaEntities.unicodeUnescape(expected)), contractSpace(result));
  }

  private static TestSuite makeSuiteJavaAnalyzerConstant() {
    //final boolean ignore = true; //T D 38 failing unit tests
    final TestSuite s = new TestSuite();
//  s.addTest(new JavaAnalyzerTestConstant(false, "", ));
    s.addTest(new JavaAnalyzerTestConstant(false, "!true", BigInteger.ZERO));
    s.addTest(new JavaAnalyzerTestConstant(false, "'\\100'", new Character('@')));
    s.addTest(new JavaAnalyzerTestConstant(false, "'\\n'", new Character('\n')));
    s.addTest(new JavaAnalyzerTestConstant(false, "'\\u0040'", new Character('@')));
    s.addTest(new JavaAnalyzerTestConstant(false, "'a'!='b'", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "'a'=='b'", BigInteger.ZERO));
    s.addTest(new JavaAnalyzerTestConstant(false, "'a'==97L", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "'b'", new Character('b')));
    s.addTest(new JavaAnalyzerTestConstant(false, "(String)\"abc\"", "abc"));
    s.addTest(new JavaAnalyzerTestConstant(false, "(boolean)true", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "(byte)'Y'", new Byte((byte)'Y')));
    s.addTest(new JavaAnalyzerTestConstant(false, "(byte)72==72.0", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "(double)'\u789a'", new Double(30874.0)));
    s.addTest(new JavaAnalyzerTestConstant(false, "(float)12", new Float(12)));
    s.addTest(new JavaAnalyzerTestConstant(false, "(int)'\\u789a'", new Integer(0x789a)));
    s.addTest(new JavaAnalyzerTestConstant(false, "(int)'\\uffff'", new Integer(0xffff)));
    s.addTest(new JavaAnalyzerTestConstant(false, "(long)12.34e5", new Long((long)12.34e5)));
    s.addTest(new JavaAnalyzerTestConstant(false, "+12.34e5", new Double(12.34e5)));
    s.addTest(new JavaAnalyzerTestConstant(false, "-12345", new Integer(-12345)));
    s.addTest(new JavaAnalyzerTestConstant(false, ".12", new Double(.12)));
    s.addTest(new JavaAnalyzerTestConstant(false, "0123", new Integer(0123)));
    s.addTest(new JavaAnalyzerTestConstant(false, "0==1?'T':'F'", new Character('F')));
    s.addTest(new JavaAnalyzerTestConstant(false, "0l", new Long(0)));
    s.addTest(new JavaAnalyzerTestConstant(false, "0x00f & 0x0ff", new Integer(0x00f)));
    s.addTest(new JavaAnalyzerTestConstant(false, "0x00f ^ 0x0ff", new Integer(0x0f0)));
    s.addTest(new JavaAnalyzerTestConstant(false, "0x00f | 0x0ff", new Integer(0x0ff)));
    s.addTest(new JavaAnalyzerTestConstant(false, "0x0123456789abcdefL", new Long(0x0123456789abcdefL)));
    s.addTest(new JavaAnalyzerTestConstant(false, "0xCafeBabe", new Integer(0xCafeBabe)));
    s.addTest(new JavaAnalyzerTestConstant(false, "0xff==255", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "1+2+\" fiddlers\"", "3 fiddlers"));
    s.addTest(new JavaAnalyzerTestConstant(false, "1-2", new Integer(-1)));
    s.addTest(new JavaAnalyzerTestConstant(false, "1-2-3", new Integer(-4)));
    s.addTest(new JavaAnalyzerTestConstant(false, "1.2/2", new Double(0.6)));
    s.addTest(new JavaAnalyzerTestConstant(false, "12 + 34", new Integer(46)));
    s.addTest(new JavaAnalyzerTestConstant(false, "12 + \"cd\"", "12cd"));
    s.addTest(new JavaAnalyzerTestConstant(false, "12*3", new Integer(36)));
    s.addTest(new JavaAnalyzerTestConstant(false, "123", new Integer(123)));
    s.addTest(new JavaAnalyzerTestConstant(false, "2<2", BigInteger.ZERO));
    s.addTest(new JavaAnalyzerTestConstant(false, "2<<4", new Integer(32)));
    s.addTest(new JavaAnalyzerTestConstant(false, "2<<4L", new Integer(32)));
    s.addTest(new JavaAnalyzerTestConstant(false, "2<=2", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "2==2.0", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "2L<'2'", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "2L<<4", new Long(32)));
    s.addTest(new JavaAnalyzerTestConstant(false, "6.022137e+23D", new Double(6.022137e+23D)));
    s.addTest(new JavaAnalyzerTestConstant(false, "6.022137e+23f", new Float(6.022137e+23f)));
    s.addTest(new JavaAnalyzerTestConstant(false, "97L-'a'", new Long(0)));
    s.addTest(new JavaAnalyzerTestConstant(false, "\"\\40\\100\"", "\40\100"));
    s.addTest(new JavaAnalyzerTestConstant(false, "\"a\\\"b\\nc\"", "a\"b\nc"));
    s.addTest(new JavaAnalyzerTestConstant(false, "\"ab\"==\"ab\"", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "\"ab\" + \"cd\"", "abcd"));
    s.addTest(new JavaAnalyzerTestConstant(false, "\"fiddlers \"+1+2", "fiddlers 12"));
    s.addTest(new JavaAnalyzerTestConstant(false, "\"hello\"", "hello"));
    s.addTest(new JavaAnalyzerTestConstant(false, "false", BigInteger.ZERO));
    s.addTest(new JavaAnalyzerTestConstant(false, "false|true", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "true && false", BigInteger.ZERO));
    s.addTest(new JavaAnalyzerTestConstant(false, "true ^ false", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "true || false", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "true", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "true&true", BigInteger.ONE));
    s.addTest(new JavaAnalyzerTestConstant(false, "true?'T':'F'", new Character('T')));
    s.addTest(new JavaAnalyzerTestConstant(false, "true^false", BigInteger.ONE));
    return s;
  }

  private static TestSuite makeSuiteJavaAnalyzerError() {
    final boolean ignore = true;
    final TestSuite s = new TestSuite();
//  s.addTest(new JavaAnalyzerTestError(false, "", "", ""));
    // ---------------------------------------------------------------
    //TD 18 (15.9) anonymous classes
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "final class B extends p.A implements p.A.B{void f(){new B(){};}}", "", TempFile.cons("package p;public class A{public interface B{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "import p2.B;class C extends p1.A{void f(){new B(){};}}", "", TempFile.cons("package p1;public class A{public interface B{}}", "p1", "A", TempFile.cons("package p2;public final class B{}", "p2", "B", null))));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{static class B{interface C{}}void f(){class C{}new B(){class D implements C{}};}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{static void f(){class B{B(Object o){}void g(){Class c=Boolean.class;}}new B(new Object(){Class c=Byte.class;});}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{static void f(){class B{static final int i=1;}new Object(){class B{static final int i=2;}void g(int j){switch(j){case 0:case 1:case B.i:}}};}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{Object f(){abstract class D{}return new D(){};}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{static Object f(){abstract class D{}return new D(){};}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Expression", "new Cloneable(){}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Statement", "test: new Object(){void f(){int i;test:i=1;}};", ""));
    // ---------------------------------------------------------------
    //TD 08 (8.8.5.1) explicit constructor invocations
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{int _a;A(int a){this._a=a;}}class B extends A{int _b;B(int a){this(a,0);}B(int a,int b){super(a);_b=b;}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class C{C(String s){}private C(Integer i){}}class D extends C{D(){super(null);}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{C(int i){}}class D extends C{D(int i){super(i);}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{}class D extends C{D(){super();}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class C{static class D{class E{}}static class F extends D.E{F(){(new D()).super();}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{A a=new A();static class A{private A(){}A(String s){}A(int i){this(null);}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int _i;C(int i){_i=i;}C(){this(0);}}", ""));
    // ---------------------------------------------------------------
    //TD 10 (14.20) unreachable statements
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{void f(){return; int i;}}", "unreachable code"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{void f(){{return;};}}", "unreachable code"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Statement", "for(;false;);", "unreachable code"));
    // ---------------------------------------------------------------
    //TD enclosing instances
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{class B{}} class C{ A.B b=new A().new B();}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{class B{private B(){}}static class C extends B{}}", "no enclosing instance"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{class B{private B(){}}static{class C extends B{}}}", "no enclosing instance"));
    // ---------------------------------------------------------------
    //TD qualified this and super
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class C{int i;}class D extends C{Object o=int.super.i;}", "super doesn't work on primitive types"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class C{int i;}class D extends C{Object o=int[].super.i;}", "super doesn't work on array types"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class C{int i;}class D extends C{Object o=null.super.i;}", "super doesn't work on null"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{public static int v=0;class I{I(int i){}}static class D extends I{D(A a, int i){a.super(v=++i);}}public static void main(String[]args){try{new D(null,5);}catch(NullPointerException e){if(v==0)System.out.print(\"OK\");else System.out.print(\"bad\");return;}System.out.print(\"bad\");}}", ""));
    // ---------------------------------------------------------------
    //TD static use of non-static
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{int i;static class B extends A{private int i;}static class C extends B{int j=i;}}", "static reference to non-static field"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{private int f(){return 1;}static class B extends A{int i=f();}}", "static use of non-static method"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int i=1; static class D{int j=i;}}", "static use of non-static field"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{private int i;static class D extends C{int j=i;}}", "static reference to non-static field"));
    // ---------------------------------------------------------------
    //TD use-def analysis
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{final int i;}", "uninitialized blank final"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{static final int i;}", "uninitialized blank final"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{final int x; class D{{x=1;}}}", "a blank final field of a lexically enclosing class can not be assigned"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{final int x; {x=1;}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int f(){}}", "missing return"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int i=(i=1)+i;}", "use before def"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int i=i;}", "use of uninitialized variable"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int i=j;int j=1;}", "use before def"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int j=i=1;final int i;}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{static{int i=j;}static int j=1;}", "use before def"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "interface A{int i;}", "uninitialized field"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class B{final static int i;static{i=1;}}", "", TempFile.cons("interface A{int i=B.i;}", "A", null)));
    // ---------------------------------------------------------------
    //TD visibility and scopes
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{int b=C.d.length;}class C{static D[]d;private static class D{}}", "unknown or ambiguous name"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class B extends p.A implements p.A.B{void f(){new B();}}", "the inherited type shadows the current enclosing type", TempFile.cons("package p;public class A{public interface B{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class B extends p.A{Object i;int j=((p.A)this).i;}", "unknown or ambiguous name", TempFile.cons("package p;public class A{protected int i;}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class BB extends p.AA{interface B{void m()throws E2;}static abstract class C extends A implements B{}static abstract class D extends C{{m();try{((C)this).m();}catch(E2 e){}}}}", "", TempFile.cons("package p;public class AA{public static class E1 extends Exception{}public static class E2 extends Exception{}public static abstract class A{protected abstract void m()throws E1;}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class B{int j=p.A.i++;}", "not accessible", TempFile.cons("package p;public class A{protected static int i;}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class C{private C(){}}class D extends C{}", "super constructor not visible"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface B{int i=2;}class C extends p1.A implements B{}class D extends C{static int j=new D().i;}", "ambiguous name i", TempFile.cons("package p1;public class A{protected int i=1;}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface B{void m(String s,Object o);}abstract class C extends p.A implements B{}abstract class D extends C{void f(){super.m(\"\",\"\");}}", "ambiguous", TempFile.cons("package p;public class A{protected void m(Object o,String s);}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface B{void m(String s,Object o);}abstract class C extends p.A implements B{}abstract class D extends C{void f(D d){d.m(\"\",\"\");}}", "ambiguous", TempFile.cons("package p;public class A{protected void m(Object o,String s){}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "package A;import A.B.C;class B{private class C{}}", "not visible"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "package p2;public abstract class B extends p1.A{protected in m(){return 1;}}", "", TempFile.cons("package p1;public abstract class A{abstract int m();}abstract class C extends p2.B{int i=m();}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{private int i;class D extends C{int j=this.i;}}", "unknown or ambiguous name"));
    // ---------------------------------------------------------------
    // TD duplicate package members
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{}class B{}", "duplicate package members", TempFile.cons("class A{}", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "package a;class b{}", "duplicate package members", TempFile.cons("package a.b;class C{}", "a", "b", "C", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "package p;class A{}class B{}", "duplicate package members", TempFile.cons("package p;class A{}", "p", "A", null)));
    // ---------------------------------------------------------------
    // TD default constructors
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class C{C()throws Exception{}}class D extends C{}", "unhandled exception in default constructor"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class C{private C(){}}class D extends C{}", "can not access super constructor from default constructor"));
    // ---------------------------------------------------------------
    // TD other failed unit tests with multiple compilation units
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class D{int i=p.C.i;}", "", TempFile.cons("package p;class A{int i;}interface B{int i=1;}public class C extends A implements B{}", "C", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class D{void m(p.C t){try{t.m();}catch(Exception e){}}}", "", TempFile.cons("package p;abstract class A}abstract void m();}interface B{void m()throws Exception;}public abstract class C extends A implements B{}", "p", "C", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "import p.A.C.*;class B extends D{}", "", TempFile.cons("package p;public class A{public int C;public int C(){return 0;}public static class C{public static class D{}}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "import p1.*;import p2.*;class B extends A{}", "", TempFile.cons("package p1;class A{}", "p1", "A", TempFile.cons("package p2;public class A{}", "p2", "A", null))));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface B{int m();}abstract class C extends p1.A implements B{}", "", TempFile.cons("package p1;public abstract class A{abstract void m();}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "package p;import p.A.*;class B implements I{}", "", TempFile.cons("package p;class A{interface I{}}", "p", "A", null)));
    // ---------------------------------------------------------------
    // TD other failed unit tests with a single compilation unit
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{class B{}}interface C{class B{}}class D extends A implements C{static Object o=new D.B();}", "ambiguous type"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{class C{}}interface B{class C{}}class D extends A implements B{D.C t;}", "ambiguous type"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{public void m(){}}interface B{void m();}class C extends A implements B{{m();}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{static void f(int i){}}class B extends A{static void f(long l){}{f(0);}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class A{void f(String s){}}abstract class B extends A{void f(Object o){}{f(\"\");}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class E1 extends Exception{}class E2 extends Exception{}class E3 extends Exception{}abstract class A{public abstract void m()throws E1,E2;}interface B{void m()throws E2,E3;}abstract class C extends A implements B{{try{m();}catch(E1 e1){}catch(E2 e2){}}}", "jacks says it should fail, but it's no problem in eclipse"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "class E1 extends Exception{}class E2 extends Exception{}class E3 extends Exception{}abstract class A{public abstract void m()throws E1,E2;}interface B{void m()throws E2,E3;}abstract class C extends A implements B{{try{m();}catch(E2 e2){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "import A.*;class A{class B{}}", "unresolved import"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "import foo.inexistsentclass;class A{}", "unknown import"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "import nonExistentPackage.*;class A{}", "package doesn't exist"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface A{Object clone()throws java.io.IOException;}abstract class B implements A{}", "incompatible exceptions"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface A{String toString();}class B implements A{}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface A{int clone();}abstract class B implements A{}", "conflicting return types"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface A{int i=1;}class B{int i=2;}class C extends B implements A{static int j=new C().i;}", "ambiguous"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface A{void f(String s);}abstract class B implements A{void f(Object o){}{f(\"\");}}", "")); //More than one maximally specific method is ambiguous, and illegal. By JLS2 Clarifications (where?), declaring type is no longer considered, so A.f(String) is more specific than B.foo(Object).
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface I{int f();}class C{void f(){}}abstract class D extends C implements I{}", "conflicting methods"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "interface I{void f();}class C{static void f(){}}abstract class D extends C implements I{}", "conflicting methods"));
    s.addTest(new JavaAnalyzerTestError(ignore, "CompilationUnit", "package A;import A.B;class B{}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{class B{int i;}class C extends B{class D{{i++;}}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{int i;class B{Object i;}class C extends B{void f(){i=null;}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{interface B{class C{}}class D{class C{}}class E extends D implements B{C c;}}", "ambiguous"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{interface B{void f();}class C{public void f(){}}class D extends C implements B{{f();}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{interface B{void f()throws Exception;}class C{public void f(){}}class D extends C implements B{}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{private static void f(){}static class B{B(){f();}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{static class B{static B t,u;}static class C extends B{static class t{static int u;}}void f(){C.t.u=null;}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{static class B{static int i;}A t;int i=t.B.i;}", "not a field"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class A{static void f(){}static class B{B(){f();}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{Cloneable[][]s=(Cloneable[][])(Object)(Integer[])(Cloneable)(int[])null;}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int f()throws ClassNotFoundException{return 1;}int i=f();C()throws ClassNotFoundException{}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int f()throws ClassNotFoundException{return 1;}{f();}C()throws ClassNotFoundException{}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int i=1;{try{i++;throw new Exception();}catch(Exception i){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{interface I1{void f();}interface I2{int f();}interface I3 extends I1,I2{}}", "return type mismatch"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{interface I{}void f(I i){i.getClass();i.toString();i.equals(null);i.hashCode();try{i.wait();i.wait(1);i.wait(1,0);i.notifyAll();i.notify();}catch(Throwable t){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{static class A{static class B{static int i=1;}}int j=new A().B.i;}", "B cannot be resolved"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{static final String[] a={\"b\",\"c\"};}", "initializer must be compile-time constant"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{void f(){int x=2;class D{int j=x;}}}", "non-local use of non-final local"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{void f(){try{throw new Exception();}finally{return;}}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{void f(byte b)throws Exception{}void f(char c)throws Exception{}void f(int i){}void g(byte b){f(true?b:'0');f(false?b:'0');f(true?'0':b);f(false?'0':b);}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{void f(int x){class D{int j=x;}}}", "non-local use of non-final local"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{{if(true)throw new ClassNotFoundException();}C()throws ClassNotFoundException{}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{{if(true)throw new ClassNotFoundException();}C()throws Throwable{}}", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{{int i;for(int i;;);}}", "duplicate variable"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class D{static class A{interface B{}}static class B extends A{{new B();}}}", "cannot instantiate interface"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class E{class A{int i;}interface B{Object i=null;}class C extends A implements B{}class D extends C{int j=super.i;}}", "ambiguous"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "interface B{Class getClass();}", "cannot override final method"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "interface I{public int toString();}", "JLS 9.2: interface implicitly declares all methods of java.lang.Object"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Statement", "switch(123){case 0:class C{}break;case 1:new C();}", "unknown class"));
    // ---------------------------------------------------------------
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", ";", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "abstract class B extends p1.A{protected int m(){return 1;}}", "", TempFile.cons("package p1;public abstract class A{abstract void m();}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "abstract class D extends p.C{{m();}}", "", TempFile.cons("package p;interface B{void m();}public abstract class C implements B{}", "p", "C", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "abstract class D extends p.C{{try{m();}catch(Exception e){}}}", "", TempFile.cons("package p;abstract class A{abstract void m();}interface B{void m()throws Exception;}public abstract class C extends A implements B{}", "p", "C", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A extends B{}", "", TempFile.cons("class B{}", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A extends p.B{}", "", TempFile.cons("package p;public class B{}", "p", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A implements B{}", "unknown class or interface B"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{Object b=B.B_CONST;Object c=C.C_CONST;}", "", TempFile.cons("class B{static final Object B_CONST=B.class;}class C extends B{static final Object C_CONST=C.class;}", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{class B{}}class C extends A{B b=null;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{class B{}}class C extends A{class D extends B{}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{private class B{}}class C extends A{A.B t;}", "unknown type A.B"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{private int x;}class B extends A{void f(){x=0;}}", "unknown or ambiguous name"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{private void f(){}}class B extends A{B(){super();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{private void f(){}}class B extends A{{f();}}", "no such method"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{protected class B{};}class C{Class d=A.B.class;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{public A(String s){}private A(Integer i){}}class B{Object o=new A(null);}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{public A(String x, String y){}private A(String x,char[] y){}}class B{Object o=new A(\"hi\", null);}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{public int f(String s){return 0;}private int f(Integer i){return 0;}}class B extends A{int i=new A().f(null);}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{static class B{void f(){g();}void g(){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{static final String s=\"a\";}class B{void f(){class C extends A{void f(){s.toString();s.valueOf(1);}}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{static void f(){}static class B{static void g(){f();}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{static{String b=\"x\";b=\"y\";}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{void f()throws IOException{}}", "unknown class or interface IOException"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{void f()throws Throwable{finalize();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{void f(){Object o=new B();}}", "", TempFile.cons("class B{void f(){Object o=new A();}}", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{void f(){new B();}private static class B{}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{void f(String s){s.getClass();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{void f(p.C x){x.m();}}", "", TempFile.cons("package p;interface B{void m();}public abstract class C implements B{}", "p", "C", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{{\"\".getClass();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends A{}", "", TempFile.cons("class A{C c;}class C extends B{}", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends A{}", "", TempFile.cons("class A{}", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends A{}", "", TempFile.cons("class \\u0041{}", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p.A{abstract class D extends C1{public void m(){}}}", "", TempFile.cons("package p;public class A{abstract class C{abstract void m();}interface I{void m();}protected abstract class C1 extends C implements I{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p.A{class D extends C{}}", "", TempFile.cons("package p;public class A{protected class C{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p.A{class D extends C{}}", "", TempFile.cons("package p;public class A{public class C{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p.A{class D implements C{}}", "", TempFile.cons("package p;public class A{protected interface C{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p.A{interface D extends C{}}", "", TempFile.cons("package p;public class A{protected interface C{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p.A{void m()throws Exception{}}", "", TempFile.cons("package p;public class A{static int m(){return 1;}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p.A{void m(){}}", "must be abstract", TempFile.cons("package p;public abstract class A{abstract void m();}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p1.A{abstract class D extends C implements I{public void m()throws Exception{}}}", "", TempFile.cons("package p1;public class A{public abstract class C{abstract void m();}public interface I{void m()throws Exception;}}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p1.A{abstract class D extends C implements I{public void m(){}}class E extends D{}}", "must be abstract", TempFile.cons("package p1;public class A{public abstract class C{abstract void m();}public interface I{void m();}}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B extends p1.A{class D extends C implements I{public void m(){}}}", "must be abstract", TempFile.cons("package p1;public class A{public abstract class C{abstract void m();}public interface I{void m();}}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class B{Class c=p.A.class;}", "", TempFile.cons("package p;class A{}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C extends p2.B{class D implements p1.A{}}", "", TempFile.cons("package p1;public class A{}", "p1", "A", TempFile.cons("package p2;public class B{public static class p1{public interface A{}}}", "p2", "B", null))));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C extends p2.B{void f(){p1.A++;}}", "", TempFile.cons("package p1;public class A{}", "p1", "A", TempFile.cons("package p2;public class B{public static class p1{public static int A;}}", "p2", "B", null))));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{C(){}C(int x){}}class D extends C{C c=new D(3);}", "could not find constructor"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{C(){}}class D{C c=new C();}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{D d;}", "unknown type D"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{Integer i;}class D extends C{Object o=super.i;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{String i;}class D extends C{int i;{i=2;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{final void f(){}}class D extends C{void f(){}}", "cannot override final method"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{int i;}class D extends C{Object o=1.super.i;}", "';' expected"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{int i;}class D extends C{Object o=super.i;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{int i;}class D extends C{String i;{D d=null;int j=((C)d).i;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{private C(){}}class D{C c=new C();}", "could not find constructor"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{private int i;}class D extends C{Object o=super.i;}", "unknown or ambiguous name"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{private int i;}class D extends C{{i=2;}}", "unknown or ambiguous name"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{private static class D{}}class E extends C.D{}", "unknown class or interface C.D"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{private static void f(){}}class D{{C.f();}}", "no such method"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{private void f(){}}class D extends C{int f(){return -1;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{protected C(){}}class D extends C{}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{public int x;}class D extends C{void f(){x=2;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{static class D{}}class E extends C{}class F extends E.D{}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{static void f(){}}class D extends C{void f(){}}", "instance method cannot override static method"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{void f()throws Exception{}}class D extends C{void f()throws NullPointerException{}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{void f()throws Exception{}}class D extends C{void f()throws Throwable{}}", "incompatible throws clause in overriding method"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{void f(){}}class D extends C{int f(){return -1;}}", "incompatible return type"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{void f(){}}class D extends C{private void f(){}}", "cannot reduce visibility"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class C{void f(){}}class D extends C{static void f(){}}", "static method cannot hide instance method"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class D extends p.C{int j=i;}", "", TempFile.cons("package p;class A{int i;}interface B{int i=1;}public class C extends A implements B{}", "p", "C", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class D extends p.C{void m(int i){switch(i){case 1:case C.i:}}}", "", TempFile.cons("package p;class A{class C{public static final int i=1;}}interface B{class C{public static final int i=2;}}public class C extends A implements B{}", "p", "C", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class D extends p.E{int x=C.i;}", "", TempFile.cons("package p;class A{class C{public static final int i=1;}}interface B{class C{public static final int i=2;}}public class E extends A implements B{}", "p", "E", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "import java.lang.*;import java.lang.Object;import java.lang.Integer;class A extends Object{Integer i;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "import java.util.Vector;import Vector.Mosquito;class A{public static void main(String[]a){System.out.println(new Vector().getClass());System.out.println(new Mosquito().getClass());}}", "", TempFile.cons("package Vector;public class Mosquito{}", "Vector", "Mosquito", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "import p.*;class A extends B{}", "", TempFile.cons("package p;public class B{}", "p", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "import p.A.C;class B extends C{}", "", TempFile.cons("package p;public class A{public int C;public int C(){return 0;}public static class C{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "import p.A;class B implements A{}", "", TempFile.cons("package p;public interface A{}", "p", "A", TempFile.cons("class A{}", "A", null))));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "import p.A;import p.A;class B extends A{}", "", TempFile.cons("package p;public class A{}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "import p.B;class A extends B{}", "", TempFile.cons("package p;public class B{}", "p", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "import p1.*;import p2.*;class B extends A{}", "", TempFile.cons("package p1;public class A{}", "p1", "A", TempFile.cons("package p2;public class A{}", "p2", "A", null))));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface A{int x=2;}interface B{int x=3;}class C implements A,B{int y=x;}", "unknown or ambiguous name"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface A{int x=2;}interface B{int x=3;}class C implements A,B{}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface A{interface B{}}interface C extends A{interface D extends B{}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface A{void f();}abstract class B implements A{}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface A{void f();}interface B{void f();}class C implements A,B{public void f(){}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface B{Class BUG=Inner.class;class Inner{}}", "", TempFile.cons("class A{Class c=B.BUG;}", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface B{void m();}abstract class C extends p1.A implements B{}", "", TempFile.cons("package p1;public abstract class A{abstract void m();}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface I{int V=1;}interface J extends I{}class C implements I,J{int i=V;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "interface I{int V=1;}interface J{int V=2;}class C implements I,J{int i=V;}", "unknown or ambiguous name"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package A;import A.B.*;class B{static class C{}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package A;import A.B.C;public class A extends C{}", "", TempFile.cons("package A.B;public class C{}", "A", "B", "C", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package bazoa;class Gabriel{static int n=org.rpgpoet.Music.wizards.length;}", "", TempFile.cons("package org.rpgpoet;import java.util.Random;public interface Music{Random[]wizards=new Random[4];}", "org", "rpgpoet", "Music", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package java.lang;class Object extends Object{}", "Object can not have an extends clause"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package java.lang;interface I{}class Object implements I{}", "Object can not have an implements clause"));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p1;public abstract class C extends p2.B{void m(){}}", "", TempFile.cons("package p1;public abstract class A{abstract void m();}", "p1", "A", TempFile.cons("package p2;public abstract class B extends p1.A{}", "p2", "B", null))));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p2;import p1.*;interface I{class B{}}class C extends A implements I{static Object o=new C.B();}", "", TempFile.cons("package p1;public class A{static class B{}}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p2;import p1.A;class B extends A{}", "", TempFile.cons("package p1;public class A{}", "p1", "A", TempFile.cons("package p2;interface A{}", "p2", "A", null))));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p2;public abstract class B extends p1.A{}", "", TempFile.cons("package p1;public abstract class A{abstract void m();}class C extends p2.B{void m(){}}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p2;public class B extends p1.A{private class p1{}}", "", TempFile.cons("package p1;public class A{public class p1{}}class C extends p2.B{p1.C p;}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p2;public class B extends p1.A{protected static int m(){return 1;}}", "", TempFile.cons("package p1;public class A{int m(){return 1;}}class C extends p2.B{int i=m();}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p2;public class B extends p1.A{public abstract class D extends C implements I{public void m()throws Exception{}}}", "", TempFile.cons("package p1;public class A{public abstract class C{abstract void m();}public interface I{void m()throws Exception;}}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p2;public class B extends p1.A{}", "", TempFile.cons("package p1;public class A{class p1{}}class C extends p2.B{p1.C p;}", "p1", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p3;import p2.*;import p1.A;class B extends A{}", "", TempFile.cons("package p1;public class A{}", "p1", "A", TempFile.cons("package p2;interface A{}", "p2", "A", null))));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p;import p.A.C;class B implements C{}", "", TempFile.cons("package p;class A{interface C{}}", "p", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p;public class B{public static A[]array;public static class A{}}", "", TempFile.cons("class A{int i=p.B.array.length;}", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p;public class B{}", "", TempFile.cons("class A{p.B x;}", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p;public class B{}", "", TempFile.cons("class A{p.B[]ref;}", "A", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package p;public class C{public static A[]a;public static class A{}}", "", TempFile.cons("class B{Object o=p.C.array.toString();}", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package q;class A extends p.B{}", "", TempFile.cons("package p;public class B{void f(){}}", "p", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "package q;class A extends p.B{}", "", TempFile.cons("package p;public class B{}", "p", "B", null)));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "abstract class C{abstract private void f(){}}", "conflicting modifiers"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "abstract class C{abstract void f();abstract int f();}", "duplicate method"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "abstract class C{public abstract String toString();}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A extends B{}", "unknown class or interface B"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{String[] s=new String[]{};}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{boolean b=new String[]{}instanceof String[];}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{byte b='\\u0080';}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{byte b=(byte)1;char c=b;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{byte b=(short)128;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{byte b=1L;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{byte n1=1;byte n2=+n1;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{byte n1=1;byte n2=-n1;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{byte n1=1;byte n2=~n1;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{char b='\\u000d';}", "single character must not be line terminator"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{char b='\\u0027';}", "character constant expected"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{char b='\\u005c';}", "array initializer expected"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{char c='1';byte b=c;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{char c=(byte)-1;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{class B{interface C{}}}", "illegal context for static member"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{class B{static class C{}}}", "illegal context for static member"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{class B{static void c(){}}}", "illegal context for static member"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{class B{}static class C extends A{private class B{}}static class D extends C{D.B b;}}", "unknown type D.B"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{double d=-1e-326;}", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{final int i=1;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{float f=(float)1/1.0;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int A;Class a=A.class;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int A;{A.class.toString();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int f(){return x;}}", "unknown or ambiguous name"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int f(long i){return 0;}long f(int i){return 0;}int i=f(0);}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=-100;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=-2147483648;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=1*2L;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=1,i2=(-i)++;}", "operand of ++ must be variable"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=1,i2=(-i)--;}", "operand of -- must be variable"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=1,i2=++(-i);}", "operand of ++ must be variable"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=1,i2=--(-i);}", "operand of -- must be variable"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=123;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{int i=1L;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{interface B{int i=1;}interface C extends B{}interface D extends B{}class E implements C,D{int j=i;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{long l=0-2147483648;}", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{long l=0-9223372036854775808L;}", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{long l=1.0D;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{long l=1L%0L;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{long l=1L/0L;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{private class B{}class C{C(){new B();}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{private class B{}static class C extends A{{new B();}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{private int f(){return 1;}class B extends A{int i=this.f();}}", "no such method"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{static int a=3;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{void f(){(\"1\"+2).toString();(\"1\"+2).valueOf(1);}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{void f(){class B{}class B{}}}", "conflicting classes"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{void f(){interface B{}}}", "interface cannot be local"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{void f(){try{Object.class.forName(\"java.lang.Object\");}catch(Exception e){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{void f(){x=2;}}", "unknown or ambiguous name"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{void f(String[]a){int i=a.length;Class c=a.getClass();String s=a.toString();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{void f(int i){switch(i){case 0:case((\"\\u0080\"==\"\"+'\\u0080')?1:0):case((\"\\u0080,\\u0080\"=='\\u0080'+\",\"+'\\u0080')?3:0):}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{void f(int[]a){int i=a.length;Class c=a.getClass();String s=a.toString();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{{A.class.toString();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{{\"\".toString();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class A{{if(new String[]{}instanceof String[]);}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C extends ClassLoader{}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C extends C{}", "circular class"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C extends String{}", "can't subclass final class"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C implements Cloneable, Cloneable{}", "duplicate superinterfaces"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C implements Runnable{abstract void run();}", "must be abstract"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C implements Runnable{public void run(){}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C implements Runnable{}", "must be abstract"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C { // \n } oops", "input not fully consumed"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C { int i; C c; int j = c.i; }", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C { int i; int j = C.i; }", "static access to non-static field"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C { int i; int j = new C().i; }", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C { static int i; int j = C.i; }", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{A a=new A();static class A{private A(){}A(String s){}}{new A(null);}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{C() throws Exception{}C(int i)throws Exception{}{throw new java.io.IOException();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{C() throws Exception{}C(int i){}{throw new Exception();}}", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{C() throws Exception{}{throw new Exception();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{C(){return null;}}", "'return' with a value, in method returning void"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{C(){}C(){}}", "duplicate method"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{Class c=Object[].class;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{Class c=Runnable[][][][].class;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{Class c=UnknownType.class;}", "unknown class or interface UnknownType"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{Object f(){class D{}return new D();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{Object f(){return new Object();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{Object x=new java.util.AbstractCollection();}", "cannot instantiate abstract type"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{Object[]a={new Object()};}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{String s1=(String)\"\";String s2=(String)null;String s3=(String)s1;String s4=(String)s2;String s5=(String)(\"1\"+\"2\");String s6=\"1\".concat(\"2\");}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{String s=new Object();}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{String toString(){return null;}}", "cannot reduce visibility"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{abstract void f();}", "must be abstract"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{boolean b=\"null\"==null;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{boolean b=null==\"1\";}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{class D{static final int i=0;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{class D{static int i=0;}}", "static variables of inner classes must be compile-time constants"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{class D{static{}}}", "inner classes may not declare static initializers"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{d(){}}", "missing return type"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{final Object[]a={new Object(),new Object()};void swap(){Object t=a[0];a[0]=a[1];a[1]=t;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{final StringBuffer s=new StringBuffer();void append(){s.append(\"nuggy\");}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{final int i=1;{switch (123){case 0:case (i==1)?1:0:}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{final volatile int i=0;}", "conflicting modifiers final and volatile"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int f(){return 0;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int f(){return 3.1;}}", "return type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int f(){return;}}", "'return' with no value, in method returning non-void"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int foo;Class c=foo.class;}", "unknown class or interface foo"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int i;static int f(){return i;}}", "static use of instance field"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int i;void f(int i){}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int i=0;static int j=i;}", "static use of instance field"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int i=1/0;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int i=1;byte b=i;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int i=i=2;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int x;int x;}", "duplicate field declaration x"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int x=2;void f(){class D{int j=x;}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int[] a = {123L};}", "array initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int[] a = {123};}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int[][]ia={{1,2},null};}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int[]a={new Object()};}", "array initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int[]f(){return g();}int g()[]{return f();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{int[]ia={{1,2},null};}", "array initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{native strictfp void f();}", "conflicting modifiers"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{private class D{}class E extends C{E.D d;}}", "unknown type E.D"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{public static int f(){return 5;}interface I{int CONSTANT=f();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{short s='\u8000';}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{short s=(short)1;char c=s;}", "initializer type mismatch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static C f(){return this;}}", "static use of this"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static String s=\"1\";void f(int j){switch(j){case 0:case((C.s==\"1\")?1:0):}}}", "case expression must be constant"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static class D{interface I{}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static class D{static{}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static final String a=\"b\";}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static int c=super.hashCode();}", "static use of super"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static int f()throws Exception{return 0;}int i=C.f();}", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static int f()throws Exception{return 0;}static int i=C.f();}", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static int m() throws Exception {return 1;}static int i=m();}", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static void f(){class D{{new D();}}new D();{new D();}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{static{throw new Exception();}}", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f();}", "missing method body"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f()throws ClassNotFoundException{throw new Exception();}}", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f()throws Exception{throw new Exception();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){12--;}}", "operand of -- must be variable"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){Comparable x;Comparable: x=\"c\";}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){String i;i++;}}", "operand of ++ must be number"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){String s=new Integer();}}", "could not find constructor"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){boolean b;b--;}}", "operand of -- must be number"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){final int i;i++;}}", "operand of ++ must not be final"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){final int x=2;class D{int j=x;}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){for (int i=0;i<10;++i) continue;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){int i;i++++;}}", "operand of ++ must be variable"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){int i;i++;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){int i;j++;}}", "operand of ++ must be variable"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){int i;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){int true;}}", "illegal identifier"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){return 0;}}", "'return' with a value, in method returning void"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){return;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){throw null;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){x:y:{for(;;)break x;}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){x:y:{for(;;)continue x;}}}", "x is not a loop label"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){x:{ for (;;) break x;}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){x:{ for (int i=0;i<10;++i) continue x;}}}", "x is not a loop label"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(){}void f(){}}", "duplicate method"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(byte b){switch(b){case 0x1ff:}}}", "invalid case clause"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(char c)throws Exception{}void f(int i){}void g(){f(true?'0':-1);f(false?'0':-1);f(true?-1:'0');f(false?-1:'0');}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(char c){switch(c){case 123:}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(final int i){i=1;}}", "left operand of assignment is final"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(final int x){class D{int j=x;}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i){for(int i=2;;);}}", "duplicate variable declaration i"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i){for(int j=2,k=3;;);}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i){int i;}}", "duplicate variable declaration i"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i){switch(i){case 0:case(('\\u0061'=='a')?1:0):}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i){switch(i){case 0:case(('\\uABcD'=='\\uabCd')?1:0):}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i){switch(i){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i){{int i;}}}", "duplicate variable declaration i"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i){for(int i=2;;);}}", "duplicate variable declaration i"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int i,int i);}", "duplicate parameter declaration i"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void f(int[]a){int b;b=a.length;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void m(){break;}}", "break without label can only be used in loop or switch"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void m(){continue;}}", "continue cannot be used outside of a loop"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void m(){i:{i:{}}}}", "duplicate label i"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{void m(){i:{}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{int i=1;switch(123){case i++:;}}}", "case expression must be constant"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{new C();}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{try{throw new ClassNotFoundException();}catch(Exception e){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{try{throw new Exception();}catch(ClassNotFoundException e){}}}", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{try{throw new Exception();}catch(Exception e){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{try{try{throw new Exception();}catch(ClassNotFoundException e){}}catch(ClassNotFoundException e){}}}", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{try{try{throw new Exception();}catch(ClassNotFoundException e){}}catch(Exception e){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{try{}catch(Exception e){}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{try{}catch(String e){}}}", "illegal type for exception parameter"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class C{{try{}catch(int e){}}}", "illegal type for exception parameter"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class H { static void i() { } static H k() { } }", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "class TestString { char[] value; int offset, count; int indexOf(TestString str, int fromIndex) { char[] v1 = value, v2 = str.value; int max = offset + (count - str.count); int start = offset + ((fromIndex < 0) ? 0 : fromIndex); i: for (int i = start; i <= max; i++) { int n = str.count, j = i, k = str.offset; while (n-- != 0) { if (v1[j++] != v2[k++]) continue i; } return i - offset; } return -1; } }", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "final abstract class C {}", "can not be both abstract and final"));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "interface A{;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "interface A{A a=null;int i=1;int j=a.i;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "public class C{void f(){Object[]o=null;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Declaration", "public public class C{}", "duplicate modifier public"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "'\\u000a'", "single character must not be line terminator"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "'\\u001a'", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "'\\u03a9'", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "'\\uFFFF'", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "'\\uuuuuuuuuuabcd'", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "'\n'", "single character must not be line terminator"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "'\r'", "single character must not be line terminator"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "(Object).class", "input not fully consumed"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "-100", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "-1e-326", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "-1e310", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "-2147483648", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "-Float.NaN", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "02000000000000000000000L", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "040000000000", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "0x123456789", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "0x123456789abcdef01L", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "0xCafeBabe", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "1.class", "input not fully consumed"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "1// This is a comment\n", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "123 instanceof String", "reference type expected"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "12345678901", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "12345678901234567890L", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "1234?1:0", "condition must be boolean"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "1\\u002f\\u002f This is a comment\\u000a", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "1e-47f", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "1e39f", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "2147483648", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "9223372036854775808L", "literal out of range"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "Object.noSuchMethod()", "no such method"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "String.class", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "System.gc()", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "System.out instanceof String", "not castable"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "System.out.println()", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"\".class", "input not fully consumed"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"\\u001a\"", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"\\u005c\\u005a\"", "unary expression expected"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"\\u03a9\"", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"\\uFFFF\"", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"\n\"", "string must not contain line terminator"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"\r\"", "string must not contain line terminator"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"hello\" instanceof Object", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"hello\" instanceof String", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "\"hi\" instanceof int", "reference type expected"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "false?-1:'0'", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "int.class", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "int[][].class", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "java.io.PrintStream.println()", "static call to non-static method"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new Object()", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new String().class", "input not fully consumed"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new String(123)", "could not find constructor"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new String[]{}instanceof String[]", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new int['3']", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new int[0]", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new int[3.0]", "dimension must be integer"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new int[3L]", "dimension must be integer"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new int[3]", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new int[3][3]", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new int[3][]", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "new int[null]", "dimension must be integer"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "null instanceof int[]", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "null.class", "input not fully consumed"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "null==\"\"", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "this.class", "input not fully consumed"));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "true?'0':-1", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Expression", "true?1:0", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "i:for(;;){break i;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch('a'){}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(12){case 0:case(((double)'\u789a'==30874.0)?1:0):}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(12){case 1:case 1:}", "duplicate case clause"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(12){case 1:case 2:}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(12){default:default:}", "duplicate default clause"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(12){}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(12.3){}", "switch expression must be char, byte, short, or int"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(123){case 0.0D:}", "invalid case clause"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(123){case 0:class C{}break;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(123){case 0:class C{}break;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "switch(123){case true:}", "invalid case clause"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "synchronized(12.5) {}", "invalid type for synchronized statement"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "synchronized(null) {}", "invalid type for synchronized statement"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "throw new ClassNotFoundException();", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "throw new Error();", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "throw new Exception();", "uncaught exception"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "throw new NullPointerException();", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "throw new RuntimeException();", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "while(1);", "condition must be boolean"));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "while(true);", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "while(true){break;}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "{class C{final int i=1;}class D extends C{{switch (123){case 0:case (i==1)?1:0:}}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "{class C{int i=1; class D{int j=i;}}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "{class C{}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "{i:while(true){continue i;}}", ""));
    s.addTest(new JavaAnalyzerTestError(false, "Statement", "{i:{continue j;}}", "the label j is missing"));
    return s;
  }

  private static TestSuite makeSuiteJavaExternalAnalyzer() {
//    final boolean ignore = true; //T D 38 failing unit tests
    final TestSuite s = new TestSuite();
//  s.addTest(new JavaExternalAnalyzerTestType(false, "Declaration", "", "", true));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", false, "class A extends B implements D,C{}", "class A extends B implements D,C{A()->void;}"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", false, "class A{class C{}class B{}}", "class A{A()->void;class A.B{B()->void;};class A.C{C()->void;};}"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", false, "class A{int b;}", "class A{field(int,b);A()->void;}"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", false, "class A{void b();C[]d;}", "class A{field(C[],d);A()->void;b()->void;}"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", false, "class A{}", "class A{A()->void;}"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", false, "interface A extends B,D,C{}", "abstract interface A extends B,D,C{}"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", false, "public final class A{}", "public final class A{public A()->void;}"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "A b,c;", "field(A,b);field(A,c);"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "A b;", "field(A,b);"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "A b=1;", "field(A,b);"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "A[]b;", "field(A[],b);"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "A[]b[];", "field(A[][],b);"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "a.b.C[]d,e[];", "field(a.b.C[],d); field(a.b.C[][],e);"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "char a;", "field(char,a);"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "int a();", "a()->int"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "int b(){}", "b()->int"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "int b(C d);", "b(param(C,d))->int"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "int b(C d,E[]f,G[][]h);", "b(param(C,d),param(E[],f),param(G[][],h))->int"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "public static final String s;", "public static final field(String,s);"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "public strictfp float b();", "public strictfp b()->float"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Declaration", true, "void a();", "a()->void"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Type", "A"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Type", "A[]"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Type", "A[][]"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Type", "a.B"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Type", "a.b.C[][]"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Type", "byte"));
    s.addTest(new JavaExternalAnalyzerTest(false, "Type", "char[]"));
    return s;
  }

  private static TestSuite makeSuiteJavaParser() {
    final boolean ignore = true; //TD 38 parser-related bugs
    final TestSuite s = new TestSuite();
    //s.addTest(new JavaParserTest("", false, "", ""));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{int i;C t;void f(){t.(i)=1;}}", "invalid syntax"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{static void f(){int i;(i=1);}}", "invalid expression statement"));
    s.addTest(new JavaAnalyzerTestError(ignore, "Declaration", "class C{void f(){}void g(){(f());}}", "invalid expression statement"));
    s.addTest(new JavaParserTest(ignore, "Expression", "class C{int i = new int[]{1}[0];}"));
    s.addTest(new JavaParserTest(false, "Expression", "(a+b)*c"));
    s.addTest(new JavaParserTest(false, "Expression", "a&b==c&&d"));
    s.addTest(new JavaParserTest(false, "Expression", "a+1"));
    s.addTest(new JavaParserTest(false, "Expression", "a+b*c"));
    s.addTest(new JavaParserTest(false, "Expression", "a-(b-c)"));
    s.addTest(new JavaParserTest(false, "Expression", "a-b-c"));
    s.addTest(new JavaParserTest(false, "Expression", "a.f(0)"));
    s.addTest(new JavaParserTest(false, "Expression", "a.f(a,b,c)"));
    s.addTest(new JavaParserTest(false, "Expression", "f()"));
    s.addTest(new JavaParserTest(false, "Expression", "f().g()"));
    s.addTest(new JavaParserTest(false, "Expression", "f(0)"));
    s.addTest(new JavaParserTest(false, "Statement", "switch (i) { case 'a': case 2: break; case 0x1: { } default: }"));
    s.addTest(new JavaParserTest(false, "Expression", "(A)b"));
    s.addTest(new JavaParserTest(false, "Expression", "(A[][])b"));
    s.addTest(new JavaParserTest(false, "Expression", "(char[])a"));
    s.addTest(new JavaParserTest(false, "Expression", "(int)'a'"));
    s.addTest(new JavaParserTest(false, "Expression", "(int)a"));
    s.addTest(new JavaParserTest(false, "Expression", "Integer[].class"));
    s.addTest(new JavaParserTest(false, "Expression", "int.class"));
    s.addTest(new JavaParserTest(false, "Expression", "int[].class"));
    s.addTest(new JavaParserTest(false, "Expression", "void.class"));
    s.addTest(new JavaParserTest(false, "CompilationUnit", "class A{class B{}} class C{ A.B b=new A().new B();}"));
    s.addTest(new JavaParserTest(false, "CompilationUnit", "class Main { public static void main(String[] args) { System.class.println(\"Hello world!\"); } }"));
    s.addTest(new JavaParserTest(false, "Expression", "(a==++b.c(1)[d.e()][2].f&g)-h"));
    s.addTest(new JavaParserTest(false, "Declaration", "A a=0;"));
    s.addTest(new JavaParserTest(false, "Declaration", "A b,c;"));
    s.addTest(new JavaParserTest(false, "Declaration", "A b;"));
    s.addTest(new JavaParserTest(false, "Declaration", "A b[],c,d[][];"));
    s.addTest(new JavaParserTest(false, "Declaration", "A[]b;"));
    s.addTest(new JavaParserTest(false, "Declaration", "A[]b[];"));
    s.addTest(new JavaParserTest(false, "Declaration", "int a;"));
    s.addTest(new JavaParserTest(false, "Declaration", "public A b;"));
    s.addTest(new JavaParserTest(false, "Declaration", "public final A b;"));
    s.addTest(new JavaParserTest(false, "Statement", "for(0,1;;);"));
    s.addTest(new JavaParserTest(false, "Statement", "for(;;);"));
    s.addTest(new JavaParserTest(false, "Statement", "for(A b=c,d=e;;);"));
    s.addTest(new JavaParserTest(false, "Statement", "for(A[]b[];;);"));
    s.addTest(new JavaParserTest(false, "Statement", "for(int a=0,b=c;a<b;a++)d*=2;"));
    s.addTest(new JavaParserTest(false, "Statement", "for(int a=0;;);"));
    s.addTest(new JavaParserTest(false, "FormalParameter", "A b"));
    s.addTest(new JavaParserTest(false, "FormalParameter", "a[][] b"));
    s.addTest(new JavaParserTest(false, "FormalParameter", "final int i"));
    s.addTest(new JavaParserTest(false, "Statement", "if(a)b;"));
    s.addTest(new JavaParserTest(false, "Statement", "if(a)b;else c;"));
    s.addTest(new JavaParserTest(false, "Declaration", "A b();"));
    s.addTest(new JavaParserTest(false, "Declaration", "A b(C d);"));
    s.addTest(new JavaParserTest(false, "Declaration", "A b(C d,E[]f){}"));
    s.addTest(new JavaParserTest(false, "Declaration", "X A()throws B{}"));
    s.addTest(new JavaParserTest(false, "Declaration", "X A(){}"));
    s.addTest(new JavaParserTest(false, "Declaration", "char a()throws B,C;"));
    s.addTest(new JavaParserTest(false, "Declaration", "public final int[]a(){}"));
    s.addTest(new JavaParserTest(false, "Declaration", "void a();"));
    s.addTest(new JavaParserTest(false, "Expression", "a.new B()"));
    s.addTest(new JavaParserTest(false, "Expression", "a.new B().new C()"));
    s.addTest(new JavaParserTest(false, "Expression", "a.new B(c,d)"));
    s.addTest(new JavaParserTest(false, "Expression", "new A()"));
    s.addTest(new JavaParserTest(false, "Expression", "new A(){}"));
    s.addTest(new JavaParserTest(false, "Expression", "new A[2]"));
    s.addTest(new JavaParserTest(false, "Expression", "new A[2][]"));
    s.addTest(new JavaParserTest(false, "Expression", "new A[][]{{b,c},{d,e}}"));
    s.addTest(new JavaParserTest(false, "Expression", "new A[]{b,c}"));
    s.addTest(new JavaParserTest(false, "Expression", "a.b"));
    s.addTest(new JavaParserTest(false, "Expression", "a.b.c"));
    s.addTest(new JavaParserTest(false, "Expression", "a.class"));
    s.addTest(new JavaParserTest(false, "Expression", "a.class.b"));
    s.addTest(new JavaParserTest(false, "Expression", "a.class.b.c"));
    s.addTest(new JavaParserTest(false, "Expression", "a[0]"));
    s.addTest(new JavaParserTest(false, "Expression", "a[0][1]"));
    s.addTest(new JavaParserTest(false, "Expression", "a[b][c][d]"));
    s.addTest(new JavaParserTest(false, "Statement", "switch(123){case 0:}"));
    s.addTest(new JavaParserTest(false, "Statement", "try{}catch(A b){}"));
    s.addTest(new JavaParserTest(false, "Statement", "try{}catch(A b){}catch(C d){}finally{}"));
    s.addTest(new JavaParserTest(false, "Statement", "try{}catch(A b){}finally{}"));
    s.addTest(new JavaParserTest(false, "Statement", "try{}finally{}"));
    s.addTest(new JavaParserTest(false, "Expression", "!a++"));
    s.addTest(new JavaParserTest(false, "Expression", "++a"));
    s.addTest(new JavaParserTest(false, "Expression", "+-!~--a++--"));
    s.addTest(new JavaParserTest(false, "Expression", "-a"));
    s.addTest(new JavaParserTest(false, "Expression", "a++"));
    s.addTest(new JavaParserTest(false, "Expression", "a--"));
    s.addTest(new JavaParserTest(false, "Declaration", "class C{int[] a = {,};}", "class C{int[] a = {};}"));
    s.addTest(new JavaParserTest(false, "Declaration", "class C{int[] a = {1,};}", "class C{int[] a = {1};}"));
    s.addTest(new JavaParserTest(false, "Expression", "'\\u005c\\u0030'"));
    s.addTest(new JavaParserTest(false, "CompilationUnit", "class c{ { this(); super(); } }"));
    s.addTest(new JavaParserTest(false, "Expression", "super()"));
    s.addTest(new JavaParserTest(false, "Expression", "this()"));
    s.addTest(new JavaParserTest(false, "Expression", "this(1, 2, null)"));
    s.addTest(new JavaParserTest(false, "Expression", "z.super()"));
    s.addTest(new JavaParserTest(false, "CompilationUnit", "class A{}//", "class A{}"));
    s.addTest(new JavaParserTest(false, "Statement", "\\u0062:;"));
    s.addTest(new JavaParserTest(false, "Expression", "B"));
    s.addTest(new JavaParserTest(false, "Expression", "\\u0062"));
    s.addTest(new JavaParserTest(false, "Expression", "\u0062"));
    return s;
  }
    
  static JavaExternalAnalyzer newJavaExternalAnalyzer() {
    return new JavaExternalAnalyzer(new Runtime(), new SymbolTable());
  }

  public static Runtime newRuntime() {
    final Runtime runtime = new Runtime();
    runtime.dir("in", Runtime.INPUT_DIRECTORY, true, "").setValue(Runtime.INPUT_DIRECTORY, JavaEntities.TEMP_DIR); //.initDefaultValues();
    return runtime;
  }

  public static String stripPrefix(final String s, final String prefix) {
    final int pos = s.indexOf(prefix);
    return -1 == pos ? s : s.substring(prefix.length() + pos);
  }

  public static String stripSuffix(final String s, final String suffix) {
    final int pos = s.indexOf(suffix);
    return -1 == pos ? s : s.substring(0, pos);
  }

  public static Test suite() {
    final TestSuite s = new TestSuite();
    if (false) { //TD 00 quick test-bed
//      s.addTest(new JavaAnalyzerTestError(false, "CompilationUnit", "class A{Character.Subset s;}", ""));
    } else {
      s.addTest(makeSuiteJavaParser());
      s.addTest(makeSuiteJavaExternalAnalyzer());
      s.addTest(makeSuiteJavaAnalyzerError());
      s.addTest(makeSuiteJavaAnalyzerConstant());
      s.addTestSuite(xtc.lang.JavaUnitTests.class);
    }
    return s;
  }
  
  /**
   * To enable assertions in eclipse, go to Run -> Run... -> Arguments, and in
   * the box labeled VM arguments, enter -enableassertions.
   */
  public final void testAssertEnabled() {
    boolean caught = false;
    try {
      assert false;
    } catch (final AssertionError e) {
      caught = true;
    }
    assertTrue(caught);
  }

  public final void testCParser_pTranslationUnit() throws Exception {
    final String[] strings = {
        "int main(int argc, char** argv) { printf(\"Hello world!\\n\"); }",
        "int x;" };
    for (int i = 0, n = strings.length; i < n; i++)
      cParserRoundTrip("TranslationUnit", strings[i]);
  }
  
  public final void testJavaAnalyzer_visitAssignmentExpression()
      throws Exception {
    final String fileABF = "package a.b;" + // .package(a.b).file(<input>)
        "class F {           " + // .F
        "  public int i1;    " + //
        "  void g(char c1) { " + // .method(g)(char c1)
        "    int[] a1;       " + //
        "    final int[] a2; " + //
        "    int[][] a3;     " + //
        "    boolean b1;     " + //
        "    char c2;        " + //
        "    float f1;       " + //
        "    int i2, i3;     " + //
        "    final int i4;   " + //
        "    String s1;      " + //
        "  }                 " + //
        "}                   ";
    final GNode ast = JavaEntities.javaStringToAst("CompilationUnit", fileABF, true);
    final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), new SymbolTable());
    ana.dispatch(ast);
    JavaEntities.enterScopeByQualifiedName(ana._table,
        ".package(a.b).file(<input>).F.method(g)(char c1)");
    javaAnalyzerTestError("Expression", "i2=40", "", ana);
    javaAnalyzerTestError("Expression", "40=i2", "left operand of assignment not l-value", ana);
    javaAnalyzerTestError("Expression", "i2=true", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "i2=i3", "", ana);
    javaAnalyzerTestError("Expression", "i2=i4", "", ana);
    javaAnalyzerTestError("Expression", "i4=40", "left operand of assignment is final", ana);
    javaAnalyzerTestError("Expression", "i2=f1", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "i2=b1", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "i2=s1", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "i2='x'", "", ana);
    javaAnalyzerTestError("Expression", "i2=c1", "", ana);
    javaAnalyzerTestError("Expression", "i2=c2", "", ana);
    javaAnalyzerTestError("Expression", "c1='x'", "", ana);
    javaAnalyzerTestError("Expression", "c1=i2", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "i1=40", "", ana);
    javaAnalyzerTestError("Expression", "i1=i2", "", ana);
    javaAnalyzerTestError("Expression", "i1=c1", "", ana);
    javaAnalyzerTestError("Expression", "i1=i4", "", ana);
    javaAnalyzerTestError("Expression", "i1=b1", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "a1[3]=40", "", ana);
    javaAnalyzerTestError("Expression", "a1[3]=true", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "i2=a1[3]", "", ana);
    javaAnalyzerTestError("Expression", "a1=a2", "", ana);
    javaAnalyzerTestError("Expression", "a2=a1", "left operand of assignment is final", ana);
    javaAnalyzerTestError("Expression", "a2[1]='a'", "", ana);
    javaAnalyzerTestError("Expression", "a3[2]=a2", "", ana);
    javaAnalyzerTestError("Expression", "a3[2][1]=2", "", ana);
    javaAnalyzerTestError("Expression", "s1=99", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "i1+=99", "", ana);
    javaAnalyzerTestError("Expression", "s1+=99", "", ana);
    javaAnalyzerTestError("Expression", "i1-=99", "", ana);
    javaAnalyzerTestError("Expression", "s1-=99", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "b1^=true", "", ana);
    javaAnalyzerTestError("Expression", "i1|=0xff", "", ana);
    javaAnalyzerTestError("Expression", "b1&=i1", "illegal assignment", ana);
    javaAnalyzerTestError("Expression", "i1^=true", "illegal assignment", ana);
  }

  public final void testJavaAnalyzer_visitCallExpression() throws Exception {
    final String fileABF = "package a.b;" + // .package(a.b).file(<input>)
        "class F {              " + // .F
        "  static void i() {    " + //
        "    G g;               " + //
        "    H h;               " + //
        "  }                    " + // .method(i)()
        "  static void j(G z) {}" + //
        "  static void j(H z) {}" + //
        "}                      " + //
        "class G extends F    { " + //
        "}                      " + //
        "class H extends F    { " + //
        "  static void i() { }  " + //
        "  static H k() { }     " + //
        "}                      " + //
        "";
    final GNode ast = JavaEntities.javaStringToAst("CompilationUnit", fileABF, true);
    final SymbolTable tab = new SymbolTable();
    final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), tab);
    ana.dispatch(ast);
    JavaEntities.enterScopeByQualifiedName(tab, ".package(a.b).file(<input>).F.method(i)()");
    javaAnalyzerTestUseDef(ana, "i()", ".package(a.b).file(<input>).F.method(i)()");
    javaAnalyzerTestUseDef(ana, "j(g)", ".package(a.b).file(<input>).F.method(j)(G z)");
    javaAnalyzerTestUseDef(ana, "j(h)", ".package(a.b).file(<input>).F.method(j)(H z)");
    javaAnalyzerTestUseDef(ana, "F.j(g)", ".package(a.b).file(<input>).F.method(j)(G z)");
    javaAnalyzerTestUseDef(ana, "g.i()", ".package(a.b).file(<input>).F.method(i)()");
    javaAnalyzerTestUseDef(ana, "h.i()", ".package(a.b).file(<input>).H.method(i)()");
    javaAnalyzerTestUseDef(ana, "H.k().i()", ".package(a.b).file(<input>).H.method(i)()");
    javaAnalyzerTestUseDef(ana, "hashCode()", ".package(java.lang).file().Object.method(hashCode)()");
  }

  public final strictfp void testJavaAnalyzer_visitConstantExpression() throws Exception {
    // gosling_et_al_2000 15.28, 3.10
    final String fileABF = "package a.b;" + // .package(a.b).file(<input>)
        "class F {                          " + // .F
        "  final static int x=123;          " + //
        "  void g() {                       " + // .method(g)()
        "    final int y=456;               " + //
        "    final String z=2+\" fiddlers\";" + //
        "  }                                " + //
        "}                                  ";
    final GNode ast = JavaEntities.javaStringToAst("CompilationUnit", fileABF, true);
    final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), new SymbolTable());
    ana.dispatch(ast);
    JavaEntities.enterScopeByQualifiedName(ana._table,
        ".package(a.b).file(<input>).F.method(g)()");
    javaAnalyzerTestConstant("x", new Integer(123), ana);
    javaAnalyzerTestConstant("y", new Integer(456), ana);
    javaAnalyzerTestConstant("a.b.F.x", new Integer(123), ana);
    javaAnalyzerTestConstant("1+z", "12 fiddlers", ana);
  }

  public final void testJavaAnalyzer_visitExpression() throws Exception {
    final String fileABF = "package a.b;" + // .package(a.b).file(<input>)
        "class F {         " + // .F
        "  void g() {      " + // .method(g)()
        "    boolean b1;   " + //
        "    int i1, i2;   " + //
        "    double d1;    " + //
        "  }               " + //
        "}                 ";
    final GNode ast = JavaEntities.javaStringToAst("CompilationUnit", fileABF, true);
    final SymbolTable tab = new SymbolTable();
    final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), tab);
    ana.dispatch(ast);
    JavaEntities.enterScopeByQualifiedName(tab,
        ".package(a.b).file(<input>).F.method(g)()");
    javaAnalyzerTestUseDef(ana, "i1",
        ".package(a.b).file(<input>).F.method(g)().i1");
    javaAnalyzerTestUseDef(ana, "i1+i2", "int");
    javaAnalyzerTestUseDef(ana, "\"a\"+i2",
        ".package(java.lang).file().tag(String)");
    javaAnalyzerTestUseDef(ana, "i1<i2", "boolean");
    javaAnalyzerTestUseDef(ana, "false", "boolean");
    javaAnalyzerTestUseDef(ana, "i1+d1", "double");
    javaAnalyzerTestUseDef(ana, "i1++", "int");
    javaAnalyzerTestUseDef(ana, "d1--", "double");
    javaAnalyzerTestUseDef(ana, "(byte)d1", "byte");
    javaAnalyzerTestUseDef(ana, "b1 ? i1 : d1", "double");
    javaAnalyzerTestUseDef(ana, "this instanceof F", "boolean");
    javaAnalyzerTestUseDef(ana, "new F()", ".package(a.b).file(<input>).tag(F)");
    javaAnalyzerTestUseDef(ana, "d1++", "d1");
    javaAnalyzerTestUseDef(ana, "this", ".package(a.b).file(<input>).tag(F)");
    javaAnalyzerTestUseDef(ana, "super", ".package(java.lang).file().tag(Object)");
    javaAnalyzerTestUseDef(ana, "F.this", ".package(a.b).file(<input>).tag(F)");
    javaAnalyzerTestUseDef(ana, "a.b.F.this", ".package(a.b).file(<input>).tag(F)");
    javaAnalyzerTestUseDef(ana, "F.super", ".package(java.lang).file().tag(Object)");
    javaAnalyzerTestUseDef(ana, "a.b.F.super", ".package(java.lang).file().tag(Object)");
    javaAnalyzerTestUseDef(ana, "this instanceof Object", "boolean");
  }
  
  public final void testJavaAnalyzer_visitPrimaryIdentifier() throws Exception {
    final File fileABQ = createTempFile(
        JavaEntities.TEMP_DIR, "a/b/Q.java", "package a.b;class Q{}");
    final File fileNOP = createTempFile(
        JavaEntities.TEMP_DIR, "n/o/P.java", "package n.o;class P{}");
    final File fileRST = createTempFile(
        JavaEntities.TEMP_DIR, "r/s/T.java", "package r.s;class T{}");
    final String fileABF = "package a.b;" + // .package(a.b).file(<input>)
        "import n.o.P;       " + //
        "import r.s.*;       " + //
        "class F {           " + // .F
        "  int h, i, j;      " + //
        "  void g(int h) {   " + // .method(g)(int h)
        "    int i, j;       " + //
        "    class L { }     " + //
        "    { int j; }      " + // .block(0)
        "    for (int q=0;;);" + //.forStatement(1)
        "  }                 " + //
        "  int k;            " + //
        "  final int l=2;    " + //
        "}                   " + //
        "class M { }         ";
    final GNode ast = JavaEntities.javaStringToAst("CompilationUnit", fileABF, true);
    final SymbolTable tab = new SymbolTable();
    final Runtime runtime = new Runtime();
    runtime.dir("in", Runtime.INPUT_DIRECTORY, true, "").setValue(Runtime.INPUT_DIRECTORY, JavaEntities.TEMP_DIR);
    final JavaAnalyzer ana = new JavaAnalyzer(runtime, tab);
    ana.dispatch(ast);
    JavaEntities.enterScopeByQualifiedName(tab,
        ".package(a.b).file(<input>).F.method(g)(int h).block(0)");
    javaAnalyzerTestUseDef(ana, "h", ".package(a.b).file(<input>).F.method(g)(int h).h");
    javaAnalyzerTestUseDef(ana, "i", ".package(a.b).file(<input>).F.method(g)(int h).i");
    javaAnalyzerTestUseDef(ana, "j", ".package(a.b).file(<input>).F.method(g)(int h).block(0).j");
    javaAnalyzerTestUseDef(ana, "k", ".package(a.b).file(<input>).F.k");
    javaAnalyzerTestUseDef(ana, "L", ".package(a.b).file(<input>).F.method(g)(int h).tag(L)");
    javaAnalyzerTestUseDef(ana, "F", ".package(a.b).file(<input>).tag(F)");
    javaAnalyzerTestUseDef(ana, "M", ".package(a.b).file(<input>).tag(M)");
    javaAnalyzerTestUseDef(ana, "P", ".package(n.o)."
        + JavaEntities.fileNameToScopeName(fileNOP.getAbsolutePath())
        + ".tag(P)");
    javaAnalyzerTestUseDef(ana, "Q", ".package(a.b)."
        + JavaEntities.fileNameToScopeName(fileABQ.getAbsolutePath())
        + ".tag(Q)");
    javaAnalyzerTestUseDef(ana, "T", ".package(r.s)."
        + JavaEntities.fileNameToScopeName(fileRST.getAbsolutePath())
        + ".tag(T)");
    javaAnalyzerTestUseDef(ana, "Object", ".package(java.lang).file().tag(Object)");
    javaAnalyzerTestUseDef(ana, "Runnable", ".package(java.lang).file().tag(Runnable)");
    javaAnalyzerTestUseDef(ana, "l", ".package(a.b).file(<input>).F.l");
    JavaEntities.enterScopeByQualifiedName(tab, ".package(a.b).file(<input>).F.method(g)(int h).forStatement(1)");
    javaAnalyzerTestUseDef(ana, "q", ".package(a.b).file(<input>).F.method(g)(int h).forStatement(1).q");
  }

  public final void testJavaAnalyzer_visitSelectionExpression()
      throws Exception {
    final String fileABF = "package a.b;" + // .package(a.b).file(<input>)
        "class F {          " + // .F
        "  static int g;    " + //
        "  void h() {       " + // .method(h)()
        "    F i;           " + //
        "    J l;           " + //
        "  }                " + //
        "}                  " + //
        "class J extends F {" + //
        "  static int k;    " + //
        "  J m;             " + //
        "}                  " + //
        "";
    final GNode ast = JavaEntities.javaStringToAst("CompilationUnit", fileABF, true);
    final SymbolTable tab = new SymbolTable();
    final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), tab);
    ana.dispatch(ast);
    JavaEntities.enterScopeByQualifiedName(tab,
        ".package(a.b).file(<input>).F.method(h)()");
    javaAnalyzerTestUseDef(ana, "i.g", ".package(a.b).file(<input>).F.g");
    javaAnalyzerTestUseDef(ana, "F.g", ".package(a.b).file(<input>).F.g");
    javaAnalyzerTestUseDef(ana, "l.k", ".package(a.b).file(<input>).J.k");
    javaAnalyzerTestUseDef(ana, "l.g", ".package(a.b).file(<input>).F.g");
    javaAnalyzerTestUseDef(ana, "l.g", ".package(a.b).file(<input>).F.g");
    javaAnalyzerTestUseDef(ana, "l.m", ".package(a.b).file(<input>).J.m");
    javaAnalyzerTestUseDef(ana, "l.m.g", ".package(a.b).file(<input>).F.g");
    javaAnalyzerTestUseDef(ana, "l.m.m", ".package(a.b).file(<input>).J.m");
    javaAnalyzerTestUseDef(ana, "l.m.m.g", ".package(a.b).file(<input>).F.g");
    javaAnalyzerTestUseDef(ana, "a.b", ".package(a).tag(b)");
    javaAnalyzerTestUseDef(ana, "a.b.F", ".package(a.b).file(<input>).tag(F)");
    javaAnalyzerTestUseDef(ana, "a.b.F.g", ".package(a.b).file(<input>).F.g");
    javaAnalyzerTestUseDef(ana, "a.b.J.g", ".package(a.b).file(<input>).F.g");
    javaAnalyzerTestUseDef(ana, "System.out", ".package(java.lang).file().System.out");
    javaAnalyzerTestUseDef(ana, "Character.Subset", ".package(java.lang).file().Character.tag(Subset)");
  }

  public final void testJavaAnalyzer_visitSubscriptExpression()
      throws Exception {
    final String fileABF = "package a.b;" + // .package(a.b).file(<input>)
        "class C {          " + // .C
        "  void d() {       " + // .method(d)()
        "    int[] e;       " + //
        "    int[][] f;     " + //
        "    float[][][] g; " + //
        "    final int[] h; " + //
        "    C[] i;         " + //
        "    String[] j;    " + //
        "  }                " + //
        "}                  " + //
        "";
    final GNode ast = JavaEntities.javaStringToAst("CompilationUnit", fileABF, true);
    final SymbolTable tab = new SymbolTable();
    final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), tab);
    ana.dispatch(ast);
    JavaEntities.enterScopeByQualifiedName(tab,
        ".package(a.b).file(<input>).C.method(d)()");
    javaAnalyzerTestUseDef(ana, "e[0]", "int");
    javaAnalyzerTestUseDef(ana, "f[0][0]", "int");
    javaAnalyzerTestUseDef(ana, "f[0]", "int[]");
    javaAnalyzerTestUseDef(ana, "g[100]", "float[][]");
    javaAnalyzerTestUseDef(ana, "h[100]", "int");
    javaAnalyzerTestUseDef(ana, "i[2]", ".package(a.b).file(<input>).tag(C)");
    javaAnalyzerTestUseDef(ana, "j[12]", ".package(java.lang).file().tag(String)");
  }
  
  public final void testJavaEntities_nestingClassification() throws Exception {
    assertTrue(JavaEntities.isScopeTopLevel(".package(a.b).file()"));
    assertTrue(JavaEntities.isScopeTopLevel(".package(a.b).file(<input>)"));
    assertFalse(JavaEntities.isScopeTopLevel(".package(a.b)"));
    assertFalse(JavaEntities.isScopeTopLevel(".package(a.b).file().x"));
    assertFalse(JavaEntities.isScopeTopLevel(".package(a.b).file(<input>).y"));
    assertFalse(JavaEntities.isScopeTopLevel(".package(a.b).file().c.d.e"));
    assertFalse(JavaEntities.isScopeNested(".package(a.b)"));
    assertFalse(JavaEntities.isScopeNested(".package(a.b).file()"));
    assertTrue(JavaEntities.isScopeNested(".package(a.b).file().a"));
    assertTrue(JavaEntities.isScopeNested(".package(a.b).file().a.b"));
    assertFalse(JavaEntities.isScopeNested(".package(a.b).file(Foo)"));
    assertTrue(JavaEntities.isScopeLocal(".package(a.b).file(Foo).A.method(f())"));
    assertFalse(JavaEntities.isScopeLocal(".package(a.b).file(Foo).A.F"));
    assertTrue(JavaEntities.isScopeForMember(".package(a.b).file(Foo).A.F"));
    assertFalse(JavaEntities.isScopeForMember(".package(a.b).file(Foo).A.method(f())"));
    final String fileABF = "package a.b;" + // .package(a.b).file(<input>)
        "class C {          " + // .package(a.b).file(<input>).C
        "  class D {}       " + // .package(a.b).file(<input>).C.D
        "  static class E {}" + // .package(a.b).file(<input>).C.E
        "  void f() {       " + // .package(a.b).file(<input>).C.method(f)()
        "    class G {      " + // .package(a.b).file(<input>).C.method(f)().G
        "      class H {}   " + // .package(a.b).file(<input>).C.method(f)().G.H
        "    }              " + //
        "  }                " + //
        "  interface I {}   " + // .package(a.b).file(<input>).C.I
        "}                  " + //
        "";
    final GNode ast = JavaEntities.javaStringToAst("CompilationUnit", fileABF, true);
    final SymbolTable tab = new SymbolTable();
    final JavaAnalyzer ana = new JavaAnalyzer(newRuntime(), tab);
    ana.dispatch(ast);
    JavaEntities.enterScopeByQualifiedName(tab, ".package(a.b).file(<input>)");
    final ClassT c = (ClassT)tab.lookup(".package(a.b).file(<input>).tag(C)");
    assertTrue(JavaEntities.isTypeTopLevel(c));
    final ClassT d = (ClassT)tab.lookup(".package(a.b).file(<input>).C.tag(D)");
    assertTrue(JavaEntities.isTypeMember(d));
    assertFalse(JavaEntities.isTypeLocal(d));
    assertTrue(JavaEntities.isTypeInner(d));
    final ClassT e = (ClassT)tab.lookup(".package(a.b).file(<input>).C.tag(E)");
    assertTrue(JavaEntities.isTypeMember(e));
    assertFalse(JavaEntities.isTypeInner(e));
    final ClassT g = (ClassT)tab.lookup(".package(a.b).file(<input>).C.method(f)().tag(G)");
    assertTrue(JavaEntities.isTypeLocal(g));
    assertTrue(JavaEntities.isTypeInner(g));
    assertTrue(JavaEntities.isTypeNested(g));
    assertTrue(JavaEntities.isTypeNamed(g));
    assertFalse(JavaEntities.isTypeMember(g));
    final ClassT h = (ClassT)tab.lookup(".package(a.b).file(<input>).C.method(f)().G.tag(H)");
    assertTrue(JavaEntities.isTypeMember(h));
    assertTrue(JavaEntities.isTypeInner(h));
    final InterfaceT i = (InterfaceT)tab.lookup(".package(a.b).file(<input>).C.tag(I)");
    assertTrue(JavaEntities.isTypeMember(i));
    assertTrue(JavaEntities.isTypeNested(i));
    assertFalse(JavaEntities.isTypeInner(i));
  }

  public final void testJavaExternalAnalyzer_visitCompilationUnit()
      throws Exception {
    final JavaExternalAnalyzer ana = newJavaExternalAnalyzer();
    ana.dispatch(JavaEntities.javaStringToAst("CompilationUnit",
        "package a.b;class C{class D{E f;}}", true));
    final SymbolTable table = ana._table;
    final PackageT ab = (PackageT) table.lookup(".package(a).tag(b)");
    assertEquals("a.b", ab.getName());
    final ClassT abc = (ClassT) table.lookup(".package(a.b).file(<input>).tag(C)");
    JavaEntities.enterScopeByQualifiedName(table, ".package(a.b).file(<input>)");
    assertEquals(
        contractSpace("class a.b.C{C()->void; class a.b.C.D{field(E,f); D()->void;};}"),
        contractSpace(JavaEntities.typeDeclString(ana._table, abc)));
    final ClassT abcd = (ClassT) table.lookup(".package(a.b).file(<input>).C.tag(D)");
    assertEquals(contractSpace("class a.b.C.D{field(E,f);D()->void;}"),
        contractSpace(JavaEntities.typeDeclString(ana._table, abcd)));
  }

  public final void testJavaExternalAnalyzer_visitImportDeclaration()
      throws Exception {
    final JavaExternalAnalyzer ana = newJavaExternalAnalyzer();
    ana.dispatch(JavaEntities.javaStringToAst("CompilationUnit",
        "package a.b;import c.*;import d.e;import f.g.*;", true));
    final SymbolTable table = ana._table;
    final List imports = (List) table.lookup(".package(a.b).file(<input>).imports(*)");
    assertEquals(imports.size(), 2);
    assertEquals(((PackageT) imports.get(0)).getName(), "c");
    assertEquals(((PackageT) imports.get(1)).getName(), "f.g");
    final AliasT de = (AliasT) table
        .lookup(".package(a.b).file(<input>).tag(e)");
    assertEquals(de.getName(), "d.e");
  }
}
