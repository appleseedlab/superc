package superc.cparser;

import java.io.Reader;

import superc.core.Lexer;
import superc.core.LexerCreator;

public class CLexerCreator implements LexerCreator {
  public Lexer newLexer(Reader in) {
    return new CLexer(in);
  }
}
