package xtc.lang.blink;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.util.HashMap;
import java.util.List;
import java.util.LinkedList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * A symbol remapper class. This is to handle symbol remapping in the Jeannie
 * source code. For instance, "y" in Jeannie source code could be access by
 * "pcEnv->y" in the gdb. Therefore, we need a symbol remapping for the Jeannie
 * source code.
 * 
 * @author Byeongcheol Lee
 */
public class SymbolMapper {

  /** The target source language. */
  enum TargetSourceLanguage {C, JAVA};

  /**
   * The Jeannie source level variable remapping. The blink debugger search the
   * source file direction for the variable remapping table. For instance, the
   * blink debugger expect to find a remap file, "Main.jni.symbol" for the
   * source file "Main.jni."
   */
  private final HashMap<String, SymbolMapper.SourceVariableMapper> varibleRemap
  = new HashMap<String, SourceVariableMapper>();

  /**
   * @param dbg The debugger.
   */
  SymbolMapper() {}

  /**
   * Tries to find the Jeannie variable remap information.
   * 
   * @param variable The variable name.
   * @param sourceFile The source file.
   * @param sourceLineNumber The source file line number.
   * @return a variable remapper object if sucessful otherwise null.
   */
  public VariableRemapEntry lookUpVariableRemap(String variable,
      String sourceFile, int sourceLineNumber) {
    if (sourceFile == null || sourceLineNumber < 0)
      return null;

    SourceVariableMapper mapper = getRemapInformation(sourceFile);
    if (mapper == null) {
      return null;
    }
    return mapper.lookUp(variable, sourceLineNumber);
  }

  /**
   * Look up a method name remapping.
   * 
   * @param methodOrFunction The name in the target language.
   * @param sourceFile The source file.
   * @return The remapping.
   */
  public MethodRemapEntry lookupMethodRemap(String methodOrFunction,
      String sourceFile) {
    if (sourceFile == null) {
      return null;
    }

    SourceVariableMapper mapper = getRemapInformation(sourceFile);
    if (mapper == null) {
      return null;
    }
    return mapper.lookupMethod(methodOrFunction);
  }

  /**
   * Look up a source variable remapping.
   * 
   * @param sourceFileName The source file name.
   * @return The remapping.
   */
  private SourceVariableMapper getRemapInformation(String sourceFileName) {
    SourceVariableMapper mapper = null;
    String remapFileName =sourceFileName + ".symbols";
    if (new File(remapFileName).canRead() && !varibleRemap.containsKey(sourceFileName)) {
      mapper = new SourceVariableMapper(remapFileName);
    } else {
      mapper = varibleRemap.get(sourceFileName);
    }
    return mapper;
  }

  /**
   * Look up variable remapping.
   * 
   * @param sourceFile The source file.
   * @param line The source line.
   * @return The remap entries.
   */
  public List<VariableRemapEntry> lookup(String sourceFile, int line) {
    LinkedList<VariableRemapEntry> list = new LinkedList<VariableRemapEntry>();    
    SourceVariableMapper mapper = getRemapInformation(sourceFile);
    if (mapper == null) {
      return list;
    }
    for(VariableRemapEntry e : mapper.ventries) {
      if (e.startLine <= line && line <= e.endLine) {
        list.add(e);
      }
    }
    return list;
  }

  /**
   * A source-level view of the current position. This is a
   * <source file, source line> pair.
   */
  static class SourceFileAndLine {

    /** The source File. */
    private final String sourceFile;

    /** The source line. */
    private final int sourceLine;

    /**
     * The constructor. 
     * 
     * @param sourceFile The source file.
     * @param sourceLine The source line.
     */
    SourceFileAndLine(String sourceFile, int sourceLine) {
      this.sourceFile = sourceFile;
      this.sourceLine = sourceLine;
    }

    /** Getter method for the source file. */
    public String getSourceFile() {
      return sourceFile;
    }

    /** Getter method for the source line. */
    public int getSourceLine() {
      return sourceLine;
    }

    /** Get source file and line format. */
    public String toString() {
      return sourceFile + ":" + sourceLine;
    }
  }

  /**
   * A source level variable entry.
   */
  static class VariableRemapEntry {

    /** The start line. */
    final int startLine;

    /** The start column. */
    final int startColumn;

    /** The end line. */
    final int endLine;

    /** The end column. */
    final int endColumn;

    /** The language. */
    final TargetSourceLanguage targetLanguage;

    /** The source variable name. */
    final String sourceVariableName;

    /** The target variable name. */
    final String targetVariableName;

    /**
     * Constructor.
     * 
     * @param startLine The start line in the target source file.
     * @param startColumn The start column in the target source file.
     * @param endLine The end line in the target source file.
     * @param endColumn The end column in the target source file.
     * @param targetLanguage The target language (C or Java).
     * @param sourceVariableName The variable name in the source language.
     * @param targetVariableName The variable name in the target language.
     */
    VariableRemapEntry(int startLine, int startColumn, int endLine,
        int endColumn, TargetSourceLanguage targetLanguage,
        String sourceVariableName, String targetVariableName) {
      this.startLine = startLine;
      this.startColumn = startColumn;
      this.endLine = endLine;
      this.endColumn = endColumn;
      this.targetLanguage = targetLanguage;
      this.sourceVariableName = sourceVariableName;
      this.targetVariableName = targetVariableName;    
    }

