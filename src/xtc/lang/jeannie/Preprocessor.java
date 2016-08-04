/* (C) Copyright IBM Corp 2005-2007. */
package xtc.lang.jeannie;

import java.io.File;
import java.io.IOException;
import java.io.Reader;

import xtc.parser.Column;
import xtc.parser.ParseException;
import xtc.parser.Result;
import xtc.parser.SemanticValue;
import xtc.tree.Node;
import xtc.util.Tool;

public class Preprocessor extends Tool {

  public static void main(final String[] args) {
    new Preprocessor().run(args);
  }
  
  public final String getCopy() {
    return "(C) 2005-2007 IBM";
  }
  
  public final String getName() {
    return "Jeannie preprocessor";
  }
  
  public static final String[] BUILTINS = {
    "_copyFromJava", "_copyToJava", "_newJavaString", "_stringUTFLength" };

  public static final String[] KEYWORDS = { "_cancel", "_commit", "_with" };
  
  public final void init() {
    super.init();
    runtime.bool("underscores", "underscores", false,
                 "Inhibit aliasing Jeannie keywords and builtins to versions " +
                 "without leading underscore. For example, copyToJava will " +
                 "remain unchanged, instead of being macro-expanded to _copyToJava.");
    runtime.setConsole(runtime.errConsole());
  }

  public final String lineMarker(final Column c) {
    final StringBuilder b = new StringBuilder();
    b.append("\n# " + c.line + " \"" + c.file.replace('\\', '/') + "\"\n");
    for (int i=0; i<c.column; i++)
    b.append(' ');
    return b.toString();
  }
  
  public final String jeannieDefs() {
    final StringBuilder b = new StringBuilder();
    b.append("\n/* start auto-injected Jeannie declarations */\n");
    b.append("#include <jni.h>\n");
    b.append("\n");
    b.append("jint _stringUTFLength(JNIEnv* env, jstring str, jint start, jint len) {\n");
    b.append("  jint result = len;\n");
    b.append("  const jchar* chars = (*env)->GetStringCritical(env, str, 0x0);\n");
    b.append("  jint i;\n");
    b.append("  for (i=0; i<len; i++) {\n");
    b.append("    const jchar c = chars[start + i];\n");
    b.append("    if (c == (jchar)0x0000) result++;\n");
    b.append("    else if (c >= (jchar)0x0080) {\n");
    b.append("      result++;\n");
    b.append("      if (c >= (jchar)0x0800) result++;\n");
    b.append("    }\n");
    b.append("  }\n");
    b.append("  (*env)->ReleaseStringCritical(env, str, chars);\n");
    b.append("  return result;\n");
    b.append("}\n");
    if (!runtime.test("underscores")) {
      b.append("\n/* aliased builtins (use -underscores to omit these definitions) */\n");
      for (final String s : BUILTINS)
        b.append("#define ").append(s.substring(1)).append(" ").append(s).append('\n');
      b.append("\n/* aliased keywords (use -underscores to omit these definitions) */\n");
      for (final String s : KEYWORDS)
        b.append("#define ").append(s.substring(1)).append(" ").append(s).append('\n');
    }
    b.append("/* end auto-injected Jeannie declarations */\n");
    return b.toString();
  }
  
  public final Node parse(final Reader in, final File file) throws IOException, ParseException {
    final PreJeannieParser parser = new PreJeannieParser(in, file.getCanonicalPath(), (int)file.length());
    parser._tool = this;
    final Result parseResult = parser.pFile(0);
    if (parseResult.hasValue()) {
      final Node result = (Node)((SemanticValue)parseResult).value;
      return result;
    } else {
      parser.signal(parseResult.parseError());
      return null;
    }
  }

  public final void process(final Node n) {
    if (null != n)
      System.out.println(n.getString(0));
  }
}
