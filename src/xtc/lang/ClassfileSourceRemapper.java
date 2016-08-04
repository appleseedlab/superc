package xtc.lang;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.File;

/**
 * A class file post-processor to rewrite a class file for the remapped line
 * number table or to append a SMAP attribute to the class file. This
 * post-processor is a utility for the source-to-source transformation tools
 * such as Jeannie. This post-processor provides the following two modes.
 * 
 * First, stratify mode with -stratify command line flag rewrites the
 * "LineNumberTable" attribute for each method in the class file, and modify the
 * "SourceFile" attribute. This has an advantage of working well with both the
 * current java VM and debugger. However, this does not work if the number of
 * the orignal source files is more than one.
 * 
 * Second, flatten mode with -flatten command line flag appends an SMAP to the
 * end of the class file as "SourceDebugExtension." This is a general and
 * powerful way to provide remapping information for the source-to-source
 * transformation. We found that this SMAP works well with the current java
 * debuggers (SUN jdb 1.6 and eclipse 3.2 Java debugger). However, JVMs in the
 * SUN JDK 1.6 and IBM J9 1.5.0 do not use SMAP when they dump stack trace.
 * 
 * By default, this remapper operates in the flatten mode. The first solution
 * with the SMAP will be the right way in the long run as JVM supports better
 * stack dump messgage with SMAP.
 * 
 * @author Byeongcheol Lee
 * 
 */
public class ClassfileSourceRemapper {

  /**
   * Class file attribute names related to the line number table remapping. For
   * further information, look at the Java virtual machine specification.
   * http://java.sun.com/docs/books/jvms/second_edition/html/ClassFile.doc.html
   */
  private static final String ANAME_SMAP = "SourceDebugExtension";
  private static final String ANAME_LINENUMBERTABLE = "LineNumberTable";
  private static final String ANAME_CODE = "Code";
  private static final String ANAME_SOURCEFILE= "SourceFile";

  /**
   * Constant pool tags for java class file. For further information, look at
   * the Java virtual machine specification.
   * http://java.sun.com/docs/books/jvms/second_edition/html/ClassFile.doc.html
   */
  public static final int CP_Class = 7;
  public static final int CP_Fieldref = 9;
  public static final int CP_Methodref = 10;
  public static final int CP_InterfaceMethodref = 11;
  public static final int CP_String = 8;
  public static final int CP_Integer = 3;
  public static final int CP_Float = 4;
  public static final int CP_Long = 5;
  public static final int CP_Double = 6;
  public static final int CP_NameAndType = 12;
  public static final int CP_Utf8 = 1;

  /**
   * A line number entry in the "LineNumberTable" attribute.
   */
  private static class LineNumberTableEntry {
    int start_pc;
    int line_number;
    LineNumberTableEntry(int pc, int line) {
      assert (pc <= 65535) & (line <= 65535);
      start_pc = pc;
      line_number =line;
    }
    int getStartPC() {return start_pc;}
    int getLineNumber() {return line_number;}
  }

  /**
   * A command line usage.
   * 
   * @param umsg An additional message to explain what is wrong.
   */
  private static void usage(String umsg) {
    String msg = "usage: ClassfileSourceRemapper {-stratify|-flatten} [java source file] [class file]";
    System.err.println(msg + "\n" + umsg);
    System.exit(-1);
  }

