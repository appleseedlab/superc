package xtc.lang.cpp;

import xtc.type.Type;
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
   * Gets the type that this declaration defines.  This works by
   * combining the type specifier with the declarator (type
   * constructor).  Declaration handles creating an alias type, since
   * only when we know there is a typedef qualifier and the complete
   * type can we construct it.
   */
  public Type getType() {
    Type type = declarator.getType(typebuilder.toType());
    if (typebuilder.isTypedef()) {
      String name = declarator.getName();
      type = new AliasT(name, type);
    }
    return type;
  }

  public String toString() {
    return String.format("%s %s", typebuilder.toString(), declarator.toString());
  }
}

