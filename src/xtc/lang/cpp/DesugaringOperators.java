package xtc.lang.cpp;

import xtc.lang.cpp.Multiverse;

import xtc.lang.cpp.Multiverse.Element;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

import xtc.lang.cpp.SymbolTable.Entry;

import xtc.lang.cpp.Declarator;
import xtc.lang.cpp.Declarator.EmptyDeclarator;
import xtc.lang.cpp.Declarator.ParenDeclarator;
import xtc.lang.cpp.Declarator.SimpleDeclarator;
import xtc.lang.cpp.Declarator.PointerDeclarator;
import xtc.lang.cpp.Declarator.QualifiedPointerDeclarator;
import xtc.lang.cpp.Declarator.PointerAbstractDeclarator;
import xtc.lang.cpp.Declarator.QualifiedPointerAbstractDeclarator;
import xtc.lang.cpp.Declarator.ArrayDeclarator;
import xtc.lang.cpp.Declarator.ArrayAbstractDeclarator;
import xtc.lang.cpp.Declarator.FunctionDeclarator;
import xtc.lang.cpp.Declarator.ParameterDeclarator;
import xtc.lang.cpp.Declarator.ParameterListDeclarator;

import xtc.type.AliasT;

import java.util.List;
import java.util.LinkedList;

/**
 * These operators are used for cartesian products and transformations
 * in the desugaring SuperC grammar implementation.  This class only
 * holds static fields and methods and is not meant to be
 * instantiated.
 */
class DesugaringOperators {

  private DesugaringOperators() { }

  /*****************************************************************************
   ********* Multiverse operators for Declarators
   *****************************************************************************/

  /**
   * Create a function declarator from the product of a declarator and parameters.
   */
  public final static Multiverse.Operator<Declarator> createCompoundDeclarator = (declarator, abstractdeclarator) -> {
    if (abstractdeclarator.isParameterListDeclarator()) {
      return new FunctionDeclarator(declarator, (ParameterListDeclarator) abstractdeclarator);
    } else if (abstractdeclarator.isArrayAbstractDeclarator()) {
      return new ArrayDeclarator(declarator, (ArrayAbstractDeclarator) abstractdeclarator);
    } else {
      throw new AssertionError("unexpected abstract declarator type in ParameterTypedefDeclarator");
    }
  };

  /**
   * Create a multiverse of qualified pointer declarators.  This is not
   * a multiverse operator, because it combines two different types,
   * TypeBuilder and Declarator.
   */
  public final static Multiverse<Declarator> createQualifiedPointerDeclarator(Multiverse<Declarator> declarators, Multiverse<TypeBuilder> qualifierlists) {
    Multiverse<Declarator> valuemv = new Multiverse<Declarator>();

    for (Element<TypeBuilder> qualifierlist : qualifierlists) {
      for (Element<Declarator> declarator : declarators) {
        PresenceCondition combinedCond = qualifierlist.getCondition().and(declarator.getCondition());
        valuemv.add(new QualifiedPointerDeclarator(declarator.getData(),
                                                   qualifierlist.getData()),
                    combinedCond);
        combinedCond.delRef();
      }
    }

    return valuemv;
  }

  /**
   * Wrap with paren declarators.
   */
  public final static Multiverse.Transformer<Declarator, Declarator> toParenDeclarator = new Multiverse.Transformer<Declarator, Declarator>() {
    Declarator transform(Declarator from) {
      return new ParenDeclarator(from);
    }
  };

  /**
   * Create pointer declarators.
   */
  public final static Multiverse.Transformer<Declarator, Declarator> toPointerDeclarator = new Multiverse.Transformer<Declarator, Declarator>() {
    Declarator transform(Declarator from) {
      return new PointerDeclarator(from);
    }
  };

  /**
   * Create qualified pointer declarators.
   */
  public final static Multiverse.Transformer<TypeBuilder, Declarator> toQualifiedPointerAbstractDeclarator = new Multiverse.Transformer<TypeBuilder, Declarator>() {
    Declarator transform(TypeBuilder from) {
      return new QualifiedPointerAbstractDeclarator(from);
    }
  };