  /**
   * Run the class file remapping process by taking a user command line.
   * 
   * @param args The command line arguments.
   */
  public static void main(String[] args) {

    //default option vlaue
    String javaSource = null;
    String classFile = null;
    boolean bStaratify = false;
    boolean bFlatten = true;

    for(int i=0;i <args.length;i++) {
      String arg = args[i];
      if (arg.equals("-stratify")) {
        bFlatten = false;
        bStaratify = true;
      } else if (arg.equals("-flatten")) {
        bFlatten = true;
        bStaratify = false;
      } else if (javaSource == null  ) {
        if (new File(arg).canRead()) {
          javaSource = arg;
        } else {
          usage("can not read " + arg);
        }
      } else if (classFile == null) {
        if (new File(arg).canRead()) {
          classFile = arg;
        } else {
          usage("can not write " + arg);
        }
      }
    }

    //validate options
    if (bStaratify && bFlatten) {usage("specify only one of the -stratify and -flatten");}
    if (javaSource== null) {usage("specify [java source file]");}
    if (classFile == null) {usage("spcify [class file]");}


    try {

      //get source-to-source map
      SourceMapExtractor smap = new SourceMapExtractor(javaSource);
      smap.genSMAP();

      //validate source-to-source map
      if (smap.getNumberOfInputSourceFiles() < 1) {
        System.err.println("no source-to-source mapping found in the " + javaSource);
        System.exit(-1);
      }
      boolean bUseJSR45 = bStaratify;
      if (!bUseJSR45) {
        if (smap.getNumberOfInputSourceFiles() >= 2 ) {
          System.err.println("more than one input source files in the " + javaSource);
          System.err.println("This tool can not process class file with -flatten option");
          System.err.println("Please consider using -stratify option");
          System.exit(-1);
        }
      }

      //update class file for line number remapping..
      ClassfileSourceRemapper lineRemapper = 
        new ClassfileSourceRemapper(smap, classFile, classFile, bUseJSR45);
      lineRemapper.doRemapping();

    } catch (IOException e) {
      System.err.println("failed in remapping line number information");
      e.printStackTrace();
    }
  }


  /**
   * A flag to rewrite line number table in the class file.
   */
  private final boolean bRemapLineNumberTable;


  /**
   * A flag to add SMAP table to the class file.
   */
  private final boolean bInsertSMAPTable;


  /**
   * An input class file name.
   */
  private final String inputClassFile;

  /**
   * An output class file name.
   */
  private final String outputClassFile;

  /**
   * A source-to-source remapping information. 
   */
  private final SourceMapExtractor smap;

  /**
   * An input stream for class file. 
   */
  private DataInputStream is;

  /**
   * An output stream for the post processed class file. 
   */
  private DataOutputStream os;

  /**
   * An in-memory stream to hold the content of postprocessed class file.
   */
  private ByteArrayOutputStream bos;

  /**
   * A constant pool index of the injected UTF8 string for the input source file
   * name in the output class file. "sourcefile_index" field of the "SourceFile"
   * class attribute will be redirected to reference this new source file name.
   */
  private int constantPoolEntryIndexForInputSourceFileName = -1;

  /**
   * A constant pool index of the injected UTF8 string for SMAP attribute name
   * in the output class file. This class file post-process will append to the
   * end of class file a "SourceDebugExtension" class attribute, and
   * "attribute_name_index" field of the debug class attribute will point to
   * this new UTF8 constant pool entry.
   */
  private int constantPoolEntryIndexForSMAP = -1;

  /**
   * A constant pool entries only for UTF8 string. For an constrant pool index
   * number, i, UTF8ConstantPoolEntries[i] is non-null if the constant poll
   * entry is UTF8 string. Otherwise, it's null.
   */
  private String[] UTF8ConstantPoolEntries; 

  /**
   * @param smap A Source-to-source mapping.
   * @param inputClassFile An input class file. 
   * @param outputClassFile An output class file.
   * @param bUseJSR45  Wheather or not to use JSR45 SMAP for remapping.
   */
  public ClassfileSourceRemapper(SourceMapExtractor smap,
      String inputClassFile, String outputClassFile, boolean bUseJSR45) {
    this.smap = smap;
    this.inputClassFile = inputClassFile;
    this.outputClassFile = outputClassFile;

    if (bUseJSR45) {
      bRemapLineNumberTable = false;
      bInsertSMAPTable = true;
    } else {
      bRemapLineNumberTable = true;
      bInsertSMAPTable = false;
    }
  }

