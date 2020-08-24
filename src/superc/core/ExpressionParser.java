/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2009-2012 New York University
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 */
package xtc.lang.cpp;

import java.util.LinkedList;
import java.util.List;
import java.util.Iterator;

import java.io.StringReader;

import xtc.lang.cpp.Syntax.Kind;

import xtc.parser.Result;

import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Token;

/**
 * A static factory class for expression parsers.
 *
 * @author Paul Gazzillo
 */
public abstract class ExpressionParser {
  /** The SuperC version of the expression parser. */
  private static ExpressionParser superc = null;

  /** The Rats! version of the expression parser. */
  private static ExpressionParser rats = null;

  /** A parser that compares the SuperC and Rats! ASTs. */
  private static ExpressionParser comparator;

  /** Please use static factory methods. */
  private ExpressionParser() {
  }

  /**
   * Parse a list of tokens.
   *
   * @param expression The list of tokens.
   * @return The AST.
   */
  public abstract Node parse(Iterator<Syntax> expression);

  /**
   * Return the instance of the expression parser implemented with
   * SuperC.  This expression parser will only work when preprocessing
   * C, since the expression parser takes tokens already lexed as C
   * tokens.
   *
   * @param presenceConditionManager The presence condition manager.
   * @return An expression parser implemented with SuperC.
   */
  public static ExpressionParser
    fromSuperC(final PresenceConditionManager presenceConditionManager) {
    if (null == superc) {
      superc = new ExpressionParser() {
          public Node parse(Iterator<Syntax> expression) {
            ForkMergeParser expressionParser
              = new ForkMergeParser(ExpressionParseTables.getInstance(),
                                    ExpressionValues.getInstance(),
                                    ExpressionActions.getInstance(), null,
                                    expression, presenceConditionManager);
            return (Node) expressionParser.parse();
          }
        };
    }
    return superc;
  }

  /**
   * Return the instance of the expression parser implemented with
   * Rats.
   *
   * @return An expression parser implemented with Rats!
   */
  public static ExpressionParser fromRats() {
    if (null == rats) {
      rats = new ExpressionParser() {
          public Node parse(Iterator<Syntax> expression) {
            StringBuilder string = new StringBuilder();
            while (expression.hasNext()) {
              Syntax syntax = expression.next();
              if (syntax.kind() != Kind.EOF) {
                string.append(syntax);
                string.append(" ");
              }
            }
            String str = string.toString();

            StringReader reader = new StringReader(str);;
            ExpressionRats parser
              = new ExpressionRats(reader, "EXPRESSION", str.length());

            Result result;
            Node tree;
            try {
              result = parser.pConstantExpression(0);
              // tree = (Node) parser.value(result);
              if (! result.hasValue()) {
                tree = null;
                System.err.println(parser.format(result.parseError()));
              } else {
                tree = result.semanticValue();
              }
            } catch (java.io.IOException e ) {
              e.printStackTrace();
              throw new RuntimeException("couldn't parse expression");
            }

            return tree;
          }
        };
    }
    return rats;
  }

  /**
   * Compare the two parsers, but return the Rats! parser's AST.
   *
   * @param presenceConditionManager The presence condition manager.
   * @return An expression parser that compares the SuperC and Rats!
   * parser.
   */
  public static ExpressionParser
    comparator(PresenceConditionManager presenceConditionManager) {
    final ExpressionParser superc = fromSuperC(presenceConditionManager);
    final ExpressionParser rats = fromRats();
    if (null == comparator) {
      comparator = new ExpressionParser() {
          public Node parse(Iterator<Syntax> expression) {
            LinkedList<Syntax> list = new LinkedList<Syntax>();

            while (expression.hasNext()) {
              list.add(expression.next());
            }

            Node sAST = superc.parse(list.iterator());
            Node rAST = rats.parse(list.iterator());

            if (! TreeComparator.compare(sAST, rAST)) {
              System.err.println("superc: " + sAST);
              System.err.println("rats:   " + rAST);

              throw new RuntimeException("asts are different");
            }

            return rAST;
          }
        };
    }
    return comparator;
  }
}
