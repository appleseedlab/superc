package superc.p4parser;

import java.io.Reader;

import superc.core.Lexer;
import superc.core.LexerCreator;

public class P4LexerCreator implements LexerCreator {
  public Lexer newLexer(Reader in) {
    return new P4Lexer(in);
  }
}
