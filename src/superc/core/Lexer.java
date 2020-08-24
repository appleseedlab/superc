package superc.core;

/**
 * This specifies the requirements of a lexer for use by SuperC.
 */
interface Lexer {
  public Syntax yylex() throws java.io.IOException;
  public void setFileName(String fileName);
}
