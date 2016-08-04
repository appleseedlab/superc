package xtc.lang.blink;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import xtc.lang.blink.Event.RawTextMessageEvent;
import xtc.lang.blink.agent.AgentCommandOptions;

/** A debuggee JVM class. */
public class DebugeeJVM extends StdIOProcess implements AgentCommandOptions {

  /** 
   * Constructor.
   * @param dbg The debugger.
   * @param name The name.
   */
  public DebugeeJVM(Blink dbg, String name) {
    super(dbg, name);
  }

  /**
   * Launch the debuggee JVM and return the JPDA listener address.
   * 
   * @param args The arguments.
   * @param address The listener address.
   */
  public void beginDebugSession(String[] args, String address)  {

    final String transport;
    if (System.getProperty("os.name").startsWith("Windows")) {
      transport="dt_shmem";
    } else {
      transport="dt_socket";
    }

    final StringBuffer agentOptions = new StringBuffer();
    if (dbg.options.hasJniCheck()) {
      agentOptions.append(JNICHECK + "=y");
    } else {
    	agentOptions.append(JNICHECK + "=n");
    }

    final List<String> jvmCommand= new LinkedList<String>();
    final String[] jvmCommandPrefix =  {
        "java", 
        String.format("-agentpath:%s=%s",dbg.ensureAgentLibraryPath(), agentOptions.toString()),
        //"-Xdebug",
        String.format("-agentlib:jdwp=server=n,suspend=y,transport=%s,address=%s", transport, address),
    };
    for(String a:jvmCommandPrefix)
      jvmCommand.add(a);
    for(String a:args)
      jvmCommand.add(a);
    begin(jvmCommand.toArray(new String[0]));
  }

  /**
   * Internally process the raw message to generate macro event.
   * 
   * @param e The raw text message event.
   */
  void processMessageEvent(RawTextMessageEvent e) {
    dbg.out(e.getMessage()); // bypass the message from the JVM.
  }
}