  /**
   * Define remapping of a line number table for a method. 
   * 
   * @param old An old line number table.
   * @param mname A method name.
   * @param mdesc A method signagure.
   * @return A new byte code to source line mapping.
   */
  private LineNumberTableEntry[] adjustLineNumberTable(
      LineNumberTableEntry[] old, String mname, String mdesc) {
    assert (old != null);
  
    LineNumberTableEntry[] newtable = new LineNumberTableEntry[old.length];
  
    for (int i = 0; i < newtable.length;i++) {
      LineNumberTableEntry oldEntry = old[i];
      int pc = oldEntry.getStartPC();
      int javaLine = oldEntry.getLineNumber();
      int jniLine = smap.getSingleSourceLine(javaLine);
      newtable[i] = new LineNumberTableEntry(pc, jniLine);
    }
  
    return newtable;
  }

  /**
   * Update the line number mapping in the class file.
   */
  public void doRemapping() throws IOException {

    assert (smap != null) && (is == null) && (os == null) && (bos == null);

    //read input class file and generate modified class file in the
    //memory
    try {
      is = new DataInputStream(new FileInputStream(inputClassFile));
      bos = new ByteArrayOutputStream();
      os = new DataOutputStream(bos);
      processClass();
      is.close();
    } catch(IOException e) {
      System.err.println("error while reading:" + inputClassFile);
      throw e;
    }


    //flush memory to the output class file
    try {
      byte cbytes[] = bos.toByteArray();
      bos.close();
      os.close();
      assert (cbytes != null) && (cbytes.length > 0);
      FileOutputStream fos = new FileOutputStream(outputClassFile);
      fos.write(cbytes);
      fos.close();
    } catch(IOException e) {
      System.err.println("error while writing to: " + outputClassFile);
      throw e;
    }

    is = null;
    os = null;
    bos = null;
    constantPoolEntryIndexForInputSourceFileName  = -1;
    constantPoolEntryIndexForSMAP = -1;
    UTF8ConstantPoolEntries = null;
  }

  /**
   * Begin the line number remapping process.
   */
  private void processClass() throws IOException {
    int magic = processInt();
    assert magic == 0xcafebabe;

    processUnsignedShort(); //minor
    processUnsignedShort(); //major
    int numCP = is.readUnsignedShort();

    assert numCP >= 1;
    UTF8ConstantPoolEntries = new String[numCP];
    os.writeShort(numCP + 1);
    for(int i = 1; i < numCP; i++) {
      int tag = processCP(i);

      //Long, and double take two constant pool entry
      if (tag == CP_Double || tag == CP_Long ) {
        i++;
      }
    }

    int next_cp_index = numCP;
    if (bRemapLineNumberTable) {
      //inject UTF8 JNI source file name
      final String jniSourceFile = smap.getSingleSourceFileName();
      final byte[] utf8InputSourceFileName = jniSourceFile.getBytes("UTF8");
      constantPoolEntryIndexForInputSourceFileName = next_cp_index++;
      os.writeByte(CP_Utf8);
      os.writeShort(utf8InputSourceFileName.length);
      os.write(utf8InputSourceFileName);
    }
    if (bInsertSMAPTable) {
      constantPoolEntryIndexForSMAP = next_cp_index++;
      byte[] smap_section_name = ANAME_SMAP.getBytes("UTF8");
      os.writeByte(1);
      os.writeShort(smap_section_name.length);
      os.write(smap_section_name);
    }

    int flag = processShort(); //flags
    int this_class = processUnsignedShort(); //this_class
    int super_class = processUnsignedShort(); //super_class

    //interfaces
    int numInterfaces = processUnsignedShort();
    if (numInterfaces > 0) {
      processBytes(numInterfaces * 2);
    }

    //fields
    int numFields = processUnsignedShort();
    for(int i = 0; i < numFields; i++) {
      //access flags(u2), name_index(u2), descriptor_index(u2)
      processBytes(6);

      //attributes_count(u2)
      int numFieldAttributes = processUnsignedShort();
      for(int j = 0; j< numFieldAttributes; j++) {
        processAttribute();
      }
    }

    //methods
    int numMethods = processUnsignedShort();
    for(int i = 0; i < numMethods; i++) {
      processMethodInfo(i);
    }

    //class attributes
    int numClassAttributes = is.readUnsignedShort();
    if (bInsertSMAPTable) {
      os.writeShort(numClassAttributes + 1);
    } else {
      os.writeShort(numClassAttributes);
    }

    for(int i = 0; i < numClassAttributes; i++) {

      int name_index = processUnsignedShort();
      String attr_name = UTF8ConstantPoolEntries[name_index];
      assert (attr_name != null);

      if (bRemapLineNumberTable &&  attr_name.equals(ANAME_SOURCEFILE)) {
        processSourceFile();
      } else {
        processBytes(processInt());
      }
    }

    if (bInsertSMAPTable) {
      //append SMAP attribute
      byte[] smap_content = smap.toStringInSMAPFormat().getBytes("UTF8");
      os.writeShort(constantPoolEntryIndexForSMAP);
      os.writeInt(smap_content.length);
      os.write(smap_content);
    }

    assert is.read() == -1;

    return;
  }

