package xtc.lang.blink;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import xtc.lang.blink.Event.UserCommandEvent;
import xtc.lang.blink.Event.BlinkEventSource;

/** A user commandline interface. */
class CommandLineInterface extends Thread implements BlinkEventSource {

  /** The Blink debugger. */
  private final Blink dbg;

  /** The user terminal input stream. */
  private final BufferedReader userInput = new BufferedReader(
      new InputStreamReader(System.in));

  /** The user terminal output stream. */
  private final BufferedOutputStream userOutput = 
    new BufferedOutputStream(System.out);

  /** The user terminal error stream. */
  private final BufferedOutputStream userError = 
    new BufferedOutputStream(System.err);

  /**
   * The constructor.
   * @param dbg The Blink debugger.
   */
  CommandLineInterface(Blink dbg) {
    super("CommandLineProcessingThread");
    this.dbg = dbg;
  }

  /** Getter method for  the string representation. */
  public String getEventSourceName() {
    return "DebuggerUser";
  }

  /** Monitor user input, and enqueue a user message event. */
  public void run() {
    while (true) {
      String line;
      try {
        line = userInput.readLine();
        if (line == null) {
          // EOF --> implicit "exit" user command.
          dbg.enqueEvent(new UserCommandEvent(this, "exit"));
          break;
        }
      } catch (IOException e) {
        dbg.err("I'm terminating this session "
            + "since I failed in getting your command.\n");
        break;
      }
      dbg.enqueEvent(new UserCommandEvent(this, line));
    }
  }

  /**
   * Print a message to the console.
   * 
   * @param msg The message to print.
   */
  void out(String msg) {
    byte[] bytes = msg.getBytes();
    out(userOutput, bytes, 0, bytes.length);
  }

  /**
   * Print an error message to the console.
   * 
   * @param msg The error message to print.
   */
  void err(String msg) {
    byte[] bytes = msg.getBytes();
    out(userError, bytes, 0, bytes.length);
  }

  /**
   * Print a message to the stream.
   * 
   * @param b The byte buffer.
   * @param off The offset.
   * @param len The length.
   */
  private static synchronized void out(BufferedOutputStream out, byte[] b, int off, int len ) {
    try {
      out.write(b, off, len);
      out.flush();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
