package superc.cdesugarer;

import java.util.List;
import java.util.LinkedList;

import xtc.type.C;
import xtc.type.Type;
import xtc.type.VariableT;
import xtc.type.StructT;
import xtc.type.UnionT;
import xtc.type.ErrorT;

import superc.core.Syntax;

import superc.core.PresenceConditionManager.PresenceCondition;

import superc.cdesugarer.Multiverse;
import superc.cdesugarer.Multiverse.Element;

import superc.cdesugarer.SymbolTable;
import superc.cdesugarer.SymbolTable.Entry;

import superc.cdesugarer.Declarator;
import superc.cdesugarer.Declarator.EmptyDeclarator;
import superc.cdesugarer.Declarator.ParenDeclarator;
import superc.cdesugarer.Declarator.SimpleDeclarator;
import superc.cdesugarer.Declarator.PointerDeclarator;
import superc.cdesugarer.Declarator.QualifiedPointerDeclarator;
import superc.cdesugarer.Declarator.PointerAbstractDeclarator;
import superc.cdesugarer.Declarator.QualifiedPointerAbstractDeclarator;
import superc.cdesugarer.Declarator.ArrayDeclarator;
import superc.cdesugarer.Declarator.ArrayAbstractDeclarator;
import superc.cdesugarer.Declarator.FunctionDeclarator;
import superc.cdesugarer.Declarator.ParameterListDeclarator;

import superc.cdesugarer.Initializer;
import superc.cdesugarer.Initializer.AssignInitializer;
import superc.cdesugarer.Initializer.ExpressionInitializer;
import superc.cdesugarer.Initializer.InitializerList;
import superc.cdesugarer.Initializer.DesignatedInitializer;
import superc.cdesugarer.Initializer.Designation;
import superc.cdesugarer.Initializer.OffsetofMemberDesignator;
import superc.cdesugarer.Initializer.Designator;
import superc.cdesugarer.Initializer.ArrayDesignator;
import superc.cdesugarer.Initializer.StructUnionDesignator;

import superc.cdesugarer.Declaration;

import superc.cdesugarer.CActions.EnumeratorValue;

import superc.cdesugarer.CActions.FreshIDCreator;


/**
 * These operators are used for cartesian products and transformations
 * in the desugaring SuperC grammar implementation.  This class only
 * holds static fields and methods and is not meant to be
 * instantiated.
 */
class DesugarOps {
  /**
   * Operations for C.  Used to compare types.
   */
  protected static C cOps = new C();

  private DesugarOps() { }

  /**
   * A generic transformer that takes an object of some type and
   * turns it into a single-element list.  This is used for taking the
   * cartesian product of a multiverse of lists with a multiverse of
   * objects of the type that list stores.
   */
  public static class ListWrapper<T> extends Multiverse.Transformer<T, List<T>> {
    List<T> transform(T from) {
      List<T> result = new LinkedList<T>();
      result.add(from);
      return result;
    }
  }
  
  // TODO: make these generic multiverse operators

