package xtc.lang;

import java.io.CharArrayWriter;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.io.File;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.TreeSet;

/**
 * A class to extract a line number mapping for a source-to-source
 * transformation. The "input source" and the "output source" are input and
 * output of the source-to-source transformation. For instance, Main.jni and
 * Main.java are input source and output source files in the Jeannie framework.
 * This source map extractor assumes that the output source file contains the
 * input source line directives in a "//#line ${lineno} ${source file} form, and
 * this form is similiar to the C line number directive.
 * 
 * The source map extractor takes an output source file (Main.java), and
 * produces a mapping from the input source files (Main.jni) to output source
 * file (Main.java) in JSR45 SMAP format. For more information, look at JSR45
 * [http://jcp.org/en/jsr/detail?id=45].
 * 
 * @author Byeongcheol Lee
 */
public class SourceMapExtractor {

  /**
   * A regular expression to recognize line number directive like the following.
   * 
   * //#line ${lineno} ${source file}
   */
  private static final Pattern lineDirectivePattern = Pattern
      .compile("^\\s*//#line\\s+([0-9]+)\\s+\"(\\S+)\"$");

  /**
   * Print a command line usage, and exit with an error code.
   * 
   * @param msg A user message to explain what was wrong.
   */
  private static void usage(String msg) {
    String umsg = "usage: SourceMapExtractor [source file]";
    System.err.println(umsg + "\n" + msg);
    System.exit(-1);
  }

  /**
   * Drives printing the source remapping infomation for the given
   * #line-decorated source file.
   * 
   * @param args A command line arguments.
   */
  public static void main(String[] args) {

    String outputSourceFileName = null;

    // parse command line argument
    for (int i = 0; i < args.length; i++) {
      String arg = args[i];
      if (outputSourceFileName == null) {
        outputSourceFileName = arg;
      } else {
        usage("can not recognize command line option:" + arg);
      }
    }

    // check outputSourceFileName is readable
    if (outputSourceFileName == null) {
      usage("please, specify [java source file]");
    }
    File javaSourceFile = new File(outputSourceFileName);
    if (!javaSourceFile.isFile()) {
      usage("can not find " + outputSourceFileName);
    }
    if (!javaSourceFile.canRead()) {
      usage("check permission for reading " + outputSourceFileName);
    }

    try {
      // read output source file to get source-to-source mapping
      SourceMapExtractor smapgen = new SourceMapExtractor(outputSourceFileName);
      smapgen.genSMAP();

      // print the source-to-source map to standard output.
      System.out.println(smapgen.toStringInSMAPFormat());

    } catch (IOException ioe) {
      System.err.println("failed in extracting SMAP from the "
          + outputSourceFileName);
    }
  }

  /**
   * The input source file.
   */
  final protected String sourceFile;

  /**
   * The total number of lines in the source file.
   */
  protected int numSourceLines = 0;

  /**
   * The line-to-line mapping from the input source file to the output source
   * file.
   */
  final protected TreeSet<SMAPLineEntry> smapLineEntries = new TreeSet<SMAPLineEntry>();

  /**
   * The mapping from an inputSourceFile to its unique id. Here, the input
   * source files appear in the line directive.
   */
  final protected HashMap<String, Integer> inputSourceFile2id = new HashMap<String, Integer>();

  /**
   * The number of input source files so far. This is to generate unique id for
   * new input file.
   */
  protected int numInputSourceFiles = 0;

  /**
   * A reverse mapping from an output source line to an input source line in
   * case of a single input source file.
   */
  private int[] outputSourceLine2inputSourceLine;

  /**
   * @param s An input source file.
   */
  public SourceMapExtractor(String s) {
    this.sourceFile = s;
  }

  /**
   * @return A number of input source files in the source-to-source mapping.
   */
  public int getNumberOfInputSourceFiles() {
    return numInputSourceFiles;
  }

  /**
   * Search for line number directive (//#line ...) to generate a
   * source-to-source mapping information.
   */
  public void genSMAP() throws IOException {
    FileReader freader = new FileReader(sourceFile);
    LineNumberReader lnr = new LineNumberReader(freader);

    LineNumberDirective prevJNILineDirective = null;
    while (true) {
      String line = lnr.readLine();
      if (line == null) {
        numSourceLines = lnr.getLineNumber();
        // EOF
        if (prevJNILineDirective != null) {
          addJNISourceLine(prevJNILineDirective, lnr.getLineNumber());
        }
        break;
      }

      // check the line is of the form: //#line ${line number} ${filename}
      LineNumberDirective curJNILineDirective = checkJNILineNumberDirective(
          line, lnr.getLineNumber());
      if (curJNILineDirective == null) {
        continue;
      }

      // handle line directive: //#line ${line number} ${filename}
      if (prevJNILineDirective != null) {
        // flush the previous line number directive.
        addJNISourceLine(prevJNILineDirective, lnr.getLineNumber() - 1);
      }

      prevJNILineDirective = curJNILineDirective;
    }
  }

