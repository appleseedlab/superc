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
package xtc.lang.blink;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import xtc.lang.JavaUnitTests;
import xtc.tree.GNode;
import xtc.tree.Node;

/**
 * JUnit tests for classes in package xtc.lang.blink.
 * 
 * This class is a good place to quickly try a method on some simple
 * inputs. The test cases also document how to use certain API and
 * what it does.
 * 
 * To run from the console, set your CLASSPATH to include
 * $JAVA_DEV_ROOT/classes and junit.jar, then run
 * 
 *   java -ea junit.textui.TestRunner xtc.lang.blink.UnitTests
 *
 * Or, to run from within eclipse, Run -> Run ... -> JUnit -> New, and
 * specify xtc.lang.blink.UnitTests.
 * 
 * @author Martin Hirzel
 * @version $Revision: 1.2 $
 */
public final class UnitTests extends TestCase {
  static final class BlinkDebuggerAnalyzerTest extends JavaUnitTests.IgnorableTest {
    private final String _expected;
    private final String _input;
    private final String _language;
    BlinkDebuggerAnalyzerTest(final boolean ignore, final String language,
        final String input, final String expected) {
      super(ignore);
      _expected = expected;
      _input = input;
      _language = language;
    }
    public void runTestIgnorable() throws Exception {
      final CommandAstAnalyzer ana = new CommandAstAnalyzer(Utilities.newRuntime());//, Utilities.debuggerNewSymbolMapper());
      UnitTests.debuggerAnalyzerTestError(_language, _input, _expected, ana);
    }
  }

  static final class BlinkDebuggerParserTest extends JavaUnitTests.IgnorableTest {
    private final String _expected;
    private final String _input;
    private final String _language;
    BlinkDebuggerParserTest(final boolean ignore, final String language, final String input) {
      super(ignore);
      _expected = input;
      _input = input;
      _language = language;
    }
    public void runTestIgnorable() throws Exception {
      if (null == _language) {
        UnitTests.debuggerParserTestRoundTrip("C", _input, _expected);
        UnitTests.debuggerParserTestRoundTrip("Java", _input, _expected);
      } else {
        UnitTests.debuggerParserTestRoundTrip(_language, _input, _expected);
      }
    }
  }
  
  static void debuggerAnalyzerTestError(final String language ,final String input, final String expected, final CommandAstAnalyzer ana) throws Exception {
    final Object astOrMsg = Utilities.debuggerParseAndAnalyze(language, input);//, Utilities.debuggerNewSymbolMapper());
    final String msg = astOrMsg instanceof Node ? "" : trimAnalyzerOutput((String)astOrMsg);
    assrtEquals(expected, msg);
  }
  
  static void debuggerParserTestRoundTrip(final String language, final String input, final String expected) throws Exception {  
    final GNode ast = Utilities.debuggerStringToAst(language, input);
    final String result = Utilities.debuggerAstToString(ast);
    assrtEquals(expected, result);
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
  
  private static TestSuite makeSuiteDebugger() {
    final TestSuite s = new TestSuite();
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "next", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print $metaVar = f()", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print $metaVariable", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print &x", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print (*x).f", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print cVar = f()", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print known", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print x + `.Java this.f($mv) + &z", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print x + `this.f($mv)", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "C", "print x->f", "the Blink debugger does not support the IndirectComponentSelection feature"));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "Java", "next", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "Java", "print $metaVar = f()", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "Java", "print &x", "expected"));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "Java", "print `&x", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "Java", "print javaVar = f()", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "Java", "print new Object()", "the Blink debugger does not support the NewClassExpression feature"));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, "Java", "watch all a.b.c.d.e.f", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, null, "break file name.jni:123", "symbol characters expected"));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, null, "break file/name.jni:123", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, null, "gdb break foo.c:10", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, null, "gdbb break foo.c:10", "break class command expected"));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, null, "n", "break class command expected"));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, null, "next", ""));
    s.addTest(new BlinkDebuggerAnalyzerTest(false, null, "stop at my.pack.Clazz:123", ""));
    s.addTest(new BlinkDebuggerParserTest(false, "C", "delete 42"));
    s.addTest(new BlinkDebuggerParserTest(false, "C", "print $metaVariable"));
    s.addTest(new BlinkDebuggerParserTest(false, "C", "print &x"));
    s.addTest(new BlinkDebuggerParserTest(false, "C", "print x + `this.f($mv)"));
    s.addTest(new BlinkDebuggerParserTest(false, "C", "print x + `this.f()"));
    s.addTest(new BlinkDebuggerParserTest(false, "C", "watch x[0]"));
    s.addTest(new BlinkDebuggerParserTest(false, "Java", "delete 42"));
    s.addTest(new BlinkDebuggerParserTest(false, "Java", "print $metaVariable"));
    s.addTest(new BlinkDebuggerParserTest(false, "Java", "print `&x + y"));
    s.addTest(new BlinkDebuggerParserTest(false, "Java", "print my.pack.Clazz.staticField"));
    s.addTest(new BlinkDebuggerParserTest(false, "Java", "watch access y.g"));
    s.addTest(new BlinkDebuggerParserTest(false, "Java", "watch all a.b.c.d.e.f"));
    s.addTest(new BlinkDebuggerParserTest(false, "Java", "watch my.pack.Clazz.h"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "   stat   "));
    s.addTest(new BlinkDebuggerParserTest(false, null, " stop at my . pack . Clazz : 123 "));
    s.addTest(new BlinkDebuggerParserTest(false, null, "break file/name.jni:123"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "continue"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "delete 42"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "down 3"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "exit"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "gdb break foo.c:10"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "help"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "info break"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "info watch"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "initj"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "jdb stop at foo.c:10"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "list"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "locals"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "next"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "step"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "stop at Clazz:1"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "stop at my.pack.Clazz:123"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "up 0"));
    s.addTest(new BlinkDebuggerParserTest(false, null, "where"));
    return s;
  }

  public static Test suite() {
    final TestSuite s = new TestSuite();
    s.addTestSuite(xtc.lang.blink.UnitTests.class);
    s.addTest(makeSuiteDebugger());
    return s;
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
}
