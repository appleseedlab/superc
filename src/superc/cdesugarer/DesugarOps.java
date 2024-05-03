package superc.cdesugarer;

import java.util.List;
import java.util.LinkedList;

import xtc.Constants;

import xtc.type.C;
import xtc.type.Type;
import xtc.type.VariableT;
import xtc.type.StructT;
import xtc.type.UnionT;
import xtc.type.EnumT;
import xtc.type.NumberT;
import xtc.type.PointerT;
import xtc.type.ErrorT;
import xtc.type.BooleanT;
import xtc.type.IntegerT;
import xtc.type.EnumeratorT;

import superc.core.Syntax;

import superc.core.PresenceConditionManager;
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
import superc.cdesugarer.Declarator.BitFieldSizeDeclarator;
import superc.cdesugarer.Declarator.NamedBitFieldSizeDeclarator;

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
import superc.cdesugarer.CActions.DeclarationOrStatementValue;
import superc.cdesugarer.CActions.LineNumbers;

import superc.cdesugarer.CActions.FreshIDCreator;
import superc.cdesugarer.CActions.StructOrUnionTypeCreator;

import superc.core.Syntax.Language;
import superc.core.Syntax.Text;

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

  /**
   * Convert Syntax to String.
   */
  public final static Multiverse.Transformer<Syntax, String> syntaxToString = new Multiverse.Transformer<Syntax, String>() {
      String transform(Syntax from) {
        return from.getTokenText();
      }
    };

  /**
   * Convert String to DeclarationOrStatementValue
   */
  public final static Multiverse.Transformer<String, DeclarationOrStatementValue> StringToDSV = new Multiverse.Transformer<String, DeclarationOrStatementValue>() {
      DeclarationOrStatementValue transform(String from) {
        return new DeclarationOrStatementValue(from);
      }
    };

  /**
   * Convert Typespecifier to String
   */
  public final static Multiverse.Transformer<TypeSpecifier, String> TypeSpecifierToString = new Multiverse.Transformer<TypeSpecifier, String>() {
      String transform(TypeSpecifier from) {
        return from.toString();
      }
    };

  /**
   * Convert LineNumbers to String
   */
  public final static Multiverse.Transformer<LineNumbers, String> LineNumbersToString = new Multiverse.Transformer<LineNumbers, String>() {
      String transform(LineNumbers from) {
        return from.getComment();
      }
    };
  

  /**
   * Convert LineNumbers to String
   */
  public final static Multiverse.Transformer<String, List<String>> StringToStringList = new Multiverse.Transformer<String, List<String>>() {
      List<String> transform(String from) {
        return new LinkedList<String>(){{add(from);}};
      }
    };
  
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
      System.err.println(qualifierlist.toString());
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

  /**
   * Add a bitfield size to a Declarator.
   */
  public final static Multiverse.Joiner<Declarator, Declarator, NamedBitFieldSizeDeclarator> joinBitFieldSize = (declarator, bitfieldsize) -> {
    if (bitfieldsize.isBitFieldSizeDeclarator()) {
      return new NamedBitFieldSizeDeclarator(declarator, (BitFieldSizeDeclarator) bitfieldsize);
    } else {
      throw new AssertionError("unexpected declarator declarator type in joinBitFieldSize");
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
            ts.addTransformation(new Text<CTag>(CTag.TYPEDEFname, from.getValue().toAlias().getName()));
          }
        }
        return ts;
      }
    };

  
  public static Multiverse<TypeSpecifier> processStructDefinitionWithFlex(Syntax keyword,
                                                                  String structTag,
                                                                  List<Multiverse<Declaration>> structfields,
                                                                  PresenceCondition pc,
                                                                  CContext scope,
                                                                  FreshIDCreator freshIdCreator,
                                                                  StructOrUnionTypeCreator suTypeCreator) {
    List<PresenceCondition> flexList = new LinkedList<PresenceCondition>();
    for (Multiverse<Declaration> m : structfields) {
      for (Element<Declaration> e : m) {
        if (e.getData().isFlexible()) {
          flexList.add(e.getCondition());
        }
      }
    }
    if (flexList.size() < 1) {
      return processStructDefinition(keyword,structTag,structfields,pc,scope,freshIdCreator,suTypeCreator);
    }
    PresenceCondition remaining = (new PresenceConditionManager()).newTrue();
    for (PresenceCondition p : flexList) {
      remaining = remaining.and(p.not());
    }
    flexList.add(remaining);
    Multiverse<TypeSpecifier> ret = new Multiverse<TypeSpecifier>();
    for (PresenceCondition p : flexList) {
      if (p.isNotFalse()) {
        List<Multiverse<Declaration>> l = new LinkedList<Multiverse<Declaration>>();
        for (Multiverse<Declaration> m : structfields){
          Multiverse<Declaration> filt = m.filter(p);
          if (!filt.isEmpty()) {
            l.add(filt);
          }
        }
        ret.addAll(processStructDefinition(keyword,structTag,l,p,scope,freshIdCreator,suTypeCreator));
      }
    }
    return ret;
  }
  /**
   * Create the semantic value for a struct definition.
   */
  public static Multiverse<TypeSpecifier> processStructDefinition(Syntax keyword,
                                                                  String structTag,
                                                                  List<Multiverse<Declaration>> structfields,
                                                                  PresenceCondition pc,
                                                                  CContext scope,
                                                                  FreshIDCreator freshIdCreator,
                                                                  StructOrUnionTypeCreator suTypeCreator) {
    // (1) add each field to the lookaside table and construct the transformation
    // get the field table for the current tag, which should be empty
    String renamedTag = freshIdCreator.freshCId(structTag);
    SymbolTable<Declaration> tagtab = scope.addLookasideTable(renamedTag);
    // prepare the desugared output of this struct
    StringBuilder transformation = new StringBuilder();
    transformation.append(keyword);
    transformation.append(" ");
    transformation.append(renamedTag);
    transformation.append(" {\n");

    CActions.todoReminder("account for bitfieldsize alone as a struct field with no name.");

    // track presence conditions of valid and invalid declarations
    PresenceCondition errorCond = pc.presenceConditionManager().newFalse();
    for (Multiverse<Declaration> structfieldmv : structfields) {
      // System.err.println("TAGATGA: " + tagtab);
      for (Element<Declaration> structfield : structfieldmv) {
        PresenceCondition combinedCond = pc.and(structfield.getCondition());
        if (combinedCond.isNotFalse()) {
          Declarator d = structfield.getData().getDeclarator();
          // if the struct field has no name, then there is no
          // possibilty of a name clash.  we just give it a new
          // name so that it can be stored in the lookaside
          // table.
          String fieldName;
          Declaration renamedDeclaration;
          String renamedField;
          if (d.hasName()) {
            fieldName = structfield.getData().getName();
            renamedField = freshIdCreator.freshCId(fieldName);
            renamedDeclaration = structfield.getData().rename(renamedField);
          } else {
            fieldName = freshIdCreator.freshCId("anonymous_field");
            renamedField = fieldName;
            if (d.isBitFieldSizeDeclarator()) {
              renamedField += d.toString();
            }
            renamedDeclaration = structfield.getData();
          }
          assert null != fieldName;
          assert null != renamedField;
          assert null != renamedDeclaration;

          if (structfield.getData().hasTypeError()) {
            tagtab.putError(fieldName, combinedCond);

            PresenceCondition newerrorCond = errorCond.or(combinedCond);
            errorCond.delRef(); errorCond = newerrorCond;
          } else { // declaration has no type error
            Multiverse<SymbolTable.Entry<Declaration>> entries = tagtab.get(fieldName, combinedCond);

	    for (Element<SymbolTable.Entry<Declaration>> entry : entries) {
              if (entry.getData().isError()) {
                // already an error, just emit a message
                System.err.println(String.format("INFO: redeclaring struct field %s in an already invalid configuration", fieldName));

                PresenceCondition newerrorCond = errorCond.or(entry.getCondition());
                errorCond.delRef(); errorCond = newerrorCond;

              } else if (entry.getData().isUndeclared()) {
                //Type fieldType = VariableT.newField(renamedDeclaration.getType(), renamedField);
                renamedDeclaration.setField();
                // add the type containing the renaming to the struct tag's symtab
                tagtab.put(fieldName, renamedDeclaration, entry.getCondition());
                transformation.append(renamedDeclaration.toString());
                transformation.append(";");
                transformation.append(CActions.typespecLines(renamedDeclaration.getTypeSpec()) + "\n");
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
          Type structRefType = suTypeCreator.create(keyword, renamedTag);
          typespecifier.setType(structRefType);
          typespecifier.addTransformation(keyword);
          typespecifier.addTransformation(new Text<CTag>(CTag.IDENTIFIER, renamedTag));
          valuemv.add(typespecifier, entry.getCondition());
              
          // add the reference to the renamed struct to the symtab
          scope.put(CContext.toTagName(structTag),
                    typespecifier.getType(),
                    entry.getCondition());

        } else {  // is a declared entry
          assert entry.getData().isDeclared();
          System.err.println(String.format("INFO: trying to redefine a struct: %s", structTag));
          TypeSpecifier typespecifier = new TypeSpecifier();
          typespecifier.setType(ErrorT.TYPE);
          valuemv.add(typespecifier, entry.getCondition());

          // this configuration has a type error entry
          scope.putError(CContext.toTagName(structTag), entry.getCondition());
          System.err.println(scope.getSymbolTable());
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
  public static Multiverse<TypeSpecifier> processStructDefinitionMV(Syntax keyword,
                                                                  Multiverse<Syntax> structTag,
                                                                  List<Multiverse<Declaration>> structfields,
                                                                  PresenceCondition pc,
                                                                  CContext scope,
                                                                  FreshIDCreator freshIdCreator,
                                                                  StructOrUnionTypeCreator suTypeCreator) {
    Multiverse<TypeSpecifier> retmv = new Multiverse<TypeSpecifier>();
    for (Element<Syntax> e : structTag) {
      String tag = e.getData().getTokenText();
      retmv.addAll(processStructDefinitionWithFlex(keyword, tag, structfields, pc.and(e.getCondition()), scope, freshIdCreator, suTypeCreator));
    }
    return retmv;
  }


  /**
   * Create the semantic value for a struct reference.
   */
  public static Multiverse<TypeSpecifier> processStructReference(Syntax keyword,
                                                                 String structTag,
                                                                 PresenceCondition pc,
                                                                 CContext scope,
                                                                 FreshIDCreator freshIdCreator,
                                                                 StructOrUnionTypeCreator suTypeCreator) {
    Multiverse<TypeSpecifier> valuemv = new Multiverse<TypeSpecifier>();
    Multiverse<SymbolTable.Entry<Type>> entries = scope.getInAnyScope(CContext.toTagName(structTag), pc);
    // System.err.println("WHY : " + entries);
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
        String forwardTagRefName;
        
        if (scope.hasForwardTagForTag(structTag)) {
          forwardTagRefName = scope.getForwardTagForTag(structTag);
        } else {
          forwardTagRefName = freshIdCreator.freshCId("forward_tag_reference");
          scope.putForwardTagReference(forwardTagRefName, structTag);
        }
        assert null != forwardTagRefName;
        
        Type forwardStructRef = suTypeCreator.createStruct(forwardTagRefName);
        typespecifier.setType(forwardStructRef);
        typespecifier.addTransformation(new Language<CTag>(CTag.STRUCT));
        typespecifier.addTransformation(new Text<CTag>(CTag.IDENTIFIER, forwardTagRefName));

        // add a symtab entry that maps the new forward
        // reference tag to the original tagname of the
        // struct/union that was referenced.  this will be used
        // to typecheck field selections, and add extra code to
        // make an indirect reference to the forward referenced
        // struct/union field.  see the direct and indirect
        // selection constructs for more info.
        // System.err.println("PUT: " + forwardTagRefName + " " + structTag);
        /* Type referencedStruct = DesugarOps.createStructOrUnionRefType(keyword, structTag); */
        /* scope.put(CContext.toTagRefName(forwardTagRefName), referencedStruct, entry.getCondition()); */
      } else {  // is a declared entry
        if (entry.getData().getValue().isStruct() && keyword.getTokenText().equals("struct")
            || entry.getData().getValue().isUnion() && keyword.getTokenText().equals("union")) {
          // valid reference to existing struct/union, so
          // nothing to do with the symtab.  create a type
          // specifier that refers to the renamed struct/union.
          typespecifier.setType(entry.getData().getValue());
          typespecifier.addTransformation(keyword);
          typespecifier.addTransformation(new Text<CTag>(CTag.IDENTIFIER, entry.getData().getValue().toStructOrUnion().getName()));
          // System.err.println("LSLSLSLSLS " + structTag);
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

  /**
   * Create the semantic value for an enum def.
   */
  public static Multiverse<TypeSpecifier> processEnumDefinition(Syntax keyword,
                                                                String enumTag,
                                                                String renamedTag,
                                                                List<Multiverse<EnumeratorValue>> list,
                                                                PresenceCondition pc,
                                                                CContext scope) {
    CActions.todoReminder("type check enumerator value.   not allowed to use same int.");
    PresenceCondition errorCond = pc.presenceConditionManager().newFalse();
    PresenceCondition validCond = pc.presenceConditionManager().newFalse();
    List<String> enums= new LinkedList<String>();
    for (Multiverse<EnumeratorValue> ratormv : list) {
      for (Element<EnumeratorValue> rator : ratormv) {
        if (rator.getData().getType() == ErrorT.TYPE) {
          PresenceCondition newerrorCond = errorCond.or(rator.getCondition());
          errorCond.delRef(); errorCond = newerrorCond;
        } else {
          PresenceCondition newvalidCond = validCond.or(rator.getCondition());
          validCond.delRef(); validCond = newvalidCond;
          String eToAdd = rator.getData().getTransformation();
          boolean found = false;
          for (String es : enums) {
            if (eToAdd.equals(es)) {
              found = true;
              break;
            }
          }
          if (!found) {
            enums.add(eToAdd);
          }
        }
      }  // end ratormv
    } // end list
    if (enums.size() == 0) {
      Multiverse<TypeSpecifier> typespecmv = new Multiverse<TypeSpecifier>();
      TypeSpecifier typespecifier = new TypeSpecifier();
      typespecifier.setType(ErrorT.TYPE);
      typespecmv.add(typespecifier, pc);
      return typespecmv;
    }
    scope.putEnumerator(enumTag,renamedTag,enums,pc);

    Multiverse<TypeSpecifier> typespecmv = new Multiverse<TypeSpecifier>();
    PresenceCondition trueValid = validCond.and(errorCond.not());
    validCond.delRef();
    if (trueValid.isNotFalse()) {
      TypeSpecifier typespec = new TypeSpecifier();
      // TODO: get largest type for enum (gcc), instead of ISO standard of int
      Type enumreftype = new EnumT(renamedTag);
      typespec.setType(enumreftype);

      typespec.addTransformation(keyword);
      typespec.addTransformation(new Text<CTag>(CTag.IDENTIFIER, renamedTag));

      typespecmv.add(typespec, trueValid);

      /* scope.put(CContext.toTagName(enumTag), enumreftype, validCond); */
    }
    
    if (errorCond.isNotFalse()) {
      TypeSpecifier typespecifier = new TypeSpecifier();
      typespecifier.setType(ErrorT.TYPE);
      typespecmv.add(typespecifier, errorCond);

      /* scope.putError(CContext.toTagName(enumTag), errorCond); */
    }
    errorCond.delRef();

    assert ! typespecmv.isEmpty();

    CActions.todoReminder("support gcc's enums larger than ISO C's int");

    return typespecmv;
  }
  
  public static Multiverse<TypeSpecifier> processEnumReference(Syntax keyword,
                                                               String enumTag,
                                                               PresenceCondition pc,
                                                               CContext scope,
                                                               FreshIDCreator freshIdCreator) {
    Multiverse<TypeSpecifier> typespecmv = new Multiverse<TypeSpecifier>();
    Multiverse<String> renamings = scope.getEnumMultiverse(enumTag,pc);
    for (Element<String> s : renamings) {
      TypeSpecifier typespec = new TypeSpecifier();
      if (s.getData().equals("<error>")) {
        typespec.setError();
      } else if (s.getData().equals("<undeclared>")) {
        String forwardTagRefName;
        if (scope.hasForwardETagForTag(enumTag)) {
          forwardTagRefName = scope.getForwardETagForTag(enumTag);
        } else {
          forwardTagRefName = freshIdCreator.freshCId("forward_tag_reference");
          scope.putForwardETagReference(forwardTagRefName, enumTag);
        }
        assert null != forwardTagRefName;

        List<VariableT> dummy = new LinkedList<VariableT>();
        dummy.add(VariableT.newField(NumberT.INT,enumTag));
        Type forwardERef = new UnionT(forwardTagRefName,dummy);
        typespec.setType(forwardERef);
        typespec.addTransformation(new Language<CTag>(CTag.UNION));
        typespec.addTransformation(new Text<CTag>(CTag.IDENTIFIER, forwardTagRefName));
        typespecmv.add(typespec, s.getCondition());
      } else {
        // TODO: get largest type for enum (gcc), instead of ISO standard of int
        Type enumreftype = new EnumT(s.getData());
        typespec.setType(enumreftype);
        
        typespec.addTransformation(keyword);
        typespec.addTransformation(new Text<CTag>(CTag.IDENTIFIER, s.getData()));
      
        typespecmv.add(typespec, s.getCondition());
      }
    }
    return typespecmv;
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
   * Convert initializer to string.
   */
  public final static Multiverse.Transformer<Initializer, String> initializerToString
    = new Multiverse.Transformer<Initializer, String>() {
        String transform(Initializer from) {
          return from.toString();
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
   * Concatenate operator for strings.x
   */
  public final static Multiverse.Operator<List<String>> concatStringsList = (sb1, sb2) -> {
    List<String> newsb = new LinkedList<String>();
    newsb.addAll(sb1);
    newsb.add(" ");
    newsb.addAll(sb2);
    return newsb;
  };
  
  /**
   * Concatenate operator for strings.x, unless a String is empty
   */
  public final static Multiverse.Operator<String> propEmptyString = (sb1, sb2) -> {
    if (sb1 == "" || sb2 == "") {
      return "";
    }
    StringBuilder newsb = new StringBuilder();
    newsb.append(sb1);
    newsb.append(" ");
    newsb.append(sb2);
    return newsb.toString();
  };

  
  public final static Multiverse.Operator<LineNumbers> combineLineNumbers = (ln1, ln2) -> {
    return new LineNumbers(ln1,ln2);
  };
  
  /**
   * Concatenate operator for strings.x unless there is an error
   */
  public final static Multiverse.Operator<String> concatStringsPropError = (sb1, sb2) -> {
    StringBuilder newsb = new StringBuilder();
    if (sb1.toString().startsWith("__static_type_error("))
      return sb1.toString();
    if (sb2.toString().startsWith("__static_type_error("))
      return sb2.toString();
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
    // System.err.println("COMPARE: " + t1 + " " + t2);
    // System.err.println("EQUALS:  " + t1.equals(t2));
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
   * 
   */
  public final static Multiverse.Operator<Type> shiftOp = (t1, t2) -> {
    // TODO: see CAnalyzer, e.g., additiveexpression, etc
    Type newtype;
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();

    if (r1.isNumber() && !((NumberT)r1).isDecimal()) {
      if (r2.isNumber() && !((NumberT)r2).isDecimal()) {
        newtype = r1;
      } else {
        newtype = ErrorT.TYPE;
      }
    } else {
      newtype = ErrorT.TYPE;
    }
    
    return newtype;
  };
  
  /**
   * product of two types. Returns an error if either type is an error.
   * otherwise returns left type. This should only be temporary in binary
   * expressions until full type checking is done.
   */
  public final static Multiverse.Operator<Type> propTypeError = (t1, t2) -> {
    if (t1 == ErrorT.TYPE || t2 == ErrorT.TYPE) {
      return ErrorT.TYPE;
    }
    Type newtype;
    newtype = t1.copy();
    if ((!t2.hasAttribute(Constants.ATT_CONSTANT) && !t2.hasConstant())) {
      if (newtype.hasConstant()) {
        newtype.removeConstant();
      } else if (newtype.hasAttribute(Constants.ATT_CONSTANT)) {
        newtype.removeAttribute(Constants.ATT_CONSTANT);
      }
    }
    return newtype;
  };

  /**
   * product of two relational types. Returns an error if either type is an error.
   * otherwise returns a boolean type. This should only be temporary in binary
   * expressions until full type checking is done.
   */
  public final static Multiverse.Operator<Type> relOpProduct = (t1, t2) -> {
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();
    
    if ( (r1.isNumber() || r1.isEnum() || r1.isEnumerator())
         &&
         (r2.isNumber() || r2.isEnum() || r2.isEnumerator())) {
      return NumberT.INT;
    }

        //compare pointer with non-decimal
    if (((r1.isPointer() || r1.isArray()) && ((r2.isNumber() && !((NumberT)r2).isDecimal()) || r2.isEnumerator() || r2.isEnum() || r2.isPointer() || r2.isArray())) ||
        ((r2.isPointer() || r2.isArray()) && ((r1.isNumber() && !((NumberT)r1).isDecimal()) || r1.isEnumerator() || r1.isEnum() || r1.isPointer() || r1.isArray()))) {
      return NumberT.INT;
    }
    return ErrorT.TYPE;
  };


  public final static Multiverse.Operator<Type> eqOp = (t1, t2) -> {
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();

    //two quantitative values
    if ( (r1.isNumber() || r1.isEnum() || r1.isEnumerator())
         &&
         (r2.isNumber() || r2.isEnum() || r2.isEnumerator())) {
      return NumberT.INT;
    }
    //compare pointer with non-decimal
    if (((r1.isPointer() || r1.isArray()) && ((r2.isNumber() && !((NumberT)r2).isDecimal()) || r2.isEnumerator() || r2.isEnum() || r2.isPointer() || r2.isArray())) ||
        ((r2.isPointer() || r2.isArray()) && ((r1.isNumber() && !((NumberT)r1).isDecimal()) || r1.isEnumerator() || r1.isEnum() || r1.isPointer() || r1.isArray()))) {
      return NumberT.INT;
    }
    return ErrorT.TYPE;
  };

        
  public final static Multiverse.Operator<Type> bitOp = (t1, t2) -> {
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();

    //two quantitative values
    if ( ((r1.isNumber() && !((NumberT)r1).isDecimal()) || r1.isEnum() || r1.isEnumerator())
         &&
         ((r2.isNumber() && !((NumberT)r2).isDecimal()) || r2.isEnum() || r2.isEnumerator())) {
      return NumberT.INT;
    }
    return ErrorT.TYPE;
  };
        
  public final static Multiverse.Operator<Type> scalarOp = (t1, t2) -> {
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();

    //two quantitative values
    if ( (r1.isStruct() || r1.isUnion() || r1 == ErrorT.TYPE)
         ||
         (r2.isStruct() || r2.isUnion()|| r2 == ErrorT.TYPE)) {
      return ErrorT.TYPE;
    }
    return NumberT.INT;
  };

  public final static Multiverse.Operator<Type> multOp = (t1, t2) -> {
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();

    //two quantitative values
    if ( (r1.isNumber() || r1.isEnum() || r1.isEnumerator())
         &&
         (r2.isNumber() || r2.isEnum() || r2.isEnumerator())) {
      return r1;
    }
    return ErrorT.TYPE;
  };
  
  public final static Multiverse.Operator<Type> modOp = (t1, t2) -> {
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();
    //two quantitative values
    if ( ((r1.isNumber() && !((NumberT)r1).isDecimal()) || r1.isEnum() || r1.isEnumerator())
         &&
         ((r2.isNumber() && !((NumberT)r2).isDecimal()) || r2.isEnum() || r2.isEnumerator())) {
      return r1;
    }
    return ErrorT.TYPE;
  };

  public final static Multiverse.Operator<Type> addOp = (t1, t2) -> {
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();

    //two quantitative values
    if ( (r1.isNumber() || r1.isEnum() || r1.isEnumerator())
         &&
         (r2.isNumber() || r2.isEnum() || r2.isEnumerator())) {
      return r1;
    }
    //compare pointer with non-decimal
    if ((r1.isPointer() || r1.isArray()) && ((r2.isNumber() && !((NumberT)r2).isDecimal()) || r2.isEnumerator() || r2.isEnum())) {
      return r1;
    } else if ((r2.isPointer() || r2.isArray()) && ((r1.isNumber() && !((NumberT)r1).isDecimal()) || r1.isEnumerator() || r1.isEnum())) {
      return r2;
    }
    return ErrorT.TYPE;
  };

  public final static Multiverse.Operator<Type> subOp = (t1, t2) -> {
    Type r1 = t1.resolve();
    Type r2 = t2.resolve();

    //two quantitative values
    if ( (r1.isNumber() || r1.isEnum() || r1.isEnumerator())
         &&
         (r2.isNumber() || r2.isEnum() || r2.isEnumerator())) {
      return r1;
    }
    //compare pointer with non-decimal
    if ((r1.isPointer() || r1.isArray()) && ((r2.isNumber() && !((NumberT)r2).isDecimal()) || r2.isEnumerator() || r2.isEnum() || r2.isPointer() || r2.isArray())) {
      return r1;
    }
    return ErrorT.TYPE;
  };

  
  /**
   * Check the type of an assignment.
   */
  public final static Multiverse<Type> checkAssignmentType(Multiverse<Type> left, Multiverse<Type> right,
                                                           Multiverse<String> opmv, PresenceCondition pc,
                                                           boolean init) {
    Multiverse<Type> resultmv = new Multiverse<Type>();

    boolean pedantic = false;
    for (Element<Type> leftelem : left) {
      PresenceCondition leftcond = leftelem.getCondition().and(pc);
      for (Element<Type> rightelem : right) {
        PresenceCondition rightcond = rightelem.getCondition().and(leftcond);
        for (Element<String> opelem : opmv) {
          PresenceCondition elemCond = opelem.getCondition().and(rightcond);
            
          if (elemCond.isNotFalse()) {
            Type t1 = leftelem.getData();
            Type t2 = rightelem.getData();
            String op = opelem.getData();
            if (t1.hasError() || t2.hasError()) {
              resultmv.add(ErrorT.TYPE, elemCond);
              continue;
            }

            final Type r1 = t1.resolve();
            final Type r2 = cOps.pointerize(t2);
            Type result   = null;

            if (r2.isVoid()) {
              System.err.println("type error: void value not ignored as it ought to be");
              resultmv.add(ErrorT.TYPE, elemCond);
              continue;
            }
            if (t1.isEnum() && (r2.isPointer() || r2.isArray())) {
              resultmv.add(ErrorT.TYPE, elemCond);
              continue;
            }

            switch (r1.tag()) {
            case BOOLEAN: {
              // Booleans can be assigned from scalar operands.
              if (cOps.isScalar(r2)) {
                result = r1;
              }
            } break;

            case INTEGER: {
              // Integers can be assigned from scalar operands, but call for a
              // warning then the operand is a pointer.
              if (cOps.isArithmetic(r2)) {
                result = r1;
              } else if (r2.isPointer()) {
                if (pedantic) {
                  System.err.println("type error: " + op + " makes integer from pointer without a cast");
                  result = ErrorT.TYPE;
                } else {
                  // GCC extension.
                  System.err.println("type warning: " + op+" makes integer from pointer without a cast");
                  result = r1;
                }
              }
            } break;

            case FLOAT: {
              // Floats can be assigned from other arithmetic types.
              if (cOps.isArithmetic(r2)) {
                result = r1;
              }
            } break;

            case STRUCT:
            case UNION: {
              // A struct or union can only be assigned from another struct or
              // union of compatible type.
              if (cOps.equal(r1, r2)) {
                result = r1;
              }
              else {
                System.err.println("type error: " + op + " makes invalid assignment to struct/union type");
                result = ErrorT.TYPE;
              }
            } break;

            case ARRAY: {
              // An array can only be assigned in an initializer and only if
              // the left-hand type is a (wide) C string and the right-hand
              // type is a matching C string constant.
              if (init) {
                if (cOps.isString(r1) && t2.hasConstant()) {
                  if (cOps.isString(t2)) {
                    result = r1;
                  } else if (cOps.isWideString(t2)) {
                    System.err.println("type error: " + "char-array initialized from wide string");
                    result = ErrorT.TYPE;
                  }

                } else if (cOps.isWideString(r1) && t2.hasConstant()) {
                  if (cOps.isString(t2)) {
                    System.err.println("type error: " + "wchar_t-array initialized from non-wide string");
                    result = ErrorT.TYPE;
                  } else if (cOps.isWideString(t2)) {
                    result = r1;
                  }
                }
              }
            } break;

            case POINTER: {
              if (r2.isPointer()) {
                final Type pt1  = r1.toPointer().getType(); // PointedTo, PTResolved
                final Type pt2  = r2.toPointer().getType();

                final Type ptr1 = pt1.resolve();
                final Type ptr2 = pt2.resolve();

                if (cOps.equal(ptr1, ptr2) || ptr1.isVoid() || ptr2.isVoid()) {
                  if (cOps.hasQualifiers(pt1, pt2) || cOps.isStringLiteral(t2)) {
                    result = r1;

                  } else if (pedantic) {
                    System.err.println("type error: " + op + " discards qualifiers from pointer target " +
                                  "type");
                    result = ErrorT.TYPE;

                  } else {
                    System.err.println("type warning: " + op + " discards qualifiers from pointer target " +
                                    "type");
                    result = r1;
                  }

                } else if (ptr1.isNumber() && ptr2.isNumber() &&
                           NumberT.equalIgnoringSign(ptr1.toNumber().getKind(),
                                                     ptr2.toNumber().getKind())) {
                  // Note: We don't need to consider booleans here because all
                  // booleans are unsigned.
                  if (pedantic) {
                    System.err.println("type error: " + "pointer targets in "+op+" differ in signedness");
                    result = ErrorT.TYPE;
                  } else {
                    // GCC extension.
                    System.err.println("type warning: " + "pointer targets in "+op+" differ in signedness");
                    result = r1;
                  }

                } else if (pedantic) {
                  System.err.println("type error: " + "incompatible pointer types in " + op);
                  result = ErrorT.TYPE;

                } else {
                  // GCC extension.
                  System.err.println("type warning: " + "incompatible pointer types in " + op);
                  result = r1;
                }

              } else if (t2.isEnum()) {
                result = ErrorT.TYPE;
              } else if (t2.hasConstant() && t2.getConstant().isNull()) {
                result = r1;
                
              } else if (cOps.isIntegral(t2)) {
                if (pedantic) {
                  System.err.println("type error: " + op + " makes pointer from integer without a cast");
                  result = ErrorT.TYPE;
                } else {
                  // GCC extension.
                  System.err.println("type warning: " + op + " makes pointer from integer without a cast");
                  result = r1;
                }
              }
            }
              break;
            case FUNCTION: {
              System.err.println("type error: " + "functions cannot be assigned to");
              result = ErrorT.TYPE;
              } break;
            default:
              if (r1.isInternal() && r2.isInternal() &&
                  r1.toInternal().getName().equals(r2.toInternal().getName())) {
                result = r1;
              }
            }
            if (result == null)
              result = ErrorT.TYPE;
            resultmv.add(result, elemCond);
          }
          elemCond.delRef();
        }
        rightcond.delRef();
      }
      leftcond.delRef();
    }

    assert ! resultmv.isEmpty();

    return resultmv;
  }

  /**
   * Check the type of a unary operator.
   */
  public final static Multiverse.Joiner<Type, Syntax, Type> checkUnaryOp = (type, op) -> {
    if (type == ErrorT.TYPE) {
      return ErrorT.TYPE;
    }
    switch (op.kind()) {
    case LANGUAGE:
    Type resolvedType = type.resolve();  // unwrap any typedef aliasing
    switch (((Language<CTag>) op).tag()) {
    case STAR:
      if (resolvedType.isPointer()) {
        return resolvedType.toPointer().getType();
      } else if (resolvedType.isArray()) {
        return resolvedType.toArray().getType();
      }else {
        return ErrorT.TYPE;
      }
      // should be unreachable
    case AND:
      return  new PointerT(type.resolve());
    case ICR:
      //fall-through
    case DECR:
      if ( resolvedType.isNumber() ||
           resolvedType.isPointer() ||
           resolvedType.isEnum() ||
           resolvedType.isEnumerator())
        return resolvedType;
      else {
        return ErrorT.TYPE;
      }
    case PLUS:
      // fall-through
    case MINUS:
      if (resolvedType.isNumber()) {
        return resolvedType;
      } else {
        return ErrorT.TYPE;
      }
    case NEGATE:
      resolvedType = type.resolve();
      // TDDO: check types of other operators
      if (resolvedType.isNumber() && !((NumberT)resolvedType).isDecimal()) {
        return resolvedType;
      } else {
        return ErrorT.TYPE;
      }
    case NOT:
      if (resolvedType.isStruct() || resolvedType.isUnion()) {
        return ErrorT.TYPE;
      } else {
        return NumberT.CHAR;
      }
      
    default:
    throw new AssertionError("unexpected unary op token");
    }
    default:
    throw new AssertionError("unary op should always be a language token");
    }
  };
  
  /**
   * Get the return type from a function type.  This will return an
   * error type when the type is not a function type.
   */
  public final static Multiverse.Transformer<Type, Type> getReturnType
    = new Multiverse.Transformer<Type, Type>() {
        Type transform(Type ftype) {
          Type x = ftype;
          if (x.isPointer()) {
            x = ((PointerT)x).getType().resolve();
          }
          if (x.isFunction() || x instanceof NamedFunctionT) {
            return x.toFunction().getResult();
          // } else if () {
          } else {
            return ErrorT.TYPE;
          }
        }
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