  /**
   * Concatenates two list non-destructively.  This is used to create
   * multiverse operators that concat multiverses of lists of any
   * type.
   */
  private static <T> List<T> concatLists(List<T> list1, List<T> list2) {
    List<T> newlist = new LinkedList<T>();
    newlist.addAll(list1);
    newlist.addAll(list2);
    return newlist;
  }

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
   * TypeSpecifier and Declarator.
   */
  public final static Multiverse<Declarator> createQualifiedPointerDeclarator(Multiverse<Declarator> declarators, Multiverse<TypeSpecifier> qualifierlists) {
    Multiverse<Declarator> valuemv = new Multiverse<Declarator>();

    for (Element<TypeSpecifier> qualifierlist : qualifierlists) {
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
  public final static Multiverse.Transformer<TypeSpecifier, Declarator> toQualifiedPointerAbstractDeclarator = new Multiverse.Transformer<TypeSpecifier, Declarator>() {
      Declarator transform(TypeSpecifier from) {
        return new QualifiedPointerAbstractDeclarator(from);
      }
    };

  /**
   * Create abstract array declarators.
   */
  public final static Multiverse.Transformer<String, Declarator> toAbstractArrayDeclarator = new Multiverse.Transformer<String, Declarator>() {
      Declarator transform(String from) {
        return new ArrayAbstractDeclarator(from);
      }
    };

  /**
   * A multiverse transformation to turn a list of Declarations
   * into a ParameterListDeclarator.
   */
  public final static Multiverse.Transformer<List<Declaration>, ParameterListDeclarator> toParameterList = new Multiverse.Transformer<List<Declaration>, ParameterListDeclarator>() {
      ParameterListDeclarator transform(List<Declaration> from) {
        return new ParameterListDeclarator(from, false);
      }
    };

  /**
   * A multiverse transformation to turn a list of Declarations
   * into a ParameterListDeclarator that have variable arguments.
   */
  public final static Multiverse.Transformer<List<Declaration>, ParameterListDeclarator> toVarArgsParameterList = new Multiverse.Transformer<List<Declaration>, ParameterListDeclarator>() {
      ParameterListDeclarator transform(List<Declaration> from) {
        return new ParameterListDeclarator(from, true);
      }
    };

  /*****************************************************************************
   ********* Multiverse operators for TypeSpecifiers
   *****************************************************************************/

  // TODO: make a product that copies the first ts, then looks at each boolean of the second and calls the appropriate specifiers.visit function or tries to set the type (which may fail).  also need an error state on the type specifier.

  public final static Multiverse.Operator<TypeSpecifier> specifierProduct = (ts1, ts2) -> {
    TypeSpecifier newts = new TypeSpecifier(ts1);
    newts.visit(ts2);
    return newts;
  };

  /**
   * A multiverse transformation to turn a symtab entries for a
   * typedefname into a multiverse of typespecifiers.
   */
  public final static Multiverse.Transformer<SymbolTable.Entry<Type>, TypeSpecifier> typedefEntriesToTypeSpecifier = new Multiverse.Transformer<SymbolTable.Entry<Type>, TypeSpecifier>() {
      TypeSpecifier transform(SymbolTable.Entry<Type> from) {
        TypeSpecifier ts = new TypeSpecifier();
        if (from.isError()) {
          System.err.println("INFO: use of typedefname with invalid declaration");
          // TODO: needs a unit test
          ts.setError();
        } else if (from.isUndeclared()) {
          System.err.println("INFO: use of undeclared typedefname");
          // TODO: needs a unit test
          ts.setError();
        } else {
          if (! from.getValue().isAlias()) {
            System.err.println("INFO: typedefname is not declared as alias type");
            ts.setError();
            // TODO: double-check that the parser already handles
            // this case, although it seems like the parser is
            // already handling this

            // TODO: use the new symtab for reclassifying
            // typedefname tokens
          } else {
            ts.setType(from.getValue().toAlias());
            ts.addTransformation(from.getValue().toAlias().getName());
          }
        }
        return ts;
      }
    };

  public static String createStructOrUnionDefTransformation(Syntax keyword, String renamedtag, List<Declaration> members) {
    StringBuilder sb = new StringBuilder();
    sb.append(keyword.getTokenText());
    sb.append(" ");
    sb.append(renamedtag);
    sb.append(" {\n");
    System.err.println("TODO: check that all members have different names, don't have type errors themselves, and rename selfrefs");
    for (Declaration declaration : members) {
      if (declaration.hasTypeError()) {
        return "";
      } else {
        sb.append(declaration.toString());
        sb.append(";\n");
      }
      // TODO: use Variable.newBitfield()
    }
    sb.append("}\n");
    return sb.toString();
  }

  public static Type createStructOrUnionDefType(Syntax keyword, String renamedtag, List<Declaration> members) {
    System.err.println("TODO: check that all members have different names, don't have type errors themselves, and rename selfrefs");
    List<VariableT> memberlist = new LinkedList<VariableT>();
    for (Declaration declaration : members) {
      if (declaration.hasTypeError()) {
        return ErrorT.TYPE;
      } else {
        VariableT member;
        if (declaration.hasName()) {
          member = VariableT.newField(declaration.getType(),
                                      declaration.getName());
        } else {
          member = VariableT.newField(declaration.getType(),
                                      null);
        }
        memberlist.add(member);
      }
      // TODO: use Variable.newBitfield()
    }

    if (keyword.getTokenText().equals("struct")) {
      return new StructT(renamedtag, memberlist);
    } else if (keyword.getTokenText().equals("union")) {
      return new UnionT(renamedtag, memberlist);
    } else {
      throw new AssertionError("unexpected keyword to createStructOrUnionDefType");
    }
  }
  
  public static Type createStructOrUnionRefType(Syntax keyword, String renamedtag) {
    if (keyword.getTokenText().equals("struct")) {
      return new StructT(renamedtag);
    } else if (keyword.getTokenText().equals("union")) {
      return new UnionT(renamedtag);
    } else {
      throw new AssertionError("unexpected keyword to createStructOrUnionRefType");
    }
  }

  /**
   * Create the semantic value for a struct definition.
   */
  public static Multiverse<TypeSpecifier> processStructDefinition(Syntax keyword,
                                                                  String structTag,
                                                                  String renamedTag,
                                                                  List<Multiverse<Declaration>> structfields,
                                                                  PresenceCondition pc,
                                                                  CContext scope,
                                                                  FreshIDCreator freshIdCreator) {
    // (1) add each field to the lookaside table and construct the transformation

    // get the field table for the current tag, which should be empty
    SymbolTable<Type> tagtab = scope.addLookasideTable(renamedTag);

    // prepare the desugared output of this struct
    StringBuilder transformation = new StringBuilder();
    transformation.append(keyword);
    transformation.append(" ");
    transformation.append(renamedTag);
    transformation.append(" {\n");

    // track presence conditions of valid and invalid declarations
    PresenceCondition errorCond = pc.presenceConditionManager().newFalse();
    for (Multiverse<Declaration> structfieldmv : structfields) {
      System.err.println("TAGATGA: " + tagtab);
      for (Element<Declaration> structfield : structfieldmv) {
        PresenceCondition combinedCond = pc.and(structfield.getCondition());
        if (combinedCond.isNotFalse()) {

          // if the struct field has no name, then there is no
          // possibilty of a name clash.  we just give it a new
          // name so that it can be stored in the lookaside
          // table.
          String fieldName;
          Declaration renamedDeclaration;
          String renamedField;
          if (structfield.getData().hasName()) {
            fieldName = structfield.getData().getName();
            renamedField = freshIdCreator.freshCId(fieldName);
            renamedDeclaration = structfield.getData().rename(renamedField);
          } else {
            fieldName = freshIdCreator.freshCId("anonymous_field");
            renamedField = fieldName;
            renamedDeclaration = structfield.getData();
          }
          assert null != fieldName;
          assert null != renamedField;
          assert null != renamedDeclaration;

          System.err.println("FIELDNAME " + fieldName);
          System.err.println("FJKLDSLKJFDS " + tagtab);
              
          if (structfield.getData().hasTypeError()) {
            System.err.println("WTF : " + fieldName);
            tagtab.putError(fieldName, combinedCond);

            PresenceCondition newerrorCond = errorCond.or(combinedCond);
            errorCond.delRef(); errorCond = newerrorCond;
          } else { // declaration has no type error
            Multiverse<SymbolTable.Entry<Type>> entries = tagtab.get(fieldName, combinedCond);
            System.err.println("MVMVMVMV: " + entries);
            System.err.println(combinedCond);
            for (Element<SymbolTable.Entry<Type>> entry : entries) {
              if (entry.getData().isError()) {
                // already an error, just emit a message
                System.err.println(String.format("INFO: redeclaring struct field %s in an already invalid configuration", fieldName));

                PresenceCondition newerrorCond = errorCond.or(entry.getCondition());
                errorCond.delRef(); errorCond = newerrorCond;

              } else if (entry.getData().isUndeclared()) {
                Type fieldType = VariableT.newField(renamedDeclaration.getType(), renamedField);

                // add the type containing the renaming to the struct tag's symtab
                tagtab.put(fieldName, fieldType, entry.getCondition());
                System.err.println("tagtab.put: " + fieldName);
                System.err.println("tagtab.put: " + fieldType);
                System.err.println("tagtab.put: " + entry.getCondition());
                // save the text of the desugared field
                transformation.append(renamedDeclaration.toString());
                transformation.append(";\n");

              } else {  // is already declared
                // emit a message
                System.err.println(String.format("INFO: type error on redeclaration of struct field %s", fieldName));
                tagtab.putError(fieldName, entry.getCondition());

                PresenceCondition newerrorCond = errorCond.or(entry.getCondition());
                errorCond.delRef(); errorCond = newerrorCond;
              }  // check existing field entry
            }  // loop over each existing entry for the field
          }  // check for struct declaration type error
        }  // combinedCond is not false
        combinedCond.delRef();
      }
    }
    transformation.append("};\n");

    // add the combined struct declaration to the top of the scope
    scope.addDeclaration(transformation.toString());

    // (2) add the struct to the regular symtab and prepare the resulting semantic value for the typespec

    Multiverse<TypeSpecifier> valuemv = new Multiverse<TypeSpecifier>();

    // add the error conditions as an error typespec
    if (errorCond.isNotFalse()) {
      TypeSpecifier typespecifier = new TypeSpecifier();
      typespecifier.setType(ErrorT.TYPE);
      valuemv.add(typespecifier, errorCond);

      // update the symtab for this configuration to reflect the type errors
      scope.putError(CContext.toTagName(structTag), errorCond);
    }
          
    // get the existing entries for this struct under the valid conditions
    PresenceCondition validCond = pc.andNot(errorCond);
    if (validCond.isNotFalse()) {
      Multiverse<SymbolTable.Entry<Type>> entries = scope.getInCurrentScope(CContext.toTagName(structTag), validCond);
      for (Element<SymbolTable.Entry<Type>> entry : entries) {
        if (entry.getData().isError()) {
          System.err.println(String.format("INFO: redefinition of tag under already-invalid configuration: %s", structTag));
          TypeSpecifier typespecifier = new TypeSpecifier();
          typespecifier.setType(ErrorT.TYPE);
          valuemv.add(typespecifier, entry.getCondition());
          // no need to add to symtab since this config is already an error

        } else if (entry.getData().isUndeclared()) {
          // set the type to be a reference to the renamed struct/union tag
          TypeSpecifier typespecifier = new TypeSpecifier();
          Type structRefType = DesugarOps.createStructOrUnionRefType(keyword, renamedTag);
          typespecifier.setType(structRefType);
          typespecifier.addTransformation(String.format("%s %s", keyword, renamedTag));
          valuemv.add(typespecifier, entry.getCondition());
              
          // add the reference to the renamed struct to the symtab
          scope.put(CContext.toTagName(structTag),
                    typespecifier.getType(),
                    entry.getCondition());

        } else {  // is a declared entry
          assert entry.getData().isDeclared();
          System.err.println(String.format("INFO: trying redefine a struct: %s", structTag));
          TypeSpecifier typespecifier = new TypeSpecifier();
          typespecifier.setType(ErrorT.TYPE);
          valuemv.add(typespecifier, entry.getCondition());

          // this configuration has a type error entry
          scope.putError(CContext.toTagName(structTag), entry.getCondition());
        }
      }
    }
          
    errorCond.delRef(); validCond.delRef();

    CActions.todoReminder("check to see if something needs to be done for empty struct/union");

    assert ! valuemv.isEmpty();

    return valuemv;
  }

  /**
   * Create the semantic value for a struct definition.
   */
  public static Multiverse<TypeSpecifier> processStructReference(Syntax keyword,
                                                                 String structTag,
                                                                 PresenceCondition pc,
                                                                 CContext scope,
                                                                 FreshIDCreator freshIdCreator) {
    Multiverse<TypeSpecifier> valuemv = new Multiverse<TypeSpecifier>();
    Multiverse<SymbolTable.Entry<Type>> entries = scope.getInAnyScope(CContext.toTagName(structTag), pc);
    System.err.println("WHY : " + entries);
    for (Element<SymbolTable.Entry<Type>> entry : entries) {
      TypeSpecifier typespecifier = new TypeSpecifier();
      if (entry.getData().isError()) {
        System.err.println(String.format("INFO: trying to use an invalid specifier: %s", structTag));
        typespecifier.setType(ErrorT.TYPE);
      } else if (entry.getData().isUndeclared()) {
        // create a forward reference tag, which will later be
        // defined to a union of all possible configurations of
        // the struct it references.
        CActions.todoReminder("make a call to rename to record the forward tag mapping.  also record tag name renamings with separate function, since it's a separate namespace");
        String forwardTagRefName = freshIdCreator.freshCId("forward_tag_reference");
        Type forwardStructRef = new StructT(forwardTagRefName);
        typespecifier.setType(forwardStructRef);
        typespecifier.addTransformation(String.format("%s %s", keyword, forwardTagRefName));

        // add a symtab entry that maps the new forward
        // reference tag to the original tagname of the
        // struct/union that was referenced.  this will be used
        // to typecheck field selections, and add extra code to
        // make an indirect reference to the forward referenced
        // struct/union field.  see the direct and indirect
        // selection constructs for more info.
        scope.putForwardTagReference(forwardTagRefName, structTag);
        System.err.println("PUT: " + forwardTagRefName + " " + structTag);
        /* Type referencedStruct = DesugarOps.createStructOrUnionRefType(keyword, structTag); */
        /* scope.put(CContext.toTagRefName(forwardTagRefName), referencedStruct, entry.getCondition()); */
      } else {  // is a declared entry
        if (entry.getData().getValue().isStruct() && keyword.getTokenText().equals("struct")
            || entry.getData().getValue().isUnion() && keyword.getTokenText().equals("union")) {
          // valid reference to existing struct/union, so
          // nothing to do with the symtab.  create a type
          // specifier that refers to the renamed struct/union.
          typespecifier.setType(entry.getData().getValue());
          typespecifier.addTransformation(String.format("%s %s", keyword, entry.getData().getValue().toStructOrUnion().getName()));
          System.err.println("LSLSLSLSLS " + structTag);
        } else {  // tag type is not a struct/union or is an enum
          System.err.println(String.format("INFO: type error on tag reference, not using same struct/union/enum keyword",
                                           structTag));
          typespecifier.setType(ErrorT.TYPE);
        }
      }  // end checking a symtab entry
      valuemv.add(typespecifier, entry.getCondition());
    }  // end loop over existing symtab entries
    // should not be empty because symtab.get is not supposed
    // to be empty
    assert ! valuemv.isEmpty();

    return valuemv;
  }  
  
  /*****************************************************************************
   ********* Multiverse operators for Declarations
   *****************************************************************************/

  /**
   * A multiverse transformation to wrap a parameter declarator into a
   * single-element list.
   */
  public final static Multiverse.Transformer<Declaration, List<Declaration>> declarationListWrap
    = new ListWrapper<Declaration>();
  
  /**
   * Concatenate two Declaration lists
   */
  public final static Multiverse.Operator<List<Declaration>> DECLARATIONLISTCONCAT = (list1, list2) -> {
    return concatLists(list1, list2);
  };

  /**
   * Combine a TypeSpecifier and Declarator into a Declaration.
   */
  public final static Multiverse.Joiner<TypeSpecifier, Declarator, Declaration> joinDeclaration = (typespecifier, declarator) -> {
    return new Declaration(typespecifier, declarator);
  };

  /**
   * Convert a type specifier into a declaration with an empty
   * declarator.  This is used for struct declarations.
   */
  public final static Multiverse.Transformer<TypeSpecifier, Declaration> typespecToDeclaration
    = new Multiverse.Transformer<TypeSpecifier, Declaration>() {
        Declaration transform(TypeSpecifier from) {
          return new Declaration(from, new EmptyDeclarator());
        }
      };

  /**
   * Convert a declaration into a string.  This is used for typename,
   * so any renaming has been done already in the typespec and the
   * declarator is abstract.
   */
  public final static Multiverse.Transformer<Declaration, String> typenameToString
    = new Multiverse.Transformer<Declaration, String>() {
        String transform(Declaration from) {
          return from.toString();
        }
      };

  /**
   * Convert a declaration into a type.  This is used for typename.
   */
  public final static Multiverse.Transformer<Declaration, Type> typenameToType
    = new Multiverse.Transformer<Declaration, Type>() {
        Type transform(Declaration from) {
          return from.getType();
        }
      };

  /*****************************************************************************
   ********* Multiverse operators for Enumerations
   *****************************************************************************/

  /**
   * A multiverse transformation to wrap an enumerator value
   * declarator into a single-element list.
   */
  public final static Multiverse.Transformer<EnumeratorValue, List<EnumeratorValue>> enumeratorValueWrap
    = new ListWrapper<EnumeratorValue>();
  
  /**
   * Concatenate two EnumeratorValue lists
   */
  public final static Multiverse.Operator<List<EnumeratorValue>> ENUMERATORLISTCONCAT = (list1, list2) -> {
    return concatLists(list1, list2);
  };
  
  /*****************************************************************************
   ********* Multiverse operators for Initializers
   *****************************************************************************/

  /**
   * Create assignment initializers.
   */
  public final static Multiverse.Transformer<Initializer, Initializer> toAssignInitializer
    = new Multiverse.Transformer<Initializer, Initializer>() {
        Initializer transform(Initializer from) {
          return new AssignInitializer(from);
        }
      };

  /**
   * Create designations.
   */
  public final static Multiverse.Transformer<List<Designator>, Designation> toDesignation
    = new Multiverse.Transformer<List<Designator>, Designation>() {
        Designation transform(List<Designator> from) {
          return new Designation(from);
        }
      };

  /**
   * Join idents and designators lists to form offsetof member designators.
   */
  public final static Multiverse.Joiner<String, List<Designator>, OffsetofMemberDesignator> joinOffsetof = (ident, list) -> {
    return new OffsetofMemberDesignator(ident, list);
  };

  /**
   * Convert offsetof member designators to strings.
   */
  public final static Multiverse.Transformer<OffsetofMemberDesignator, String> offsetofToString
    = new Multiverse.Transformer<OffsetofMemberDesignator, String>() {
        String transform(OffsetofMemberDesignator from) {
          return from.toString();
        }
      };

  /**
   * Create intializer lists.
   */
  public final static Multiverse.Transformer<List<Initializer>, Initializer> toInitializerList
    = new Multiverse.Transformer<List<Initializer>, Initializer>() {
        Initializer transform(List<Initializer> from) {
          return new InitializerList(from);
        }
      };

  /**
   * Transform an initializer into a designatedinitializer
   */
  public final static Multiverse.Joiner<Designation, Initializer, Initializer> joinDesignatedInitializer = (designation, initializer) -> {
    return new DesignatedInitializer(designation, initializer);
  };

  // TODO: make these generic

  /**
   * Join a Type and a String into an ExpressionInitializer.
   */
  public final static Multiverse.Joiner<Type, String, ExpressionInitializer> joinExpressionInitializer = (type, expression) -> {
    return new ExpressionInitializer(type, expression);
  };

  /**
   * Join a Type and a String into an ArrayDesignator;
   */
  public final static Multiverse.Joiner<Type, String, ArrayDesignator> joinArrayDesignator = (type, expression) -> {
    return new ArrayDesignator(type, expression);
  };

  /**
   * A multiverse transformation to wrap a designator in a
   * single-element list.
   */
  public final static Multiverse.Transformer<Initializer, List<Initializer>> initializerListWrap
    = new ListWrapper<Initializer>();

  /**
   * Concatenate two Designator lists
   */
  public final static Multiverse.Operator<List<Initializer>> INITIALIZERLISTCONCAT = (list1, list2) -> {
    return concatLists(list1, list2);
  };

  /**
   * A multiverse transformation to wrap a designator in a
   * single-element list.
   */
  public final static Multiverse.Transformer<Designator, List<Designator>> designatorListWrap
    = new ListWrapper<Designator>();

  /**
   * Concatenate two Designator lists
   */
  public final static Multiverse.Operator<List<Designator>> DESIGNATORLISTCONCAT = (list1, list2) -> {
    return concatLists(list1, list2);
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

  /**
   * Concatenate operator for strings.x
   */
  public final static Multiverse.Operator<String> concatStrings = (sb1, sb2) -> {
    StringBuilder newsb = new StringBuilder();
    newsb.append(sb1);
    newsb.append(" ");
    newsb.append(sb2);
    return newsb.toString();
  };

  /**
   * Product of two types.  Results in an ErrorT if they aren't
   * compatible.
   */
  public final static Multiverse.Operator<Type> compareTypes = (t1, t2) -> {
    // TODO: see CAnalyzer, e.g., additiveexpression, etc
    Type newtype;
    if (cOps.equal(t1, t2)) {
      // TODO: may need to pick correct type based on kind of
      // construct
      newtype = t1;
    } else {
      System.err.println("WARNING: support C's type coercion rules.  see CAnalyzer.processAssignment");
      newtype = ErrorT.TYPE;
    }
    return newtype;
  };

  /**
   * A multiverse transformation to wrap string into a single-element
   * list.
   */
  public final static Multiverse.Transformer<String, List<String>> stringListWrap
    = new ListWrapper<String>();

  /**
   * A multiverse transformation to turn a list of strings into a
   * concatenated list of strings.
   */
  public final static Multiverse.Transformer<List<String>, String> stringListMerge
    = new Multiverse.Transformer<List<String>, String>() {
        String transform(List<String> from) {
          return String.join("\n", from);
        }
      };

  /**
   * A multiverse transformation to wrap a type into a single-element
   * list.
   */
  public final static Multiverse.Transformer<Type, List<Type>> typeListWrap
    = new ListWrapper<Type>();
  
  /**
   * Concatenate two String lists
   */
  public final static Multiverse.Operator<List<String>> STRINGLISTCONCAT = (list1, list2) -> {
    return concatLists(list1, list2);
  };
  
  /**
   * Concatenate two Type lists
   */
  public final static Multiverse.Operator<List<Type>> TYPELISTCONCAT = (list1, list2) -> {
    return concatLists(list1, list2);
  };
}