  /**
   * Check if the current line is line number directive. If this line is not a
   * line number directive, this method returns null. Otherwise, this method
   * returns a line number directive object.
   * 
   * @param line A line to be checked.
   * @param lineNumber The current java line where the line appears.
   * @return An line number directive object.
   */
  private LineNumberDirective checkJNILineNumberDirective(String line,
      int lineNumber) {
    // try paring : //#line ${file name} ${line number}
    final Matcher m = lineDirectivePattern.matcher(line);
    if (!m.matches()) {
      return null;
    }

    assert (m.group(1).length() > 0) && (m.group(2).length() > 0);

    int jniLineNumber = Integer.parseInt(m.group(1));
    String fileName = m.group(2);
    int fileID = ensureSourceFileID(fileName);
    LineNumberDirective directive = new LineNumberDirective(fileID,
        jniLineNumber, lineNumber);

    return directive;
  }

  /**
   * Add a line-to-line mapping entry to the smapLineEntries table.
   * 
   * @param lineDirective A line number directive.
   * @param lineEnd The end line number that the lineDirective affects.
   */
  private void addJNISourceLine(final LineNumberDirective lineDirective,
      final int lineEnd) {

    final int javaBegin = lineDirective.outputSourceLineNumber + 1;
    final int count = lineEnd - javaBegin + 1;
    // non-empty java line
    assert (javaBegin > 0) && (lineEnd > 0) && (count >= 1);

    final int jniLineStart = lineDirective.inputSurceLineNumber;
    final int jniFileID = lineDirective.sourceFileID;

    SMAPLineEntry entry = new SMAPLineEntry(jniLineStart, jniFileID, javaBegin,
        count);

    smapLineEntries.add(entry);
  }

  /**
   * Ensure the input source file id is present in the inputSourceFile2id table.
   * 
   * @param sourceFile A source file name.
   * @return A file identification number.
   */
  private int ensureSourceFileID(final String sourceFile) {
    int id;

    if (inputSourceFile2id.containsKey(sourceFile)) {
      id = inputSourceFile2id.get(sourceFile);
    } else {
      numInputSourceFiles++;
      id = numInputSourceFiles;
      inputSourceFile2id.put(sourceFile, id);
    }

    assert inputSourceFile2id.containsKey(sourceFile);

    return id;
  }

  /**
   * This routine returns a source file name that appeared in all the line
   * number directive. This routine is only for the -fatten option in the
   * ClassSOurceRemapper.
   * 
   * @return A source file name.
   */
  protected String getSingleSourceFileName() {

    assert numInputSourceFiles == 1;

    String singleJNIFile = null;
    for (final String jniFile : inputSourceFile2id.keySet()) {
      singleJNIFile = jniFile;
      break;
    }

    return singleJNIFile;
  }

  /**
   * Given output source line number (e.g. in Main.java), this routine returns a
   * corresponding input source line number (e.g. in Main.jni). This routine is
   * only for the -fatten option in the ClassSOurceRemapper.
   * 
   * @param sourceLineNumber An output source line number.
   * @return An input source line number.
   */
  protected int getSingleSourceLine(int sourceLineNumber) {

    assert numInputSourceFiles == 1;

    if (outputSourceLine2inputSourceLine == null) {
      outputSourceLine2inputSourceLine = new int[numSourceLines + 1];
      for (final SMAPLineEntry entry : smapLineEntries) {
        int begin = entry.getOutputLineBegin();
        int end = entry.getOutputLineEnd();
        assert (begin >= 1) && (end >= begin);
        for (int outputLine = begin; outputLine <= end; outputLine++) {
          int inputLine = entry.getInputSourceLine(outputLine);
          int oldInputLine = outputSourceLine2inputSourceLine[outputLine];
          if (oldInputLine >= 1) {
            // take minium if conflict
            if (oldInputLine < inputLine) {
              outputSourceLine2inputSourceLine[outputLine] = inputLine;
            }
          } else {
            // first time
            outputSourceLine2inputSourceLine[outputLine] = inputLine;
          }
        }
      }
    }

    assert outputSourceLine2inputSourceLine != null;
    return outputSourceLine2inputSourceLine[sourceLineNumber];
  }