  /**
   * Handle a constant pool entyr at an index.
   * 
   * @param index A constant pool index number.
   * @return A tag value for the constant pool entry.
   */
  private int processCP(int index) throws IOException
  {
    byte tag = processByte();
    switch(tag)
    {
    case CP_Class:
      processBytes(2);
      break;

    case CP_Fieldref:
    case CP_Methodref:
    case CP_InterfaceMethodref:
      processBytes(2);
      processBytes(2);
      break;

    case CP_String:
      processBytes(2);
      break;

    case CP_Integer:
    case CP_Float:
      processBytes(4);
      break;

    case CP_Long:
    case CP_Double:
      processBytes(8);
      break;

    case CP_NameAndType:
      processBytes(4);
      break;

    case CP_Utf8: {
      int len = processUnsignedShort();
      final byte[] utf8string = processBytes(len);
      UTF8ConstantPoolEntries[index] = new String(utf8string, "UTF8");
      break;
    }
    default:
      assert false;
    break;
    }
    return tag;
  }

  /**
   * Process i's  method info.
   * 
   * @param i An index number of the current method info to be processed.
   */
  private void processMethodInfo(int i) throws IOException {

    // access flags(u2)
    int flag = processUnsignedShort();

    //name_index(u2)
    int name_index = processUnsignedShort();
    String mname = UTF8ConstantPoolEntries[name_index];

    //descriptor_index(u2)
    int desc_index = processUnsignedShort();
    String mdesc = UTF8ConstantPoolEntries[desc_index];

    //attributes_count(u2)
    int numMethodAttributes = processUnsignedShort();
    if (bRemapLineNumberTable) {
      for(int j = 0; j < numMethodAttributes; j++) {
        int attr_name_index = processUnsignedShort();
        String attr_name = UTF8ConstantPoolEntries[attr_name_index];
        if (attr_name.equals(ANAME_CODE)) {
          processMethodCodeAttribute(attr_name_index, mname, mdesc);
        } else {
          processBytes(processInt());
        }
      }
    } else {
      for(int j = 0; j < numMethodAttributes; j++) {
        processAttribute();
      }
    }
  }

