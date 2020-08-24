package superc.core;

import java.io.Reader;

/**
 * This interface is used by the language builder to allow SuperC to
 * create a new lexer for a new file.  It is used by SuperC to start
 * lexing a given file and by HeaderFileManager to handle include
 * files.
 */
interface LexerCreator {
  public Lexer newLexer(Reader in);
}
