package superc.cdesugarer;

import java.util.List;
import java.util.LinkedList;

import xtc.type.Type;
import xtc.type.VariableT;
import xtc.type.AliasT;

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

  public Declaration(TypeSpecifier typespecifier, Declarator declarator) {
    this.typespecifier = typespecifier;
    this.declarator = declarator;
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

  /**
   * Renames the declaration.  If the declarator is abstract, that
   * object will cause an illegal state exception.
   */
  public Declaration rename(String renaming) {
    return new Declaration(this.typespecifier, this.declarator.rename(renaming));
  }

  /*
   * Gets the type that this declaration defines.  This is meant to be
   * used by the desugaring to wrap the type with the renaming using
   * VariableT, AliasT, or NamedFunctionT.
   */
  public Type getType() {
    return declarator.getType(typespecifier.getType());
  }

  public String toString() {
    return String.format("%s %s", typespecifier.toString(), declarator.toString());
  }

  /**
   * Returns false if the typespecifier && declarator aren't valid
   */
  private boolean notCompatible(){
    Type t = typespecifier.getType().resolve();
    if ( t.isVoid() &&
         !typespecifier.contains(Constants.ATT_STORAGE_TYPEDEF) &&
         !declarator.isFunctionDeclarator() &&
         !declarator.isPointerDeclarator() &&
         !declarator.isEmptyDeclarator())
      return true;
    return false;
  }
}