    /**
     * Generate the variable expression in the target language environment such
     * that jdb or gdb can recognize the expression.
     * 
     * @return jdb or gdb expression for the variable.
     */
    String targetLanguageExpression() {
      StringBuffer sb = new StringBuffer();
      switch(targetLanguage) {
      case JAVA:
        sb.append("this.").append(targetVariableName);
        break;
      case C:
        sb.append("pcEnv->").append(targetVariableName);
        break;
      default:
        assert false;
        break;
      }
      return sb.toString();
    }
  }

  /**
   * A method remap entry.
   *
   */
  static class MethodRemapEntry {

    /** The symbol name in the source language. */
    final String sourceLanguageName;

    /** The symbol name in the target language. */
    final String targetLanguageName;

    /**
     * The constructor.
     * 
     * @param sourceLanguageName The name in the source langguage.
     * @param targetLanguageName The name in the target langauge.
     */
    public MethodRemapEntry(final String sourceLanguageName,
        final String targetLanguageName) {
      this.sourceLanguageName = sourceLanguageName;
      this.targetLanguageName = targetLanguageName;
    }

    /** Getter method for source langauge. */
    public String getSourceLanguageName() {
      return sourceLanguageName;
    }

    /** Getter method for target langauge. */
    public String getTargetLanguageName() {
      return targetLanguageName;
    }
   }

  /**
   * A source level variable remapping table for a source file.
   */
  private static class SourceVariableMapper {

    /** The remap file. */
    private final String remapFile;

    /** The list of variable remap entry. */
    private final List<VariableRemapEntry> ventries = new LinkedList<VariableRemapEntry>();

    /** The list of method name remap entry. */
    private final HashMap<String, MethodRemapEntry> mentries = new HashMap<String, MethodRemapEntry>();

    /**
     * The constructor.
     * 
     * @param remapFile The file containing the variable remapping information.
     */
    public SourceVariableMapper(String remapFile)  {
      this.remapFile = remapFile;
      try {
      updateRemapEntry();
      } catch(IOException e) {
        throw new RuntimeException(e);
      }
    }

    /** Update the remap entry from the remap file.
     * @throws FileNotFoundException */
    private void updateRemapEntry() throws IOException  {
      ventries.clear();

      Pattern variableRemapEntryPattern = Pattern
          .compile("\\s*(\\S+) (\\d+) (\\d+) (\\d+) (\\d+) (Java|C) (\\S+) (\\S+)");
      Pattern methodRemapEntryPattern = Pattern.compile("\\s*(\\S+)\\s*(\\S+)");

      BufferedReader br = new BufferedReader(new FileReader(remapFile));
      int phase = 0;
      for (String line = br.readLine(); line != null; line = br.readLine()) {
        if (line.equals("LocalVariableMap:")) {
          phase = 1;
          continue;
        }
        if (line.equals("MethodMap:")) {
          phase = 2;
          continue;
        }

        if (phase == 1) {
          Matcher m = variableRemapEntryPattern.matcher(line);
          if (m.matches()) {
            int startLine = Integer.parseInt(m.group(2));
            int startColumn = Integer.parseInt(m.group(3));
            int endLine = Integer.parseInt(m.group(4));
            int endColumn = Integer.parseInt(m.group(5));
            String targetLanguageStr = m.group(6);
            TargetSourceLanguage tlang;
            if (targetLanguageStr.equals("Java")) {
              tlang = TargetSourceLanguage.JAVA;
            } else {
              assert targetLanguageStr.equals("C");
              tlang = TargetSourceLanguage.C;
            }
            String sourceVariableName = m.group(7);
            String targetVariableName = m.group(8);
            VariableRemapEntry e = new VariableRemapEntry(startLine,
                startColumn, endLine, endColumn, tlang, sourceVariableName,
                targetVariableName);
            ventries.add(e);
          }
        } else if (phase == 2) {
          Matcher mMethodRemap = methodRemapEntryPattern.matcher(line);
          if (mMethodRemap.matches()) {
            String nameInSourceLanguage = mMethodRemap.group(1);
            String nameInTargetLanguage = mMethodRemap.group(2);
            MethodRemapEntry e = new MethodRemapEntry(nameInSourceLanguage,
                nameInTargetLanguage);
            mentries.put(nameInTargetLanguage, e);
          }
        }
      }
      br.close();
    }

    /**
     * Look up for the variable remap entry.
     * 
     * @param var The variable name.
     * @param sourceLine The source line number for the variable.
     * @return A VariableRemapEntry object if found, or null otherwise.
     */
    VariableRemapEntry lookUp(String var, int sourceLine) {
      for (final VariableRemapEntry e : ventries) {
        if (sourceLine >= e.startLine && sourceLine <= e.endLine
            && e.sourceVariableName.equals(var)) {
          return e;
        }
      }
      return null;
    }

    /**
     * Look up by method name.
     * 
     * @param method The method name.
     * @return The methe name remap entry.
     */
    MethodRemapEntry lookupMethod(String method) {
      return mentries.get(method);
    }
  }  
}
