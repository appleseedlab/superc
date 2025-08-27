package superc.cdesugarer;

import java.util.List;
import java.util.LinkedList;

import xtc.type.Type;
import xtc.type.VariableT;
import xtc.type.AliasT;
import xtc.type.StructOrUnionT;

import superc.cdesugarer.Declarator.ArrayDeclarator;

import superc.core.Syntax;
import xtc.Constants;


/**
 * This class represents a single-configuration declaration and is
 * used by Declaration to get the type and string versions of the
 * declaration.
 */
class Declaration {
  /** The type. */
  protected final TypeSpecifier typespecifier;

  /** The declarator. */
  protected final Declarator declarator;

  protected boolean isField;
  
  public Declaration(TypeSpecifier typespecifier, Declarator declarator) {
    this.typespecifier = typespecifier;
    this.declarator = declarator;
  }

  public Declarator getDeclarator() {
    return declarator;
  }

  public TypeSpecifier getTypeSpec() {
    return new TypeSpecifier(typespecifier);
  }

  /**
   * Returns true if the type specifier is invalid.
   */
  public boolean hasTypeError() {
      return typespecifier.getType().isError() || declarator.hasTypeError() || notCompatible();
  }

  /**
   * Get the name from the declarator.
   */
  public String getName() {
    return this.declarator.getName();
  }

  /**
   * Returns true if the declaration has a name.  Struct fields can
   * have declarations with no name.
   */
  public boolean hasName() {
    return this.declarator.hasName();
  }

  public boolean isFlexible() {
    return declarator.isFlexible();
  }

  /**
   * Renames the declaration.  If the declarator is abstract, that
   * object will cause an illegal state exception.
   */
  public Declaration rename(String renaming) {
    Declaration d =  new Declaration(this.typespecifier, this.declarator.rename(renaming));
    if (isField) {
	d.setField();
    }
    return d;
  }

  /*
   * Gets the type that this declaration defines.  This is meant to be
   * used by the desugaring to wrap the type with the renaming using
   * VariableT, AliasT, or NamedFunctionT.
   */
  public Type getType() {
    Type t = declarator.getType(typespecifier.getType());
    if (isField) {
      if (hasName()) {
        t = VariableT.newField(t,getName());
      } else {
        t = VariableT.newField(t,"");
      }
    }
    return t; 
  }

  public void setField() {
    isField = true;
  }

  public String printType() {
    return getType().printTypeNameless();
    //return String.format("%s %s", typespecifier.toString(), declarator.printType());
  }
    
    public String printType(String x) {
      return String.format("%s %s:%s", typespecifier.toString(), x, declarator.printType());
    }
  
  public String toString() {
    return String.format("%s %s", typespecifier.toString(), declarator.toString());
  }

  public String toString(int len) {
    return String.format("%s %s", typespecifier.toString(), declarator.toString(len));
  }
  
  /**
   * Returns false if the typespecifier && declarator aren't valid
   */
  private boolean notCompatible(){
    Type t = typespecifier.getType().resolve();
    if (
        //void is only allowed if right is a function, pointer, or is abstract
        (t.isVoid() &&
         !typespecifier.contains(Constants.ATT_STORAGE_TYPEDEF) &&
         !declarator.isFunctionDeclarator() &&
         !declarator.isPointerDeclarator() &&
         !declarator.isPointerAbstractDeclarator() &&
         !declarator.isQualifiedPointerDeclarator() &&
         !declarator.isQualifiedPointerAbstractDeclarator() &&
         !declarator.isEmptyDeclarator()) ||
        //if the left is inline, right must be a function
        (typespecifier.hasInline() && !declarator.isFunctionDeclarator()))
      return true;
    return false;
  }

  public boolean isNonPointerForwardRef() {
    Type t = typespecifier.getType();
    return ((t.isStruct() || t.isUnion()) && ((StructOrUnionT)t).getName().startsWith("__forward_tag_reference"))
      && !(declarator.isPointerDeclarator() || declarator.isQualifiedPointerDeclarator()) ;
  }
}

