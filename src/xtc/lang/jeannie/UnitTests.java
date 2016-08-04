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

import java.io.StringWriter;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import xtc.lang.JavaEntities;
import xtc.lang.JavaUnitTests;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Printer;
import xtc.type.Type;
import xtc.util.Runtime;
import xtc.util.SymbolTable;

/**
 * JUnit tests for classes in package xtc.lang.jeannie.
 * 
 * This class is a good place to quickly try a method on some simple
 * inputs. The test cases also document how to use certain API and
 * what it does.
 * 
 * To run from the console, set your CLASSPATH to include
 * $JAVA_DEV_ROOT/classes and junit.jar, then run
 * 
 *   java -ea junit.textui.TestRunner xtc.lang.jeannie.UnitTests
 *
 * Or, to run from within eclipse, Run -> Run ... -> JUnit -> New, and
 * specify xtc.lang.jeannie.UnitTests.
 * 
 * @author Martin Hirzel
 * @version $Revision: 1.35 $
 */
public final class UnitTests extends TestCase {
  static final class JeannieAnalyzerTestError extends JavaUnitTests.IgnorableTest {
    private final String _expected;
    private final String _input;
    private final String _language;
    private final String _production;
    JeannieAnalyzerTestError(final boolean ignore, final String production, final String language,
        final String input, final String expected) {
      super(ignore);
      _expected = expected;
      _input = input;
      _language = language;
      _production = production;
    }
    public void runTestIgnorable() throws Exception {
      final Analyzer ana = new Analyzer(Utilities.newRuntime(), new SymbolTable(), _language);
      if (!"File".equals(_production) && !"CompilationUnit".equals(_production) && !"TranslationUnit".equals(_production))
        JavaUnitTests.enterPackageFile(ana._table, "", "<input>");
      UnitTests.jeannieAnalyzerTestError(_production, _language, _input, _expected, ana);
    }
  }

  static final class JeannieCodeGeneratorTest extends JavaUnitTests.IgnorableTest {
    private final String _cExpected;
    private final String _input;
    private final String _javaExpected;
    private final String _language;
    private final String _production;
    JeannieCodeGeneratorTest(final boolean ignore, final String production, final String language,
        final String input) {
      super(ignore);
      _cExpected = null;
      _input = input;
      _javaExpected = null;
      _language = language;
      _production = production;
    }
    JeannieCodeGeneratorTest(final boolean ignore, final String production, final String language,
        final String input, final String cExpected, final String javaExpected) {
      super(ignore);
      _cExpected = cExpected;
      _input = input;
      _javaExpected = javaExpected;
      _language = language;
      _production = production;
    }
    public void runTestIgnorable() throws Exception {
      final GNode ast = Utilities.jeannieStringToAst(_production, _language, _input);
      final Runtime runtime = Utilities.newRuntime();
      final SymbolTable tab = new SymbolTable();
      final Analyzer ana = new Analyzer(runtime, tab, _language);
      ana.dispatch(ast);
      final CodeGenerator codeGenerator = new CodeGenerator(runtime, tab);
      final CodeGenerator.Out out = (CodeGenerator.Out)codeGenerator.dispatch(ast);
      assertTrue(null == out._cExternalDeclarations && null == out._cMembers && null == out._javaMembers);
      final String cCode = Utilities.cAstToString(out._cNode);
      final String javaCode = Utilities.javaAstToString(out._javaNode);
      assrtEquals(_cExpected, cCode);
      assrtEquals(_javaExpected, javaCode);
    }
  }
  
  static class JeannieParserTest extends JavaUnitTests.IgnorableTest {
    private final String _expected;
    private final String _input;
    private final String _language;
    private final String _production;
    JeannieParserTest(final boolean ignore, final String production, final String language, final String input) {
      super(ignore);
      _expected = input;
      _input = input;
      _language = language;
      _production = production;
    }
    public void runTestIgnorable() throws Exception {
      UnitTests.jeannieParserTestRoundTrip(_production, _language, _input, _expected, false);
      UnitTests.jeannieParserTestRoundTrip(_production, _language, _input, _expected, true);
    }
  }
  
  static void assrtEquals(final String expected, final String actual) {
    if (null == expected)
      return;
    final String e = JavaUnitTests.contractSpace(expected);
    final String a = JavaUnitTests.contractSpace(actual);
    if (e.equals(a))
      return;
    assertEquals(e, a);
  }