  /**
   * Return the source-to-source information in SMAP (JSR45) format.
   * 
   * @return A text in SMAP format.
   */
  public String toStringInSMAPFormat() {

    CharArrayWriter wa = new CharArrayWriter();
    PrintWriter w = new PrintWriter(wa);
    w.println("SMAP");
    w.println(sourceFile);
    w.println("JNI");
    w.println("*S JNI");

    // list of jni source file name and id
    w.println("*F");
    for (final String fname : inputSourceFile2id.keySet()) {
      int fid = inputSourceFile2id.get(fname);
      w.println("" + fid + " " + fname);
    }

    // list of JNI to java line number with the following format (JSR45)
    w.println("*L");
    for (final SMAPLineEntry jline : smapLineEntries) {
      w.println(jline.toStringInSMAPFormat());
    }

    w.println("*E");
    w.close();

    return wa.toString();
  }

  /**
   * A SMAP line mapping entry class.
   * 
   */
  private static final class SMAPLineEntry implements Comparable<SMAPLineEntry> {

    /**
     * These fields represent a partial continuous line number mapping from the
     * input source files to the output source file. For futher information,
     * look at JSR45.
     */
    private final int inputStartLine;

    private final int inputFileID;

    private final int repeat;

    private final int outputStartline;

    private final int ouputLineIncrement;

    /**
     * @param inputLine A beginning input source line number.
     * @param inputFileID An intput source file id number.
     * @param outputLineStart A beginning output source line number.
     * @param count A number of lines in the inputr source.
     */
    SMAPLineEntry(int inputLine, int inputFileID, int outputLineStart, int count) {
      assert (inputLine >= 1) && (outputLineStart >= 1) && (count > 0);
      this.inputStartLine = inputLine;
      this.inputFileID = inputFileID;
      this.repeat = count;
      this.outputStartline = outputLineStart;
      this.ouputLineIncrement = 1;
    }

    /**
     * @return The beginning input source line number.
     */
    private int getInputLineBegin() {
      return inputStartLine;
    }

    /**
     * @return The ending input source line number.
     */
    private int getInputLineEnd() {
      return inputStartLine + repeat - 1;
    }

    /**
     * @return The beginning output source line number.
     */
    private int getOutputLineBegin() {
      return outputStartline;
    }

    /**
     * @return The end of output source line number.
     */
    private int getOutputLineEnd() {
      return outputStartline + repeat * ouputLineIncrement - 1;
    }

    /**
     * @param outputLine The line number of the output file.
     * @return An line number of the input file.
     */
    private int getInputSourceLine(int outputLine) {
      assert (outputLine >= getOutputLineBegin())
          && (outputLine <= getOutputLineEnd());
      int jniLine = (outputLine - outputStartline) / ouputLineIncrement
          + inputStartLine;
      assert (jniLine >= inputStartLine) && (jniLine <= getInputLineEnd());
      return jniLine;
    }

    /**
     * @return A text in the SMAP format.
     */
    private String toStringInSMAPFormat() {
      StringBuffer sb = new StringBuffer();

      sb.append(inputStartLine);
      sb.append("#").append(inputFileID);
      if (repeat != 1) {
        sb.append(",").append(repeat);
      }
      sb.append(":").append(outputStartline);
      if (ouputLineIncrement != 1) {
        sb.append(",").append(ouputLineIncrement);
      }

      return sb.toString();
    }

    /**
     * Compare and Order smap entry by output source line number.
     * 
     * @param o2 A SMAP entry.
     * @return An integer value to compare two SMAP entry.
     */
    public int compareTo(SMAPLineEntry o2) {
      if (inputFileID != o2.inputFileID) {
        return inputFileID - o2.inputFileID;
      } else {
        if (outputStartline != o2.outputStartline) {
          return outputStartline - o2.outputStartline;
        } else {
          return inputStartLine - o2.inputStartLine;
        }
      }
    }
  }

  /**
   * A class to represent a line number directive event.
   */
  private static final class LineNumberDirective {

    /**
     * The output source file line number where this event happened.
     */
    private final int outputSourceLineNumber;

    /**
     * The input source line number that appeared in the line number directive.
     */
    private final int inputSurceLineNumber;

    /**
     * The id number for the input source file that appeared in the line number
     * directive.
     */
    private final int sourceFileID;

    /**
     * @param fid  The input source file id number.
     * @param inline The input source line number.
     * @param outline The outoput source line number.
     */
    public LineNumberDirective(int fid, int inline, int outline) {
      assert (fid > 0) & (inline > 0) & (outline > 0);
      sourceFileID = fid;
      inputSurceLineNumber = inline;
      outputSourceLineNumber = outline;
    }
  }
}