  /**
   * Create abstract array declarators.
   */
  public final static Multiverse.Transformer<StringBuilder, Declarator> toAbstractArrayDeclarator = new Multiverse.Transformer<StringBuilder, Declarator>() {
    Declarator transform(StringBuilder from) {
      return new ArrayAbstractDeclarator(from);
    }
  };

  // TODO make these two methods generic for any list
  /**
   * Concatenate two ParmeterListDeclarators
   */
  public final static Multiverse.Operator<List<ParameterDeclarator>> PARAMLISTCONCAT = (list1, list2) -> {
    List<ParameterDeclarator> newlist = new LinkedList<ParameterDeclarator>();
    newlist.addAll(list1);
    newlist.addAll(list2);
    return newlist;
  };

  /**
     * A multiverse transformation to wrap a parameter declarator into a
  * single-element list.
  */
 public final static Multiverse.Transformer<ParameterDeclarator, List<ParameterDeclarator>> listWrap = new Multiverse.Transformer<ParameterDeclarator, List<ParameterDeclarator>>() {
   List<ParameterDeclarator> transform(ParameterDeclarator from) {
     List result = new LinkedList();
     result.add(from);
     return result;
   }
 };

 /**
  * A multiverse transformation to turn a list of ParameterDeclarators
  * into a ParameterListDeclarator.
  */
 public final static Multiverse.Transformer<List<ParameterDeclarator>, ParameterListDeclarator> toParameterList = new Multiverse.Transformer<List<ParameterDeclarator>, ParameterListDeclarator>() {
   ParameterListDeclarator transform(List<ParameterDeclarator> from) {
     return new ParameterListDeclarator(from);
   }
 };

 /*****************************************************************************
  ********* Multiverse operators for TypeBuilders
  *****************************************************************************/

 public final static Multiverse.Operator<TypeBuilder> TBCONCAT = (tb1, tb2) -> {
   return tb1.combine(tb2);
 };

  /**
   * A multiverse transformation to turn a symtab entries for a
   * typedefname into a multiverse of typebuilders.
   */
  public final static Multiverse.Transformer<SymbolTable.Entry, TypeBuilder> typedefEntriesToTypeBuilder = new Multiverse.Transformer<SymbolTable.Entry, TypeBuilder>() {
      TypeBuilder transform(SymbolTable.Entry from) {
        // TODO: improve TypeBuilder's interface
        TypeBuilder tbunit = new TypeBuilder();
        if (from == SymbolTable.ERROR) {
          System.err.println("INFO: use of typedefname with invalid declaration");
          // TODO: needs a unit test
          tbunit.isTypeError = true;
        } else if (from == SymbolTable.UNDECLARED) {
          System.err.println("INFO: use of undeclared typedefname");
          // TODO: needs a unit test
          tbunit.isTypeError = true;
        } else {
          System.err.println("TODO: check that type is actually alias " + from.getType().isAlias());
          if (! from.getType().isAlias()) {
            System.err.println("INFO: typedefname is not declared as alias type");
            tbunit.isTypeError = true;
            // TODO: double-check that the parser already handles
            // this case, although it seems like the parser is
            // already handling this

            // TODO: use the new symtab for reclassifying
            // typedefname tokens
          } else {
            AliasT aliastype = from.getType().toAlias();
            AliasT renamedalias = new AliasT(from.getRenaming(), aliastype.getType());
            tbunit.setTypedef(renamedalias);
          }
        }
        return tbunit;
      }
    };

 /*****************************************************************************
  ********* Multiverse operators for Statements and Expressions
  *****************************************************************************/

  /**
   * Concatenate operator for string builders.
   */
  public final static Multiverse.Operator<StringBuilder> SBCONCAT = (sb1, sb2) -> {
    StringBuilder newsb = new StringBuilder();
    newsb.append(sb1);
    newsb.append(sb2);
    return newsb;
  };
}