  static void jeannieAnalyzerTestError(final String production, final String language, final String input, 
      final String expected, final Analyzer ana) throws Exception {
    final StringWriter stringWriter = new StringWriter();
    ana._runtime.setErrConsole(new Printer(stringWriter));
    final GNode ast = Utilities.jeannieStringToAst(production, language, input);
    ana.dispatch(ast);
    final String output = trimAnalyzerOutput(stringWriter.toString());
    assrtEquals(expected, output);
  }

  static String trimAnalyzerOutput(String output) {
    output = JavaUnitTests.stripPrefix(output, "error:");
    final int warningPos = output.indexOf("warning:");
    if (-1 != warningPos)
      output = output.substring(warningPos);
    output = JavaUnitTests.stripSuffix(output, "\n");
    output = output.trim();
    return output;    
  }
  
  static void jeannieParserTestRoundTrip(final String production, final String language,
      final String input, final String expected, final boolean simple)
      throws Exception {
    final String unescaped = JavaEntities.unicodeUnescape(input);
    final GNode ast = Utilities.jeannieStringToAst(production, language, unescaped, simple);
    final String result = Utilities.jeannieAstToString(ast, language);
    final String exp = JavaUnitTests.contractSpace(JavaEntities.unicodeUnescape(expected));
    assrtEquals(exp, result);
  }

