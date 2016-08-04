/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2005-2008 Robert Grimm
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
package xtc.lang;

import java.math.BigInteger;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.IdentityHashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import xtc.Constants;
import xtc.Limits;

import xtc.tree.Attribute;
import xtc.tree.GNode;
import xtc.tree.Node;
import xtc.tree.Token;
import xtc.tree.Visitor;

import xtc.type.AliasT;
import xtc.type.ArrayT;
import xtc.type.BooleanT;
import xtc.type.C;
import xtc.type.CastReference;
import xtc.type.Constant;
import xtc.type.DynamicReference;
import xtc.type.EnumT;
import xtc.type.EnumeratorT;
import xtc.type.ErrorT;
import xtc.type.FieldReference;
import xtc.type.FunctionT;
import xtc.type.InternalT;
import xtc.type.LabelT;
import xtc.type.NullReference;
import xtc.type.NumberT;
import xtc.type.PointerT;
import xtc.type.Reference;
import xtc.type.StaticReference;
import xtc.type.StringReference;
import xtc.type.StructOrUnionT;
import xtc.type.StructT;
import xtc.type.Tagged;
import xtc.type.Type;
import xtc.type.Type.Tag;
import xtc.type.UnionT;
import xtc.type.VariableT;
import xtc.type.VoidT;

import xtc.util.SymbolTable;
import xtc.util.SymbolTable.Scope;
import xtc.util.Runtime;
import xtc.util.SingletonIterator;
import xtc.util.Utilities;

/**
 * A visitor to type check C programs.
 *
 * @author Robert Grimm
 * @version $Revision: 1.214 $
 */
public class CAnalyzer extends Visitor {

  /**
   * The semantic information contained in a sequence of declaration
   * specifiers.
   */
  public class Specifiers extends Visitor {

    /** The declaration specifiers. */
    protected GNode specifiers;

    /** The flag for whether a tag reference is a declaration. */
    protected boolean refIsDecl;

    /** The type, if any. */
    protected Type type;

    /** The storage class attribute, if any. */
    private Attribute storage;

    /** The thread-local attribute, if any. */
    private Attribute threadlocal;

    /** The inline attribute, if any. */
    private Attribute function;

    /** Any other attributes. */
    private List<Attribute> attributes;

    // The internal state for tracking type specifiers.
    private boolean seenSigned;
    private boolean seenUnsigned;
    private boolean seenBool;
    private boolean seenChar;
    private boolean seenShort;
    private boolean seenInt;
    private int     longCount;
    private boolean seenFloat;
    private boolean seenDouble;
    private boolean seenComplex;

    /**
     * Create a new sequence of specifiers.  This constructor analyzes
     * the specified AST node and may print error messages as a
     * result.
     *
     * @param specifiers The node holding the declaration specifiers
     *   (which may be <code>null</code>).
     * @param refIsDecl The flag for whether a struct/union reference
     *   also is a struct/union declaration.
     */
    public Specifiers(GNode specifiers, boolean refIsDecl) {
      // Remember the arguments.
      this.specifiers = specifiers;
      this.refIsDecl  = refIsDecl;

      // Process the individual specifiers.
      if (null != specifiers) {
        for (Object o : specifiers) dispatch((Node)o);
      }

      // Fill in the resulting type.
      if (null != type) {
        // Nothing to do.

      } else if (seenBool) {
        type = BooleanT.TYPE;
      } else if (seenChar) {
        if (seenUnsigned) {
          type = NumberT.U_CHAR;
        } else if (seenSigned) {
          type = NumberT.S_CHAR;
        } else {
          type = NumberT.CHAR;
        }
      } else if (seenShort) {
        if (seenUnsigned) {
          type = NumberT.U_SHORT;
        } else {
          type = NumberT.SHORT;
        }
      } else if (seenFloat) {
        if (seenComplex) {
          type = NumberT.FLOAT_COMPLEX;
        } else {
          type = NumberT.FLOAT;
        }
      } else if (seenDouble) {
        if (0 < longCount) {
          if (seenComplex) {
            type = NumberT.LONG_DOUBLE_COMPLEX;
          } else {
            type = NumberT.LONG_DOUBLE;
          }
        } else {
          if (seenComplex) {
            type = NumberT.DOUBLE_COMPLEX;
          } else {
            type = NumberT.DOUBLE;
          }
        }
      } else if (1 == longCount) {
        if (seenUnsigned) {
          type = NumberT.U_LONG;
        } else {
          type = NumberT.LONG;
        }
      } else if (1 < longCount) {
        if (seenUnsigned) {
          type = NumberT.U_LONG_LONG;
        } else {
          type = NumberT.LONG_LONG;
        }
      } else if (seenUnsigned) {
        type = NumberT.U_INT;
      } else if (seenSigned) {
        type = NumberT.S_INT;
      } else if (seenInt) {
        type = NumberT.INT;
      } else {
        type = C.IMPLICIT;
      }

      // Annotate the type.
      if ((! type.hasError()) && (null != attributes)) {
        type = type.annotate().attribute(attributes);
      }

      // Seal the type.
      type.seal();
    }

    /**
     * Get the base type.  The base type has been annotated with all
     * attributes besides the storage class and function specifier
     * attributes.
     *
     * @return The base type.
     */
    public Type getBaseType() {
      return type;
    }

    /**
     * Determine whether the base type is the default type.
     *
     * @return <code>true</code> if the base type is the default type.
     */
    public boolean isDefault() {
      return type.hasTag(Tag.INTEGER) &&
        type.resolve().hasAttribute(Constants.ATT_IMPLICIT);
    }

    /**
     * Determine whether the specifiers contain the specified
     * attribute.
     *
     * @param att The attribute.
     * @return <code>true</code> if the specifiers contain the
     *   specified attribute.
     */
    public boolean contains(Attribute att) {
      if ((null != attributes) && attributes.contains(att)) return true;
      if (att.equals(storage)) return true;
      if (att.equals(threadlocal)) return true;
      return att.equals(function);
    }

    /**
     * Determine whether the specifiers include any attributes besides
     * a function specifier, storage class, and thread-local
     * specifier.
     *
     * @return <code>true</code> if the specifiers include any
     *   attributes besides a function specifier, storage class, and
     *   thread-local specifier.
     */
    public boolean hasBaseAttributes() {
      return null != attributes;
    }

    /**
     * Determine whether the specifiers include a function specifier.
     *
     * @return <code>true</code> if the specifiers include a function
     *   specifier.
     */
    public boolean hasInline() {
      return null != function;
    }

    /**
     * Determine whether the specifiers include a thread-local
     * specifier.
     *
     * @return <code>true</code> if the specifiers include a
     *   thread-local specifier.
     */
    public boolean hasThreadLocal() {
      return null != threadlocal;
    }

    /**
     * Get the storage class.
     *
     * @return The storage class or <code>null</code> if the
     * specifiers do contain one.
     */
    public Attribute getStorageClass() {
      return storage;
    }

    /**
     * Annotate the specified base type.  This method annotates the
     * specified type with all attributes besides the storage class,
     * thread-local specifier, and function specifier attributes.
     *
     * @param base The base type.
     * @return The annnotated base type.
     */
    public Type annotateBase(Type base) {
      return (null != attributes)? base.attribute(attributes) : base;
    }

    /**
     * Annotate the specified full type.  This method annotates the
     * specified type with any storage class, thread-local specifier,
     * and function specifier attributes.
     *
     * @param full The full type.
     * @return The annotated full type.
     */
    public Type annotateFull(Type full) {
      // If the full type is the same type as the base type, wrap the
      // type with an annotated pseudo-type to prevent changes to the
      // base type across several declarations.
      if (null != storage || null != threadlocal || null != function) {
        if (type == full)        full = full.annotate();
        if (null != storage)     full = full.attribute(storage);
        if (null != threadlocal) full = full.attribute(threadlocal);
        if (null != function)    full = full.attribute(function);
      }
      return full;
    }

    /** Add the specified attribute. */
    protected void add(Attribute att) {
      if (null == attributes) {
        attributes = new ArrayList<Attribute>();
        attributes.add(att);
      } else if (! attributes.contains(att)) {
        attributes.add(att);
      }
    }

    /** Test for previous storage class specifier and report error. */
    protected boolean testStorageClass() {
      if (null == storage) {
        return false;
      } else {
        runtime.error("multiple storage classes in declaration specifiers",
                      specifiers);
        return true;
      }
    }

    /** Test for previous type. */
    protected boolean hasType() {
      return
        (seenBool || seenChar || seenShort || seenInt || (0 < longCount) ||
         seenFloat || seenDouble || seenComplex ||
         (null != type));
    }

    /** Report error indicating multiple types. */
    protected void multipleTypes() {
      runtime.error("multiple data types in declaration specifiers",
                    specifiers);
      type = ErrorT.TYPE;
    }

    /** Process the auto specifier. */
    public void visitAutoSpecifier(GNode n) {
      if (Constants.ATT_STORAGE_AUTO.equals(storage)) {
        runtime.error("duplicate 'auto'", n);
      } else if (! testStorageClass()) {
        storage = Constants.ATT_STORAGE_AUTO;
      }
    }
    
    /** Process the extern specifier. */
    public void visitExternSpecifier(GNode n) {
      if (Constants.ATT_STORAGE_EXTERN.equals(storage)) {
        runtime.error("duplicate 'extern'", n);
      } else if (! testStorageClass()) {
        storage = Constants.ATT_STORAGE_EXTERN;

        if (null != threadlocal) {
          runtime.error("'__thread' before 'extern'", specifiers);
        }
      }
    }
    
    /** Process the register specifier. */
    public void visitRegisterSpecifier(GNode n) {
      if (Constants.ATT_STORAGE_REGISTER.equals(storage)) {
        runtime.error("duplicate 'register'", n);
      } else if (! testStorageClass()) {
        storage = Constants.ATT_STORAGE_REGISTER;
      }
    }
    
    /** Process the static specifier. */
    public void visitStaticSpecifier(GNode n) {
      if (Constants.ATT_STORAGE_STATIC.equals(storage)) {
        runtime.error("duplicate 'static'", n);
      } else if (! testStorageClass()) {
        storage = Constants.ATT_STORAGE_STATIC;

        if (null != threadlocal) {
          runtime.error("'__thread' before 'static'", specifiers);
        }
      }
    }
    
    /** Process the typedef specifier. */
    public void visitTypedefSpecifier(GNode n) {
      if (Constants.ATT_STORAGE_TYPEDEF.equals(storage)) {
        runtime.error("duplicate 'typedef'", n);
      } else if (! testStorageClass()) {
        storage = Constants.ATT_STORAGE_TYPEDEF;
      }
    }

    /** Process the thread-local specifier. */
    public void visitThreadSpecifier(GNode n) {
      if (null != threadlocal) {
        runtime.error("duplicate '__thread'", n);
      } else {
        threadlocal = Constants.ATT_THREAD_LOCAL;
      }
    }

    /** Process the typeof specifier. */
    public void visitTypeofSpecifier(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        type = processExpression(n.getNode(0));

        // Strip any annotations from the type, but do keep the
        // qualifiers.
        if (type.hasEnum()) {
          type = c().qualify(type.toEnum(), type);
        } else {
          type = c().qualify(type.resolve(), type);
        }
      }
    }
    
    /** Process the volatile qualifier. */
    public void visitVolatileQualifier(GNode n) {
      add(Constants.ATT_VOLATILE);
    }
    
    /** Process the constant qualifier. */
    public void visitConstantQualifier(GNode n) {
      add(Constants.ATT_CONSTANT);
    }
    
    /** Process the restrict qualifier. */
    public void visitRestrictQualifier(GNode n) {
      add(Constants.ATT_RESTRICT);
    }
    
    /** Process the function specifier. */
    public void visitFunctionSpecifier(GNode n) {
      if (null == function) {
        function = Constants.ATT_INLINE;
      }
    }
    
    /** Process the signed type specifier. */
    public void visitSigned(GNode n) {
      if (seenUnsigned) {
        seenSigned = true;
        runtime.error("both 'signed' and 'unsigned' in declaration " +
                      "specifiers", specifiers);
      } else if (seenSigned) {
        runtime.error("duplicate 'signed'", n);
      } else {
        seenSigned = true;
      }
    }
    
    /** Process the unsigned type specifier. */
    public void visitUnsigned(GNode n) {
      if (seenSigned) {
        seenUnsigned = true;
        runtime.error("both 'signed' and 'unsigned' in declaration " +
                      "specifiers", specifiers);
      } else if (seenUnsigned) {
        runtime.error("duplicate 'unsigned'", n);
      } else {
        seenUnsigned = true;
      }
    }
    