  /**
   * Handle a line number table for each method.
   * 
   * @param mname A method name.
   * @param mdesc A method descriptor.
   */
  private void processLineNumberTable(String mname, String mdesc)
      throws IOException {

    //read old table
    int ilen = is.readInt();
    int inum_table_entries = is.readUnsignedShort();
    LineNumberTableEntry[] oldTable = new LineNumberTableEntry[inum_table_entries];
    for(int i =0; i < inum_table_entries;i++){
      int pc = is.readUnsignedShort();
      int line = is.readUnsignedShort();
      oldTable[i] = new LineNumberTableEntry(pc, line);
    }

    //write new table
    LineNumberTableEntry[] newTable = adjustLineNumberTable(oldTable, mname, mdesc);
    assert (newTable.length == oldTable.length);

    int onum_table_entries = newTable.length;
    int oAttributelen = 2 + onum_table_entries * (2+2);
    os.writeInt(oAttributelen);
    os.writeShort(onum_table_entries);
    for(int i =0; i < onum_table_entries;i++) {
      int pc = newTable[i].getStartPC();
      int line = newTable[i].getLineNumber();
      os.writeShort(pc);
      os.writeShort(line);
    }
  }

  /**
   * Handle SourceFile attribute.
   */
  private void processSourceFile() throws IOException {

    //read old attribute
    int ilen = is.readInt();
    int iSourceFileIndex = is.readUnsignedShort();
    String oldSourceFileName = UTF8ConstantPoolEntries[iSourceFileIndex];

    assert (ilen == 2) && constantPoolEntryIndexForInputSourceFileName >= 1;

    //write new attribute
    os.writeInt(2);
    os.writeShort(constantPoolEntryIndexForInputSourceFileName);
  }

  /**
   * Handle a method code attribute.
   *  
   * @param attr_name_index A constant pool index for UTF8 attribute index.
   * @param mname A method name.
   * @param mdesc A method signature.
   */
  private void processMethodCodeAttribute(int attr_name_index, String mname,
      String mdesc) throws IOException {

    assert UTF8ConstantPoolEntries[attr_name_index].equals(ANAME_CODE);

    //u4 attribute_length
    int codeAttrLen = processInt();

    //u2 max_stack
    int max_stack = processUnsignedShort();

    //u2 max_locals
    int max_locals = processUnsignedShort();

    //u4 code_length;u1 code[code_length];
    int code_length = processInt();
    processBytes(code_length);

    //u2 exception_table_length; exception_table[exception_table_length]
    int ex_length = processUnsignedShort();
    processBytes(8 * ex_length);

    int nested_attr_count = processUnsignedShort();
    for(int i = 0;i <  nested_attr_count;i++) {
      int name_index = processUnsignedShort();
      String attr_name = UTF8ConstantPoolEntries[name_index];
      if (attr_name.equals(ANAME_LINENUMBERTABLE)) {
        processLineNumberTable(mname, mdesc);
      } else {
        processBytes(processInt());
      }
    }
  }


  /**
   * Skip the current attribute section.
   */
  private void processAttribute() throws IOException {
    processBytes(2);
    int i = processInt();
    processBytes(i);
  }

  /**
   * Skip specified number of bytes.
   * 
   * @param i A number of bytes to skip.
   * @return A byte array.
   */
  private byte[] processBytes(int i) throws IOException {
    byte buf[] = new byte[i];
    int j = is.read(buf);
    assert j == i;
  
    os.write(buf);
    return buf;
  }

  /**
   * Skip 4 bytes for intger value.
   * 
   * @return An integer value.
   */
  private int processInt() throws IOException {
    int i = is.readInt();
    os.writeInt(i);
    return i;
  }

  /**
   * Skip two bytes for the signed short.
   * 
   * @return A signed short value.
   */
  private short processShort() throws IOException {
    short word0 = is.readShort();
    os.writeShort(word0);
    return word0;
  }

  /**
   * Skip 2 bytes for unsigned shour value.
   * 
   * @return An unsighed short value.
   */
  private int processUnsignedShort() throws IOException {
    int i = is.readUnsignedShort();
    os.writeShort(i);
    return i;
  }

  /**
   * Skip 1 byte.
   * 
   * @return A byte value.
   */
  private byte processByte() throws IOException {
    byte byte0 = is.readByte();
    os.writeByte(byte0);
    return byte0;
  }
}
