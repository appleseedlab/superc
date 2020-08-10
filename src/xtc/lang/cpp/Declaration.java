package xtc.lang.cpp;

import xtc.type.Type;
import xtc.type.VariableT;
import xtc.type.AliasT;

/**
 * This class represents a single-configuration declaration and is
 * used by Declaration to get the type and string versions of the
 * declaration.
 */
class Declaration {
  /** The type. */
  protected final TypeBuilder typebuilder;

  /** The declarator. */
  protected final Declarator declarator;

  public Declaration(TypeBuilder typebuilder, Declarator declarator) {
    this.typebuilder = typebuilder;
    this.declarator = declarator;
  }

  /**
   * Returns true if the type specifier is invalid.
   */
  public boolean hasTypeError() {
    return typebuilder.hasTypeError();
  }

  /**
   * Get the name from the declarator.
   */
  public String getName() {
    return this.declarator.getName();
  }

  /*
   * Gets the type that this declaration defines.  This is meant to be
   * used by the desugaring to wrap the type with the renaming using
   * VariableT, AliasT, or NamedFunctionT.
   */
  public Type getType() {
    String name = declarator.getName();
    return declarator.getType(typebuilder.toType());
  }

  public String toString() {
    return String.format("%s %s", typebuilder.toString(), declarator.toString());
  }
}