    /** Process the boolean type specifier. */
    public void visitBool(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        seenBool = true;
      }
    }
    
    /** Process the char type specifier. */
    public void visitChar(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        seenChar = true;
      }
    }
    
    /** Process the short specifier. */
    public void visitShort(GNode n) {
      if (seenBool || seenChar || seenShort || (0 < longCount) ||
          seenFloat || seenDouble || seenComplex ||
          (null != type)) {
        multipleTypes();
      } else {
        seenShort = true;
      }
    }
    
    /** Process the int type specifier. */
    public void visitInt(GNode n) {
      if (seenBool || seenChar || seenInt ||
          seenFloat || seenDouble || seenComplex ||
          (null != type)) {
        multipleTypes();
      } else {
        seenInt = true;
      }
    }
    
    /** Process the long type specifier. */
    public void visitLong(GNode n) {
      if (seenBool || seenChar || seenShort || (1 < longCount) ||
          seenFloat ||
          ((seenDouble || seenComplex) &&
           (0 < longCount)) ||
          (null != type)) {
        multipleTypes();
      } else {
        longCount++;
      }
    }
    
    /** Process the float type specifier. */
    public void visitFloat(GNode n) {
      if (seenBool || seenChar || seenShort || seenInt || (0 < longCount) ||
          seenDouble ||
          (null != type)) {
        multipleTypes();
      } else {
        seenFloat = true;
      }
    }
    
    /** Process the double type specifier. */
    public void visitDouble(GNode n) {
      if (seenBool || seenChar || seenShort || seenInt || (1 < longCount) ||
          seenFloat ||
          (null != type)) {
        multipleTypes();
      } else {
        seenDouble = true;
      }
    }
    
    /** Process the complex type specifier. */
    public void visitComplex(GNode n) {
      if (seenBool || seenChar || seenShort || seenInt || (1 < longCount) ||
          (null != type)) {
        multipleTypes();
      } else {
        seenComplex = true;
      }
    }

    /**
     * Check that the tag declaration is not located within a
     * parameter list.  If the declaration is located within a
     * parameter list, this method prints the appropriate warning.
     *
     * @param node The node.
     * @param kind The kind of tag.
     */
    private void checkNotParameter(Node node, String kind) {
      if (TMP_SCOPE.equals(table.current().getName())) {
        final String tag = node.getString(1);
        final String msg;
        if (null == tag) {
          msg = "anonymous " + kind + " declared inside parameter list";
        } else {
          msg = "'" + kind + " " + tag + "' declared inside parameter list";
        }

        runtime.warning(msg, node);
      }
    }
    
    /**
     * Process the structure declaration list.  Note that this
     * method assumes that the current symbol table scope is the
     * corresponding struct's or union's scope.
     */
    private List<VariableT> processMembers(GNode declarationList,
                                           boolean isStruct) {
      final int       size      = declarationList.size() - 1;
      List<VariableT> members   = new ArrayList<VariableT>(size);
      HashSet<String> names     = new HashSet<String>();
      int             count     = 0;
      for (int i=0; i<size; i++) {
        final GNode      declaration = declarationList.getGeneric(i);
        final GNode      specifiers  = declaration.getGeneric(1);
        final Specifiers spec        = newSpecifiers(specifiers, false);

        if (null == declaration.get(2)) {
          // We expect an unnamed struct/union member.
          final Type type = spec.annotateFull(spec.getBaseType());

          if (type.hasStructOrUnion() &&
              type.toTagged().isUnnamed() &&
              ! pedantic) {
            // Check for incomplete types (C99 6.7.2.1).
            if (c().isIncomplete(type)) {
              final String kind = type.hasTag(Tag.STRUCT) ? "struct" : "union";
              runtime.error("unnamed " + kind + " has incomplete type",
                            declaration);
            } else if (c().hasTrailingArray(type)) {
              runtime.error("unnamed struct ends with flexible array member",
                            declaration);
            }
            members.add(VariableT.newField(type, null));

          } else {
            runtime.warning("declaration does not declare anything",
                            declaration);
          }

        } else {
          Iterator<Object> iter = declaration.getGeneric(2).iterator();
          while (iter.hasNext()) {
            GNode         declarator = GNode.cast(iter.next());
            final GNode   original   = declarator;
            
            final boolean isBitField = declarator.hasName("BitField");
            GNode         widthExpr  = null;
            int           width      = -1;
            if (isBitField) {
              widthExpr  = declarator.getGeneric(2);
              declarator = declarator.getGeneric(1);
            }
            
            final GNode   identifier = getDeclaredId(declarator);
            String        name       = null;
            if (null != identifier) {
              count++;
              name = identifier.getString(0);
            }
            Type    type       = getDeclaredType(spec.getBaseType(), declarator);
            type               = spec.annotateFull(type);

            if (isBitField) {
              final Type         resolved = type.resolve();
              final NumberT.Kind kind     = resolved.isInteger() ?
                resolved.toInteger().getKind() : null;

              // Make sure the base type is valid.  Consistent with
              // GCC, we allow any integer type, not just __Bool,
              // (signed) int, and unsigned int (unless, of course, we
              // are running in pedantic mode).
              if ((! resolved.isBoolean()) &&
                  ((! resolved.isInteger()) ||
                   (resolved.isInteger() &&
                    pedantic &&
                    (! NumberT.equal(NumberT.Kind.INT,   kind)) &&
                    (! NumberT.equal(NumberT.Kind.U_INT, kind))))) {
                if (null == identifier) {
                  runtime.error("bit-field has invalid type", original);
                } else {
                  runtime.error("bit-field '" + name + "' has invalid type",
                                original);
                }
              }
              
              // Process the width expression.
              final Type widthType = processExpression(widthExpr);
              
              if (widthType.hasError()) {
                // Ignore to avoid cascading error messages
                // but patch in width.
                width = 0;
                
              } else if ((! widthType.hasConstant()) ||
                         (! c().isIntegral(widthType))) {
                if (null == identifier) {
                  runtime.error("bit-field width not an integer constant",
                                widthExpr);
                } else {
                  runtime.error("bit-field '" + name +
                                "' width not an integer constant", widthExpr);
                }
                // Patch in width.
                width = 0;
                
              } else if (c().isIntegral(resolved)) {
                final int typeWidth = (int)c().getWidth(resolved);

                BigInteger widthValue;
                try {
                  widthValue = widthType.getConstant().bigIntValue();
                } catch (IllegalStateException x) {
                  if (null == identifier) {
                    runtime.error("can't compute width in bit-field", widthExpr);
                  } else {
                    runtime.error("can't compute width in bit-field '" + name +
                                  "'", widthExpr);
                  }
                  widthValue = BigInteger.ZERO;
                }
                  
                // Test: widthValue > typeWidth
                if (widthValue.compareTo(BigInteger.valueOf(typeWidth)) > 0) {
                  if (null == identifier) {
                    runtime.error("bit-field width exceeds its type",
                                  widthExpr);
                  } else {
                    runtime.error("bit-field '" + name +
                                  "' width exceeds its type", widthExpr);
                  }
                  // Patch in width.
                  width = typeWidth;
                  
                  // Test: widthValue < 0
                } else if (widthValue.compareTo(BigInteger.ZERO) < 0) {
                  if (null == identifier) {
                    runtime.error("negative width in bit-field", widthExpr);
                  } else {
                    runtime.error("negative width in bit-field '" + name +
                                  "'", widthExpr);
                  }
                  // Patch in width.
                  width = 0;

                } else if (widthValue.compareTo(BigInteger.ZERO) == 0) {
                  // C99 6.7.2.1-3: Zero width bit-fields have no declarator.
                  if (null != identifier) {
                    runtime.error("zero width for bit-field '" + name + "'",
                                  widthExpr);
                  }
                  width = 0;
                  
                } else {
                  // Use specified value.
                  width = widthValue.intValue();
                }
                
              } else {
                // Width does not matter b/c the base type is invalid.
                width = 0;
              }
              
            } else {
              // Enforce constraints on incomplete types (C99 6.7.2.1)
              // and on fields not being functions.
              final Type resolved = type.resolve();

              if (! checkType(declaration, name, type)) {
                // Error has already been reported.

              } else if (resolved.isFunction()) {
                runtime.error("field '" + name + "' declared as a function",
                              declaration);

              } else if (resolved.isArray()) {
                ArrayT array = resolved.toArray();
                
                if (c().isIncomplete(array.getType()) ||
                    c().hasTrailingArray(array.getType())) {
                  runtime.error("field '" + name +
                                "' has array with incomplete element type",
                                declaration);

                } else if (array.isVarLength()) {
                  // GCC allows variable length arrays in structs and
                  // unions outside external declarations.
                  if (pedantic) {
                    runtime.error("field '" + name + "' has variable length " +
                                  "array type", declaration);
                  } else if (isTopLevel &&
                             (! TMP_SCOPE.equals(table.current().getName()))) {
                    runtime.error("variable length array type declared " +
                                  "outside of any function", declaration);
                  }

                } else if (! array.hasLength()) {
                  if (! isStruct) {
                    runtime.error("flexible array member '" + name + 
                                  "' in union", declaration);
                  } else if ((i < size-1) || iter.hasNext()) {
                    runtime.error("flexible array member '" + name +
                                  "' not at end of struct", declaration);
                  } else if (1 >= count) {
                    runtime.error("flexible array member '" + name +
                                  "' in otherwise empty struct", declaration);
                  }
                }
                
              } else if (c().isIncomplete(type)) {
                if (resolved.isVoid()) {
                  runtime.error("field '" + name + "' declared void",
                                declaration);
                } else {
                  runtime.error("field '" + name + "' has incomplete type",
                                declaration);
                }
              } else if (c().hasTrailingArray(type)) {
                // GCC allows struct fileds with flexible array
                // members.
                if (pedantic) {
                  runtime.error("field '" + name +
                                "' has struct with flexible array member",
                                declaration);
                }
              } else if (c().isVariablyModified(type)) {
                // GCC allows variably modified types in structs and
                // unions outside external declarations.
                if (pedantic) {
                  runtime.error("field '" + name + "' has variably modified " +
                                "type", declaration);
                } else if (isTopLevel &&
                           (! TMP_SCOPE.equals(table.current().getName()))) {
                  runtime.error("variably modified type declared " +
                                "outside of any function", declaration);
                }
              }
            }

            if (names.contains(name)) {
              runtime.error("duplicate member '" + name + "'", original);
            } else {
              if (null != name) names.add(name);
              if (-1 == width) {
                members.add(VariableT.newField(type, name));
              } else {
                members.add(VariableT.newBitfield(type, name, width));
              }
            }
          }
        }
      }
      
      return members;
    }
    
    /** Process the structure type definition. */
    public void visitStructureTypeDefinition(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        String tag  = n.getString(1);
        String name;
        if (null == tag) {
          tag  = table.freshName("tag");
          name = tag;
        } else {
          name = SymbolTable.toTagName(tag);
        }
        
        if (table.current().isDefinedLocally(name)) {
          final Type t = (Type)table.current().lookupLocally(name);

          if (! t.isStruct()) {
            runtime.error("'" + tag + "' defined as wrong kind of tag", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;

          } else if (null != t.toTagged().getMembers()) {
            runtime.error("redefinition of 'struct " + tag + "'", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;

          } else if (t.hasAttribute(Constants.ATT_DEFINED)) {
            runtime.error("nested redefinition of 'struct " + tag + "'", n);
            type = ErrorT.TYPE;
            return;

          } else {
            type = t;
          }
        } else {
          checkNotParameter(n, "struct");

          // Declare the struct so that members can reference it.
          type = new StructT(tag);
          table.current().define(name, type);
        }

        // Update the location.
        type.setLocation(n);

        // Update the GCC attributes.
        for (Attribute a : toAttributeList(n.getGeneric(0))) {
          type.addAttribute(a);
        }
        for (Attribute a : toAttributeList(n.getGeneric(3))) {
          type.addAttribute(a);
        }

        // Process the members and update the struct declaration.  Use
        // defined attribute to protect against nested redefinition.
        type.addAttribute(Constants.ATT_DEFINED);
        List<VariableT> members = processMembers(n.getGeneric(2), true);
        type.toStruct().setMembers(members);
        type.removeAttribute(Constants.ATT_DEFINED);

        // Seal the struct.
        type.seal();

        // Mark the node.
        mark(n, type);
      }
    }
    
    /** Process the structure type reference. */
    public void visitStructureTypeReference(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        final String tag  = n.getString(1);
        final String name = SymbolTable.toTagName(tag);

        if ((refIsDecl && table.current().isDefinedLocally(name)) ||
            ((! refIsDecl) && table.isDefined(name))) {
          final Type t = (Type)table.lookup(name);

          if (! t.isStruct()) {
            runtime.error("'" + tag + "' defined as wrong kind of tag", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;
          } else {
            type = t;

            // If the struct has not yet been defined, update the
            // location and GCC attributes.
            if (refIsDecl && (null == type.toStruct().getMembers())) {
              type.setLocation(n);
              for (Attribute a : toAttributeList(n.getGeneric(0))) {
                type.addAttribute(a);
              }
            }
          }
        } else {
          checkNotParameter(n, "struct");

          type = new StructT(tag).locate(n);
          for (Attribute a : toAttributeList(n.getGeneric(0))) {
            type.addAttribute(a);
          }
          table.current().define(name, type);
        }

        // Mark the node.
        mark(n, type);
      }
    }
    
    /** Process the union type definition. */
    public void visitUnionTypeDefinition(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        String tag  = n.getString(1);
        String name;
        if (null == tag) {
          tag  = table.freshName("tag");
          name = tag;
        } else {
          name = SymbolTable.toTagName(tag);
        }
        
        if (table.current().isDefinedLocally(name)) {
          final Type t = (Type)table.current().lookupLocally(name);

          if (! t.isUnion()) {
            runtime.error("'" + tag + "' defined as wrong kind of tag", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;

          } else if (null != t.toTagged().getMembers()) {
            runtime.error("redefinition of 'union " + tag + "'", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;

          } else if (t.hasAttribute(Constants.ATT_DEFINED)) {
            runtime.error("nested redefinition of 'union " + tag + "'", n);
            type = ErrorT.TYPE;
            return;

          } else {
            type = t;
          }
        } else {
          checkNotParameter(n, "union");

          // Declare the union so that members can reference it.
          type = new UnionT(tag);
          table.current().define(name, type);
        }

        // Update the location.
        type.setLocation(n);

        // Update the GCC attributes.
        for (Attribute a : toAttributeList(n.getGeneric(0))) {
          type.addAttribute(a);
        }
        for (Attribute a : toAttributeList(n.getGeneric(3))) {
          type.addAttribute(a);
        }

        // Process the members and update the union declaration.  Use
        // defined attribute to protected against nested redefinition.
        type.addAttribute(Constants.ATT_DEFINED);
        List<VariableT> members = processMembers(n.getGeneric(2), false);
        type.toUnion().setMembers(members);
        type.removeAttribute(Constants.ATT_DEFINED);

        // Seal the union.
        type.seal();

        // Mark the node.
        mark(n, type);
      }
    }
    
    /** Process the union type reference. */
    public void visitUnionTypeReference(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        final String tag  = n.getString(1);
        final String name = SymbolTable.toTagName(tag);

        if ((refIsDecl && table.current().isDefinedLocally(name)) ||
            ((! refIsDecl) && table.isDefined(name))) {
          final Type t = (Type)table.lookup(name);

          if (! t.isUnion()) {
            runtime.error("'" + tag + "' defined as wrong kind of tag", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;
          } else {
            type = t;

            // If the union has not yet been defined, update the
            // location and GCC attributes.
            if (refIsDecl && (null == type.toUnion().getMembers())) {
              type.setLocation(n);
              for (Attribute a : toAttributeList(n.getGeneric(0))) {
                type.addAttribute(a);
              }
            }
          }
        } else {
          checkNotParameter(n, "union");

          type = new UnionT(tag).locate(n);
          for (Attribute a : toAttributeList(n.getGeneric(0))) {
            type.addAttribute(a);
          }
          table.current().define(name, type);
        }

        // Mark the node.
        mark(n, type);
      }
    }
    
    /** Process the enumeration type definition. */
    public void visitEnumerationTypeDefinition(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        String tag  = n.getString(1);
        String name;
        if (null == tag) {
          tag  = table.freshName("tag");
          name = tag;
        } else {
          name = SymbolTable.toTagName(tag);
        }

        if (table.current().isDefinedLocally(name)) {
          final Type t = (Type)table.current().lookupLocally(name);

          if (! t.isEnum()) {
            runtime.error("'" + tag + "' defined as wrong kind of tag", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;

          } else if (null != t.toTagged().getMembers()) {
            runtime.error("redefinition of 'enum " + tag + "'", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;

          } else {
            type = t;
          }
        } else {
          checkNotParameter(n, "enum");

          type = new EnumT(tag);
        }
        
        // Process the enumerators.
        final GNode             enumerators = n.getGeneric(2);
        final List<EnumeratorT> types       =
          new ArrayList<EnumeratorT>(enumerators.size());
        BigInteger              lastValue   = BigInteger.ONE.negate();
        for (Object o : enumerators) {
          final GNode  rator = GNode.cast(o);
          final String rname = rator.getString(0);
          final Node   vnode = rator.getNode(1); // The value node.

          BigInteger value = null;
          if (null != vnode) {
            // The enumerator has an explicitly specified value.
            final Type vtype = processExpression(vnode);

            if (vtype.hasError()) {
              // Ignore to avoid cascading error messages.

            } else if ((! vtype.hasConstant()) ||
                       (! c().isIntegral(vtype))) {
              runtime.error("enumerator value for '" + rname +
                            "' is not an integer constant", vnode);

            } else {
              try {
                value     = vtype.getConstant().bigIntValue();
                lastValue = value;
              } catch (IllegalStateException x) {
                runtime.warning("can't compute value for '" + rname + "'",
                                vnode);
                value     = lastValue.add(BigInteger.ONE);
                lastValue = value;
              }
            }
          }

          if (null == value) {
            // If the value has not been specified or is erroneous,
            // fall back on increment-by-one.
            value     = lastValue.add(BigInteger.ONE);
            lastValue = value;
          }

          // Record the enumerator in the symbol table.
          final EnumeratorT ratorT =
            new EnumeratorT(c().fit(value), rname, value);
          if (table.current().isDefinedLocally(rname)) {
            runtime.error("redefinition of '" + rname + "'",
                          rator);
          } else {
            table.current().define(rname, ratorT);
          }

          // Add the enumerator to the list of enumerators.
          types.add(ratorT);
        }
        
        // Determine the minimum and maximum value.
        BigInteger min = BigInteger.ZERO;
        BigInteger max = BigInteger.ZERO;
        for (EnumeratorT r : types) {
          final BigInteger value = r.getConstant().bigIntValue();

          // Test: value < min
          if (value.compareTo(min) < 0) min = value;

          // Test: value > max
          if (value.compareTo(max) > 0) max = value;
        }

        // Find a fitting overall type.
        final Type baseT;
        if (Limits.fitsInt(min) &&
            Limits.fitsInt(max)) {
          baseT = NumberT.INT;
        } else if (Limits.fitsUnsignedInt(min) &&
                   Limits.fitsUnsignedInt(max)) {
          baseT = NumberT.U_INT;
        } else if (Limits.fitsLong(min) &&
                   Limits.fitsLong(max)) {
          baseT = NumberT.LONG;
        } else if (Limits.fitsUnsignedLong(min) &&
                   Limits.fitsUnsignedLong(max)) {
          baseT = NumberT.U_LONG;
        } else if (Limits.fitsLongLong(min) &&
                   Limits.fitsLongLong(max)) {
          baseT = NumberT.LONG_LONG;
        } else if (Limits.fitsUnsignedLongLong(min) &&
                   Limits.fitsUnsignedLongLong(max)) {
          baseT = NumberT.U_LONG_LONG;
        } else {
          runtime.error("enumeration values exceed range of largest integer", n);
          baseT = ErrorT.TYPE;
        }

        // Done.
        ((EnumT)type).setMembers(types);
        ((EnumT)type).setType(baseT);
        type.setLocation(n);
        for (Attribute a : toAttributeList(n.getGeneric(0))) {
          type.addAttribute(a);
        }
        for (Attribute a : toAttributeList(n.getGeneric(3))) {
          type.addAttribute(a);
        }
        type.seal();
        table.current().define(name, type);

        // Mark the node.
        mark(n, type);
      }
    }
    
    /** Process the enumeration type reference. */
    public void visitEnumerationTypeReference(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        final String tag  = n.getString(1);
        final String name = SymbolTable.toTagName(tag);

        if (table.isDefined(name)) {
          final Type t = (Type)table.lookup(name);

          if (! t.isEnum()) {
            runtime.error("'" + tag + "' defined as wrong kind of tag", n);
            reportPreviousTag(t);
            type = ErrorT.TYPE;
            return;
          } else {
            type = t;

            // If the enum has not yet been defined, update the
            // location and GCC attributes.
            if (null == type.toEnum().getMembers()) {
              type.setLocation(n);
              for (Attribute a : toAttributeList(n.getGeneric(0))) {
                type.addAttribute(a);
              }
            }
          }
        } else {
          checkNotParameter(n, "enum");

          type = new EnumT(tag).locate(n);
          for (Attribute a : toAttributeList(n.getGeneric(0))) {
            type.addAttribute(a);
          }
          table.current().define(name, type);
        }

        // Mark the node.
        mark(n, type);
      }
    }
    
    /** Process the void type specifier. */
    public void visitVoidTypeSpecifier(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        type = VoidT.TYPE;
      }
    }
    
    /** Process the variable argument list specifier. */
    public void visitVarArgListSpecifier(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        type = InternalT.VA_LIST;
      }
    }
    
    /** Process the typedef name. */
    public void visitTypedefName(GNode n) {
      if (hasType()) {
        multipleTypes();
      } else {
        final String name  = n.getString(0);
        final Type   value = (Type)table.current().lookup(name);

        if ((null != value) && value.isAlias()) {
          type = value;
        } else {
          runtime.error("typedef name '" + name + "' undefined", n);
          type = ErrorT.TYPE;
        }
      }
    }
    
    /** Process the attribute specifier. */
    public void visitAttributeSpecifier(GNode n) {
      final List<Attribute> atts = toAttributeList(n);

      if (! atts.isEmpty()) {
        if (null == attributes) {
          attributes = atts;
        } else {
          attributes.addAll(atts);
        }
      }
    }

  }

  // ========================================================================

  /** The saved state of the initializer. */
  static class State {
    public Type    base;
    public Type    element;
    public boolean top;
    public long    index;
    public long    size;

    public State(Type base, Type element, boolean top, long index, long size) {
      this.base    = base;
      this.element = element;
      this.top     = top;
      this.index   = index;
      this.size    = size;
    }
  }

  /** The semantic information contained in an initializer. */
  public class Initializer {

    /** The debug level. */
    private static final int DEBUG = 0;

    /** The overall initializer list. */
    private GNode node;

    /** The overall type. */
    private Type type;

    /** The flag for whether the type has automatic storage. */
    private boolean auto;

    /** The current base type. */
    private Type base;

    /** The current element type. */
    private Type element;

    /** The flag for whether the initializer is top-level. */
    private boolean top;

    /** The current index into aggregate types. */
    private long index;

    /** The size of aggregate types. */
    private long size;

    /** The count of a top-level array's elements. */
    private long count;

    /** The stack of processing states. */
    private List<State> states;

    /**
     * Create a new initializer.  The specified node must represent an
     * initializer list.
     *
     * @param node The node.
     * @param type The type.
     * @param auto The flag for automatic storage.
     */
    public Initializer(GNode node, Type type, boolean auto) {
      this.node      = node;
      this.type      = type;
      this.auto      = auto;
      this.base      = type.resolve();
      switch (this.base.tag()) {
      case ARRAY:
        this.element = base.toArray().getType().resolve();
        this.top     = true;
        this.size    = getSize(base);
        break;
      case STRUCT:
      case UNION:
        this.element = null;
        this.top     = false;
        this.size    = getSize(base);
        break;
      default:
        this.element = base;
        this.top     = true;
        this.size    = 1;
      }
      this.index     = -1;
      this.count     = 0;
      states         = new ArrayList<State>();
    }

    /**
     * Create a new nested initializer.  The specified node must
     * represent an initializer list.  Both types must have been
     * resolved.  The element type may be <code>null</code>.
     *
     * @param node The node.
     * @param base The base type.
     * @param element The element type.
     * @param auto The flag for automatic storage.
     */
    Initializer(GNode node, Type base, Type element, boolean auto) {
      this.node      = node;
      this.type      = base;
      this.auto      = auto;
      this.base      = base;
      this.element   = element;
      this.top       = false;
      this.size      = (base == element) ? 1 : getSize(base);
      this.index     = -1;
      this.count     = 0;
      states         = new ArrayList<State>();
    }

    /**
     * Process the initializer.  This method processes this
     * initializer, reporting any errors and returning the processed
     * type.  The processed type generally is the same as the type
     * provided to this class' constructor.  However, if this
     * intializer's type is a top-level incomplete array, it is
     * updated with the actual size.
     *
     * @return The processed type.
     */
    public Type process() {
      // DEBUG: Open brace.
      if (1 <= DEBUG) {
        runtime.console().pln('{').incr().flush();
      }

      // Iterate over the initializer list entries.
      final int num = node.size();
      for (int cursor = 0; cursor < num; cursor++) {
        // Get the entry and its children.
        final GNode entry       = node.getGeneric(cursor);
        final GNode designation = entry.getGeneric(0);
        final GNode initializer = entry.getGeneric(1);

        // Process the designation.
        if (! designation(designation)) {
          // DEBUG: Close brace.
          if (1 <= DEBUG) runtime.console().decr().indent().pln("};").flush();
          return getResult();
        }

        // Process the intializer.
        if (initializer.hasName("InitializerList")) {
          // DEBUG: Print the designation.
          if (1 <= DEBUG) {
            runtime.console().indent().p(toString()).p(" = ").flush();
          }

          switch (element.tag()) {
          case BOOLEAN:
          case INTEGER:
          case FLOAT:
          case POINTER: {
            runtime.warning("braces around scalar initializer", initializer);
            new Initializer(initializer, element, element, auto).process();
          } break;
          case ARRAY: {
            new Initializer(initializer, element, element.toArray().getType().
                            resolve(), auto).process();
          } break;
          default:
            new Initializer(initializer, element, null, auto).process();
          }

        } else {
          // Determine the right hand type.
          final Type right;
          if (runtime.test("optionMarkAST") &&
              initializer.getBooleanProperty(MARKED)) {
            right = (Type)initializer.getProperty(Constants.TYPE);
          } else {
            right = processExpression(initializer);
          }

          // Top-level initializer may only contain constant.
          if ((! auto) && 
              (! right.hasConstant()) &&
              (! c().hasConstRef(right))) {
            runtime.error("initializer element is not constant", initializer);
          }

          // Try to initialize the left-hand type with the right-hand
          // type.
          loop: while (true) {
            if (isInitializable(element, right)) {
              // DEBUG: Print the assignment.
              if (1 <= DEBUG) {
                runtime.console().indent().p(toString()).p(" = ");
                if (right.hasConstant()) {
                  runtime.console().p(right.getConstant().getValue().toString());
                } else if (c().hasConstRef(right)) {
                  runtime.console().p(c().getConstRef(right).toString());
                } else {
                  runtime.console().p("<val>");
                }
                runtime.console().pln(';').flush();
              }

              // Process the assignment and string size for any warnings.
              processAssignment(true,"initializer",initializer,element,right);
              processStringSize(initializer,"initializer",true,element,right);
              break;
            }

            switch (element.tag()) {
            case ARRAY: {
              // Initialize the array's elements.
              push(element);
            } break;

            case STRUCT:
            case UNION: {
              if (0 == element.toTagged().getMemberCount()) {
                // Continue with the next subobject.
                if (! designation(null)) {
                  // DEBUG: Close brace.
                  if (1 <= DEBUG) {
                    runtime.console().decr().indent().pln("};").flush();
                  }
                  return getResult();
                }

              } else {
                // Initialize the struct/union members.
                push(element);
              }
            } break;

            default:
              // The assignment fails.
              processAssignment(true,"initializer",initializer,element,right);
              break loop;
            }
          }
        }
      }

      // Check for empty scalar initializers.
      if ((0 == num) && c().isScalar(type)) {
        runtime.error("empty scalar initializer", node);
      }

      // DEBUG: Close brace.
      if (1 <= DEBUG) runtime.console().decr().indent().pln("};").flush();
      return getResult();
    }

    /**
     * Process the specified designation.  This method updates the
     * internal state to reflect the designation.
     *
     * @param designation The designation, which may be
     *   <code>null</code>.
     * @return <code>false</code> if the designation contains an
     *   error.
     */
    private boolean designation(GNode designation) {
      if (null == designation) {
        while (true) {
          index++;

          if ((-1 == size) || (index < size)) {
            // We have an object to initialize.
            if (base.hasStructOrUnion()) {
              // Set the element type for struct/union types.
              element = base.toTagged().getMember((int)index).resolve();

            } else if ((! hasSize(type)) &&
                       (0 == states.size()) &&
                       top) {
              // We are processing an initializer list that is not
              // nested and has an incomplete array as its type.
              // Therefore, we record the maximum size.
              count = Math.max(count, index+1);
            }

            // Done.
            return true;

          } else {
            // We are done with the base type.
            if (0 == states.size()) {
              // There are no more objects to initialize.  Get the
              // first excess element.
              final GNode excess = node.getGeneric((int)index);

              // Report excess elements first.
              if (pedantic) {
                runtime.error("excess elements in " + c().toDesignation(base) +
                              " initializer", excess);
              } else {
                runtime.warning("excess elements in " + c().toDesignation(base) +
                                " initializer", excess);
              }

              // Report any extra brace groups.
              for (int i=(int)index; i<node.size(); i++) {
                final GNode el = node.getGeneric(i);

                if (el.getGeneric(1).hasName("InitializerList")) {
                  runtime.error("extra brace group at end of initializer", el);
                }
              }

              // Done.
              return false;

            } else {
              // Continue with the encapsulating type.
              pop();
            }
          }
        }

      } else {
        // Clear the saved states.  We are starting with the overall
        // type.
        if (0 != states.size()) {
          final State state = states.get(0);
          base    = state.base;
          element = state.element;
          top     = state.top;
          index   = state.index;
          size    = state.size;
          states.clear();
        }
        if (base.isArray()) push(base);

        // Process the designators.
        final Iterator<Object> iter;
        if (designation.hasName("Designation")) {
          iter = designation.iterator();
        } else {
          iter = new SingletonIterator<Object>(designation);
        }

        while (iter.hasNext()) {
          final GNode designator = GNode.cast(iter.next());

          if (designator.hasName("ObsoleteFieldDesignation") ||
              ".".equals(designator.getString(0))) {
            // A struct/union field.
            if (! base.hasStructOrUnion()) {
              runtime.error("field name not in struct or union initializer",
                            designator);
              return false;
            }

            // Extract the field name.
            String name = designator.hasName("ObsoleteFieldDesignation") ?
              designator.getString(0) : designator.getGeneric(1).getString(0);

            // Find the field.
            if (! lookup(name)) {
              runtime.error("unknown field '" + name + "' in initializer",
                            designator);
              return false;
            }
            
          } else {
            // An array index.  Make sure the base type is an array.
            if (! base.isArray()) {
              runtime.error("array index in non-array initializer", designator);
              return false;
            }

            // Determine the index types.
            final Type t1 = processExpression(designator.getNode(1));
            final Type t2 = (3 == designator.size()) ?
              processExpression(designator.getNode(2)) : null;

            // Make sure that the indices are constant integers.
            if ((! c().isIntegral(t1)) ||
                ((null != t2) && (! c().isIntegral(t2)))) {
              runtime.error("array index in initializer not of integer type",
                            designator);
              return false;

            } else if ((! t1.hasConstant()) ||
                       ((null != t2) && (! t2.hasConstant()))) {
              runtime.error("nonconstant array index in initializer",
                            designator);
              return false;

            }

            // Make sure that the indices are neither too small nor
            // too large and that the range is not empty.
            final BigInteger i1 = t1.getConstant().bigIntValue();
            final BigInteger i2 = 
              (null == t2) ? null : t2.getConstant().bigIntValue();

            // Test: i1 < 0, i2 < 0
            if ((i1.compareTo(BigInteger.ZERO) < 0) ||
                ((null != i2) && (i2.compareTo(BigInteger.ZERO) < 0))) {
              runtime.error("negative array index in initializer",
                            designator);
              return false;

              // Test: i1 > ARRAY_MAX, i2 > ARRAY_MAX
            } else if ((i1.compareTo(Limits.ARRAY_MAX) > 0) ||
                       ((null != i2) && (i2.compareTo(Limits.ARRAY_MAX) > 0))) {
              runtime.error("array index in initializer is too large",
                            designator);
              return false;

              // Test: i2 < i1
            } else if ((null != i2) && (i2.compareTo(i1) < 0)) {
              runtime.error("empty index range in initializer", designator);
              return false;

            }

            // Make sure that the array index is within the array
            // bounds.
            final long max = (null == i2) ? i1.longValue() : i2.longValue();
            if ((-1 < size) && (max >= size)) {
              runtime.error("array index in initializer exceeds array bounds",
                            designator);
              return false;
            }

            if ((! hasSize(type)) && (0 == states.size()) && top) {
              // We are processing an initializer list that is not
              // nested and has an incomplete array as its type.
              // Therefore, we record the maximum size.
              count = Math.max(count, max+1);
            }

            // Update the current index.
            index = max;
          }

          // Prepare for the next designator.
          if (iter.hasNext()) push(element);
        }

        // Done.
        return true;
      }
    }

    /**
     * Look up the specified field.  The current base type must be a
     * struct or union type.
     *
     * @return <code>true</code> if the field was found.
     */
    private boolean lookup(String name) {
      index = -1;

      for (VariableT member : base.toStructOrUnion().getMembers()) {
        if (member.hasName()) {
          index++;
          if (member.hasName(name)) {
            element = member.resolve();
            return true;
          }

        } else if (! member.hasWidth()) {
          index++;
          element = member.resolve();
          push(element);

          if (lookup(name)) return true;

          pop();
        }
      }

      return false;
    }

    /**
     * Make the specified type the current type.  The type must have
     * been resolved.
     *
     * @param type The type.
     */
    private void push(Type type) {
      // DEBUG: Print pushed type.
      if (2 <= DEBUG) {
        runtime.console().indent().p("push ");
        type.trace(runtime);
        runtime.console().flush();
      }

      State state = new State(base, element, top, index, size);
      states.add(state);
      base        = type;
      switch (type.tag()) {
      case ARRAY:
        element   = type.toArray().getType().resolve();
        break;
      case STRUCT:
      case UNION:
        element   = type.toTagged().getMember(0).resolve();
        break;
      default:
        element   = type;
      }
      top         = false;
      index       = 0;
      size        = getSize(type);
    }

    /** Restore the previous type and its processing state. */
    private void pop() {
      // DEBUG: Pop.
      if (2 <= DEBUG) runtime.console().indent().pln("pop").flush();

      assert 0 != states.size() : "Empty initializer type stack";

      final State state = states.remove(states.size()-1);
      base    = state.base;
      element = state.element;
      top     = state.top;
      index   = state.index;
      size    = state.size;
    }

    /**
     * Get the result type.  If this initializer list is not nested
     * and has an incomplete array as its type, this method patches
     * the array's size.  Otherwise, it returns the overall type.
     *
     * @return The result type.
     */
    private Type getResult() {
      if ((! hasSize(type)) &&
          (((0 == states.size()) && top) ||
           ((0 < states.size()) && states.get(0).top))) {
        type = type.copy();
        type.resolve().toArray().setLength(count);
      }
      return type;
    }

    /**
     * Convert this initializer as a string.  This method returns a
     * string representing the array/struct/union designation of the
     * current initializer state.
     *
     * @return This initializer as a string.
     */
    public String toString() {
      final StringBuilder buf = new StringBuilder();

      for (State state : states) {
        if (state.base != state.element) {
          if (state.base.isArray()) {
            buf.append('[');
            buf.append(state.index);
            buf.append(']');

          } else if (state.base.hasStructOrUnion()) {
            final VariableT m = state.base.toTagged().
              getMember((int)state.index).toVariable();
            if (m.hasName()) {
              buf.append('.');
              buf.append(m.getName());
            } else {
              buf.append(".<anon>");
            }
          }
        }
      }

      if ((base != element) && (-1 != index)) {
        if (base.isArray()) {
          buf.append('[');
          buf.append(index);
          buf.append(']');

        } else if (base.hasStructOrUnion()) {
          final VariableT m = base.toTagged().
            getMember((int)index).toVariable();
          if (m.hasName()) {
            buf.append('.');
            buf.append(m.getName());
          } else {
            buf.append(".<anon>");
          }
        }
      }

      // Cover the base case.
      if ((base == element) && (0 == states.size())) buf.append("<obj>");

      return buf.toString();
    }

    /**
     * Determine whether the specified type has a size.  Only arrays
     * without a length do not have a size.  This method is
     * effectively static.
     *
     * @param type The type.
     * @return <code>true</code> if the type has a size.
     */
    private boolean hasSize(Type type) {
      return (! type.hasTag(Tag.ARRAY)) ||
        type.resolve().toArray().hasLength();
    }

    /**
     * Determine the size of the specified type.  For scalars, this
     * method returns 1.  For unions, this method returns 1 if the
     * union has any accessible members and 0 otherwise.  For structs,
     * this method returns the number of accessible members.  For
     * arrays, it returns the size if known and -1 otherwise.  This
     * method is effectively static.
     *
     * @param type The type.
     * @return The type's size.
     */
    private long getSize(Type type) {
      switch (type.tag()) {
      case ARRAY:
        return type.toArray().getLength();
      case STRUCT:
        return type.toTagged().getMemberCount();
      case UNION:
        return 0 < type.toTagged().getMemberCount() ? 1 : 0;
      default:
        return 1;
      }
    }

  }

  // ========================================================================

  /** The state for checking incomplete types. */
  public static class CompletenessCheck {

    /** The type. */
    public Type type;

    /** The identifier. */
    public String name;

    /** The node. */
    public Node node;

    /**
     * Create a new completeness check.
     *
     * @param type The type.
     * @param name The name.
     * @param node The node.
     */
    public CompletenessCheck(Type type, String name, Node node) {
      this.type = type;
      this.name = name;
      this.node = node;
    }

  }

  // ========================================================================

  /**
   * The name of the node property indicating that a node has already
   * been marked with its type during initializer processing.
   */
  protected static final String MARKED = "marked";

  /** The relative name of the scope for external declarations. */
  protected static final String EXTERN_SCOPE = "extern";

  /** The relative name of the temporary scope for parameter declarations. */
  protected static final String TMP_SCOPE = "tmp";

  /** The fully qualified name of the scope for external declarations. */
  protected static final String EXTERN_PATH = Constants.QUALIFIER + EXTERN_SCOPE;

  /** The common type operations for C. */
  protected final C cops;

  /** The runtime. */
  protected final Runtime runtime;
  
  /** The flag for pedantic mode. */
  protected final boolean pedantic;

  /** The symbol table. */
  protected SymbolTable table;

  /**
   * The flag for whether the current declaration is top-level, that
   * is, an external declaration.
   */
  protected boolean isTopLevel;

  /**
   * The flag for whether the immediately nested compound statement
   * has a scope.
   */
  protected boolean hasScope;

  /**
   * The list of loop statement flags.  For each nested loop
   * statement, this list contains exactly one boolean.
   */
  protected List<Boolean> loops;

  /**
   * The list of switch statement flags.  For each nested switch
   * statement, this list contains exactly one boolean, which is
   * <code>true</code> if a default label has been seen.
   */
  protected List<Boolean> switches;

  /**
   * The flag for a statement as expression node.  This flag
   * is <code>true</code> if the current compound statement
   * is nested within a statement as expression node.
   */
  protected boolean isStmtAsExpr;

  /**
   * The list of completeness checks to perform at the end of a
   * translation unit.
   */
  protected List<CompletenessCheck> checks;

  /**
   * Create a new C analyzer.  The newly created analyzer uses {@link
   * C} for common type operations.
   *
   * @param runtime The runtime.
   */
  public CAnalyzer(Runtime runtime) {
    this(new C(), runtime);
  }

  /**
   * Create a new C analyzer.
   *
   * @param cops The common type operations for C.
   * @param runtime The runtime.
   */
  public CAnalyzer(C cops, Runtime runtime) {
    this.cops    = cops;
    this.runtime = runtime;
    pedantic     = runtime.test("optionPedantic");
    loops        = new ArrayList<Boolean>();
    switches     = new ArrayList<Boolean>();
    checks       = new ArrayList<CompletenessCheck>();
  }

  /**
   * Analyze the specified translation unit.
   *
   * @param unit The translation unit.
   * @return The corresponding symbol table.
   */
  public SymbolTable analyze(Node unit) {
    return analyze(unit, new SymbolTable());
  }

  /**
   * Process the specified translation unit.
   *
   * @param unit The translation unit.
   * @param table The symbol table.
   * @return The symbol table.
   */
  public SymbolTable analyze(Node unit, SymbolTable table) {
    this.table   = table;
    isTopLevel   = true;
    isStmtAsExpr = false;
    loops.clear();
    switches.clear();
    checks.clear();
    dispatch(unit);
    return table;
  }

  /**
   * Get this analyzer's common type operations for the C language.
   *
   * @return The common type operations.
   */
  public C c() {
    return cops;
  }

  /** Visit the specified translation unit. */
  public void visitTranslationUnit(GNode n) {
    for (Object o : n) dispatch((Node)o);

    // Process any tagged checks.
    for (CompletenessCheck check : checks) {
      if (c().isIncomplete(check.type)) {
        runtime.error("storage size of '" + check.name + "' isn't known",
                      check.node);
      }
    }
  }

  /** Visit the specified declaration. */
  public void visitDeclaration(GNode n) {
    final GNode      specifiers   = n.getGeneric(1);
    final Specifiers spec         = newSpecifiers(specifiers, null == n.get(2));
    final GNode      initDeclList = n.getGeneric(2);

    if (null == initDeclList) {
      // ----------------------------------------------------------------------
      //                           Empty declarations
      // ----------------------------------------------------------------------

      // Check for useless attributes.
      if (spec.contains(Constants.ATT_INLINE)) {
        runtime.error("'inline' in empty declaration", n);
      }
      if (null != spec.getStorageClass()) {
        runtime.warning("useless storage class specifier in empty declaration",
                        n);
      }
      if (spec.contains(Constants.ATT_VOLATILE) ||
          spec.contains(Constants.ATT_CONSTANT) ||
          spec.contains(Constants.ATT_RESTRICT)) {
        runtime.warning("useless type qualifier in empty declaration", n);
      }

      // Make sure the type is tagged.
      if ((! spec.getBaseType().hasError()) &&
          (! spec.getBaseType().hasTagged())) {
        runtime.warning("empty declaration", n);
      }

    } else {
      // Iterate over the initialized declarator list.
      for (Object o : initDeclList) {
        final GNode  initDecl    = GNode.cast(o);
        final GNode  declarator  = initDecl.getGeneric(1);
        final GNode  identifier  = getDeclaredId(declarator);
        final String name        = identifier.getString(0);
        Type         type        = 
          getDeclaredType(spec.getBaseType(), declarator);
        final GNode  initializer = initDecl.getGeneric(4);
        
        dispatch(initDecl.getGeneric(2)); // Process assembly expression.

        if (spec.contains(Constants.ATT_STORAGE_TYPEDEF)) {
          // ------------------------------------------------------------------
          //                        Typedef declarations
          // ------------------------------------------------------------------

          // Check for invalid attributes.
          if (spec.contains(Constants.ATT_INLINE)) {
            runtime.error("typedef '"+name+"' is declared 'inline'",
                          getSpecifier("FunctionSpecifier", specifiers));
          }
          if (spec.contains(Constants.ATT_THREAD_LOCAL)) {
            runtime.error("'__thread' used with 'typedef'", initDecl);
          }

          // Check for initializers.
          if (null != initializer) {
            runtime.error("typedef '" + name + "' is initialized", initDecl);
          }

          // Check that the type is well-formed.
          checkType(initDecl, name, type);

          // Check for previous definitions.
          if (table.current().isDefinedLocally(name)) {
            Type previous = (Type)table.current().lookupLocally(name);

            if (previous.isAlias()) {
              runtime.error("redefinition of typedef '" + name + "'", initDecl);
            } else {
              runtime.error("'"+name+"' redeclared as different kind of symbol",
                            initDecl);
            }
            reportPrevious(name, previous);

          } else {
            table.current().
              define(name, new AliasT(name, type).locate(n).seal());
          }

        } else {
          // ------------------------------------------------------------------
          //                  Object declarations/definitions
          // ------------------------------------------------------------------

          // The flags for whether to enter the definition into the
          // symbol table at the local, at the global, and the extern
          // level, respectively.
          boolean define       = true;
          boolean defineGlobal = false;
          boolean defineExtern = false;

          // Annotate the type.
          type = spec.annotateFull(type.annotate());
          type = type.attribute(toAttributeList(initDecl.getGeneric(0)));
          type = type.attribute(toAttributeList(initDecl.getGeneric(3)));

          // Check that the type is well-formed.
          checkType(initDecl, name, type);

          Type resolved = type.resolve();

          // Check function types for invalid storage class,
          // parameters, and initializer.
          if (resolved.isFunction()) {
            FunctionT function = resolved.toFunction();

            if (type.hasAttribute(Constants.ATT_STORAGE_AUTO) ||
                type.hasAttribute(Constants.ATT_STORAGE_REGISTER) ||
                type.hasAttribute(Constants.ATT_THREAD_LOCAL)) {
              runtime.error("invalid storage class for function '" + name +
                            "'", initDecl);
            }

            if (type.hasAttribute(Constants.ATT_STYLE_OLD) &&
                (! function.getParameters().isEmpty())) {
              runtime.warning("parameter names (without types) in function " +
                              "declaration", initDecl);
              function.getParameters().clear();
            }

            if (null != initializer) {
              runtime.error("function '" + name + "' is initialized like a " +
                            "variable", initDecl);
            }

          } else {
            // Check non-function types for inline specifier.
            if (type.hasAttribute(Constants.ATT_INLINE)) {
              runtime.warning("variable '" + name + "' declared 'inline'",
                              getSpecifier("FunctionSpecifier", specifiers));
              type.removeAttribute(Constants.ATT_INLINE);
            }

            // Check non-function types for thread-local specifier.
            if (type.hasAttribute(Constants.ATT_THREAD_LOCAL)) {
              if (type.hasAttribute(Constants.ATT_STORAGE_AUTO)) {
                runtime.error("'__thread' used with 'auto'", specifiers);
              } else if (type.hasAttribute(Constants.ATT_STORAGE_REGISTER)) {
                runtime.error("'__thread' used with 'register'", specifiers);
              } else if (! type.hasAttribute(Constants.NAME_STORAGE) &&
                         ! isTopLevel) {
                runtime.error("function-scope '" + name + "' implicitly auto " +
                              "and declared '__thread'", initDecl);
              } else if (! c().hasThreadLocals()) {
                runtime.error("thread-local storage not supported for this " +
                              "target", initDecl);
              }
            }
          }

          // Check for compatibility with prevous declarations.
          if (isTopLevel) {
            // An external declaration/definition.

            // Check for invalid storage class specifiers.
            if (! resolved.isFunction()) {
              if (type.hasAttribute(Constants.ATT_STORAGE_AUTO)) {
                runtime.error("file-scope declaration of '" + name +
                              "' specifies 'auto'",
                              getSpecifier("AutoSpecifier", specifiers));
                
              } else if (type.hasAttribute(Constants.ATT_STORAGE_REGISTER)) {
                // As a GCC extension, the register specifier may
                // appear in global register variable declarations.
                // Such a declaration, however, requires a simple
                // assembly expression.
                if (pedantic || null == initDecl.get(2)) {
                  runtime.error("file-scope declaration of '" + name +
                                "' specifies 'register'",
                                getSpecifier("RegisterSpecifier", specifiers));
                }
              }
            }

            final Type    extern = lookupExtern(name);
            final boolean global = table.current().isDefinedLocally(name);
            if (null != extern || global) {
              final Type previous =
                global ? (Type)table.current().lookupLocally(name) : extern;

              // Check for same symbol kind and type compatibility.
              Type composite = compose(initDecl, name, type, previous, false);

              // Check for redefinitions and storage class compatibility.
              if (composite.isError()) {
                define = (null != extern);

              } else if ((null != initializer) &&
                         previous.hasAttribute(Constants.ATT_DEFINED)) {
                runtime.error("redefinition of '" + name + "'", initDecl);
                reportPrevious(name, previous);
                define = (null != extern);
                
              } else if ((! resolved.isFunction()) &&
                         previous.hasAttribute(Constants.ATT_STORAGE_STATIC) &&
                         (! type.hasAttribute(Constants.ATT_STORAGE_STATIC)) &&
                         (! type.hasAttribute(Constants.ATT_STORAGE_EXTERN))) {
                runtime.error("non-static declaration of '" + name +
                              "' follows static declaration", initDecl);
                reportPrevious(name, previous);
                define = (null != extern);

              } else if ((! previous.hasAttribute(Constants.ATT_MACRO)) &&
                         (! previous.hasAttribute(Constants.ATT_STORAGE_STATIC))
                         && type.hasAttribute(Constants.ATT_STORAGE_STATIC)) {
                runtime.error("static declaration of '" + name +
                              "' follows non-static declaration", initDecl);
                reportPrevious(name, previous);
                define = (null != extern);
                
              } else if (previous.hasAttribute(Constants.ATT_MACRO) ||
                         previous.hasAttribute(Constants.ATT_DEFINED)) {
                // There's nothing to add.
                define = (null != extern);

              } else {
                // We have a winner.
                composite = composite.annotate();
                
                // C99 6.7.4: inline only needs to appear
                // once. Similarly for static.
                if (resolved.isFunction()) {
                  if ((previous.hasAttribute(Constants.ATT_INLINE) ||
                       type.hasAttribute(Constants.ATT_INLINE)) &&
                      (! composite.hasAttribute(Constants.ATT_INLINE))) {
                    composite = composite.attribute(Constants.ATT_INLINE);
                  }
                  if ((previous.hasAttribute(Constants.ATT_STORAGE_STATIC) ||
                       type.hasAttribute(Constants.ATT_STORAGE_STATIC)) &&
                      (! composite.hasAttribute(Constants.ATT_STORAGE_STATIC))) {
                    composite = composite.
                      attribute(Constants.ATT_STORAGE_STATIC);
                  }
                }

                // Preserve the lvalue.
                if (! composite.hasShape()) {
                  composite = composite.shape(previous.getShape());
                }

                // Update the location.
                composite = composite.locate(n);

                // Continue with the composite type.
                type     = composite;
                resolved = type.resolve();
              }

            } else {
              // The name has not been declared before.

              // Create an lvalue.
              type = type.shape(true, name);

              // Remember the location.
              type = type.locate(n);
            }

          } else {
            // A block-level declaration/definition.

            if (type.hasAttribute(Constants.ATT_STORAGE_EXTERN) ||
                resolved.isFunction()) {
              // Extern and function declarations at the block-level
              // are effectively external declarations.

              // Process the function type's storage class.
              if (resolved.isFunction()) {
                if (type.hasAttribute(Constants.ATT_STORAGE_AUTO) ||
                    type.hasAttribute(Constants.ATT_STORAGE_REGISTER) ||
                    type.hasAttribute(Constants.ATT_STORAGE_STATIC) ||
                    type.hasAttribute(Constants.ATT_THREAD_LOCAL)) {
                  // C99 6.7.1-5
                  runtime.error("invalid storage class for function '" + name +
                                "'", initDecl);
                  type.
                    removeAttribute(type.getAttribute(Constants.NAME_STORAGE));
                }

                // C99 6.2.2
                type = type.attribute(Constants.ATT_STORAGE_EXTERN);
              }

              final Type local  = (Type)table.current().lookupLocally(name);
              final Type global = (Type)table.root().lookupLocally(name);
              final Type extern = lookupExtern(name);

              if (null != local || null != global || null != extern) {
                final Type previous;
                if (null != local) {
                  previous = local;
                } else if (null != global) {
                  previous = global;
                } else {
                  previous = extern;
                }

                Type composite = compose(initDecl, name, type, previous, false);

                if (composite.isError()) {
                  define = false;

                } else if (null != local &&
                           ! previous.resolve().isFunction() &&
                           ! previous.
                             hasAttribute(Constants.ATT_STORAGE_EXTERN)) {
                  runtime.error("extern declaration of '" + name + "' follows " +
                                "declaration with no linkage", initDecl);
                  reportPrevious(name, previous);
                  define = false;

                } else if (previous.hasAttribute(Constants.ATT_STORAGE_STATIC) &&
                           previous != 
                           table.current().getParent().lookup(name)) {
                  // C99 6.2.2-4: If the previous declaration has
                  // internal linkage (i.e., is declared as static)
                  // and is not visible in the surrounding scope, then
                  // this declaration tries to change to external
                  // linkage, which is a program error.

                  // Aside: It is extremely clever language design
                  // practice to make a declaration's properties
                  // dependent on an identifier of the same name in
                  // the surrounding scope.
                  runtime.error("variable previously declared 'static' " +
                                "redeclared 'extern'", initDecl);
                  reportPrevious(name, previous);

                } else if (previous.hasAttribute(Constants.ATT_MACRO) ||
                           previous.hasAttribute(Constants.ATT_DEFINED)) {
                  // There's nothing to add.
                  type     = previous;
                  resolved = type.resolve();
                  define   = (null == local);

                } else {
                  // We have a winner.
                  composite = composite.annotate();

                  // Preserve inline and static attributes for functions.
                  if (resolved.isFunction()) {
                    if ((previous.hasAttribute(Constants.ATT_INLINE) ||
                         type.hasAttribute(Constants.ATT_INLINE)) &&
                        (! composite.hasAttribute(Constants.ATT_INLINE))) {
                      composite = composite.attribute(Constants.ATT_INLINE);
                    }
                    if ((previous.hasAttribute(Constants.ATT_STORAGE_STATIC) ||
                         type.hasAttribute(Constants.ATT_STORAGE_STATIC)) &&
                        (! composite.
                           hasAttribute(Constants.ATT_STORAGE_STATIC))) {
                      composite = composite.
                        attribute(Constants.ATT_STORAGE_STATIC);
                    }
                  }

                  // Update the lvalue.
                  if (! composite.hasShape()) {
                    composite = composite.shape(previous.getShape());
                  }

                  // Update the locaton.
                  composite    = composite.locate(n);

                  // Continue with the composite type.
                  type         = composite;
                  resolved     = type.resolve();
                  defineGlobal = (null != global);
                  defineExtern = (null != extern);
                }

              } else {
                // The name has not been declared before.

                // Create an lvalue.
                type = type.shape(true, name);

                // Remember the location.
                type = type.locate(n);

                // Enter into extern scope.
                defineExtern = true;
              }

            } else if (table.current().isDefinedLocally(name)) {
              // Non-extern redeclarations at the block-level are
              // always errors.  We just play along to determine what
              // kind of error.
              final Type previous  = (Type)table.current().lookupLocally(name);
              final Type composite = compose(initDecl,name,type,previous,false);

              if (composite.isError()) {
                define = false;

              } else if (previous.hasAttribute(Constants.ATT_STORAGE_EXTERN)) {
                runtime.error("declaration of '" + name + "' with no " +
                              "linkage follows extern declaration", initDecl);
                reportPrevious(name, previous);
                define = false;

              } else {
                runtime.error("redeclaration of '" + name + "' with no linkage",
                              initDecl);
                reportPrevious(name, previous);
                define = false;
              }

            } else {
              // The name has not been declared before.

              // Add the storage class if missing.
              if (! type.hasAttribute(Constants.NAME_STORAGE)) {
                type = type.attribute(Constants.ATT_STORAGE_AUTO);
              }

              // Create an lvalue.
              type = type.
                shape(type.hasAttribute(Constants.ATT_STORAGE_STATIC), name);

              // Remember the location.
              type = type.locate(n);
            }
          }

          // Check for incomplete types.
          boolean incomplete = false;
          if ((! type.hasAttribute(Constants.ATT_STORAGE_EXTERN)) ||
              (null != initializer)) {

            if (resolved.isArray()) {
              final Type element = resolved.toArray().getType();
              if (c().isIncomplete(element) ||
                  (pedantic && c().hasTrailingArray(element))) {
                runtime.error("array type has incomplete element type",
                              initDecl);
                incomplete = true;
              }

            } else if (c().isIncomplete(type)) {
              if (null == initializer) {
                // Per C99 6.9.2-2, as a special case, top-level
                // tagged types without initializers are logically
                // moved to the end of the translation unit and
                // automatically initialized to zero.  We simply redo
                // the completeness check at the end of the
                // translation unit.
                if (isTopLevel &&
                    type.hasTagged() &&
                    (null == type.toTagged().getMembers())) {
                  checks.add(new CompletenessCheck(type, name, initDecl));

                } else if (resolved.isVoid()) {
                  runtime.error("variable '" + name + "' declared void",
                                initDecl);
                } else {
                  runtime.error("storage size of '" + name + "' isn't known",
                                initDecl);
                }
              } else {
                runtime.error("variable '" + name + "' has initializer but " +
                              "incomplete type", initDecl);
              }
              incomplete = true;
            }
          }

          // Process the initializer.
          if ((null != initializer) && (! resolved.isFunction())) {
            if (type.hasAttribute(Constants.ATT_STORAGE_EXTERN)) {
              if (isTopLevel) {
                runtime.warning("'"+name+"' initialized and declared 'extern'",
                                initDecl);
                type = type.attribute(Constants.ATT_DEFINED);
              } else {
                runtime.error("'"+name+"' has both 'extern' and initializer",
                              initDecl);
              }
            } else {
              type = type.attribute(Constants.ATT_DEFINED);
            }

            if (! incomplete) {
              // C99 6.2.1-4: An identifiers scope starts with its
              // declarator.  Consequently, we "pre-define" the
              // identifier before processing the initializer.
              if (define) {
                table.current().define(name, type);
              }

              // Do the actual processing.
              type = processInitializer(initDecl, name, type, initializer);
            }
          }

          // (Re)define the name and type.
          if (define) {
            table.current().define(name, type);
          }
          if (defineGlobal) {
            table.root().define(name, type);
          }
          if (defineExtern) {
            defineExtern(name, type);
          }
        }
      }
    }
  }

  /**
   * Process the specified initializer.  This method checks that the
   * specified initializer is consistent with the specified type.  It
   * also completes the type based on the literal.
   *
   * @param expr The overall expression node.
   * @param name The name of the variable being initialized, which may
   *   be <code>null</code>.
   * @param left The left-hand type.
   * @param literal The literal node.
   */
  protected Type processInitializer(GNode expr, String name,
                                    Type left, GNode literal) {
    if (left.hasError()) return left;

    // Fix the description for error reporting.
    name = (null == name) ? "initializer" : "initializer for '" + name + "'";

    // Determine whether the left-hand size has automatic storage.
    final boolean auto = (left.hasAttribute(Constants.ATT_STORAGE_AUTO) ||
                          left.hasAttribute(Constants.ATT_STORAGE_REGISTER));

    // Check the actual initializer.
    if (literal.hasName("InitializerList")) {

      // Take care of braced string literals here.
      if ((c().isString(left) || c().isWideString(left)) &&
          (0 < literal.size()) &&
          (null == literal.getGeneric(0).get(0)) &&
          (! literal.getGeneric(0).getGeneric(1).hasName("InitializerList"))) {
        final Type right = (Type)dispatch(literal.getGeneric(0).getGeneric(1));

        if (c().isStringLiteral(right)) {
          if (1 < literal.size()) {
            if (c().isString(left)) {
              runtime.error("excess elements in char array initializer",
                            literal);
            } else {
              runtime.error("excess elements in wchar_t array initializer",
                            literal);
            }
            return left;
          } else {
            processAssignment(true, name, literal, left, right);
            return processStringSize(literal, name, false, left, right);
          }
        }

        // Unmark the already processed node again b/c it will be
        // reprocessed below.
        if (runtime.test("optionMarkAST")) {
          literal.getGeneric(0).getGeneric(1).setProperty(MARKED, Boolean.TRUE);
        }
      }

      // Otherwise, just process the initializer list.
      return new Initializer(literal, left, auto).process();

    } else {
      final Type right = (Type)dispatch(literal);

      // A non-automatic initializer must be constant.
      if ((! auto) && (! right.hasConstant()) && (! c().hasConstRef(right))) {
        runtime.error(name + " is not constant", expr);
      }

      // Are the two types compatible?
      processAssignment(true, name, literal, left, right);
      return processStringSize(literal, name, false, left, right);
    }
  }

  /**
   * Process the string sizes for the specified types.  If the
   * specified types are not compatible string types or the right-hand
   * type does no represent a string constant, this method simply
   * returns the specified left-hand type.  Otherwise, if the
   * left-hand type is an incomplete array and the expression is not
   * nested, this method updates a copy of the left-hand type and
   * returns that copy.  If the left-hand type is a complete array and
   * the right-hand type is longer, it emits a warning.
   *
   * @param expr The overall expression node.
   * @param desc The description.
   * @param nested The flag for nested initializers.
   * @param left The left-hand type.
   * @param right The right-hand type.
   * @return The updated type.
   */
  protected Type processStringSize(GNode expr, String desc, boolean nested,
                                   Type left, Type right) {
    if (((c().isString(left) && c().isString(right)) ||
         (c().isWideString(left) && c().isWideString(right))) &&
        right.hasConstant()) {
      
      final ArrayT array = left.resolve().toArray();
      if ((! array.isVarLength()) && (! array.hasLength()) && (! nested)) {
        left = left.copy();
        left.resolve().toArray().
          setLength(right.resolve().toArray().getLength());

      } else if (array.hasLength() &&
                 (array.getLength() < right.resolve().toArray().getLength())) {
        runtime.warning("string literal in " + desc + " is too long", expr);
      }
    }

    return left;
  }

  /** Visit the specified function definition. */
  public void visitFunctionDefinition(GNode n) {
    final GNode      specifiers = n.getGeneric(1);
    final GNode      declarator = n.getGeneric(2);
    final GNode      identifier = getDeclaredId(declarator);
    final String     name       = identifier.getString(0);

    final Specifiers spec       = newSpecifiers(specifiers, false);
    Type             type       = getDeclaredType(spec.getBaseType(),declarator);
    type                        = spec.annotateFull(type);

    // Make sure the type actually is a function.
    if (! type.resolve().isFunction()) {
      runtime.error("function definition without function declarator",
                    declarator);
      return;
    }

    // Check the storage class.
    if (type.hasAttribute(Constants.ATT_STORAGE_AUTO)) {
      runtime.error("function definition declared 'auto'", n);
    } else if (type.hasAttribute(Constants.ATT_STORAGE_REGISTER)) {
      runtime.error("function definition declared 'register'", n);
    } else if (type.hasAttribute(Constants.ATT_STORAGE_TYPEDEF)) {
      runtime.error("function definition declared 'typedef'", n);
    } else if (type.hasAttribute(Constants.ATT_THREAD_LOCAL)) {
      runtime.error("function definition declared '__thread'", n);
    }

    // Check the function's result type.
    checkType(n, name, type);

    // The flag for a GCC inline extern function, i.e., macro.
    final boolean isMacro = (! pedantic &&
                             type.hasAttribute(Constants.ATT_STORAGE_EXTERN) &&
                             type.hasAttribute(Constants.ATT_INLINE));

    // The flag for whether to enter the definition into the symbol table.
    boolean define = true;

    // Check previous declarations/definitions.
    final Type    extern = lookupExtern(name);
    final boolean global = table.current().isDefinedLocally(name);
    if (null != extern || global) {
      final Type previous =
        global ? (Type)table.current().lookupLocally(name) : extern;
      final Type composite = compose(n, name, type, previous, true);

      if (composite.isError()) {
        define = (null != extern);

      } else if (previous.hasAttribute(Constants.ATT_DEFINED) ||
                 (isMacro && previous.hasAttribute(Constants.ATT_MACRO))) {
        runtime.error("redefinition of '" + name + "'", n);
        reportPrevious(name, previous);
        define = (null != extern);
                 
      } else if ((! previous.hasAttribute(Constants.ATT_MACRO)) &&
                 (! previous.hasAttribute(Constants.ATT_STORAGE_STATIC)) &&
                 type.hasAttribute(Constants.ATT_STORAGE_STATIC)) {
        runtime.error("static declaration of '" + name +
                      "' follows non-static declaration", n);
        reportPrevious(name, previous);
        define = (null != extern);

      } else {
        // Continue with the composite type.
        type = composite;

        // Preserve inline and static attributes.
        if ((! previous.hasAttribute(Constants.ATT_MACRO)) &&
            previous.hasAttribute(Constants.ATT_INLINE) &&
            (! type.hasAttribute(Constants.ATT_INLINE))) {
          type = type.annotate().attribute(Constants.ATT_INLINE);
        }

        if (previous.hasAttribute(Constants.ATT_STORAGE_STATIC) &&
            (! type.hasAttribute(Constants.ATT_STORAGE_STATIC))) {
          type = type.annotate().attribute(Constants.ATT_STORAGE_STATIC);
        }

      }

      type = type.annotate();

      // Mark the type as defined.
      if (type.resolve().isSealed()) {
        type = isMacro ? type.attribute(Constants.ATT_MACRO) :
          type.attribute(Constants.ATT_DEFINED);
      } else if (isMacro) {
        type.resolve().addAttribute(Constants.ATT_MACRO);
      } else {
        type.resolve().addAttribute(Constants.ATT_DEFINED);
      }

      // Ensure the type is marked as an lvalue.
      if (! type.hasShape()) {
        type = type.shape(true, name);
      }

      // Update the type's location.
      type = type.locate(n);

    } else {
      // The function has not been declared before.  Mark it's type as
      // a defined lvalue and remember the location.
      if (isMacro) {
        type.resolve().addAttribute(Constants.ATT_MACRO);
      } else {
        type.resolve().addAttribute(Constants.ATT_DEFINED);
      }
      type = type.annotate().shape(true, name).locate(n);
    }

    // Update the symbol table.
    if (define) {
      // Note that processParameters() below may modify the type's
      // parameters.
      table.current().define(name, type);
    }

    // Check that main's return type is int.
    if ("main".equals(name) && type.resolve().isFunction() &&
        ! NumberT.INT.equals(type.resolve().toFunction().getResult())) {
      runtime.warning("return type of 'main' is not 'int'", n);
    }
    
    // Enter function scope.
    final String scopeName = isMacro ? SymbolTable.toMacroScopeName(name) :
      SymbolTable.toFunctionScopeName(name);
    table.enter(scopeName);
    table.mark(n);

    // C99 6.4.2.2: Declare the function name.
    table.current().define("__func__", toFuncType(name));
    
    // Process the parameters.
    processParameters(n, type.resolve().toFunction());

    // Process the body.
    final boolean top   = isTopLevel;
    isTopLevel          = false;
    final boolean scope = hasScope;
    hasScope            = false;
    
    dispatch(n.getNode(4));
    
    isTopLevel = top;
    hasScope   = scope;
    
    table.exit();

    // Check labels.
    if (isTopLevel) {
      checkUsedLabels(n);
      checkDefinedLabels(n);
    }
  }

  /**
   * Create <code>__func__</code>'s type for the function with the
   * specified name.
   *
   * @param name The function name.
   * @return The corresponding type.
   */
  public static Type toFuncType(String name) {
    final Type elem  = NumberT.CHAR.annotate().
      attribute(Constants.ATT_CONSTANT);
    final Type array = new ArrayT(elem, name.length()).annotate().
      attribute(Constants.ATT_STORAGE_STATIC).shape(true, "__func__").seal();

    return array;
  }

  /**
   * Process the specified function's parameters.  This method checks
   * that all parameters are named and have valid and complete types.
   * Furthermore, for old-style function definitions, it checks that
   * the parameter types are consistent with any previous new-style
   * declaration and, for previous old-style declarations, updates the
   * function's type with the parameter types.  Finally, it adds the
   * appropriate definitions to the current symbol table scope.
   *
   * <p />Note that the specified type is expected to be the result of
   * composing the defined type with any previous declarations.  For
   * old-style definitions, this type contains the parameter types of
   * any previous new-style declaration or is old-style as well, if
   * any previous declarations are also old-style.
   *
   * @param node The node representing the function.
   * @param function The function's type.
   */
  protected void processParameters(GNode node, FunctionT function) {
    // Extract the parameter list.
    GNode parameters = getFunctionDeclarator(node.getGeneric(2)).getGeneric(1);

    if ((null == parameters) || parameters.hasName("IdentifierList")) {
      // An old-style definition: We first process any identifiers.
      final Set<String> names = new HashSet<String>();
      if (null != parameters) {
        for (Object o : parameters) names.add((String)o);
      }

      // Next, we process any declarations.
      final GNode declarations = node.getGeneric(3);
      if (null != declarations) {
        for (Object o : declarations) {
          final GNode      declaration = GNode.cast(o);
          final GNode      specifiers  = declaration.getGeneric(1);
          final Specifiers spec        = newSpecifiers(specifiers,
                                                       null==declaration.get(2));

          if (null == declaration.get(2)) {
            runtime.warning("empty declaration", declaration);

          } else {
            for (Object o2 : declaration.getGeneric(2)) {
              final GNode  initDecl   = GNode.cast(o2);
              final GNode  declarator = initDecl.getGeneric(1);
              final GNode  identifier = getDeclaredId(declarator);
              final String name       = identifier.getString(0);
              Type         type       =
                getDeclaredType(true, spec.getBaseType(), declarator);

              // Check that the type is well-formed.
              checkType(declaration, name, type);

              // Pointerize array and function parameter types.
              switch (type.tag()) {
              case ARRAY:
                type =
                  c().qualify(new PointerT(type.resolve().toArray().getType()),
                              type);
                break;
              case FUNCTION:
                type = c().qualify(new PointerT(type.resolve()), type);
                break;
              }

              // Annotate the type.
              type = spec.annotateFull(VariableT.newParam(type, name)).
                attribute(toAttributeList(initDecl.getGeneric(0))).
                attribute(toAttributeList(initDecl.getGeneric(3))).
                shape(false, name);
              
              // Check for storage class specifiers and initializers.
              if ((type.hasAttribute(Constants.NAME_STORAGE) &&
                   (! type.hasAttribute(Constants.ATT_STORAGE_REGISTER))) ||
                  type.hasAttribute(Constants.ATT_THREAD_LOCAL)) {
                runtime.error("storage class specified for parameter '"+name+
                              "'", declaration);
              } else if (! type.hasAttribute(Constants.NAME_STORAGE)) {
                type = type.attribute(Constants.ATT_STORAGE_AUTO);
              }

              if (null != initDecl.get(4)) {
                runtime.error("parameter '" + name + "' is initialized",
                              initDecl.getNode(4));
              }

              // Check for incomplete types.
              if (c().isIncomplete(type)) {
                if (type.resolve().isVoid()) {
                  runtime.error("parameter '" + name + "' declared void",
                                declaration);
                } else {
                  runtime.error("parameter '"+ name + "' has incomplete type",
                                declaration);
                }
              }

              // Check parameter name and previous definitions.
              if (! names.contains(name)) {
                runtime.error("declaration for parameter '" + name +
                              "' but no such parameter", declaration);

              } else if (table.current().isDefinedLocally(name)) {
                runtime.error("redefinition of parameter '" + name + "'",
                              declaration);
              } else {
                table.current().define(name, type);
              }
            }
          }
        }
      }

      // Next, we process any undeclared identifiers.
      for (String name : names) {
        if (! table.current().isDefinedLocally(name)) {
          final Type type = VariableT.newParam(C.IMPLICIT, name).
            attribute(Constants.ATT_STORAGE_AUTO).shape(false, name);
          table.current().define(name, type);

          if (pedantic) {
            runtime.warning("type of '" + name + "' defaults to 'int'", node);
          }
        }
      }

      // Finally, for old-style declarations, we patch the function
      // type and, for new-style declarations, we compare the
      // parameter types.
      if (function.hasAttribute(Constants.ATT_STYLE_OLD)) {
        // An old-style declaration (or none).
        List<Type> types = function.getParameters();
        final int  size  = types.size();
        for (int i=0; i<size; i++) {
          final Type t = types.get(i);
          
          // Old-style declarations have parameter types even if they
          // contain errors, since they always have a name.
          if (! t.hasError()) {
            final String name = t.toVariable().getName();
            
            if (table.current().isDefinedLocally(name)) {
              types.set(i, (Type)table.current().lookupLocally(name));
            }
          }
        }

      } else {
        // A new-style declaration.

        // Fix parameters.
        if (null == parameters) {
          parameters = GNode.create("IdentifierList", false);
        }

        if (parameters.size() != function.getParameters().size()) {
          runtime.error("number of arguments doesn't match prototype", node);

        } else {
          final int size = parameters.size();
          for (int i=0; i<size; i++) {
            final Type t1 = (Type)table.current().
              lookupLocally((String)parameters.get(i));
            final Type t2 = function.getParameters().get(i);

            if (t1.hasError() || t2.hasError()) {
              // Ignore.
            } else if (c().compose(t2, c().promoteArgument(t1), pedantic).
                       isError()) {
              runtime.error("argument '" + t1.toVariable().getName() +
                            "' doesn't match prototype", node);
            } else if (pedantic && ! c().hasSameQualifiers(t2, t1)) {
              // C99 6.7.5.3 15
              runtime.error("type qualifiers of argument '" +
                            t1.toVariable().getName() + 
                            "' don't match prototype", node);
            }
          }
        }
      }

    } else {
      // A new-style definition.
      if (null != node.get(3)) {
        runtime.error("old-style parameter declarations in prototyped " +
                      "function definition", node.getNode(3));
      }

      // Note that void parameter lists are checked for
      // well-formedness by getParameterTypes(), which is invoked by
      // getDeclaredType(), which, in turn, is invoked by
      // visitFunctionDefinition().
      if (! isVoidParameterTypeList(parameters)) {
        parameters             = parameters.getGeneric(0);
        Iterator<Object> iter1 = parameters.iterator();
        Iterator<Type>   iter2 = function.getParameters().iterator();
        while (iter1.hasNext()) {
          final GNode  decl  = GNode.cast(iter1.next());
          final Type   type  = iter2.next();
          final String name  = type.hasVariable() ?
            type.toVariable().getName() : null;

          // Check for incomplete types.
          if (c().isIncomplete(type)) {
            if (null == name) {
              runtime.error("unnamed parameter has incomplete type", decl);
            } else {
              runtime.error("parameter '"+name+"' has incomplete type", decl);
            }
          }

          // Add to symbol table.
          if (null == name) {
            if (! type.hasError()) {
              runtime.error("parameter name omitted", decl);
            }
          } else if (! table.current().isDefinedLocally(name)) {
            table.current().define(name, type);
          }
        }
      }
    }
  }  

  /**
   * Check that all labels used in the specified top-level function
   * are also defined.  This method requires that all relevant AST
   * nodes have been associated with their symbol table {@link
   * Constants#SCOPE scopes}.
   *
   * @param function The function to check.
   */
  protected void checkUsedLabels(GNode function) {
    checkUsedLabelsVisitor.dispatch(function);
  }

  /** The actual implementation of {@link #checkUsedLabels(GNode)}. */
  @SuppressWarnings("unused")
  private Visitor checkUsedLabelsVisitor = new Visitor() {
      private void check(String id, GNode labelRef) {
        final String name = SymbolTable.toLabelName(id);

        // Start looking for a definition in the current scope.
        Scope scope = table.current();

        // If there is a local declaration or definition, use that
        // one.
        while (! isFunctionScope(scope.getName())) {
          final Type type = (Type)scope.lookupLocally(name);
          if (null != type) {
            assert type.resolve().isLabel() : "Malformed label type";
            if (type.hasAttribute(Constants.ATT_UNINITIALIZED)) {
              runtime.error("label '"+id+"' used but not defined", labelRef);
            }
            type.addAttribute(Constants.ATT_USED);
            return;
          }

          scope = scope.getParent();
        }

        // Otherwise, check the function's scope.
        final Type type = (Type)scope.lookupLocally(name);
        if (null == type) {
          runtime.error("label '" + id + "' used but not defined", labelRef);
        } else {
          if (type.hasAttribute(Constants.ATT_UNINITIALIZED)) {
            runtime.error("label '" + id + "' used but not defined", labelRef);
          }
          type.addAttribute(Constants.ATT_USED);
        }
      }

      public void visitGotoStatement(GNode n) {
        if (null == n.get(0)) {
          check(n.getGeneric(1).getString(0), n);
        }
      }

      public void visitLabelAddressExpression(GNode n) {
        check(n.getString(0), n);
      }

      public void visit(Node n) {
        table.enter(n);
        for (Object o : n) {
          if (o instanceof Node) dispatch((Node)o);
        }
        table.exit(n);
      }
    };

  /**
   * Check that all labels defined in the specified top-level function
   * are also used.  This method requires that all relevant AST nodes
   * have been associated with their symbol table {@link
   * Constants#SCOPE scopes} and that all used labels have been
   * annotated as {@link Constants#ATT_USED used}.
   *
   * @param function The function to check.
   */
  protected void checkDefinedLabels(GNode function) {
    @SuppressWarnings("unused")
    final Visitor v = new Visitor() {
      final Map<Type, Type> checkedDefined = new IdentityHashMap<Type, Type>();
      final Map<Type, Type> checkedUsed    = new IdentityHashMap<Type, Type>();

      public void visitNamedLabel(GNode n) {
        final String id   = n.getString(0);
        final String name = SymbolTable.toLabelName(id);
        final Type   type = (Type)table.current().lookup(name);

        if (null != type) {
          if (! checkedUsed.containsKey(type)) {
            checkedUsed.put(type, type);

            if (! type.hasAttribute(Constants.ATT_USED)) {
              runtime.warning("label '" + id + "' defined but not used", n);
            }
          }
        }
      }

      public void visitLocalLabelDeclaration(GNode n) {
        for (Object o : n) {
          final String id   = Token.cast(o);
          final String name = SymbolTable.toLabelName(id);
          final Type   type = (Type)table.current().lookup(name);

          if (null != type) {
            if (! checkedDefined.containsKey(type))  {
              checkedDefined.put(type, type);
            
              if (type.hasAttribute(Constants.ATT_UNINITIALIZED) &&
                  ! type.hasAttribute(Constants.ATT_USED)) {
                runtime.warning("label '" + id + "' declared but not defined",n);
              }
            }
          }
        }
      }

      public void visit(Node n) {
        table.enter(n);
        for (Object o : n) {
          if (o instanceof Node) dispatch((Node)o);
        }
        table.exit(n);
      }
    };
    v.dispatch(function);
  }

  /** Visit the specified labeled statement. */
  public Type visitLabeledStatement(GNode n) {
    // Process the label.
    dispatch(n.getNode(0));

    // Process the statement.  If the statement has a type, capture
    // that type.
    final Object o      = dispatch(n.getNode(1));
    final Type   result = (o instanceof Type) ? (Type)o : VoidT.TYPE;

    mark(n, result);
    return result;
  }

  /** Visit the specified named label. */
  public void visitNamedLabel(GNode n) {
    final String          id   = n.getString(0);
    final String          name = SymbolTable.toLabelName(id);
    final List<Attribute> atts = toAttributeList(n.getGeneric(1));

    // Start looking for a suitable scope with the current scope.
    Scope scope = table.current();

    // If there is a local label declaration, define the label in the
    // declaration's scope.
    while (! isFunctionScope(scope.getName())) {
      final Type type = (Type)scope.lookupLocally(name);

      if (null != type) {
        assert type.isLabel() : "Malformed label type";
        if (type.hasAttribute(Constants.ATT_UNINITIALIZED)) {
          scope.define(name, new LabelT(id).locate(n).
                       attribute(Constants.ATT_DEFINED).attribute(atts));
        } else {
          runtime.error("duplicate label '" + id + "'", n);
          reportPrevious(id, type);
        }
        return;
      }

      scope = scope.getParent();
    }

    // Define the label in the function's scope.
    final Type type = (Type)scope.lookupLocally(name);

    if (null != type && ! type.hasAttribute(Constants.ATT_UNINITIALIZED)) {
      runtime.error("duplicate label '" + id + "'", n);
      reportPrevious(id, (Type)scope.lookupLocally(name));
    } else {
      scope.define(name, new LabelT(id).locate(n).
                   attribute(Constants.ATT_DEFINED).attribute(atts));
    }
  }

  /** Visit the specified case label. */
  public void visitCaseLabel(GNode n) {
    if (0 == switches.size()) {
      runtime.error("case label not within a switch statement", n);
      return;
    }

    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);
    final Node n2 = (2 == n.size()) ? n.getNode(1) : null;
    final Type t2 = (Type)dispatch(n2);

    if (t1.isError() || (null != t2 && t2.isError())) {
      return;

    } else if ((! c().isIntegral(t1)) ||
               ((null != t2) && (! c().isIntegral(t2)))) {
      runtime.error("case label not of integer type", n);
      return;
      
    } else if ((! t1.hasConstant()) ||
               ((null != t2) && (! t2.hasConstant()))) {
      runtime.error("case label not constant", n);
      return;
    }

    if (null != t2) {
      // Test: i2 < i1
      try {
        if (t2.getConstant().bigIntValue().
            compareTo(t2.getConstant().bigIntValue()) < 0) {
          runtime.error("empty range in case label", n);
        }
      } catch (IllegalStateException x) {
        runtime.warning("can't compute range in case label", n);
      }
    }
  }

  /** Visit the specified default label. */
  public void visitDefaultLabel(GNode n) {
    if (0 == switches.size()) {
      runtime.error("'default' label not within a switch statement", n);
    } else if (switches.get(switches.size()-1)) {
      runtime.error("multiple default labels in one switch", n);
    } else {
      switches.set(switches.size()-1, Boolean.TRUE);
    }
  }

  /** Visit the specified local label declaration. */
  public void visitLocalLabelDeclaration(GNode n) {
    for (Object o : n) {
      final String id   = Token.cast(o);
      final String name = SymbolTable.toLabelName(id);
      if (table.current().isDefinedLocally(name)) {
        runtime.error("duplicate label declaration '" + id + "'", n);
        reportPrevious(id, (Type)table.current().lookupLocally(name));
      } else {
        table.current().define(name, new LabelT(id).locate(n).
                               attribute(Constants.ATT_UNINITIALIZED));
      }
    }
  }

  /** Visit the specified compound statement. */
  public Type visitCompoundStatement(GNode n) {
    final boolean scope    = hasScope;
    hasScope               = true;
    final boolean stmtexpr = isStmtAsExpr;
    isStmtAsExpr           = false;

    if (scope || stmtexpr) {
      String name = table.freshName("block");
      table.enter(name);
      table.mark(n);
    }

    Type result = VoidT.TYPE;

    final int size = n.size();
    for (int i=0; i<size; i++) {
      Object o = dispatch((Node)n.get(i));

      if ((size-2 == i) && (o instanceof Type)) {
        // If the last statement (i.e., the child before the trailing
        // annotations) is an expression statement, capture that
        // expression's type.
        result = (Type)o;
      }
    }

    if (scope || stmtexpr) {
      table.exit();
    } 
    hasScope = scope;
    return stmtexpr ? result : VoidT.TYPE;
  }

  /** Visit the specified if else statement. */
  public void visitIfElseStatement(GNode n) {
    final Node n1 = n.getNode(0);
    ensureScalar(n1, c().pointerize((Type)dispatch(n1)));
    dispatch(n.getNode(1));
    dispatch(n.getNode(2));
  }

  /** Visit the specified if else statement. */
  public void visitIfStatement(GNode n) {
    final Node n1 = n.getNode(0);
    ensureScalar(n1, c().pointerize((Type)dispatch(n1)));
    dispatch(n.getNode(1));
  }

  /** Visit the specified while statement. */
  public void visitWhileStatement(GNode n) {
    final Node n1 = n.getNode(0);
    ensureScalar(n1, c().pointerize((Type)dispatch(n1)));

    loops.add(Boolean.TRUE);
    dispatch(n.getNode(1));
    loops.remove(loops.size()-1);
  }

  /** Visit the specified do statement. */
  public void visitDoStatement(GNode n) {
    loops.add(Boolean.TRUE);
    dispatch(n.getNode(0));
    loops.remove(loops.size()-1);

    final Node n2 = n.getNode(1);
    ensureScalar(n2, c().pointerize((Type)dispatch(n2)));
  }

  /** Visit the specified for statement. */
  public void visitForStatement(GNode n) {
    final boolean scope = hasScope;
    hasScope            = false;
    final String  name  = table.freshName("forloop");
    table.enter(name);
    table.mark(n);

    dispatch(n.getNode(0));
    if (null != n.get(1)) {
      Node n2 = n.getNode(1);
      ensureScalar(n2, c().pointerize((Type)dispatch(n2)));
    }
    dispatch(n.getNode(2));

    loops.add(Boolean.TRUE);
    dispatch(n.getNode(3));
    loops.remove(loops.size()-1);

    table.exit();
    hasScope      = scope;
  }

  /** Visit the specified switch statement. */
  public void visitSwitchStatement(GNode n) {
    final Node n1 = n.getNode(0);
    ensureInteger(n1, c().pointerize((Type)dispatch(n1)));
    switches.add(Boolean.FALSE);
    dispatch(n.getNode(1));
    switches.remove(switches.size()-1);
  }

  /** Visit the specified break statement. */
  public void visitBreakStatement(GNode n) {
    if ((0 == switches.size()) && (0 == loops.size())) {
      runtime.error("break statement not within loop or switch", n);
    }
  }

  /** Visit the specified continue statement. */
  public void visitContinueStatement(GNode n) {
    if (0 == loops.size()) {
      runtime.error("continue statement not within a loop", n);
    }
  }

  /** Visit the specified return statement. */
  public Type visitReturnStatement(GNode n) {
    final Type t1 = (Type)dispatch(n.getNode(0));

    // Find the enclosing function scope.
    Scope scope = table.current();
    while (! isFunctionScope(scope.getName())) {
      scope = scope.getParent();
    }

    // Determine the function's name, type, and result type.
    final String name     = SymbolTable.fromNameSpace(scope.getName());
    final Type   function = (Type)scope.getParent().lookupLocally(name);
    final Type   result   = function.resolve().toFunction().getResult();

    // Check for consistenty.
    if (result.hasTag(Tag.VOID)) {
      if ((null != t1) && ! t1.hasTag(Tag.VOID)) {
        runtime.warning("'return' with a value, in function returning void", n);
      }
    } else {
      if (null != t1) {
        processAssignment(false, "return", n, result, t1);
      } else if (pedantic) {
        runtime.warning("'return' with no value, in function returning " +
                        "non-void", n);
      }
    }

    // Done.
    mark(n, result);
    return result;
  }

  /** Visit the specified goto statement. */
  public void visitGotoStatement(GNode n) {
    // Regular goto labels are checked by checkLabels().
    if (null == n.get(0)) return;

    // Computed goto statements are checked right here.
    final Node n1 = n.getNode(1);
    final Type t1 = (Type)dispatch(n1);
    if (ensureScalar(n1, t1) && t1.resolve().isFloat()) {
      runtime.error("cannot convert to pointer type", n);
    }
  }

  /** Visit the specified expression statement. */
  public Type visitExpressionStatement(GNode n) {
    final Type t = (Type)dispatch(n.getNode(0));

    // The resulting type is not an lvalue.
    final Type result = c().toRValue(t);

    mark(n, result);
    return result;
  }

  /** Visit the specified expression list. */
  public List visitExpressionList(GNode n) {
    // Create a list of expression types and return it.
    final List<Type> result = new ArrayList<Type>(n.size());
    for (Object o : n) result.add((Type)dispatch((Node)o));
    return result;
  }

  /**
   * Process the specified expression node.  This method simply
   * dispatches this visitor on the specified node and returns the
   * resulting type.  It is typically used from other visitors nested
   * in this class.
   *
   * @param n The expression node.
   * @return The corresponding type.
   */
  public Type processExpression(Node n) {
    return (Type)dispatch(n);
  }

  /** Visit the specified comma expression. */
  public Type visitCommaExpression(GNode n) {
    // C99 6.5.17
    dispatch(n.getNode(0));
    final Type t2 = (Type)dispatch(n.getNode(1));
    final Type r2 = c().pointerize(t2); // GCC performs pointer decay; so do we.

    // C99 6.5.17, footnote 95: the result is not an lvalue.
    final Type result = c().toRValue(r2);

    mark(n, result);
    return result;
  }

  /** Visit the specified assignment expression. */
  public Type visitAssignmentExpression(GNode n) {
    // C99 6.5.16
    final Node   n1 = n.getNode(0);
    final String op = n.getString(1);
    final Node   n2 = n.getNode(2);

    final Type   t1 = (Type)dispatch(n1);
    final Type   t2 = (Type)dispatch(n2);

    Type result;
    if (t1.hasError() || t2.hasError()) {
      // Nothing to see here.  Move on.
      result = ErrorT.TYPE;

    } else if ("=".equals(op)) {
      final boolean cond1 = ensureLValue(n1, t1);
      result              = processAssignment(false, "assignment", n, t1, t2);

      // Patch in error type.
      if (! cond1) result = ErrorT.TYPE;

    } else if ("+=".equals(op) || "-=".equals(op)) {
      // Addition and subtraction require either arithmetic operands
      // or the left side to be a pointer and the right side to be an
      // integer.
      final Type r1 = t1.resolve();

      switch (r1.tag()) {
      case BOOLEAN:
      case INTEGER:
      case FLOAT: {
        final boolean cond1 = ensureLValue(n1, t1);
        final boolean cond2 = ensureArithmetic(n2, t2);
        result              = cond1 && cond2 ? r1 : ErrorT.TYPE;
      } break;

      case POINTER: {
        final boolean cond1 = ensureLValue(n1, t1);
        final boolean cond2 = ensureInteger(n2, t2);
        result              = cond1 && cond2 ? r1 : ErrorT.TYPE;
      } break;

      default:
        runtime.error("invalid "+toDescription(n1)+" where scalar required", n1);
        result = ErrorT.TYPE;
      }

    } else if ("*=".equals(op) || "/=".equals(op)) {
      // Multiplication and division require arithmetic operands.
      final boolean cond1 = ensureArithmetic(n1, t1) && ensureLValue(n1, t1);
      final boolean cond2 = ensureArithmetic(n2, t2);
      result              = cond1 && cond2 ? t1.resolve() : ErrorT.TYPE;

    } else {
      // Modulo, shift, bitwise and, bitwise xor, and bitwise or
      // require integer operands.
      final boolean cond1 = ensureInteger(n1, t1) && ensureLValue(n1, t1);
      final boolean cond2 = ensureInteger(n2, t2);
      result              = cond1 && cond2 ? t1.resolve() : ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified conditional expression. */
  public Type visitConditionalExpression(GNode n) {
    // C99 6.5.15
    final Node n1 = n.getNode(0);
    final Node n2 = n.getNode(1);
    final Node n3 = n.getNode(2);

    final Type t1 = (Type)dispatch(n1);
    Type       t2 = (Type)dispatch(n2);
    final Type t3 = (Type)dispatch(n3);

    if (null == t2) t2 = t1; // Allow for GCC's omitted middle operand.

    final Type r2 = c().pointerize(t2);
    final Type r3 = c().pointerize(t3);

    Type result;
    final boolean cond1 = ensureScalar(n1, c().pointerize(t1));
    if (r2.isError() || r3.isError()) {
      result = ErrorT.TYPE;

    } else if (c().isArithmetic(t2) && c().isArithmetic(t3)) {
      result = cond1 ? c().convert(t2, t3) : ErrorT.TYPE;
      result = valueConditional(result, t1, t2, t3);

    } else if ((r2.isStruct() && r3.isStruct() && c().equal(t2, t3)) ||
               (r2.isUnion()  && r3.isUnion()  && c().equal(t2, t3))) {
      result = cond1 ? c().qualify(r2, t2) : ErrorT.TYPE;

    } else if (r2.isVoid() && r3.isVoid()) {
      result = cond1 ? (Type)VoidT.TYPE : ErrorT.TYPE;

    } else if (r2.isPointer() && t3.hasConstant() && t3.getConstant().isNull()) {
      result = cond1 ? c().qualify(r2, t2) : ErrorT.TYPE;
      result = valueConditional(result, t1, t2, t3);

    } else if (t2.hasConstant() && t2.getConstant().isNull() && r3.isPointer()) {
      result = cond1 ? c().qualify(r3, t3) : ErrorT.TYPE;
      result = valueConditional(result, t1, t2, t3);

    } else if (r2.isPointer() && r3.isPointer()) {
      final Type pt2  = r2.toPointer().getType(); // PointedTo, PointedToResolved
      final Type pt3  = r3.toPointer().getType();

      final Type ptr2 = pt2.resolve();
      final Type ptr3 = pt3.resolve();

      if (ptr2.isError() || ptr3.isError()) {
        result = ErrorT.TYPE;

      } else if (c().equal(ptr2, ptr3)) {
        if (cond1) {
          result = new PointerT(c().qualify(c().qualify(ptr2, pt2), pt3));
          result = c().qualify(c().qualify(result, t2), t3);
          result = valueConditional(result, t1, t2, t3);
        } else {
          result = ErrorT.TYPE;
        }

      } else if (ptr2.isVoid() || ptr3.isVoid()) {
        if (cond1) {
          result = new PointerT(c().qualify(c().qualify(VoidT.TYPE, pt2), pt3));
          result = c().qualify(c().qualify(result, t2), t3);
          result = valueConditional(result, t1, t2, t3);
        } else {
          result = ErrorT.TYPE;
        }

      } else {
        runtime.error("pointer type mismatch in conditional expression", n);
        result = ErrorT.TYPE;
      }

    } else if ((c().isIntegral(t2) && r3.isPointer()) ||
               (r2.isPointer() && c().isIntegral(t3))) {
      runtime.error("pointer/integer type mismatch in conditional expression",n);
      result = ErrorT.TYPE;

    } else {
      runtime.error("type mismatch in conditional expression", n);
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /**
   * Determine a conditional expression's value.  If a conditional
   * expression's value can be statically determined, this method
   * annotates the expression's result with that value.
   *
   * @param result The result type.
   * @param t1 The conditional's type.
   * @param t2 The consequence's type.
   * @param t3 The alternative's type.
   * @return The annotated result type.
   */
  protected Type valueConditional(Type result, Type t1, Type t2, Type t3) {
    if (result.isError()) return result;

    if (t1.hasConstant()) {
      final Type type = t1.getConstant().isTrue() ? t2 : t3;

      if (type.hasConstant()) {
        result = result.annotate().constant(type.getConstant().getValue());
      }
    }
    return result;
  }

  /** Visit the specified logical or expression. */
  public Type visitLogicalOrExpression(GNode n) {
    // C99 6.5.14
    final Node n1 = n.getNode(0);
    final Node n2 = n.getNode(1);
    final Type t1 = (Type)dispatch(n1);
    final Type t2 = (Type)dispatch(n2);

    Type result;
    final boolean cond1 = ensureScalar(n1, c().pointerize(t1));
    final boolean cond2 = ensureScalar(n2, c().pointerize(t2));
    if (cond1 && cond2) {
      result = NumberT.INT;

      if (t1.hasConstant()) {
        if (t1.getConstant().isTrue()) {
          result = result.annotate().constant(true);
        } else if (t2.hasConstant()) {
          result = result.annotate().constant(t2.getConstant().isTrue());
        }
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified logical and expression. */
  public Type visitLogicalAndExpression(GNode n) {
    // C99 6.5.13
    final Node n1 = n.getNode(0);
    final Node n2 = n.getNode(1);
    final Type t1 = (Type)dispatch(n1);
    final Type t2 = (Type)dispatch(n2);

    Type result;
    final boolean cond1 = ensureScalar(n1, c().pointerize(t1));
    final boolean cond2 = ensureScalar(n2, c().pointerize(t2));
    if (cond1 && cond2) {
      result = NumberT.INT;

      if (t1.hasConstant()) {
        if (! t1.getConstant().isTrue()) {
          result = result.annotate().constant(false);
        } else if (t2.hasConstant()) {
          result = result.annotate().constant(t2.getConstant().isTrue());
        }
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified bitwise or expression. */
  public Type visitBitwiseOrExpression(GNode n) {
    // C99 6.5.12
    final Node n1 = n.getNode(0);
    final Node n2 = n.getNode(1);
    final Type t1 = (Type)dispatch(n1);
    final Type t2 = (Type)dispatch(n2);

    Type result;
    final boolean cond1 = ensureInteger(n1, t1);
    final boolean cond2 = ensureInteger(n2, t2);
    if (cond1 && cond2) {
      result = c().convert(t1, t2);

      if (t1.hasConstant() && t2.hasConstant()) {
        result = result.annotate();
        try {
          result = result.
            constant(c().mask(t1.getConstant().bigIntValue(), result).
                     or(c().mask(t2.getConstant().bigIntValue(), result)));
        } catch (IllegalStateException x) {
          result = result.constant(new StaticReference(result));
        }
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified bitwise xor expression. */
  public Type visitBitwiseXorExpression(GNode n) {
    // C99 6.5.11
    final Node n1 = n.getNode(0);
    final Node n2 = n.getNode(1);
    final Type t1 = (Type)dispatch(n1);
    final Type t2 = (Type)dispatch(n2);

    Type result;
    final boolean cond1 = ensureInteger(n1, t1);
    final boolean cond2 = ensureInteger(n2, t2);
    if (cond1 && cond2) {
      result = c().convert(t1, t2);

      if (t1.hasConstant() && t2.hasConstant()) {
        result = result.annotate();
        try {
          result = result.
            constant(c().mask(t1.getConstant().bigIntValue(), result).
                     xor(c().mask(t2.getConstant().bigIntValue(), result)));
        } catch (IllegalStateException x) {
          result = result.constant(new StaticReference(result));
        }
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified bitwise and expression. */
  public Type visitBitwiseAndExpression(GNode n) {
    // C99 6.5.10
    final Node n1 = n.getNode(0);
    final Node n2 = n.getNode(1);
    final Type t1 = (Type)dispatch(n1);
    final Type t2 = (Type)dispatch(n2);

    Type result;
    final boolean cond1 = ensureInteger(n1, t1);
    final boolean cond2 = ensureInteger(n2, t2);
    if (cond1 && cond2) {
      result = c().convert(t1, t2);

      if (t1.hasConstant() && t2.hasConstant()) {
        result = result.annotate();
        try {
          result = result.
            constant(c().mask(t1.getConstant().bigIntValue(), result).
                     and(c().mask(t2.getConstant().bigIntValue(), result)));
        } catch (IllegalStateException x) {
          result = result.constant(new StaticReference(result));
        }
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified equality expression. */
  public Type visitEqualityExpression(GNode n) {
    // C99 6.5.9
    final Node   n1 = n.getNode(0);
    final String op = n.getString(1);
    final Node   n2 = n.getNode(2);
    final Type   t1 = (Type)dispatch(n1);
    final Type   t2 = (Type)dispatch(n2);
    final Type   r1 = c().pointerize(t1);
    final Type   r2 = c().pointerize(t2);

    Type result;
    if (r1.isError() || r2.isError()) {
      // Nothing to see here.  Move on.
      result = ErrorT.TYPE;

    } else if (c().isArithmetic(t1) && c().isArithmetic(t2)) {
      result = NumberT.INT;

      if (t1.hasConstant() && t2.hasConstant()) {
        result = result.annotate();
        try {
          if (c().isIntegral(r1) && c().isIntegral(r2)) {
            final BigInteger i1 = t1.getConstant().bigIntValue();
            final BigInteger i2 = t2.getConstant().bigIntValue();
            
            result = result.constant("==".equals(op) ? i1.compareTo(i2) == 0 :
                                     i1.compareTo(i2) != 0);
            
          } else {
            final double d1 = t1.getConstant().doubleValue();
            final double d2 = t2.getConstant().doubleValue();
            
            result = result.constant("==".equals(op) ? d1 == d2 : d1 != d2);
          }
        } catch (IllegalStateException x) {
          result = result.constant(new StaticReference(result));
        }
      }

    } else if (r1.isPointer() && t2.hasConstant() && t2.getConstant().isNull()) {
      result = NumberT.INT;

      if (t1.hasConstant()) {
        result = result.annotate().constant(! t1.getConstant().isTrue());
      }

    } else if (t1.hasConstant() && t1.getConstant().isNull() && r2.isPointer()) {
      result = NumberT.INT;

      if (t2.hasConstant()) {
        result = result.annotate().constant(! t2.getConstant().isTrue());
      }

    } else if (! pedantic && ((r1.isPointer() && c().isIntegral(r2)) ||
                              (c().isIntegral(r1) && r2.isPointer()))) {
      runtime.warning("comparison between pointer and integer", n);
      result = NumberT.INT;

      if (t1.hasConstant() && t2.hasConstant()) {
        final boolean equal = t1.getConstant().getValue().
          equals(t2.getConstant().getValue());
        result = result.annotate().constant("==".equals(op) ? equal : ! equal);
      }

    } else if (r1.isPointer() && r2.isPointer()) {
      final Type ptr1 = r1.toPointer().getType().resolve(); // PointedToResolved
      final Type ptr2 = r2.toPointer().getType().resolve();

      if (ptr1.isError() || ptr2.isError()) {
        result = ErrorT.TYPE;

      } else if (c().equal(ptr1, ptr2) || ptr1.isVoid() || ptr2.isVoid()) {
        result = NumberT.INT;

        if (t1.hasConstant() && t2.hasConstant()) {
          final boolean equal = t1.getConstant().getValue().
            equals(t2.getConstant().getValue());
          result = result.annotate().constant("==".equals(op)? equal : ! equal);
        }

      } else {
        runtime.error("comparison of distinct pointer types lacks a cast", n);
        result = ErrorT.TYPE;
      }

    } else {
      runtime.error("invalid operands to 'binary " + op + "'", n);
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified relational expression. */
  public Type visitRelationalExpression(GNode n) {
    // C99 6.5.8
    final Node   n1 = n.getNode(0);
    final String op = n.getString(1);
    final Node   n2 = n.getNode(2);
    final Type   t1 = (Type)dispatch(n1);
    final Type   t2 = (Type)dispatch(n2);
    final Type   r1 = c().pointerize(t1);
    final Type   r2 = c().pointerize(t2);

    Type result;
    if (r1.isError() || r2.isError()) {
      // Nothing to see here.  Move on.
      result = ErrorT.TYPE;

    } else if (c().isReal(t1) && c().isReal(t2)) {
      result = NumberT.INT;

      if (t1.hasConstant() && t2.hasConstant()) {
        result = result.annotate();
        try {
          if (c().isIntegral(r1) && c().isIntegral(r2)) {
            final BigInteger i1 = t1.getConstant().bigIntValue();
            final BigInteger i2 = t2.getConstant().bigIntValue();
            
            if ("<".equals(op)) {
              result = result.constant(i1.compareTo(i2) < 0);
            } else if (">".equals(op)) {
              result = result.constant(i1.compareTo(i2) > 0);
            } else if ("<=".equals(op)) {
              result = result.constant(i1.compareTo(i2) <= 0);
            } else {
              result = result.constant(i1.compareTo(i2) >= 0);
            }
            
          } else {
            final double d1 = t1.getConstant().doubleValue();
            final double d2 = t2.getConstant().doubleValue();
            
            if ("<".equals(op)) {
              result = result.constant(d1 < d2);
            } else if (">".equals(op)) {
              result = result.constant(d1 > d2);
            } else if ("<=".equals(op)) {
              result = result.constant(d1 <= d2);
            } else {
              result = result.constant(d1 >= d2);
            }
          }
        } catch (IllegalStateException x) {
          result = result.constant(new StaticReference(result));
        }
      }

    } else if (r1.isPointer() && r2.isPointer()) {
      final Type ptr1 = r1.toPointer().getType().resolve(); // PointedToResolved
      final Type ptr2 = r2.toPointer().getType().resolve();

      if (ptr1.isError() || ptr2.isError()) {
        result = ErrorT.TYPE;

      } else if (c().equal(ptr1, ptr2)) {
        result = NumberT.INT;

        if (t1.hasConstant() && t2.hasConstant()) {
          result = result.annotate().constant(new StaticReference(result));
        }

      } else {
        runtime.error("comparison of distinct pointer types lacks a cast", n);
        result = ErrorT.TYPE;
      }

    } else {
      runtime.error("invalid operands to 'binary " + op + "'", n);
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified shift expression. */
  public Type visitShiftExpression(GNode n) {
    // C99 6.5.7
    final Node   n1 = n.getNode(0);
    final String op = n.getString(1);
    final Node   n2 = n.getNode(2);

    final Type   t1 = (Type)dispatch(n1);
    final Type   t2 = (Type)dispatch(n2);

    Type result;
    final boolean cond1 = ensureInteger(n1, t1);
    final boolean cond2 = ensureInteger(n2, t2);
    if (cond1 && cond2) {
      result = c().promote(t1);

      if (t2.hasConstant()) {
        BigInteger distance;
        try {
          distance = t2.getConstant().bigIntValue();
        } catch (IllegalStateException x) {
          runtime.warning("can't compute shift count", n2);
          distance = BigInteger.ZERO;
        }
        final BigInteger width = BigInteger.valueOf(c().getWidth(result));

        // Test: distance >= width
        if (distance.compareTo(width) >= 0) {
          if ("<<".equals(op)) {
            runtime.warning("left shift count >= width of type", n2);
          } else {
            runtime.warning("right shift count >= width of type", n2);
          }

          // Test: distance < 0
        } else if (distance.compareTo(BigInteger.ZERO) < 0) {
          if ("<<".equals(op)) {
            runtime.warning("left shift count is negative", n2);
          } else {
            runtime.warning("right shift count is negative", n2);
          }

        } else if (t1.hasConstant()) {
          result = result.annotate();
          try {
            final BigInteger value = t1.getConstant().bigIntValue();

            if ("<<".equals(op)) {
              result = result.constant(value.shiftLeft(distance.intValue()));
              result = c().qualify(result, t1);
            } else {
              result = result.constant(value.shiftRight(distance.intValue()));
              result = c().qualify(result, t1);
            }
          } catch (IllegalStateException x) {
            result = result.constant(new StaticReference(result));
            result = c().qualify(result, t1);
          }

        } else {
          result = c().qualify(result, t1);
        }

      } else {
        result = c().qualify(result, t1);
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified additive expression. */
  public Type visitAdditiveExpression(GNode n) {
    // C99 6.5.6
    final Node   n1 = n.getNode(0);
    final String op = n.getString(1);
    final Node   n2 = n.getNode(2);
    final Type   t1 = (Type)dispatch(n1);
    final Type   t2 = (Type)dispatch(n2);
    final Type   r1 = c().pointerize(t1);
    final Type   r2 = c().pointerize(t2);

    Type result;
    if (r1.isError() || r2.isError()) {
      result = ErrorT.TYPE;

    } else if (c().isArithmetic(t1) && c().isArithmetic(t2)) {
      result = c().convert(t1, t2);

      if (t1.hasConstant() && t2.hasConstant()) {
        result = result.annotate();
        if (c().isIntegral(result)) {
          // If one of the terms has a reference value, try to
          // preserve a meaningful value.
          if (t1.getConstant().isReference() &&
              (! t2.getConstant().isReference())) {

            if ("+".equals(op)) {
              // ref + int
              result = result.
                constant(t1.getConstant().refValue().
                         add(t2.getConstant().bigIntValue()));
            } else {
              // ref - int
              result = result.
                constant(t1.getConstant().refValue().
                         subtract(t2.getConstant().bigIntValue()));
            }

          } else if ((! t1.getConstant().isReference()) && "+".equals(op) &&
                     t2.getConstant().isReference()) {
            // int + ref
            result = result.
              constant(t2.getConstant().refValue().
                       add(t1.getConstant().bigIntValue()));

          } else if (t1.getConstant().isReference() && "-".equals(op) &&
                     t2.getConstant().isReference()) {
            // ref - ref
            final BigInteger diff = t1.getConstant().refValue().
              difference(t2.getConstant().refValue());
            if (null != diff) {
              result = result.constant(diff);
            } else {
              result = result.constant(new StaticReference(result));
            }

          } else {
            try {
              final BigInteger i1 = t1.getConstant().bigIntValue();
              final BigInteger i2 = t2.getConstant().bigIntValue();

              // int + int
              result = result.constant("+".equals(op) ? i1.add(i2) :
                                       i1.subtract(i2));
            } catch(IllegalStateException x) {
              // ref + ref
              result = result.constant(new StaticReference(result));
            }
          }

        } else {
          try {
            final double d1 = t1.getConstant().doubleValue();
            final double d2 = t2.getConstant().doubleValue();

            result = result.constant("+".equals(op) ? d1 + d2 : d1 - d2);
          } catch (IllegalStateException x) {
            result = result.constant(new StaticReference(result));
          }
        }
      }

    } else if ("+".equals(op)) {
      if (r1.isPointer() && c().isIntegral(r2)) {
        if (ensurePointerArithmetic(n, r1)) {
          result = r1;
          
          if (c().hasConstRef(t1) && t2.hasConstant()) {
            result = result.annotate();
            try {
              result = result.
                constant(c().getConstRef(t1).
                         add(t2.getConstant().bigIntValue()));
            } catch (IllegalStateException x) {
              result = result.constant(new StaticReference(result));
            }
          }
        } else {
          result = ErrorT.TYPE;
        }

      } else if (c().isIntegral(r1) && r2.isPointer()) {
        if (ensurePointerArithmetic(n, r2)) {
          result = r2;
          
          if (t1.hasConstant() && c().hasConstRef(t2)) {
            result = result.annotate();
            try {
              result = result.
                constant(c().getConstRef(t2).
                         add(t1.getConstant().bigIntValue()));
            } catch (IllegalStateException x) {
              result = result.constant(new StaticReference(result));
            }
          }
        } else {
          result = ErrorT.TYPE;
        }

      } else {
        runtime.error("invalid operands to 'binary +'" , n);
        result = ErrorT.TYPE;
      }

    } else if (r1.isPointer() && r2.isPointer()) {
      final Type ptr1 = r1.toPointer().getType().resolve();
      final Type ptr2 = r2.toPointer().getType().resolve();
      
      if (ptr1.isError() || ptr2.isError()) {
        result = ErrorT.TYPE;
        
      } else if (c().equal(ptr1, ptr2)) {
        result = C.PTR_DIFF;
        
        if (c().hasConstRef(t1) && c().hasConstRef(t2)) {
          BigInteger diff = c().getConstRef(t1).difference(c().getConstRef(t2));
          
          result = result.annotate();
          if (null == diff) {
            result = result.constant(new StaticReference(result));
          } else {
            result = result.constant(diff);
          }
        }
        
      } else {
        runtime.error("invalid operands to 'binary -'", n);
        result = ErrorT.TYPE;
      }
      
    } else if (r1.isPointer() && c().isIntegral(r2)) {
      if (ensurePointerArithmetic(n, r1)) {
        result = r1;
        if (c().hasConstRef(t1) && t2.hasConstant()) {
          result = result.annotate();
          try {
            result = result.constant(c().getConstRef(t1).
                                     subtract(t2.getConstant().bigIntValue()));
          } catch (IllegalStateException x) {
            result = result.constant(new StaticReference(result));
          }
        }
      } else {
        result = ErrorT.TYPE;
      }

    } else {
      runtime.error("invalid operands to 'binary -'", n);
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified multiplicative expression. */
  public Type visitMultiplicativeExpression(GNode n) {
    // C99 6.5.5
    final Node   n1 = n.getNode(0);
    final String op = n.getString(1);
    final Node   n2 = n.getNode(2);
    final Type   t1 = (Type)dispatch(n1);
    final Type   t2 = (Type)dispatch(n2);

    Type result;
    final boolean cond1 = (("%".equals(op) && ensureInteger(n1, t1)) ||
                           ((! "%".equals(op)) && ensureArithmetic(n1, t1)));
    final boolean cond2 = (("%".equals(op) && ensureInteger(n2, t2)) ||
                           ((! "%".equals(op)) && ensureArithmetic(n2, t2)));
    if (cond1 && cond2) {
      result = c().convert(t1, t2);

      if (t2.hasConstant()) {
        Constant c2 = t2.getConstant();

        if ((! "*".equals(op)) && (! c2.isTrue())) {
          runtime.warning("division by zero", n2);

        } else if (t1.hasConstant()) {
          Constant c1 = t1.getConstant();
          result      = result.annotate();

          try {
            if (c().isIntegral(result)) {
              BigInteger i1 = c1.bigIntValue();
              BigInteger i2 = c2.bigIntValue();
              
              if ("*".equals(op)) {
                result = result.constant(i1.multiply(i2));
              } else if ("/".equals(op)) {
                result = result.constant(i1.divide(i2));
              } else {
                result = result.constant(i1.remainder(i2));
              }
              
            } else {
              double d1 = c1.doubleValue();
              double d2 = c2.doubleValue();
              
              result = result.constant("*".equals(op) ? d1 * d2 : d1 / d2);
            }
          } catch (IllegalStateException x) {
            result = result.constant(new StaticReference(result));
          }
        }
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified cast expression. */
  public Type visitCastExpression(GNode n) {
    // C99 6.5.4, 6.3.2.3
    final Node n1 = n.getNode(0);
    final Node n2 = n.getNode(1);
    final Type t1 = (Type)dispatch(n1);
    final Type t2 = (Type)dispatch(n2);
    final Type r1 = t1.resolve();
    final Type r2 = c().pointerize(t2);

    // As an exception, GCC allows a struct or union cast to itself,
    // ignoring qualifiers.
    final boolean gcc = (! pedantic &&
                         r1.hasStructOrUnion() && r2.hasStructOrUnion() &&
                         c().equal(r1, r2));
    Type result;
    final boolean cond2 = r1.isVoid() || gcc || ensureScalar(n2, r2);
    switch (r1.tag()) {
    case ERROR: {
      result = ErrorT.TYPE;
    } break;

    case VOID: {
      // Cast to void.
      result = t1;
    } break;

    case POINTER: {
      // Cast to a pointer.
      if (! cond2) {
        result = ErrorT.TYPE;

      } else if (r2.isFloat()) {
        runtime.error("cannot convert to pointer type", n);
        result = ErrorT.TYPE;

      } else if (c().isIntegral(r2)) {
        // Cast from an integer.
        result = t1;

        if (t2.hasConstant()) {
          Type pt1 = r1.toPointer().getType();

          // Capture the memory location.
          Reference ref;
          try {
            ref = NullReference.NULL.add(t2.getConstant().bigIntValue());
          } catch (IllegalStateException x) {
            ref = new StaticReference(pt1);
          }

          result = result.annotate();
          if (pt1.hasTag(Tag.VOID) || c().isChar(pt1) || ref.isStatic()) {
            result = result.constant(ref);
          } else {
            result = result.constant(new CastReference(pt1, ref));
          }
        }

      } else {
        // Cast from another pointer.
        result = r1;

        if (c().hasConstRef(t2)) {
          Type pt1 = r1.toPointer().getType();
          Type pt2 = r2.toPointer().getType();
          result   = result.annotate();

          if (pt1.equals(pt2)) {
            // The types have the same memory shape.
            result = result.constant(c().getConstRef(t2));

          } else {
            // The types have different shapes.
            result =
              result.constant(new CastReference(pt1, c().getConstRef(t2)));
          }
        }
      }
    } break;

    case BOOLEAN:
    case INTEGER:
    case FLOAT: {
      // Cast to a number.
      if (! cond2) {
        result = ErrorT.TYPE;

      } else if (c().isArithmetic(r2)) {
        // Cast from another number.
        result = t1;

        if (t2.hasConstant()) {
          result = result.annotate();
          if (c().isIntegral(r1)) {
            if (c().isIntegral(r2)) {
              // Cast int to int.
              result = result.constant(t2.getConstant().getValue());
            } else {
              // Cast float to int: try to convert the original value
              // to a big integer value.
              try {
                result = result.constant(t2.getConstant().bigIntValue());
              } catch (IllegalStateException x) {
                result = result.constant(new StaticReference(result));
              }
            }
          } else {
            // Cast number to float: try to convert the original value
            // to a double value.
            try {
              result = result.constant(t2.getConstant().doubleValue());
            } catch (IllegalStateException x) {
              result = result.constant(new StaticReference(result));
            }
          }
        }

      } else {
        // Cast from a pointer.
        if (r1.isFloat()) {
          runtime.error("cannot convert from pointer type", n);
          result = ErrorT.TYPE;

        } else {
          result = t1;

          if (c().hasConstRef(t2)) {
            Reference ref = c().getConstRef(t2);
            Type      pt2 = r2.toPointer().getType();
            result        = result.annotate();

            if (ref.hasLocation()) {
              // Preserve the location.
              result = result.constant(ref.getLocation(c()));
            } else {
              // Soldier on with the reference as an arithmetic value
              // and hope that the program doesn't do any arithmetic
              // on the value beyond what is legal for pointers...
              result = result.constant(ref);
            }
          }
        }
      }
    } break;

    case ARRAY: {
      runtime.error("cast specifies array type", n);
      result = ErrorT.TYPE;
    } break;

    case FUNCTION: {
      runtime.error("cast specifies function type", n);
      result = ErrorT.TYPE;
    } break;

    case STRUCT:
    case UNION: {
      if (gcc) {
        // Handle the GCC exception.
        result = t1;
        break;
      }
      // Otherwise, fall through.
    }

    default:
      runtime.error("conversion to non-scalar type requested", n);
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified sizeof expression. */
  public Type visitSizeofExpression(GNode n) {
    // C99 6.5.3.4
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);
    final Type r1 = t1.resolve();

    Type result;
    if (r1.isError()) {
      // Nothing to see here.  Move on.
      result = ErrorT.TYPE;

    } else if (c().isIncomplete(t1) && ! r1.isVoid()) {
      runtime.error("invalid application of 'sizeof' to incomplete type", n);
      result = ErrorT.TYPE;

    } else if (t1.hasVariable() && t1.toVariable().hasWidth()) {
      runtime.error("'sizeof' applied to a bit-field", n);
      result = ErrorT.TYPE;

    } else if (pedantic && r1.isFunction()) {
      runtime.error("'sizeof' applied to funcion", n);
      result = ErrorT.TYPE;

    } else {
      result = C.SIZEOF;

      if (! c().isVariablyModified(r1)) {
        result = result.annotate().
          constant(BigInteger.valueOf(c().getSize(r1)));
      }
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified alignof expression. */
  public Type visitAlignofExpression(GNode n) {
    // No formal specification, so we treat it just like sizeof.
    // Experiments with GCC bear this out.
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);
    final Type r1 = t1.resolve();

    final Type result;
    if (t1.hasError()) {
      // Nothing to see here.  Move on.
      result = ErrorT.TYPE;

    } else if (c().isIncomplete(t1) && ! r1.isVoid() && ! r1.isArray()) {
      runtime.error("invalid application of '__alignof' to incomplete type", n);
      result = ErrorT.TYPE;

    } else if (t1.hasVariable() && t1.toVariable().hasWidth()) {
      runtime.error("'__alignof' applied to a bit-field", n);
      result = ErrorT.TYPE;

    } else if (pedantic && r1.isFunction()) {
      runtime.error("'__alignof' applied to function", n);
      result = ErrorT.TYPE;

    } else {
      result = C.SIZEOF.annotate().
        constant(BigInteger.valueOf(c().getAlignment(t1)));
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified offset of expression. */
  public Type visitOffsetofExpression(GNode n) {
    final Type base   = (Type)dispatch(n.getNode(0));
    final Type member = processOffset(base, n.getGeneric(1));

    final Type result;
    if (member.isError()) {
      result = ErrorT.TYPE;
    } else if (member.hasConstant()) {
      result = C.SIZEOF.annotate().constant(member.getConstant().getValue());
    } else {
      result = C.SIZEOF;
    }

    mark(n, result);
    return result;
  }

  /**
   * Process the specified offset selection.
   *
   * @param base The base type.
   * @param selection The selection.
   * @return The selected type annotated with its offset or
   *   <code>ErrorT.TYPE</code> on errors.
   */
  protected Type processOffset(Type base, GNode selection) {
    if (selection.hasName("PrimaryIdentifier")) {
      final String name   = selection.getString(0);
      final Type   member = processSelection(selection, base, name, false);
      if (member.isError()) return ErrorT.TYPE;

      final long offset = c().getOffset(base.toStructOrUnion(), name);
      return member.annotate().constant(BigInteger.valueOf(offset));

    } else if (selection.hasName("DirectComponentSelection")) {
      base = processOffset(base, selection.getGeneric(0));
      if (base.isError()) return ErrorT.TYPE;

      final String name   = selection.getString(1);
      final Type   member = processSelection(selection, base, name, false);
      if (member.isError()) return ErrorT.TYPE;

      if (! base.hasConstant()) return member;

      final long offset = base.getConstant().longValue() +
        c().getOffset(base.toStructOrUnion(), name);
      return member.annotate().constant(BigInteger.valueOf(offset));

    } else if (selection.hasName("SubscriptExpression")) {
      base = processOffset(base, selection.getGeneric(0));
      if (base.isError()) return ErrorT.TYPE;

      final Type index = (Type)dispatch(selection.getNode(1));
      if (index.isError()) return ErrorT.TYPE;

      final Type element = processSubscript(selection, base, index);
      if (element.isError()) return ErrorT.TYPE;

      if (! base.hasConstant() || ! index.hasConstant()) return element;

      final long offset = base.getConstant().longValue() +
        c().getSize(element) * index.getConstant().longValue();
      return element.annotate().constant(BigInteger.valueOf(offset));

    } else {
      runtime.error("second argument to 'offsetof' neither a " +
                    "selection nor a subscript", selection);
      return ErrorT.TYPE;
    }
  }

  /** Visit the specified type compatibility expression. */
  public Type visitTypeCompatibilityExpression(GNode n) {
    final Type t1     = (Type)dispatch(n.getNode(0));
    final Type t2     = (Type)dispatch(n.getNode(1));

    final Type result = NumberT.INT.annotate().
      constant(c().compose(t1, t2, pedantic).isError() ?
               BigInteger.ZERO : BigInteger.ONE);

    mark(n, result);
    return result;
  }

  /** Visit the specified unary minus expression. */
  public Type visitUnaryMinusExpression(GNode n) {
    // C99 6.5.3.3
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);

    Type result;
    if (ensureArithmetic(n1, t1)) {
      result = c().promote(t1);

      if (t1.hasConstant()) {
        result = result.annotate();
        try {
          if (c().isIntegral(result)) {
            result = result.
              constant(c().mask(t1.getConstant().bigIntValue().negate(),result));
          } else {
            result = result.constant(-t1.getConstant().doubleValue());
          }
        } catch (IllegalStateException x) {
          result = result.constant(new StaticReference(result));
        }
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified unary plus expression. */
  public Type visitUnaryPlusExpression(GNode n) {
    // C99 6.5.3.3
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);

    Type result;
    if (ensureArithmetic(n1, t1)) {
      result = c().promote(t1);

      if (t1.hasConstant()) {
        result = result.annotate().constant(t1.getConstant().getValue());
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified logical negation expression. */
  public Type visitLogicalNegationExpression(GNode n) {
    // C99 6.5.3.3
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);
    final Type r1 = c().pointerize(t1);

    Type result;
    if (ensureScalar(n1, r1)) {
      result = NumberT.INT;

      if (t1.hasConstant()) {
        result = result.annotate().constant(! t1.getConstant().isTrue());
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified bitwise negation expression. */
  public Type visitBitwiseNegationExpression(GNode n) {
    // C99 6.5.3.3
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);

    Type result;
    if (ensureInteger(n1, t1)) {
      result = c().promote(t1);

      if (t1.hasConstant()) {
        try {
          result = result.annotate().
            constant(c().mask(t1.getConstant().bigIntValue().not(), result));
        } catch (IllegalStateException x) {
          result = result.constant(new StaticReference(result));
        }
      }

    } else {
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified address expression. */
  public Type visitAddressExpression(GNode n) {
    // C99 6.5.3.2
    final GNode n1 = n.getGeneric(0);

    // &(*...) and &(x[y]) expressions get special treatment.
    if (n1.hasName("IndirectionExpression")) {
      // Determine the base type.
      final Type base = (Type)dispatch(n1.getGeneric(0));

      // Process the indirection and address to ensure that the types
      // are valid.
      Type type = processIndirection(n1, base, false);
      type      = processAddress(n, type);

      // Return the base, but not as an lvalue.
      Type result;
      if (type.isError()) {
        result = ErrorT.TYPE;
      } else {
        // Ensure the result is a pointer and an rvalue.
        result = c().toRValue(c().pointerize(base));

        // Track any constant value.
        final Type resolved = base.resolve();
        if (resolved.isArray() || resolved.isFunction()) {
          // Account for pointer decay.
          if (base.hasShape() && base.getShape().isConstant()) {
            result = result.annotate().constant(base.getShape());
          }
        } else if (base.hasConstant()) {
          result = result.annotate().constant(base.getConstant().getValue());
        }
      }

      mark(n, result);
      return result;

    } else if (n1.hasName("SubscriptExpression")) {
      // Determine the base and index types.
      final Type base  = (Type)dispatch(n1.getGeneric(0));
      final Type index = (Type)dispatch(n1.getGeneric(1));

      // Process the subscript to ensure that the types are valid.
      final Type type  = processSubscript(n1, base, index);

      // Return the type as if performing a pointer, integer addition.
      Type result;
      if (type.isError()) {
        result = ErrorT.TYPE;
      } else {
        // Ensure the result is a pointer.
        result = c().pointerize(base);

        // Track any constant value.
        Reference ref = null;

        if (base.resolve().isArray() &&
            base.hasShape() && base.getShape().isConstant()) {
          // Account for pointer decay.
          ref = base.getShape();

        } else if (base.hasConstant()) {
          // A pointer's constant value must be a reference.
          assert base.getConstant().isReference();

          ref = (Reference)base.getConstant().getValue();
        }

        if (null != ref && index.hasConstant()) {
          result = result.annotate();
          try {
            result = result.constant(ref.add(index.getConstant().bigIntValue()));
          } catch (IllegalStateException x) {
            result = result.constant(new StaticReference(result));
          }
        }
      }

      mark(n, result);
      return result;
    }

    // Back to normal operation.
    final Type t1     = (Type)dispatch(n1);
    Type       result = processAddress(n, t1);

    // Track compile-time constant pointers.
    if (t1.hasShape() && t1.getShape().isConstant()) {
      result = result.annotate().constant(t1.getShape());
    }

    // Done.
    mark(n, result);
    return result;
  }

  /**
   * Process the specified address expression.  This method assumes
   * that the specified node neither is an indirection nor a subscript
   * expression.
   *
   * @param n The node.
   * @param type The type.
   * @return The resulting type.
   */
  protected Type processAddress(GNode n, Type type) {
    final Type resolved = type.resolve();

    if (resolved.isError()) {
      return ErrorT.TYPE;

    } else if (type.hasShape()) {
      if (type.hasVariable() && type.toVariable().hasWidth()) {
        runtime.error("cannot take address of bit-field '" +
                      type.toVariable().getName() + "'", n);
        return ErrorT.TYPE;

      } else if (type.hasAttribute(Constants.ATT_STORAGE_REGISTER)) {
        runtime.error("address of register " + toDescription(n.getNode(0)) +
                      " requested", n);
        return ErrorT.TYPE;

      } else {
        Type result = new PointerT(c().qualify(resolved, type));
        if (type.getShape().isConstant()) {
          result = result.annotate().constant(type.getShape());
        }
        return result;
      }

    } else {
      runtime.error("invalid lvalue in unary '&'", n.getNode(0));
      return ErrorT.TYPE;
    }
  }

  /** Visit the specified label address expression. */
  public Type visitLabelAddressExpression(GNode n) {
    // The label's name is checked in a second phase after all a
    // function's labels have been added to the symbol table.  Here,
    // we only construt the appropriate type (void *).
    final Type result = PointerT.TO_VOID.annotate().
      constant(new StaticReference(n.getString(0), VoidT.TYPE));

    mark(n, result);
    return result;
  }

  /** Visit the specified indirection expression. */
  public Type visitIndirectionExpression(GNode n) {
    // C99 6.5.3.2
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);

    final Type result = processIndirection(n, t1, true);

    mark(n, result);
    return result;
  }

  /**
   * Process the specified indirection expression.
   *
   * @param n The node.
   * @param type The type.
   * @param warn The flag for whether to emit any warnings.
   * @return The resulting type.
   */
  protected Type processIndirection(Node n, Type type, boolean warn) {
    final Type resolved = c().pointerize(type);

    if (resolved.isError()) {
      return ErrorT.TYPE;

    } else if (resolved.isPointer()) {
      final Type pt  = resolved.toPointer().getType(); // PointedTo, PTResolved
      final Type ptr = pt.resolve();

      Type result;
      if (ptr.isError()) {
        result = ErrorT.TYPE;

      } else if (c().isIncomplete(pt)) {
        runtime.error("dereferencing pointer to incomplete type", n);
        result = ErrorT.TYPE;

      } else {
        final Reference ref;
        if (type.hasShape()) {
          ref = type.getShape().indirect(type);
        } else if (type.hasConstant()) {
          // Note that arrays and functions never have a value.  So,
          // just using the reference value is safe.
          ref = type.getConstant().refValue();
        } else {
          ref = new DynamicReference(ptr);
        }
        result = c().qualify(ptr, pt).annotate().shape(ref);
      }

      if (ptr.isVoid() && warn) {
        runtime.warning("dereferencing 'void *' pointer", n);
      }

      return result;

    } else {
      runtime.error("operand to 'unary *' not a pointer type", n);
      return ErrorT.TYPE;
    }
  }

  /** Visit the specified preincrement expression. */
  public Type visitPreincrementExpression(GNode n) {
    // C99 6.5.3.1
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);

    Type result;
    if (ensureScalar(n1, t1) &&
        ensurePointerArithmetic(n, t1) &&
        ensureLValue(n1, t1)) {
      result = t1.resolve();
    } else {
      result = ErrorT.TYPE;
    }
   
    mark(n, result);
    return result;
  }

  /** Visit the specified predecrement expression. */
  public Type visitPredecrementExpression(GNode n) {
    // C99 6.5.3.1
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);

    Type result;
    if (ensureScalar(n1, t1) &&
        ensurePointerArithmetic(n, t1) &&
        ensureLValue(n1, t1)) {
      result = t1.resolve();
    } else {
      result = ErrorT.TYPE;
    }
   
    mark(n, result);
    return result;
  }

  /** Visit the specified extension expression. */
  public Type visitExtensionExpression(GNode n) {
    // Nothing to see here.  Move on.
    return (Type)dispatch(n.getNode(0));
  }

  /** Visit the specified subscript expression. */
  public Type visitSubscriptExpression(GNode n) {
    // C99 6.5.2.1
    final Node n1 = n.getNode(0);
    final Node n2 = n.getNode(1);
    final Type t1 = (Type)dispatch(n1);
    final Type t2 = (Type)dispatch(n2);

    final Type result = processSubscript(n, t1, t2);

    mark(n, result);
    return result;
  }

  /**
   * Process the specified subscript expression.
   *
   * @param n The node.
   * @param base The base type.
   * @param index The index type.
   * @return The corresponding element type or an error type in case
   *   of an error.
   */
  protected Type processSubscript(Node n, Type base, Type index) {
    // C99 6.5.2.1
    final Type resolved = c().pointerize(base);

    final boolean cond2;
    if (index.hasError()) {
      cond2 = false;
    } else if (c().isIntegral(index)) {
      cond2 = true;
    } else {
      runtime.error("array subscript is not an integer", n);
      cond2 = false;
    }

    if (base.hasError()) {
      return ErrorT.TYPE;

    } else if (resolved.isPointer()) {
      final Type pt1  = resolved.toPointer().getType(); // PointedTo, PTResolved
      final Type ptr1 = pt1.resolve();

      if (ptr1.isError()) {
        return ErrorT.TYPE;

      } else if (ptr1.isFunction()) {
        runtime.error("subscripted value is pointer to function", n);
        return ErrorT.TYPE;

      } else if (c().isIncomplete(pt1)) {
        runtime.error("dereferencing pointer to incomplete type", n);
        return ErrorT.TYPE;

      } else if (cond2) {
        Reference ref;
        if (base.hasShape() && index.hasConstant()) {
          try {
            ref = base.getShape().indirect(base).
              add(index.getConstant().bigIntValue());
          } catch (IllegalStateException x) {
            ref = new StaticReference(ptr1);
          }
        } else {
          ref = new DynamicReference(ptr1);
        }
        return c().qualify(ptr1, pt1).annotate().shape(ref);

      } else {
        return ErrorT.TYPE;
      }

    } else {
      runtime.error("subscripted value is neither array nor pointer", n);
      return ErrorT.TYPE;
    }
  }

  /** Visit the specified direct component selection. */
  public Type visitDirectComponentSelection(GNode n) {
    // C99 6.5.2.3
    final Node   n1 = n.getNode(0);
    final String id = n.getString(1);
    final Type   t1 = (Type)dispatch(n1);

    final Type result = processSelection(n1, t1, id, false);

    mark(n, result);
    return result;
  }

  /** Visit the specified indirect component selection. */
  public Type visitIndirectComponentSelection(GNode n) {
    // C99 6.5.2.3
    final Node   n1 = n.getNode(0);
    final String id = n.getString(1);
    final Type   t1 = (Type)dispatch(n1);

    final Type result = processSelection(n1, t1, id, true);

    mark(n, result);
    return result;
  }

  /**
   * Process a component selection.  This method extracts the member
   * type for the member with the specified name from the specified
   * struct or union type.
   *
   * @param node The node.
   * @param type The type.
   * @param name The name of the member.
   * @param indirect The flag for whether the component selection is
   *   indirect.
   * @return The corresponding member type or an error type in case of
   *   a malformed type or field name.
   */
  protected Type processSelection(Node node, Type type, String name,
                                  boolean indirect) {
    if (type.hasError()) return ErrorT.TYPE;

    // First, resolve any indirection.
    Type base;
    if (indirect) {
      final Type resolved = c().pointerize(type);

      if (resolved.isPointer()) {
        base = resolved.toPointer().getType();

        if (c().isIncomplete(base)) {
          runtime.error("dereferencing pointer to incomplete type", node);
          return ErrorT.TYPE;
        }

      } else {
        runtime.error("invalid type argument of '->'", node);
        return ErrorT.TYPE;
      }
    } else {
      base = type;
    }

    // Second, extract the member type.
    if (base.hasError()) {
      return ErrorT.TYPE;

    } else if (base.hasStructOrUnion()) {
      final Tagged tag    = base.toTagged();
      Type         result = tag.lookup(name);

      if (result.isError()) {
        runtime.error("'" + (tag.isStruct() ? "struct " : "union ") +
                      tag.getName() + "' has no member named '" + name + "'",
                      node);
        return ErrorT.TYPE;

      } else {
        result = c().qualify(result, base);

        if (indirect || type.hasShape()) {
          Reference ref;
          if (type.hasShape()) {
            ref = indirect ? type.getShape().indirect(type) : type.getShape();
          } else if (type.hasConstant()) {
            // Note that arrays and functions never have a value.  So,
            // just using the reference value is safe.
            ref = type.getConstant().refValue();
          } else {
            ref = new DynamicReference(base);
          }

          result = result.annotate().shape(new FieldReference(ref, name));
        }

        return result;
      }

    } else {
      runtime.error("request for member '" + name +
                    "' in something not a struct or union", node);
      return ErrorT.TYPE;
    }
  }

  /** Visit the specified function call. */
  public Type visitFunctionCall(GNode n) {
    final Node n1   = n.getNode(0);
    final Node n2   = n.getNode(1);

    Type t1;
    if (GNode.cast(n1).hasName("PrimaryIdentifier")) {
      final String name = GNode.cast(n1).getString(0);

      // Support __xtc_trace() diagnostic.
      if ("__xtc_trace".equals(name)) {
        @SuppressWarnings("unchecked")
        final List<Type> args = (List<Type>)dispatch(n2);

        boolean first  = true;
        Type    result = null;

        for (Type t : args) {
          if (first) {
            first  = false;
            result = t;
          }

          runtime.console().loc(n).p(": ");
          t.trace(runtime);
        }

        if (null == result) result = VoidT.TYPE;
        mark(n, result);
        return result;
      }

      // Back to our regularly scheduled programming...
      t1 = (Type)table.lookup(name);
      if (null == t1) {

        if (pedantic) {
          runtime.error("'" + name + "' undeclared", n1);
          t1 = ErrorT.TYPE;

        } else {
          // Implicitly declare this identifier as a function.  Since
          // the lookup failed, the identifier is not declared in the
          // current scope nor in the global scope.
          t1 = new FunctionT(NumberT.INT, new ArrayList<Type>(0), false).
            attribute(Constants.ATT_STYLE_OLD).
            attribute(Constants.ATT_IMPLICIT).
            annotate().attribute(Constants.ATT_STORAGE_EXTERN);

          // Always enter the implicit declaration in the local scope.
          table.current().define(name, t1.shape(true, name).locate(n));

          // Compare to any previous extern declarations.
          final Type extern = lookupExtern(name);
          if (null == extern) {
            // runtime.warning("implicit declaration of function '"+name+"'", n);
            defineExtern(name, t1.shape(true, name).locate(n));

          } else if (! extern.hasAttribute(Constants.ATT_IMPLICIT)) {
            // FIXME: add warning for first implicit declaration.

            // Compose the two types to detect any errors.
            compose(n, name, t1, extern, false);
          }
        }
      }
    } else {
      t1 = (Type)dispatch(n1);
    }

    final Type       r1   = c().pointerize(t1);
    @SuppressWarnings("unchecked")
    final List<Type> args = (List<Type>)dispatch(n2);

    Type result;
    if (r1.isError()) {
      result = ErrorT.TYPE;

    } else if (r1.isPointer() &&
               r1.toPointer().getType().hasTag(Tag.FUNCTION)) {
      final FunctionT  function   = 
        r1.toPointer().getType().resolve().toFunction();
      final List<Type> parameters = function.getParameters();

      // If the function has a prototype, check the types.
      if (! function.hasAttribute(Constants.ATT_STYLE_OLD)) {
        final int    size1 = parameters.size();
        final int    size2 = (null == args) ? 0 : args.size();
        final int    min   = Math.min(size1, size2);
        final String name  = toFunctionName(n1);

        for (int i=0; i<min; i++) {
          String desc = "passing argument " + (i+1);
          if (null != name) desc = desc + " to '" + name + "'";
          processAssignment(false, desc, n, parameters.get(i), args.get(i));
        }

        if (size1 > size2) {
          if (null == name) {
            runtime.error("too few arguments to function", n);
          } else {
            runtime.error("too few arguments to function '" + name + "'", n);
          }
        } else if ((! function.isVarArgs()) && (size1 < size2)) {
          if (null == name) {
            runtime.error("too many arguments to function", n);
          } else {
            runtime.error("too many arguments to function '" + name + "'", n);
          }
        }
      }

      result = function.getResult();

    } else {
      runtime.error("called " + toDescription(n1) + " is not a function", n);
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified postincrement expression. */
  public Type visitPostincrementExpression(GNode n) {
    // C99 6.5.2.4
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);

    Type result;
    if (ensureScalar(n1, t1) &&
        ensurePointerArithmetic(n, t1) &&
        ensureLValue(n1, t1)) {
      result = t1.resolve();
    } else {
      result = ErrorT.TYPE;
    }
   
    mark(n, result);
    return result;
  }

  /** Visit the specified postdecrement expression. */
  public Type visitPostdecrementExpression(GNode n) {
    // C99 6.5.2.4
    final Node n1 = n.getNode(0);
    final Type t1 = (Type)dispatch(n1);

    Type result;
    if (ensureScalar(n1, t1) &&
        ensurePointerArithmetic(n, t1) &&
        ensureLValue(n1, t1)) {
      result = t1.resolve();
    } else {
      result = ErrorT.TYPE;
    }
   
    mark(n, result);
    return result;
  }

  /** Visit the specified compound literal. */
  public Type visitCompoundLiteral(GNode n) {
    // C99 6.5.2.5
    Type t1 = (Type)dispatch(n.getNode(0));

    // Compound literals are compile-time constant lvalues.
    final Reference ref = new StaticReference("<literal>", t1.resolve());
    t1 = t1.annotate().shape(ref).constant(ref);

    if (isTopLevel) {
      // Top-level compound literals have static storage.
      t1 = t1.attribute(Constants.ATT_STORAGE_STATIC);
    } else {
      // Block-scope compound literals have automatic storage.
      t1 = t1.attribute(Constants.ATT_STORAGE_AUTO);
    }

    // Process the initializer.
    final Type result;

    if (t1.hasStructOrUnion() && c().isIncomplete(t1)) {
      final String kind = t1.hasTag(Tag.STRUCT) ? "struct" : "union";
      if (t1.toTagged().isUnnamed()) {
        runtime.error("unnamed " + kind + " has incomplete type", n);
      } else {
        runtime.error("'" + kind + " " + t1.toTagged().getName() +
                      "' has incomplete type", n);
      }
      result = ErrorT.TYPE;
    } else {
      result = processInitializer(n, null, t1, n.getGeneric(1));
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified primary identifier. */
  public Type visitPrimaryIdentifier(GNode n) {
    Type result = (Type)table.lookup(n.getString(0));
    if (null == result) {
      runtime.error("'" + n.getString(0) + "' undeclared", n);
      result = ErrorT.TYPE;
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified floating constant. */
  public Type visitFloatingConstant(GNode n) {
    final Type result = c().typeFloat(n.getString(0));

    mark(n, result);
    return result;
  }

  /** Visit the specified integer constant. */
  public Type visitIntegerConstant(GNode n) {
    Type result = c().typeInteger(n.getString(0));

    if (! c().fits(result.getConstant().bigIntValue(), result)) {
      runtime.warning("integer constant is too large for its type");

      // Reconstruct value.
      result = result.resolve().annotate().
        constant(c().mask(result.getConstant().bigIntValue(), result));
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified character constant. */
  public Type visitCharacterConstant(GNode n) {
    Type result = c().typeCharacter(n.getString(0));

    if (! c().fits(result.getConstant().bigIntValue(), result)) {
      runtime.warning("character constant too large for its type", n);

      // Reconstruct value.
      result = result.resolve().annotate().
        constant(c().mask(result.getConstant().bigIntValue(), result));
    }

    mark(n, result);
    return result;
  }

  /** Visit the specified string constant. */
  public Type visitStringConstant(GNode n) {
    // C99 6.4.5

    // Build up the actual string value.
    final StringBuilder buf  = new StringBuilder();
    boolean             wide = false;
    for (Object o : n) {
      String s = Token.cast(o);

      if (s.startsWith("L")) {
        try {
          buf.append(Utilities.unescape(s.substring(2, s.length()-1)));
        } catch (IllegalArgumentException x) {
          runtime.error(x.getMessage(), n);
        }
        wide = true;
      } else {
        try {
          buf.append(Utilities.unescape(s.substring(1, s.length()-1)));
        } catch (IllegalArgumentException x) {
          runtime.error(x.getMessage(), n);
        }
      }
    }
    final String value = buf.toString();

    // Construct the type.  Note that we ignore the terminating null
    // character for the string constant's size because later
    // comparisons with fixed-size arrays do not consider it (C99
    // 6.7.8).
    Type base   = wide ? C.WCHAR : NumberT.CHAR;
    if (Limits.IS_STRING_CONST) {
      base = base.annotate().attribute(Constants.ATT_CONSTANT);
    }

    Type result = new ArrayT(base, value.length());
    result      = result.annotate().shape(new StringReference(value, result));
    result      = result.constant(result.getShape());

    // Done.
    mark(n, result);
    return result;
  }

  /** Visit the specified statement as expression. */
  public Type visitStatementAsExpression(GNode n) {
    isStmtAsExpr = true;

    final Type result = (Type)dispatch(n.getNode(0));

    mark(n, result);
    return result;
  }

  /** Visit the specified variable argument access. */
  public Type visitVariableArgumentAccess(GNode n) {
    final Type list = (Type)dispatch(n.getNode(0));

    if (! c().equal(InternalT.VA_LIST, list.resolve())) {
      runtime.error("first argument to 'va_arg' not of type 'va_list'");
    }

    final Type result = (Type)dispatch(n.getNode(1));

    mark(n, result);
    return result;
  }

  /** Visit the specified type name. */
  public Type visitTypeName(GNode n) {
    final Specifiers spec = newSpecifiers(n.getGeneric(0), false);

    Type result = getDeclaredType(spec.getBaseType(), n.getGeneric(1));
    result      = spec.annotateFull(result);

    mark(n, result);
    return result;
  }

  /** Visit the specified generic node. */
  public void visit(Node n) {
    final boolean scope = hasScope;
    hasScope            = true;
    for (Object o : n) {
      if (o instanceof Node) dispatch((Node)o);
    }
    hasScope = scope;
  }

  // ========================================================================

  /**
   * Check that the specified type is well-formed.  This method checks
   * that the specified type is not an array of functions, not a
   * function returning an array or a function, and not a pointer to
   * either of the first two types.
   *
   * @param node The declaring node.
   * @param name The optional name.
   * @param type The type.
   * @return <code>true</code> if the type is well-formed.
   */
  public boolean checkType(GNode node, String name, Type type) {
    // Resolve the type.
    type = type.resolve();

    // Strip any pointers.
    while (type.isPointer()) {
      type = type.toPointer().getType().resolve();
    }

    // Check arrays.
    if (type.isArray()) {
      Type element = type;
      do {
        element = element.toArray().getType().resolve();
      } while (element.isArray());
      if (element.isFunction()) {
        if (null == name) {
          runtime.error("declaration of array of functions", node);
        } else {
          runtime.error("'" + name + "' declared as array of functions",
                        node);
        }
        return false;

      } else {
        // Recursively check the element type.
        return checkType(node, name, element);
      }
    }

    // Check functions.
    if (type.isFunction()) {
      Type result = type.toFunction().getResult().resolve();
      if (result.isArray()) {
        if (null == name) {
          runtime.error("declaration of function returning an array", node);
        } else {
          runtime.error("'" + name + "' declared as function returning " +
                        "an array", node);
        }
        return false;

      } else if (result.isFunction()) {
        if (null == name) {
          runtime.error("declaration of function returning a function", node);
        } else {
          runtime.error("'" + name + "' declared as function returning " +
                        "a function", node);
        }
        return false;

      } else {
        // Recursively check the result type.
        return checkType(node, name, result);
      }
    }

    return true;
  }

  /**
   * Compose the specified type with the type of the previous
   * declaration.  This method composes compatible object and function
   * types with each other, while also reporting any errors.
   *
   * @param decl The current declaration's node.
   * @param name The identifier name.
   * @param type The current declaration's type.
   * @param previous The previous declaration's type.
   * @param isFuncDef The flag for whether the composition is for a
   *   function definition.
   * @return The composite type or {@link ErrorT#TYPE} if the two
   *   types are not compatible.
   */
  public Type compose(GNode decl, String name, Type type, Type previous,
                      boolean isFuncDef) {
    if (previous.isAlias() ||
        type.resolve().isFunction() != previous.resolve().isFunction()) {
      runtime.error("'" + name + "' redeclared as different kind of symbol",
                    decl);
      reportPrevious(name, previous);
      return ErrorT.TYPE;
    }

    // For an invocation of C.compose(t1, t2), t1's attributes
    // dominate.  Therefore, we give precedence to types not having
    // the extern attribute.
    Type composite;
    if (previous.hasAttribute(Constants.ATT_STORAGE_EXTERN) ||
        (! type.hasAttribute(Constants.ATT_STORAGE_EXTERN)) ||
        isFuncDef) {
      composite = c().compose(type, previous, pedantic);
    } else {
      composite = c().compose(previous, type, pedantic);
    }

    if (composite.isError()) {
      if (previous.hasAttribute(Constants.ATT_BUILTIN) &&
          previous.resolve().isFunction()) {
        runtime.error("conflicting types for built-in function '" + name + "'",
                      decl);
      } else {
        runtime.error("conflicting types for '" + name + "'", decl);
        reportPrevious(name, previous);
      }
      return ErrorT.TYPE;

    } else if (! c().hasSameQualifiers(type, previous)) {
      runtime.error("conflicting type qualifiers for '" + name + "'", decl);
      reportPrevious(name, previous);
      return ErrorT.TYPE;
    }

    return composite;
  }

  /**
   * Get the first declaration specifier with the specified name.
   *
   * @param name The name.
   * @param specifiers The specifiers.
   * @return The corresponding declaration specifier or
   *   <code>null</code> if no such specifier exists.
   */
  public static GNode getSpecifier(String name, GNode specifiers) {
    for (Object o : specifiers) {
      final GNode specifier = GNode.cast(o);
      if (specifier.hasName(name)) return specifier;
    }
    return null;
  }

  /**
   * Create a new sequence of specifiers.  This factory method should
   * be used instead of allocating an instance of {@link Specifiers}
   * directly, so that the processing of declaration specifiers can be
   * customized by subclasses.
   *
   * @param specifiers The node holding the declaration specifiers
   *   (which may be <code>null</code>).
   * @param refIsDecl The flag for whether a struct/union reference
   *   also is a struct/union declaration.
   * @return The sequence of specifiers.
   */
  public Specifiers newSpecifiers(GNode specifiers, boolean refIsDecl) {
    return new Specifiers(specifiers, refIsDecl);
  }

  /**
   * Convert the specified GCC attribute specifier or GCC attribute
   * specifier list to an xtc attribute list.  If the specified node
   * is <code>null</code>, this method returns an empty list.
   * Otherwise, it returns a newly allocated, unsealed list.
   *
   * @param spec The GCC attribute specifier (list).
   * @return The corresponding xtc attributes.
   */
  public List<Attribute> toAttributeList(GNode spec) {
    if (null == spec) {
      return Collections.emptyList();
    } else {
      return toAttributeList(spec, new ArrayList<Attribute>());
    }
  }

  /** The actual implementation of {@link #toAttributeList(GNode)}. */
  private List<Attribute> toAttributeList(GNode spec,
                                          List<Attribute> result) {
    if (spec.hasName("AttributeSpecifier")) {
      if (null != spec.get(0)) {
        for (Object o : spec.getGeneric(0)) {
          final GNode  entry = GNode.cast(o);
          final String name  = toAttributeName(entry.getString(0));
          final Object value = toAttributeValue(entry.getGeneric(1));

          // Check values of known attributes.
          boolean seenError = false;

          if ("packed".equals(name)) { // -------------------------------------
            if (null != value) {
              runtime.error("wrong number of arguments specified for 'packed'" +
                            " attribute", entry);
              seenError = true;
            }

          } else if ("aligned".equals(name)) { // -----------------------------
            if (null == value) {
              // Ignore.
            } else if (value instanceof List) {
              runtime.error("wrong number of arguments specified for 'aligned'" +
                            " attribute", entry);
              seenError = true;
            } else if (value instanceof Node) {
              runtime.error("requested alignment is not a constant", entry);
              seenError = true;
            } else if (! (value instanceof BigInteger)) {
              runtime.error("requested alignment is not an integer constant",
                            entry);
              seenError = true;
            } else {
              BigInteger i = (BigInteger)value;

              if (1 != i.signum() || 1 != i.bitCount()) {
                runtime.error("requested alignment is not a power of 2", entry);
                seenError = true;
              } else if (Limits.INT_MAX.compareTo(i) < 0) {
                runtime.error("requested alignment is too large", entry);
                seenError = true;
              }
            }
          }

          // Create attribute.
          if (! seenError) {
            result.
              add(new Attribute(Constants.NAME_GCC, new Attribute(name, value)));
          }
        }
      }
      return result;
      
    } else if (spec.hasName("AttributeSpecifierList")) {
      for (Object o : spec) toAttributeList(GNode.cast(o), result);
      return result;

    } else {
      throw new AssertionError("Not an attribute specifier (list): " + spec);
    }
  }

  /**
   * Convert the specified string to an attribute name.
   *
   * @param s The string.
   * @return The corresponding name.
   */
  public String toAttributeName(String s) {
    if (s.startsWith("__")) s = s.substring(2);
    if (s.endsWith("__")) s = s.substring(0, s.length()-2);
    return s;
  }

  /**
   * Convert the specified node to an attribute value.  This method
   * converts a node representing a GCC attribute's value to the
   * actual attribute's value:<ul>
   *
   * <li>If the node is <code>null</code> or an empty expression list,
   * this method returns <code>null</code>.</li>
   *
   * <li>If the node is an expression list with one element, it
   * returns the result of recursively processing that element.</li>
   *
   * <li>If the node is an expression list with more than one element,
   * it recursively processes each element, returning a new Java
   * collections framework list.</li>
   *
   * <li>If the node is a primary identifier, it returns the
   * corresponding symbol (without checking that the symbol is
   * defined).</li>
   *
   * <li>If the node is a constant expression, it returns the
   * corresponding value.</li>
   *
   * <li>Otherwise, it returns the AST node.</li>
   *
   * </ul>
   *
   * @param node The node.
   * @return The corresponding value.
   */
  public Object toAttributeValue(GNode node) {
    if (null == node) return null;

    if (node.hasName("ExpressionList")) {
      if (0 == node.size()) {
        return null;

      } else if (1 == node.size()) {
        return toAttributeValue(node.getGeneric(0));

      } else {
        final List<Object> l = new ArrayList<Object>(node.size());
        for (Object o : node) l.add(toAttributeValue(GNode.cast(o)));
        return l;
      }

    } else if (node.hasName("PrimaryIdentifier")) {
      return node.getString(0);

    } else {
      final Type t = (Type)dispatch(node);

      return t.hasConstant() ? t.getConstant().getValue() : node;
    }
  }

  /**
   * Get the parameter types for the specified parameter declaration.
   * As a side effect, this method reports any errors in a parameter's
   * declaration specifiers, any void parameters (besides a single
   * void specifier), any multiple parameters in old-style
   * declarations, and any parameter redefinitions in new-style
   * declarations.
   *
   * @param parameters The parameters, which may be <code>null</code>.
   * @return The corresponding function type with the argument types
   *   and variable flag filled in.
   */
  public FunctionT getParameterTypes(GNode parameters) {
    if (null == parameters) {
      // No parameters.
      final FunctionT function = 
        new FunctionT(null, new ArrayList<Type>(0), false);
      function.addAttribute(Constants.ATT_STYLE_OLD);
      return function;

    } else if (parameters.hasName("ParameterTypeList")) {
      // Enter a temporary scope so that variable length arrays can
      // reference previously declared parameters.
      table.enter(TMP_SCOPE);

      // A new-style parameter type list.
      final boolean    variable;
      final List<Type> types;

      if (isVoidParameterTypeList(parameters)) {
        variable   = false;
        types      = new ArrayList<Type>(0);

        // Get the type.
        final GNode      param = parameters.getGeneric(0).getGeneric(0);
        final Specifiers spec  = newSpecifiers(param.getGeneric(0), false);
        final Type       type  = spec.annotateFull(spec.getBaseType());

        // Check that the void specifier does not have a storage
        // class, qualifier, or function specifier.
        if (type.hasAttribute(Constants.NAME_STORAGE)) {
          runtime.error("'void' as only parameter may not have storage class",
                        parameters);
        }
        if (c().hasQualifiers(type)) {
          runtime.error("'void' as only parameter may not be qualified",
                        parameters);

        }
        if (type.hasAttribute(Constants.ATT_INLINE)) {
          runtime.error("'void' as only parameter may not be declared 'inline'",
                        parameters);
        }

      } else {
        variable   = (null != parameters.get(1));
        parameters = parameters.getGeneric(0);
        types      = new ArrayList<Type>(parameters.size());
        for (Object o : parameters) {
          final GNode      param = GNode.cast(o);
          final GNode      decl  = param.getGeneric(1);
          final GNode      ident = getDeclaredId(decl);
          final String     name  = (null != ident) ? ident.getString(0) : null;
          final Specifiers spec  = newSpecifiers(param.getGeneric(0), false);
          Type             type  =
            getDeclaredType(true, spec.getBaseType(), decl);

          // Check that the type is well-formed.
          checkType(param, name, type);

          // Pointerize array and function parameter types.
          switch (type.tag()) {
          case ARRAY:
            type = c().
              qualify(new PointerT(type.resolve().toArray().getType()), type);
            break;
          case FUNCTION:
            type = c().qualify(new PointerT(type.resolve()), type);
            break;
          }
          
          // Annotate the type.
          if (null == name) {
            type = type.annotate().shape(false, "<param>");
          } else {
            type = VariableT.newParam(type, name).shape(false, name);
          }
          type = spec.annotateFull(type).
            attribute(toAttributeList(param.getGeneric(2)));
          
          // Check that any storage class specifier is register.
          if ((type.hasAttribute(Constants.NAME_STORAGE) &&
               (! type.hasAttribute(Constants.ATT_STORAGE_REGISTER))) ||
              type.hasAttribute(Constants.ATT_THREAD_LOCAL)) {
            if (null == name) {
              runtime.error("storage class specified for parameter", param);
            } else {
              runtime.error("storage class specified for parameter '"+name+"'",
                            param);
            }
          }
          
          // Check that there is no function specifier.
          if (spec.contains(Constants.ATT_INLINE)) {
            if (null == name) {
              runtime.error("parameter declared 'inline'", param);
            } else {
              runtime.error("parameter '"+name+"' declared 'inline'", param);
            }
          }
          
          if (null == name) {
            types.add(type);
          } else if (table.current().isDefinedLocally(name)) {
            runtime.error("redefinition of parameter '" + name + "'", param);
            types.add(VariableT.newParam(ErrorT.TYPE, name));
          } else {
            table.current().define(name, type);
            types.add(type);
          }
        }
      }

      // Exit the temporary scope and delete it again.
      table.exit();
      table.delete(TMP_SCOPE);

      // Done.
      final FunctionT function = new FunctionT(null, types, variable);
      function.addAttribute(Constants.ATT_STYLE_NEW);
      return function;

    } else if (parameters.hasName("IdentifierList")) {
      // An old-style identifier list.
      Set<String> names = new HashSet<String>();
      List<Type>  types = new ArrayList<Type>(parameters.size());
      for (Object o : parameters) {
        final String name  = Token.cast(o);
        
        if (names.contains(name)) {
          runtime.error("multiple parameters named '" + name + "'", parameters);
          types.add(VariableT.newParam(ErrorT.TYPE, name));
        } else {
          names.add(name);
          types.add(VariableT.newParam(C.IMPLICIT, name).shape(false, name));
        }
      }

      // Done.
      final FunctionT function = new FunctionT(null, types, false);
      function.addAttribute(Constants.ATT_STYLE_OLD);
      return function;

    } else {
      throw new
        AssertionError("Unrecognized parameter representation: " + parameters);
    }
  }

  /**
   * Get the declared type.  The type is not a parameter type.
   *
   * @param base The base type.
   * @param declarator The declarator, which may be abstract or
   *   <code>null</code>.
   * @return The declared type.
   */
  public Type getDeclaredType(Type base, GNode declarator) {
    return getDeclaredType(false, base, declarator);
  }

  /**
   * Get the declared type.  In addition to determining the declared
   * type, this method checks that any static storage class specifier
   * or type qualifiers only appear in an array declarator if the
   * declarator is part of a parameter declaration.
   *
   * @param isParam The flag for whether the type is a parameter type.
   * @param base The base type.
   * @param declarator The declarator, which may be abstract or
   *   <code>null</code>.
   * @return The declared type.
   */
  @SuppressWarnings("unused")
  public Type getDeclaredType(final boolean isParam, final Type base,
                              final GNode declarator) {
    return (null == declarator)? base : (Type)new Visitor() {
        private Type            result = base;
        private List<Attribute> list1  = null;
        private List<Attribute> list2  = null;

        private void annotate() {
          if ((null != list1) && (0 < list1.size())) {
            result = result.annotate().attribute(list1);
            list1  = null;
          }
          if ((null != list2) && (0 < list2.size())) {
            result = result.annotate().attribute(list2);
            list2  = null;
          }
        }

        private void processPointer(GNode pointer) {
          while (null != pointer) {
            final Specifiers spec = newSpecifiers(pointer.getGeneric(0), false);
            if (spec.hasBaseAttributes()) {
              result = spec.annotateBase(new PointerT(result).annotate());
            } else {
              result = new PointerT(result);
            }
            pointer = pointer.getGeneric(1);
          }
        }

        private Type processArray(Type element, GNode expr, GNode decl) {
          // Process the size expression.
          if ((null != expr) && expr.hasName("VariableLength")) {
            // [*] denotes an incomplete variable length array.  We
            // simply return an incomplete array type.
            if (! isParam) {
              runtime.error("'[*]' in non-parameter array declarator", decl);
            }
            return new ArrayT(element, true);

          } else if (null == expr) {
            // An incomplete array.
            return new ArrayT(element);

          } else {
            final Type size = processExpression(expr);

            if (size.hasError()) {
              return new ArrayT(element);

            } else if (! c().isIntegral(size)) {
              final GNode id = getDeclaredId(decl);
              if (null == id) {
                runtime.error("size of array has non-integer type",
                              GNode.cast(expr));
              } else {
                runtime.error("size of array '" + id.getString(0) +
                              "' has non-integer type", GNode.cast(expr));
              }
              return new ArrayT(element);

            } else if (size.hasConstant()) {
              BigInteger value;
              try {
                value = size.getConstant().bigIntValue();
              } catch (IllegalStateException x) {
                final GNode id = getDeclaredId(decl);
                if (null == id) {
                  runtime.warning("can't compute size of array",
                                  GNode.cast(expr));
                } else {
                  runtime.warning("can't compute size of array '" +
                                  id.getString(0) + "'", GNode.cast(expr));
                }
                value = BigInteger.ONE;
              }
                
              // Test: value == 0
              if (value.compareTo(BigInteger.ZERO) == 0) {
                if (pedantic) {
                  final GNode id = getDeclaredId(decl);
                  if (null == id) {
                    runtime.error("ISO C forbids zero-size array",
                                  GNode.cast(expr));
                  } else {
                    runtime.error("ISO C forbids zero-size array '" +
                                  id.getString(0) + "'", GNode.cast(expr));
                  }
                }
                return new ArrayT(element, 0);

              // Test: value < 0
              } else if (value.compareTo(BigInteger.ZERO) < 0) {
                final GNode id = getDeclaredId(decl);
                if (null == id) {
                  runtime.error("size of array is negative", GNode.cast(expr));
                } else {
                  runtime.error("size of array '" + id.getString(0) +
                                "' is negative", GNode.cast(expr));
                }
                return new ArrayT(element, 0);
                
                // Test: value > ARRAY_MAX
              } else if (value.compareTo(Limits.ARRAY_MAX) > 0) {
                final GNode id = getDeclaredId(decl);
                if (null == id) {
                  runtime.error("size of array is too large", GNode.cast(expr));
                } else {
                  runtime.error("size of array '" + id.getString(0) +
                                "' is too large", GNode.cast(expr));
                }
                return new ArrayT(element, 0);
                
              } else {
                return new ArrayT(element, value.longValue());
              }

            } else {
              return new ArrayT(element, true);
            }
          }
        }

        public Object visitAttributedDeclarator(GNode n) {
          if (null != n.get(0)) list1 = toAttributeList(n.getGeneric(0));
          if (null != n.get(2)) list2 = toAttributeList(n.getGeneric(2));

          return dispatch(n.getGeneric(1));
        }

        public Object visitPointerDeclarator(GNode n) {
          processPointer(n.getGeneric(0));
          annotate();
          return dispatch(n.getGeneric(1));
        }

        public Object visitArrayDeclarator(GNode n) {
          // Process the array size.
          result = processArray(result, n.getGeneric(2), n);

          // Process the array qualifier list.
          if (isParam) {
            if (n.getGeneric(0).hasName("SimpleDeclarator")) {
              final Specifiers spec = newSpecifiers(n.getGeneric(1), false);
              if (spec.hasBaseAttributes()) {
                result = spec.annotateBase(result.annotate());
              }
              if (spec.hasInline() || (null != spec.getStorageClass())) {
                result = spec.annotateFull(result.annotate());
              }
            } else if (0 < n.getGeneric(1).size()) {
              runtime.error("static or type qualifiers not in outermost " +
                            "array type derivation", n);
            }

          } else if (0 < n.getGeneric(1).size()) {
            runtime.error("static or type qualifiers in non-parameter " +
                          "array declarator", n);
          }

          // Process any annotations.
          annotate();

          // Done.
          return dispatch(n.getGeneric(0));
        }

        public Object visitFunctionDeclarator(GNode n) {
          final FunctionT function = getParameterTypes(n.getGeneric(1));
          function.setResult(result);
          result = function;
          annotate();
          return dispatch(n.getGeneric(0));
        }

        public Object visitSimpleDeclarator(GNode n) {
          annotate();
          return result;
        }

        public Object visitAttributedAbstractDeclarator(GNode n) {
          if (null != n.get(0)) list1 = toAttributeList(n.getGeneric(0));

          return dispatch(n.getGeneric(1));
        }

        public Object visitAbstractDeclarator(GNode n) {
          processPointer(n.getGeneric(0));
          annotate();
          return (null == n.get(1))? result : dispatch(n.getGeneric(1));
        }

        public Object visitDirectAbstractDeclarator(GNode n) {
          if (3 == n.size()) {
            if ("[".equals(n.getString(1))) {
              result = processArray(result, n.getGeneric(2), n);

            } else {
              final FunctionT function = getParameterTypes(n.getGeneric(2));
              function.setResult(result);
              result = function;
            }

            if (null == n.get(0)) {
              annotate();
              return result;
            } else {
              annotate();
              return dispatch(n.getGeneric(0));
            }

          } else if (null == n.get(0)) {
            annotate();
            return result;

          } else {
            annotate();
            return dispatch(n.getGeneric(0));
          }
        }

      }.dispatch(declarator);
  }

  /**
   * Get the declared identifier from the specified declarator.
   *
   * @param declarator The declarator, which may be abstract or
   *   <code>null</code>.
   * @return The simple declarator node representing the declared
   *   identifier or <code>null</code> if the specified declarator is
   *   abstract or <code>null</code>.
   */
  public static GNode getDeclaredId(GNode declarator) {
    return GNode.cast(getDeclaredIdVisitor.dispatch(declarator));
  }

  /** The actual implementation of {@link #getDeclaredId(GNode)}. */
  @SuppressWarnings("unused")
  private static final Visitor getDeclaredIdVisitor = new Visitor() {
      public Object visitBitField(GNode n) {
        return dispatch(n.getGeneric(1));
      }
      public Object visitAttributedDeclarator(GNode n) {
        return dispatch(n.getGeneric(1));
      }
      public Object visitPointerDeclarator(GNode n) {
        return dispatch(n.getGeneric(1));
      }
      public Object visitFunctionDeclarator(GNode n) {
        return dispatch(n.getGeneric(0));
      }
      public Object visitArrayDeclarator(GNode n) {
        return dispatch(n.getGeneric(0));
      }
      public Object visitSimpleDeclarator(GNode n) {
        return n;
      }
      public Object visitAttributedAbstractDeclarator(GNode n) {
        return null;
      }
      public Object visitAbstractDeclarator(GNode n) {
        return null;
      }
      public Object visitDirectAbstractDeclarator(GNode n) {
        return null;
      }
    };

  /**
   * Get the innermost function declarator from the specified
   * declarator.  The innermost function declarator's parameters are
   * the parameters for a function declaration or definition.
   *
   * @param declarator The declarator.
   * @return The innermost function declarator or <code>null</code> if
   *   the declarator does not contains a function declarator.
   */
  public static GNode getFunctionDeclarator(GNode declarator) {
    return GNode.cast(getFunctionDeclaratorVisitor.dispatch(declarator));
  }

  /** The actual implementation of {@link #getFunctionDeclarator}. */
  @SuppressWarnings("unused")
  private static final Visitor getFunctionDeclaratorVisitor = new Visitor() {
      public Object visitAttributedDeclarator(GNode n) {
        return dispatch(n.getGeneric(1));
      }
      public Object visitPointerDeclarator(GNode n) {
        return dispatch(n.getGeneric(1));
      }
      public Object visitFunctionDeclarator(GNode n) {
        Object result = dispatch(n.getGeneric(0));
        return (null == result)? n : result;
      }
      public Object visitArrayDeclarator(GNode n) {
        return dispatch(n.getGeneric(0));
      }
      public Object visitSimpleDeclarator(GNode n) {
        return null;
      }
    };

  /**
   * Determine whether the specified parameter type list represents a
   * function taking no arguments.  This method checks whether the
   * parameter type list contains a single parameter without a
   * declarator, whose specifiers either contains a void type
   * specifier or a typedef name aliasing void.  Though the parameter
   * type list may still be malformed, e.g., contain a qualifier,
   * storage class, or another type specifier.
   *
   * @param parameters The parameter type list.
   * @return <code>true</code> if the corresponding function takes no
   *   arguments.
   */
  public boolean isVoidParameterTypeList(GNode parameters) {
    assert parameters.hasName("ParameterTypeList");

    if (null != parameters.get(1)) return false;
    parameters = parameters.getGeneric(0);
    if (1 != parameters.size()) return false;
    final GNode parameter = parameters.getGeneric(0);
    if (null != parameter.get(1)) return false;
    final GNode specifiers = parameter.getGeneric(0);

    for (Object o : specifiers) {
      final GNode spec = GNode.cast(o);

      if (spec.hasName("VoidTypeSpecifier")) {
        return true;

      } else if (spec.hasName("TypedefName")) {
        final Type type = (Type)table.current().lookup(spec.getString(0));

        if ((null != type) && type.isAlias() && type.resolve().isVoid()) {
          return true;
        }
      }
    }
    return false;
  }

  /**
   * Determine whether the specified left-hand type can be initialized
   * from the specified right-hand type.
   *
   * @param t1 The left-hand type.
   * @param t2 The right-hand type.
   * @return <code>true</code> if the left-hand type can be
   *   initialized by the right-hand type.
   */
  protected boolean isInitializable(Type t1, Type t2) {
    if (t1.hasError() || t2.hasError()) return true;

    final Type r1     = t1.resolve();
    final Type r2     = c().pointerize(t2);

    switch (r1.tag()) {
    case BOOLEAN:
    case INTEGER:
    case FLOAT: {
      if (r1.isBoolean()) {
        // Booleans can be assigned from scalar operands.
        return c().isScalar(r2);
      } else {
        // All other arithmetic types can only be assigned from
        // arithmetic types.  GCC also allows assignments from
        // pointers.
        return c().isArithmetic(r2) || (r2.isPointer() && ! pedantic);
      }
    }

    case STRUCT:
    case UNION: {
      // A struct or union can only be assigned from another struct or
      // union of compatible type.
      return c().equal(r1, r2);
    }

    case ARRAY: {
      // An array can only be assigned in an initializer and only if
      // the left-hand type is a (wide) C string and the right-hand
      // type is a matching C string constant.
      return (t2.hasConstant() &&
              ((c().isString(r1) && c().isString(t2)) ||
               (c().isWideString(r1) && c().isWideString(t2))));
    }

    case POINTER: {
      if (r2.isPointer()) {
        final Type pt1  = r1.toPointer().getType(); // PointedTo, PTResolved
        final Type pt2  = r2.toPointer().getType();

        final Type ptr1 = pt1.resolve();
        final Type ptr2 = pt2.resolve();

        if (c().hasQualifiers(pt1, pt2) &&
            (c().equal(ptr1, ptr2) || ptr1.isVoid() || ptr2.isVoid())) {
          return true;
        } else {
          // GCC extension.
          return ! pedantic;
        }

      } else if (t2.hasConstant() && t2.getConstant().isNull()) {
        return true;

      } else if (c().isIntegral(t2)) {
        // GCC extension.
        return ! pedantic;

      } else {
        return false;
      }
    }

    default:
      return (r1.isInternal() && r2.isInternal() &&
              r1.toInternal().getName().equals(r2.toInternal().getName()));
    }
  }

  /**
   * Process the assignment.  This method determines the resulting
   * type when assigning a value of the specified right-hand type to
   * an object with the specified left-hand type.  It does not check
   * that the left-hand side represents a modifiable lvalue.
   *
   * @param init The flag for whether the assignment is in an
   *   initializer.
   * @param op The name of the operation.
   * @param n The node.
   * @param t1 The left-hand type.
   * @param t2 The right-hand type.
   * @return The resulting type.
   */
  protected Type processAssignment(boolean init, String op, Node n,
                                   Type t1, Type t2) {
    if (t1.hasError() || t2.hasError()) return ErrorT.TYPE;

    final Type r1 = t1.resolve();
    final Type r2 = c().pointerize(t2);
    Type result   = null;

    if (r2.isVoid()) {
      runtime.error("void value not ignored as it ought to be", n);
      return ErrorT.TYPE;
    }

    switch (r1.tag()) {
    case BOOLEAN: {
      // Booleans can be assigned from scalar operands.
      if (c().isScalar(r2)) {
        result = r1;
      }
    } break;

    case INTEGER: {
      // Integers can be assigned from scalar operands, but call for a
      // warning then the operand is a pointer.
      if (c().isArithmetic(r2)) {
        result = r1;
      } else if (r2.isPointer()) {
        if (pedantic) {
          runtime.error(op + " makes integer from pointer without a cast", n);
          result = ErrorT.TYPE;
        } else {
          // GCC extension.
          runtime.warning(op+" makes integer from pointer without a cast", n);
          result = r1;
        }
      }
    } break;

    case FLOAT: {
      // Floats can be assigned from other arithmetic types.
      if (c().isArithmetic(r2)) {
        result = r1;
      }
    } break;

    case STRUCT:
    case UNION: {
      // A struct or union can only be assigned from another struct or
      // union of compatible type.
      if (c().equal(r1, r2)) {
        result = r1;
      }
    } break;

    case ARRAY: {
      // An array can only be assigned in an initializer and only if
      // the left-hand type is a (wide) C string and the right-hand
      // type is a matching C string constant.
      if (init) {
        if (c().isString(r1) && t2.hasConstant()) {
          if (c().isString(t2)) {
            result = r1;
          } else if (c().isWideString(t2)) {
            runtime.error("char-array initialized from wide string", n);
            result = ErrorT.TYPE;
          }

        } else if (c().isWideString(r1) && t2.hasConstant()) {
          if (c().isString(t2)) {
            runtime.error("wchar_t-array initialized from non-wide string", n);
            result = ErrorT.TYPE;
          } else if (c().isWideString(t2)) {
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

        if (c().equal(ptr1, ptr2) || ptr1.isVoid() || ptr2.isVoid()) {
          if (c().hasQualifiers(pt1, pt2) || c().isStringLiteral(t2)) {
            result = r1;

          } else if (pedantic) {
            runtime.error(op + " discards qualifiers from pointer target " +
                          "type", n);
            result = ErrorT.TYPE;

          } else {
            runtime.warning(op + " discards qualifiers from pointer target " +
                            "type", n);
            result = r1;
          }

        } else if (ptr1.isNumber() && ptr2.isNumber() &&
                   NumberT.equalIgnoringSign(ptr1.toNumber().getKind(),
                                             ptr2.toNumber().getKind())) {
          // Note: We don't need to consider booleans here because all
          // booleans are unsigned.
          if (pedantic) {
            runtime.error("pointer targets in "+op+" differ in signedness",n);
            result = ErrorT.TYPE;
          } else {
            // GCC extension.
            runtime.warning("pointer targets in "+op+" differ in signedness",n);
            result = r1;
          }

        } else if (pedantic) {
          runtime.error("incompatible pointer types in " + op, n);
          result = ErrorT.TYPE;

        } else {
          // GCC extension.
          runtime.warning("incompatible pointer types in " + op, n);
          result = r1;
        }

      } else if (t2.hasConstant() && t2.getConstant().isNull()) {
        result = r1;

      } else if (c().isIntegral(t2)) {
        if (pedantic) {
          runtime.error(op + " makes pointer from integer without a cast", n);
          result = ErrorT.TYPE;
        } else {
          // GCC extension.
          runtime.warning(op + " makes pointer from integer without a cast", n);
          result = r1;
        }
      }
    } break;

    default:
      if (r1.isInternal() && r2.isInternal() &&
          r1.toInternal().getName().equals(r2.toInternal().getName())) {
      result = r1;
      }
    }

    // Patch in generic error type and message.
    if (null == result) {
      runtime.error("incompatible types in " + op, n);
      result = ErrorT.TYPE;
    }

    // Done.
    return result;
  }

  /**
   * Mark the specified node with the specified type.
   *
   * @param node The node.
   * @param type The type.
   */
  public void mark(Node node, Type type) {
    if (runtime.test("optionMarkAST")) {
      type.mark(node);
    }
  }

  /**
   * Ensure that the specified node with the specified type represents
   * a modifiable lvalue.
   *
   * @param n The node.
   * @param t The type.
   * @return <code>true</code> if the specified node represents a
   *   modifiable lvalue.
   */
  public boolean ensureLValue(Node n, Type t) {
    if (t.hasError()) {
      return false;
    } else if (! t.hasShape()) {
      runtime.error("invalid operand where lvalue required", n);
      return false;
    } else if (c().isIncomplete(t)) {
      runtime.error("assignment of incomplete " + toDescription(n), n);
      return false;
    } else if (! c().isModifiable(t)) {
      runtime.error("assignment of read-only " + toDescription(n), n);
      return false;
    } else {
      return true;
    }
  }

  /**
   * Ensure that the specified node with the specified type represents
   * a scalar.
   *
   * @param n The node.
   * @param t the type.
   * @return <code>true</code> if the specified node represents a
   *   scalar.
   */
  public boolean ensureScalar(Node n, Type t) {
    if (t.hasError()) {
      return false;
    } else if (! c().isScalar(t)) {
      runtime.error("invalid " + toDescription(n) + " where scalar required", n);
      return false;
    } else {
      return true;
    }
  }

  /**
   * Ensure that the specified node represents valid pointer
   * arithmetic for the specified type.  If the specified type is a
   * pointer, this method ensures that the pointer points to a
   * complete type.  For all other types besides the error type, it
   * returns <code>true</code>.
   *
   * @param n The node.
   * @param t The type.
   * @return <code>true</code> if the specified node represents valid
   *   pointer arithmetic.
   */
  public boolean ensurePointerArithmetic(Node n, Type t) {
    if (t.hasError()) {
      return false;

    } else if (t.resolve().isPointer()) {
      final Type pt = t.resolve().toPointer().getType();

      if (! pt.resolve().isVoid() && c().isIncomplete(pt)) {
        runtime.error("arithmetic on pointer to an incomplete type", n);
        return false;
      } else {
        return true;
      }

    } else {
      return true;
    }
  }

  /**
   * Ensure that the specified node with the specified type represents
   * an arithmetic type.
   *
   * @param n The node.
   * @param t The type.
   * @return <code>true</code> if the specified node represents an
   *   arithmetic type.
   */
  public boolean ensureArithmetic(Node n, Type t) {
    if (t.hasError()) {
      return false;
    } else if (! c().isArithmetic(t)) {
      runtime.error("invalid " + toDescription(n) +
                    " where arithmetic value required", n);
      return false;
    } else {
      return true;
    }
  }

  /**
   * Ensure that the specified note with the specified type represents
   * an integer.
   *
   * @param n The node.
   * @param t The type.
   * @return <code>true</code> if the specified node represents an
   *   integer.
   */
  public boolean ensureInteger(Node n, Type t) {
    if (t.hasError()) {
      return false;
    } else if (! c().isIntegral(t)) {
      runtime.error("invalid " + toDescription(n) +
                    " where integer required", n);
      return false;
    } else {
      return true;
    }
  }

  /**
   * Convert the specified node representing an operand to its
   * description.
   *
   * @param n The node.
   * @return The corresponding description.
   */
  public static String toDescription(Node n) {
    final GNode node = GNode.cast(n);

    if (node.hasName("PrimaryIdentifier")) {
      return "variable '" + node.getString(0) + "'";
    } else if (node.hasName("DirectComponentSelection") ||
               node.hasName("IndirectComponentSelection")) {
      return "field '" + node.getString(1) + "'";
    } else if (node.hasName("IndirectionExpression")) {
      final GNode child = node.getGeneric(0);
      if (child.hasName("PrimaryIdentifier")) {
        return "object '*" + child.getString(0) + "'";
      } else {
        return "location";
      }
    } else if (node.hasName("TypeName")) {
      return "type name";
    } else {
      return "operand";
    }
  }

  /**
   * Convert the specified node representing a function to its
   * name.
   *
   * @param n The node.
   * @return The corresponding name or <code>null</code> if the name
   *   cannot be determined.
   */
  public static String toFunctionName(Node n) {
    final GNode node = GNode.cast(n);

    if (node.hasName("PrimaryIdentifier")) {
      return node.getString(0);
    } else if (node.hasName("DirectComponentSelection") ||
               node.hasName("IndirectComponentSelection")) {
      return node.getString(1);
    } else if (node.hasName("indirectionExpressiion")) {
      final GNode child = node.getGeneric(0);
      if (child.hasName("PrimaryIdentifier")) {
        return child.getString(0);
      } else {
        return null;
      }
    } else {
      return null;
    }
  }

  /**
   * Determine whether the specified scope name represents a function
   * or macro scope.
   *
   * @param name The name.
   * @return <code>true</code> if the specified name represents a
   *   function or macro scope.
   */
  public static boolean isFunctionScope(String name) {
    return (SymbolTable.isFunctionScopeName(name) ||
            SymbolTable.isMacroScopeName(name));
  }

  /**
   * Look up the specified name in the scope for extern declarations.
   *
   * @param name The name.
   * @return The corresponding type or <code>null</code> if no such
   *   binding exists.
   */
  public Type lookupExtern(String name) {
    final Scope scope = table.getScope(EXTERN_PATH);
    return null == scope ? null : (Type)scope.lookupLocally(name);
  }

  /**
   * Define the specified name in the scope for extern declarations.
   *
   * @param name The name.
   * @param type The type.
   */
  public void defineExtern(String name, Type type) {
    Scope scope = table.getScope(EXTERN_PATH);

    // If the extern scope does not exist, create it.
    if (null == scope) {
      final Scope current = table.current();
      table.setScope(table.root());
      table.enter(EXTERN_SCOPE);
      scope = table.current();
      table.setScope(current);
    }

    scope.define(name, type);
  }

  /**
   * Report a previous declaration or definition.  If the specified
   * type has a location, this method prints that location as a
   * previous declaration or definition.
   *
   * @param name The name.
   * @param type The type.
   */
  public void reportPrevious(String name, Type type) {
    // If the type has a location, print the error message.
    if (type.hasLocation()) {
      runtime.errConsole().loc(type).
        p(": error: previous ");
      if (type.hasAttribute(Constants.ATT_MACRO) ||
          type.hasAttribute(Constants.ATT_DEFINED)) {
        runtime.errConsole().p("definition");
      } else {
        runtime.errConsole().p("declaration");
      }
      runtime.errConsole().p(" of '").p(name).pln("' was here").flush();
    }
  }

  /**
   * Report a previous declaration or definition of the specified
   * tagged type.  If the specified type has a location, this method
   * prints that location as a previous declaration or definition.
   *
   * @param type The type.
   */
  public void reportPreviousTag(Type type) {
    final Tagged tag = type.toTagged();

    if (type.hasLocation()) {
      runtime.errConsole().loc(type).
        p(": error: previous ");
      if (null != tag.getMembers()) {
        runtime.errConsole().p("definition");
      } else {
        runtime.errConsole().p("declaration");
      }
      runtime.errConsole().p(" of '").p(tag.getName()).p("' was here").flush();
    }
  }

}