  private static TestSuite makeSuiteJeannieAnalyzerError() {
    final TestSuite s = new TestSuite();
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{double y; }class A{int x=`y;}", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{enum e{a,b}y; }class A{int x=`y;}", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{enum e{a,b}y; }class A{long x=`y;}", "warning: converting C type 'annotated(enum e)' to Java type 'long'"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{float y;}class A{double x=`y;}", "warning: converting C type 'annotated(float)' to Java type 'double'"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{float y;}class A{float x=`y;}", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{float y;}class A{int x=`y;}", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{int i=0;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{int i=\"s\";}", "initializer for 'i' makes integer from pointer without a cast"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{int y;}class A{int x=`&y;}", "illegal C type 'annotated(pointer(int))' in Java expression"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{int y;}class A{int x=`y;}", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{int y;}class A{long x=`y;}", "warning: converting C type 'annotated(int)' to Java type 'long'"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{int y[5];}class A{int x=`y;}", "illegal C type 'annotated(array(int, 5))' in Java expression"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{int* y;}class A{int x=`y;}", "illegal C type 'annotated(pointer(int))' in Java expression"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{long double y;}class A{int x=`y;}", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{long long y;}class A{int x=`y;}", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{struct s{}y;}class A{int x=`y;}", "illegal C type 'annotated(struct s)' in Java expression"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef float jfloat; float y; }class A{float x=`y;}", "warning: converting C type 'annotated(float)' to Java type 'float'"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef float jfloat; jfloat y; }class A{float x=`y;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;typedef char jbyte;typedef int jint;extern int printf(__const char*__restrict __format,...);}class Main{public static void main(String[]args){String js=\"abc\";`{jbyte*bs;_with(bs=`js){printf(\"%*s\\n\",bs,`js.length());}}}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;typedef int jintArray;}class A{native int[]f()`{jintArray a;return a;}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;typedef void* jstring;}class A{native void f()`{jstring s=_newJavaString(123);}}", "expected pointer to char, `byte, or `char"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;typedef void* jstring;}class A{native void f()`{jstring s=_newJavaString(\"hi\");}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;void f(JNIEnv*env){`{{System.out.println();}}}}class A{}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;void f(JNIEnv*env){`{try{}catch(Error e){}}}}class A{}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;}class A{int f(){int i;return `i;}}", "cannot use Java entity 'i' in C context"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;}class A{int f(){return env;}}", "cannot use C entity 'env' in Java context"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;}class A{int f(int i){return `i;}}", "cannot use Java entity 'i' in C context"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;}class A{int i;int f(){return `i;}}", "cannot use Java entity 'i' in C context"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;}class A{native void f()`{JNIEnv* e=env;}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;}class A{native void f(int env)`{}}", "formal parameter declaration of 'env' conflicts with implicit JNIEnv pointer"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int jint; int y; }class A{int x=`y;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int jint; jint i=0; typedef void* JNIEnv;} class A { int f(){return `i;} } ", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int jint; long y; }class A{long x=`y;}", "warning: converting C type 'annotated(long)' to Java type 'long'"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef long jint; long y; }class A{int x=`y;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef unsigned char jboolean;jboolean b;}class A{boolean x=`b;} ", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef unsigned char jboolean;}class A{boolean x=`((jboolean)(2<3));} ", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef unsigned char jboolean;}class A{boolean x=`(2<3);} ", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void(*FP)(int);void g(FP fp){}void h(int i){}void f(){g(h);}}class A{}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void* JNIEnv;typedef int jint;}class A{int f(){return `((jint)env);}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void* JNIEnv;}class A{native Exception f()`{return 123;}}", "return type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void* JNIEnv;}class A{native int f()`{return;}}", "'return' with no value, in method returning non-void")); 
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void* JNIEnv;}class A{native void f()`{}}", "")); 
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void* JNIEnv;}class A{void f(){if(true)`{int*p=0;}}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void* JNIEnv;}class A{void f(){if(true)`{int*p=3;}}}", "initializer for 'p' makes pointer from integer without a cast")); 
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void*JNIEnv;typedef int jint;extern int printf(__const char* __restrict __format, ...);}class A{static native void f()`{jint a=0,b=0;b=`(1+`((jint)(a=1)));printf(\"%d,%d\\\\n\",a,b);}public static void main(String[]args){f();}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void*JNIEnv;typedef int jint;}class A{native int f()`{return (jint)1000;}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void*JNIEnv;typedef int jint;}class A{public static void main(String args[]){int a=0,b=0;b=`((jint)(1+`(a=1)));System.out.println(a+\",\"+b);}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void*JNIEnv;}class Main{native void f()`{int a[1]={3+5};}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef void*JNIEnv;}class Main{native void f()`{int a[1]={3};}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{union u{}y;}class A{int x=`y;}", "illegal C type 'annotated(union u)' in Java expression"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{unsigned y;}class A{int x=`y;}", "initializer type mismatch"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{}class A extends B {}", "unknown class or interface B"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{}class A{native void f();}", "methods should be abstract iff they have no body")); 
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{}class A{native void f()`{}}", "C typedef for 'JNIEnv' missing; did you forget to #include <jni.h>?"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{}class A{native void f(){}}", "methods should be native iff their body is in C"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{}class A{static{String b=\"x\";b=\"y\";}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{}class A{}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.Java{import java.util.*;}typedef int JNIEnv;typedef void* jobject;jobject f(JNIEnv*env){return `((Vector)null);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.Java{import java.util.Vector;}int i=`0;", "C typedef for 'jint' missing; did you forget to #include <jni.h>?"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.Java{import java.util.Vector;}typedef int JNIEnv;typedef int jint;int f(JNIEnv*env){return `0;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.Java{import java.util.Vector;}typedef int JNIEnv;typedef void* jobject;jobject f(JNIEnv*env){return `((Vector)null);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`Exception e;", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "int f(){return 123;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "int i;void f(){_cancel i;}", "no enclosing _with statement for 'i'"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "int i;void f(){_commit i;}", "no enclosing _with statement for 'i'"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "package p;`.C{typedef int JNIEnv;void printf(char*);void fflush(int);int stdout;void f(JNIEnv*env){printf(\"f 1\\n\");fflush(stdout);`p.Main.g();printf(\"f 2\\n\");fflush(stdout);}}public class Main{public static void g(){System.out.println(\"Main.g\");System.out.flush();}public static void main(String[]args){System.out.println(\"Main.main 1\");System.out.flush();`f(env);System.out.println(\"Main.main 2\");System.out.flush();}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef char jboolean;typedef int jintArray;void f(){jboolean* ca;_with(ca=`new int[5]){}}", "type 'jint*' expected"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef double jdouble;jdouble f(JNIEnv*env){return `1.5;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef int jboolean;typedef int jbooleanArray;void f(JNIEnv*env){jboolean* ca;_with(ca=`new boolean[5]){}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef int jboolean;typedef int jobjectArray;void f(JNIEnv*env){jboolean* ca;_with(ca=`new String[5]){}}", "type 'jobject*' expected"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef int jint;int f(JNIEnv*env)`{return 123;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef int jint;typedef void* jintArray;void f(JNIEnv*env){jint* ca;_copyFromJava(ca, 0, `new int[5], 0, 3);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef int jint;typedef void* jintArray;void f(JNIEnv*env){jint* ca;_copyFromJava(ca, 0, `new int[5], 3-1, 2);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef int jint;typedef void* jintArray;void f(JNIEnv*env){jint* ca;_copyFromJava(ca, 0, `new int[5], 3.1, 3);}", "invalid operand where integer required"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef int jint;typedef void* jintArray;void f(JNIEnv*env){jint* ca;_with(ca=`new int[5]){_cancel ca;}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef int jint;typedef void* jintArray;void f(JNIEnv*env){jint* ca;_with(ca=`new int[5]){_commit ca;}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jobject;int f(JNIEnv*env){return `null;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jobject;jobject f(JNIEnv*env){return `((Vector)null);}", "unknown class or interface Vector"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jobject;jobject f(JNIEnv*env){return `null;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jobject;typedef jobject jthrowable;jobject f(JNIEnv*env){return `new Exception();}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;jstring f(JNIEnv*env){return `\"hi\";}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;jstring f(JNIEnv*env){return `new String(1,2,3,4,5);}", "could not find constructor"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;typedef char jbyte;void f(JNIEnv*env){jbyte* ca;_with(ca=`\"abc\"){}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;typedef int jchar;typedef int jint;void f(JNIEnv*env){jchar* ca;_copyFromJava(ca, 0, `\"abc\", 0, 3);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;typedef int jchar;void f(JNIEnv*env){jchar* ca;_copyToJava(`\"abc\", 0, ca, 0, 3);}", "_copyToJava target must not be String"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;typedef int jchar;void f(JNIEnv*env){jchar* ca;_with(ca=`'a'){}}", "string or primitive array expected"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;typedef int jchar;void f(JNIEnv*env){jchar* ca;_with(ca=`(new Object().toString())){}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;typedef int jchar;void f(JNIEnv*env){jchar* ca;_with(ca=`\"abc\"){}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;void f(JNIEnv*env){int* ca;_with(ca=`\"abc\"){}}", "type 'jchar*' or 'jbyte*' expected"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jstring;void f(JNIEnv*env,jstring s)`{throw new Error(`s);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jthrowable;jthrowable f(JNIEnv*env){return `((Exception)null);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;typedef void* jthrowable;jthrowable f(JNIEnv*env){return `new Exception();}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env)`throws Exception{`throw new Exception();}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env)`throws Exception{}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env)`throws Exception{}void g(){f(0);}", "uncaught exception"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env)`throws Object{}", "throwable expected"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env)`throws RuntimeException{}void g(){f(0);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env)`throws java.io.FileNotFoundException, java.io.EOFException{}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env)`throws java.io.IOException{}void g(JNIEnv*env)`throws Exception{f(env);}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env)`{throw new Error();}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env){`Exception x,y;x=y;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env){`Object x;`Exception y;x=y;}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env){`Object x;`Exception y;y=x;}", "illegal C assignment to Java type 'java.lang.Exception'"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env){`throw new Exception();}", "uncaught exception"));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env){`try`{`throw new Exception();}catch(Exception e){}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env){`{String s=\"hi\";}}", ""));
    s.addTest(new JeannieAnalyzerTestError(false, "File", null, "typedef int JNIEnv;void f(JNIEnv*env){int* x;`Object y;`{y=x;}}", "cannot use C entity 'y' in Java context"));
    return s;
  }
  
  private static TestSuite makeSuiteJeannieCodeGenerator() {
    final TestSuite s = new TestSuite();
    s.addTest(new JeannieCodeGeneratorTest(false, "File" /* 000 hello world */, null, "`.C{typedef void* JNIEnv;extern int printf(__const char *__restrict __format,...);}class Main{static native void sayHi()`{printf(\"Hello world!\\n\");}public static void main(String[]args){sayHi();}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", /* 013 _with */ null, "`.C{typedef void* JNIEnv;typedef int jint;typedef char jboolean;typedef void* jintArray;}class Main{static native int sum(int[] ja)`{int i,n;jint* ca,s;n=`ja.length;s=0;_with(ca=`ja){for(i=0;i<n;i++)s+=ca[i];_cancel ca;}return s;}public static void main(String[] args){int[] a ={3,1,4};System.out.println(\"expected 8,got \" + sum(a));}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", /* 027 C function */ null, "`.C{typedef void* JNIEnv;struct L{struct L* x;};}class A{native void f()`{struct L* y=0;}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;typedef char jbyte;typedef int jint;typedef void* jstring;typedef char jboolean;extern int printf(__const char*__restrict __format,...);}class Main{public static void main(String[]args){String js=\"abc\";`{jbyte*bs;_with(bs=`js){printf(\"%*s\\n\",bs,`js.length());}}}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;typedef int jint;struct s{int i;}g;}class A{void f(){int j=`g.i;}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;typedef int jlong;}class A{native int f()`{switch(0){case 0:``((jlong)1);}}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;typedef int jstring;}class A{void f(){throw new Error(`_newJavaString(\"boo\"));}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;typedef void* jstring;}class A{native void f()`{jstring s=_newJavaString(\"hi\");}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;void f(JNIEnv*env){`{int i;i=1;}}}class A{}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;void f(JNIEnv*env){`{int i;i=1;}}}class A{}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int jint;jint i=42;typedef void* JNIEnv;}class A{void f(){int j=0;j=`i;}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef void* JNIEnv;}class A{void f(){}}", "typedef void* JNIEnv;", "class A{void f(){}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{}class A{}", "", "class A{}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File",/* 002 callStatic */ null, "`.C{typedef void* JNIEnv;typedef int jint;extern int printf(__const char *__restrict __format,...);}class Main{native static void foo()`{int y;y=`Math.max(123,456);printf(\"return value: %d\\n\",y);}public static void main(String[]args){foo();}}"));
    s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "package p;`.C{typedef int JNIEnv;void printf(char*);void fflush(int);int stdout;void f(JNIEnv*env){printf(\"f 1\\n\");fflush(stdout);`p.Main.g();printf(\"f 2\\n\");fflush(stdout);}}public class Main{public static void g(){System.out.println(\"Main.g\");System.out.flush();}public static void main(String[]args){System.out.println(\"Main.main 1\");System.out.flush();`f(env);System.out.println(\"Main.main 2\");System.out.flush();}}"));
    return s;
  }
  
  private static TestSuite makeSuiteJeannieParser() {
    final TestSuite s = new TestSuite();
    s.addTest(new JeannieParserTest(false, "Block", "Java", "`{int i = &a; someCFunction(i);}"));
    s.addTest(new JeannieParserTest(false, "Block", "Java", "{int i = a >>> 3; someJavaMethod(i);}"));
    s.addTest(new JeannieParserTest(false, "CompoundStatement", "C", "`{int i = a >>> 3; someJavaMethod(i);}"));
    s.addTest(new JeannieParserTest(false, "CompoundStatement", "C", "{int i = &a; someCFunction(i);}"));
    s.addTest(new JeannieParserTest(false, "File" /* 000 hello world */, null, "`.C{extern int printf(__const char *__restrict __format, ...);}class Main{static native void sayHi() `{printf(\"Hello world!\\n\");}public static void main(String[]args){sayHi();}}"));
    s.addTest(new JeannieParserTest(false, "File" /* 001 pure Java hello world */ , null, "`.C{}class Main{public static void main(String[]args){System.out.println(\"Hello, world\");}}"));
    s.addTest(new JeannieParserTest(false, "File" /* 002 callStatic */, null, "`.C{extern int printf(__const char *__restrict __format, ...);}class Main{native static void foo() `{int y; y = `Math.max(123, 456); printf(\"return value: %d\\n\", y);}public static void main(String[] args){foo();}}"));
    s.addTest(new JeannieParserTest(false, "File", null, ""));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{extern int printf(__const char*__restrict __format,...);}class Main{static native void f(int[]ja)throws Exception`{int i;jint*ca;_with(ca=`ja){for(i=0;i<3;i++){if(ca[i]==4)`throw new Exception();printf(\"p0 (%d:%d)\\n\",i,ca[i]);}printf(\"p1\\n\");_commit ca;}printf(\"p2\\n\");}public static void main(String[]args){int[]a={3,1,4};try{f(a);System.out.println(\"p3\");}catch(Exception e){System.out.println(\"p4\");}}}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{typedef int jint; jint i=0;}class A{int f(){return `&i;}}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{typedef int jint; jint i=0;}class A{int f(){return `((jint)&i);}}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{typedef int jint; jint i=0;}class A{int f(){return `(i+2);}}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{typedef int jint;}class Main{static native int sum(int[] ja)`{jint *ca,s;int i,n;s=0;n=`ja.length;_with(ca=`ja){for(i=0;i<n;i++)s+=ca[i];_cancel ca;}return s;}public static void main(String[]args){int[] a={3,1,4};System.out.println(\"expected 8, got \"+sum(a));}}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{} class A{int f(){return `(1+2);}}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{} class A{void f(){int x=0;}}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{} class A{} "));
    s.addTest(new JeannieParserTest(false, "File", null, "`.C{}class A{native void f()`{}}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.Java{import java.util.Vector;}int f(){}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.Java{}"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.Java{}`java.lang.Integer i;"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.Java{}const `java.lang.Integer *i[10];"));
    s.addTest(new JeannieParserTest(false, "File", null, "`.Java{}int f()`throws E{}"));
    s.addTest(new JeannieParserTest(false, "JeannieC$ConditionalExpression", "C", "1+2"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "_cancel a;"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "_commit a;"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "_copyFromJava(ca, 0, `ja, 0, 2);"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "_copyToJava(`ja, 0, ca, 0, `ja.length-1);"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "_with(ca=`ja){}"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "_with(ca=`new int[123]){}"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "_with(ca=ja){ca[0]=3;}"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "_with(ca=ja){}"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "`synchronized(m){}"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "`throw new E();"));
    s.addTest(new JeannieParserTest(false, "JeannieC$Statement", "C", "`try{}catch(E e){}"));
    s.addTest(new JeannieParserTest(false, "JeannieC$UnaryExpression", "C", "`(x >>> 3)"));
    s.addTest(new JeannieParserTest(false, "JeannieC$UnaryExpression", "C", "`x"));
    s.addTest(new JeannieParserTest(false, "JeannieJava$Declaration", "Java", "A b(C d,E[]f){}"));
    s.addTest(new JeannieParserTest(false, "JeannieJava$Expression", "Java", "(a==++b.c(1)[d.e()][2].f&g)-h"));
    s.addTest(new JeannieParserTest(false, "JeannieJava$Expression", "Java", "`&x"));
    s.addTest(new JeannieParserTest(false, "JeannieJava$Expression", "Java", "`(1?2:3)"));
    s.addTest(new JeannieParserTest(false, "JeannieJava$Expression", "Java", "new A[][]{{b,c},{d,e}}"));
    return s;
  }

  public static Test suite() {
    final TestSuite s = new TestSuite();
    if (false) { //TD 00 quick test-bed
      s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;typedef int jint;int f(JNIEnv*env)`{return 0;}}class A{}"));
      //s.addTest(new JeannieAnalyzerTestError(false, "File", null, "`.C{typedef int JNIEnv;}class A{}", ""));
      //s.addTest(new JeannieCodeGeneratorTest(false, "File", null, "`.C{typedef int JNIEnv;}class A{}"));
    } else {
      s.addTestSuite(xtc.lang.jeannie.UnitTests.class);
      s.addTest(makeSuiteJeannieCodeGenerator());
      s.addTest(makeSuiteJeannieAnalyzerError());
      s.addTest(makeSuiteJeannieParser());
      s.addTest(JavaUnitTests.suite());
    }
    return s;
  }

  private void addJniTypedefs(final Runtime runtime, final SymbolTable tab) {
    final StringBuffer defs = new StringBuffer();
    defs.append("typedef int jint;");
    defs.append("typedef long jlong;");
    defs.append("typedef void* jobject;");
    defs.append("typedef jobject jintArray;");
    defs.append("typedef jobject jobjectArray;");
    final GNode builtins = Utilities.jeannieStringToAst("CompilationUnit", "Java", "`.C{" + defs + "}class A{}");
    new Analyzer(runtime, tab, null).dispatch(builtins);
  }
  
  public final void testJeannieParser_pFile() throws Exception {
    final GNode ast = Utilities.jeannieStringToAst("File", null,
        "`.C{} class A { }", false);
    final String out = Utilities.jeannieAstToString(ast, null);
    if (false)
      System.out.println(out);
  }

  public final void testJeannieUtil_cAstToString() throws Exception {
    for (final String s : new String[]{ "{}", "{int*i,j=2+2,(*k)[5];}" }) {
      final GNode ast = Utilities.cStringToAst("CompoundStatement", s);
      assertEquals(s, JavaUnitTests.contractSpace(Utilities.cAstToString(ast)));
    }
  }
  
  public final void testJeannieUtil_containsCCode() throws Exception {
    assertFalse(Utilities.containsJavaToCTransition(Utilities.jeannieStringToAst("JavaInJavaBlock", "java", "{}")));
	assertTrue(Utilities.containsJavaToCTransition(Utilities.jeannieStringToAst("JavaInJavaBlock", "java", "{`{}}")));
    assertFalse(Utilities.containsJavaToCTransition(Utilities.jeannieStringToAst("JavaInJavaBlock", "java", "{int i = 2;}")));
    assertTrue(Utilities.containsJavaToCTransition(Utilities.jeannieStringToAst("JavaInJavaBlock", "java", "{int i = 3.5 * `(2 + 2);}")));
  }

  public final void testJeannieUtil_cTypeToJavaType() throws Exception {
    final Runtime runtime = Utilities.newRuntime();
    final SymbolTable tab = new SymbolTable();
    addJniTypedefs(runtime, tab);
    assertEquals("int", JavaEntities.javaTypeToString(tab, Utilities.cTypeToJavaType(tab, runtime, null, Utilities.cStringToType("char"))));
    assertEquals("long", JavaEntities.javaTypeToString(tab, Utilities.cTypeToJavaType(tab, runtime, null, Utilities.cStringToType("long"))));
  }
  
  public final void testJeannieUtil_cTypeToString() throws Exception {
    for (final String s : new String[]{ "int", "int*", "int[]", "int(*)[3]", "struct s***" }) {
      final Type type = Utilities.cStringToType(s);
      assertEquals(s, JavaUnitTests.contractSpace(Utilities.cTypeToString(type)));
    }
    assertEquals("struct t", JavaUnitTests.contractSpace(Utilities.cTypeToString(Utilities.cStringToType("struct t{int i;}"))));
    assertEquals("int(*p)[3]", JavaUnitTests.contractSpace(Utilities.cTypeToString(Utilities.cStringToType("int(*)[3]"), "p")));
  }
  
  public final void testJeannieUtil_javaTypeToApiType() {
    assertEquals("int", Utilities.javaTypeToApiType(JavaEntities.javaStringToType("int")));
    assertEquals("Object", Utilities.javaTypeToApiType(JavaEntities.javaStringToType("int[][]")));
    assertEquals("intArray", Utilities.javaTypeToApiType(JavaEntities.javaStringToType("int[]")));
    assertEquals("boolean", Utilities.javaTypeToApiType(JavaEntities.javaStringToType("boolean")));
    assertEquals("Object", Utilities.javaTypeToApiType(JavaEntities.javaStringToType("String")));
  }

  public final void testJeannieUtil_javaTypeToCType() throws Exception {
    final Runtime runtime = Utilities.newRuntime();
    final SymbolTable tab = new SymbolTable();
    addJniTypedefs(runtime, tab);
    assertEquals("jint", Utilities.cTypeToString(Utilities.javaTypeToCType(tab, runtime, null, JavaEntities.javaStringToType("int"), false)));
    assertEquals("jintArray", Utilities.cTypeToString(Utilities.javaTypeToCType(tab, runtime, null, JavaEntities.javaStringToType("int[]"), false)));
    assertEquals("jobjectArray", Utilities.cTypeToString(Utilities.javaTypeToCType(tab, runtime, null, JavaEntities.javaStringToType("int[][]"), false)));
    assertEquals("jobject", Utilities.cTypeToString(Utilities.javaTypeToCType(tab, runtime, null, JavaEntities.javaStringToType("Object"), false)));
  }

  public final void testJeannieUtil_javaTypeToString() {
    for (final String s : new String[]{ "int", "int[][]", "java.lang.Object", "java.io.Writer[]" }) {
      final Type type = JavaEntities.javaStringToType(s);
      assertEquals(s, JavaEntities.javaTypeToString(null, type));
    }
    assertEquals("java.lang.Object", JavaEntities.javaTypeToString(null, JavaEntities.javaStringToType("Object")));
  }
  
  public final void testJeannieUtil_jniMangledName() {
    assertEquals("a_b_C", Utilities.jniMangledName("a.b.C"));
    assertEquals("C_1x", Utilities.jniMangledName("C_x"));
    assertEquals("java_lang_Object", Utilities.jniMangledName("java.lang.Object"));
    assertEquals("java_lang_String", Utilities.jniMangledName(null, JavaEntities.javaStringToType("java.lang.String")));
  }
}
