/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004-2008 Robert Grimm
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

import java.util.HashMap;

import xtc.tree.Annotation;
import xtc.tree.LineMarker;
import xtc.tree.Location;
import xtc.tree.Node;
import xtc.tree.Pragma;
import xtc.tree.SourceIdentity;

import xtc.util.State;

/**
 * The global state for parsing C.  This class provides a simplified
 * symbol table that is organized as a stack of parsing contexts, with
 * a new context being pushed onto the stack through {@link #start()}
 * and popped again through {@link #commit()} or {@link #abort()}.
 *
 * @author Robert Grimm
 * @version $Revision: 1.16 $
 */
public class CParserState implements State {

  /** A parsing context. */
  protected static class Context {

    /** The next context. */
    public Context next;

    /**
     * The flags for this context.  The flags from LSB to MSB are:
     * FLAG_TYPEDEF, FLAG_SCOPE, FLAG_TYPE_SPEC, FLAG_PARAMS,
     * FLAG_MODIFIED, FLAG_STRUCTURE.
     */
    public int flags;

    /** The bindings for this context, if any. */
    public final HashMap<String,Boolean> bindings;

    /** The marked annotation, if any. */
    public Annotation mark;

    // ------------------------------------------------------------------------

    /** Create a new context. */
    public Context() {
      bindings = new HashMap<String,Boolean>();
    }

    // ------------------------------------------------------------------------

    /** Clear this context. */
    public void clear() {
      if (isSet(FLAG_MODIFIED)) {
        bindings.clear();
      }
      flags = 0;
      mark  = null;
    }

    // ------------------------------------------------------------------------

    /**
     * Determine whether the specified flag is set.
     *
     * @param flag The flag.
     * @return <code>true</code> if the flag is set.
     */
    public boolean isSet(final int flag) {
      return (0 != (flag & flags));
    }

    /**
     * Set the specified flag.
     *
     * @param flag The flag.
     */
    public void set(final int flag) {
      flags |= flag;
    }

    /**
     * Clear the specified flag.
     *
     * @param flag The flag.
     */
    public void clear(final int flag) {
      flags &= ~flag;
    }

    // ------------------------------------------------------------------------

    /** Print a trace of all contexts starting with this context. */
    public void trace() {
      Context c = this;

      do {
        System.out.print("  Context@0x");
        System.out.print(Integer.toHexString(System.identityHashCode(c)));
        System.out.print(": flags=0b");
        System.out.println(Integer.toBinaryString(c.flags));

        c = c.next;
      } while (null != c);

      System.out.flush();
    }

  }

  // ==========================================================================

  /** The flag for whether to print debug information to the console. */
  protected static final boolean DEBUG = false;

  /** The initial size of the context pool. */
  protected static final int POOL_INIT = 10;

  /** The increment of the context pool. */
  protected static final int POOL_INCR = 5;

  /** The flag for typedefs. */
  protected static final int FLAG_TYPEDEF = 0x01;
  
  /** The flag for scopes. */
  protected static final int FLAG_SCOPE = 0x02;
  
  /** The flag for having parsed a type specifier. */
  protected static final int FLAG_TYPE_SPEC = 0x04;
  
  /** The flag for having parsed a function parameter list. */
  protected static final int FLAG_PARAMS = 0x08;
  
  /** The flag for having modified the bindings. */
  protected static final int FLAG_MODIFIED = 0x10;

  /** The flag for structure/union declaration lists. */
  protected static final int FLAG_STRUCTURE = 0x20;
  
  // ==========================================================================

  /** The pool of parsing contexts. */
  private Context pool;

  /**
   * The top of the context stack.  The implementation assumes that
   * this field always references at least one context, which
   * corresponds to the global namespace.
   */
  protected Context top;

  /** The current nesting level. */
  protected int nesting;

  /** The current annotation, if any. */
  protected Annotation annotation;

  // ==========================================================================

  /** Create a C parser state object. */
  public CParserState() {
    fillPool(POOL_INIT);
    top        = new Context();
    reset(null);
  }

  // ==========================================================================

  /**
   * Add the specified number of fresh contexts to the pool.
   *
   * @param n The number to add.
   */
  protected void fillPool(int n) {
    for (int i=0; i<n; i++) {
      addToPool(new Context());
    }
  }

  /**
   * Take a context from the pool, refilling the pool if necessary.
   *
   * @return A fresh context.
   */
  protected Context takeFromPool() {
    if (null == pool) {
      fillPool(POOL_INCR);
    }

    Context c = pool;
    pool      = c.next;
    c.next    = null;
    return c;
  }

  /**
   * Return the specified context to the pool, clearing it along the
   * way.
   *
   * @param c The context to return.
   */
  protected void addToPool(Context c) {
    c.next     = pool;
    c.clear();
    pool       = c;
  }

  // ==========================================================================

  /**
   * Push the specified context onto the context stack.
   *
   * @param c The context to push.
   */
  protected void push(Context c) {
    c.next = top;
    top    = c;
  }

  /**
   * Pop a context from the context stack.
   *
   * @return The top-most context.
   */
  protected Context pop() {
    Context c = top;
    top       = c.next;
    c.next    = null;
    return c;
  }

  // ==========================================================================

  public void reset(String file) {
    if (DEBUG) System.out.println("reset(" + file + ")");

    // Return all contexts besides the top-level context from the
    // stack to the pool.
    while (null != top.next) {
      addToPool(pop());
    }

    // Clear the top-level context.
    top.clear();
    top.set(FLAG_SCOPE);

    // Clear the nesting level.
    nesting    = 0;

    // Clear any annotations.
    annotation = null;
  }

  public void start() {
    if (DEBUG) {
      nesting++;
      System.out.println("start(" + nesting + ")");
    }

    push(takeFromPool());
  }

  public void commit() {
    if (DEBUG) {
      if (top.isSet(FLAG_SCOPE)) {
        System.out.println("implied exitScope(" + nesting + ")");
      }
      System.out.println("commit(" + nesting + ")");
      nesting--;
    }

    addToPool(pop());
  }

  public void abort() {
    if (DEBUG) {
      if (top.isSet(FLAG_SCOPE)) {
        System.out.println("implied exitScope(" + nesting + ")");
      }
      System.out.println("abort(" + nesting + ")");
      nesting--;
    }

    addToPool(pop());
  }

  // ==========================================================================

  /** Record a typedef storage class specifier. */
  public void typedef() {
    if (DEBUG) System.out.println("typedef()");
    top.set(FLAG_TYPEDEF);
  }

  /** Record a function parameter list. */
  public void parameters() {
    if (DEBUG) System.out.println("parameters()");
    top.set(FLAG_PARAMS);
  }

  /** Record a function declarator. */
  public void functionDeclarator() {
    if (DEBUG) System.out.println("functionDeclarator()");
    top.clear(FLAG_PARAMS);
  }

  /** Record a type specifier. */
  public void typeSpecifier() {
    if (DEBUG) System.out.println("typeSpecifier()");
    top.set(FLAG_TYPE_SPEC);
  }

  /** Enter a new scope. */
  public void pushScope() {
    if (DEBUG) System.out.println("pushScope(" + nesting + ")");
    top.set(FLAG_SCOPE);
  }

  /** Exit the last scope. */
  public void popScope() {
    if (DEBUG) System.out.println("popScope(" + nesting + ")");
    top.clear(FLAG_SCOPE);
  }

  /** Enter a structure declaration list. */
  public void enterStructure() {
    if (DEBUG) System.out.println("enterStructure(" + nesting + ")");
    top.set(FLAG_STRUCTURE);
  }

  /** Exit a structure declaration list. */
  public void exitStructure() {
    if (DEBUG) System.out.println("exitStructure(" + nesting + ")");
    top.clear(FLAG_STRUCTURE);
  }

  /**
   * Implicitly bind the specified identifier.  Depending on the
   * current parsing context, the identifier is either bound as a type
   * or as an object/function/constant.
   *
   * @param id The identifier.
   */
  public void bind(String id) {
    // Ignore the binding if a function parameter list has already
    // been parsed or the binding appears inside a structure
    // declaration list.
    if (top.next.isSet(FLAG_PARAMS) || top.next.isSet(FLAG_STRUCTURE)) {
      if (DEBUG) {
        System.out.println("ignoring bind(" + id + ", " +
                           top.isSet(FLAG_TYPEDEF) + ")");
      }
      return;
    } else if (DEBUG) {
      System.out.println("bind(" + id + ", " + top.isSet(FLAG_TYPEDEF) + ")");
    }

    // Get the top-most scope.
    Context c = top;
    while (! c.isSet(FLAG_SCOPE)) {
      c = c.next;
    }

    // Record the name.
    if (c.bindings.containsKey(id)) {
      if (DEBUG) {
        System.out.println("ignoring rebinding of " + id);
      }
    } else {
      c.bindings.put(id, top.isSet(FLAG_TYPEDEF)? Boolean.TRUE : Boolean.FALSE);
      c.set(FLAG_MODIFIED);
    }
  }

  /**
   * Explicitly bind the specified identifier.
   *
   * @param id The identifier.
   * @param isType The flag for whether the identifier represents a
   *   type.
   */
  public void bind(String id, boolean isType) {
    if (DEBUG) {
      System.out.println("bind(" + id + ", " + isType + ')');
    }

    // Get the top-most scope.
    Context c = top;
    while (! c.isSet(FLAG_SCOPE)) {
      c = c.next;
    }

    // Record the name.
    if (c.bindings.containsKey(id)) {
      if (DEBUG) {
        System.out.println("ignoring rebinding of " + id);
      }
    } else {
      c.bindings.put(id, isType ? Boolean.TRUE : Boolean.FALSE);
      c.set(FLAG_MODIFIED);
    }
  }

  /**
   * Determine whether the specified identifier names a type.
   *
   * @param id The identifier.
   * @return <code>true</code> if the specified identifier names a type.
   */
  public boolean isType(String id) {
    // If we have already parsed a type specifier, the identifier does
    // not name a type.
    if (top.isSet(FLAG_TYPE_SPEC)) {
      if (DEBUG) System.out.println("isType(" + id + ") -> false");
      return false;
    }

    // Otherwise, we consult the symbol table.
    Context c = top;

    do {
      while (! c.isSet(FLAG_SCOPE)) {
        c = c.next;
      }

      Boolean value = c.bindings.get(id);
      if (null != value) {
        boolean type = value.booleanValue();
        if (DEBUG) System.out.println("isType(" + id + ") -> " + type);
        return type;
      }

      c = c.next;
    } while (null != c);

    if (DEBUG) System.out.println("isType(" + id + ") -> false");
    return false;
  }

  /**
   * Determine whether a declaration actually is a declaration.  This
   * method determines whether the sequence
   * <pre>
   *   DeclarationSpecifiers l:InitializedDeclaratorList?
   * </pre>
   * can actually represent a declaration.  It assumes that any type
   * specifier encountered while parsing
   * <code>DeclarationSpecifiers</code> has been marked through {@link
   * #typeSpecifier()}.
   *
   * @param idl The result of parsing the optional initialized
   *   declarator list.
   * @return <code>true</code> if the declaration is a declaration.
   */
  public boolean isValid(Node idl) {
    return top.isSet(FLAG_TYPE_SPEC) || (null != idl);
  }

  // ==========================================================================

  /**
   * Record a line marker.  Note that string values for the four flags
   * are interpreted as follows: Any non-null string counts for
   * <code>true</code>, while null counts for <code>false</code>.
   *
   * @see LineMarker
   *
   * @param file The file name (without quotes).
   * @param line The line number.
   * @param isStartFile The start file flag.
   * @param isReturnToFile The return to file flag.
   * @param isSystemHeader The system header flag.
   * @param isExternC The extern C flag.
   * @param location The line marker's source location.
   */
  public void lineMarker(String file, int line, String isStartFile,
                         String isReturnToFile, String isSystemHeader,
                         String isExternC, Location location) {
    if (DEBUG) System.out.println("lineMarker(" + file + ": " + line + ")");

    int flags = 0;
    if (null != isStartFile)    flags |= LineMarker.FLAG_START_FILE;
    if (null != isReturnToFile) flags |= LineMarker.FLAG_RETURN_TO_FILE;
    if (null != isSystemHeader) flags |= LineMarker.FLAG_SYSTEM_HEADER;
    if (null != isExternC)      flags |= LineMarker.FLAG_EXTERN_C;

    LineMarker marker = new LineMarker(line, file, flags, null);
    marker.setLocation(location);
    if (null == annotation) {
      annotation = marker;
    } else {
      annotation.innerMost().setNode(marker);
    }
  }

  /**
   * Record a pragma.
   *
   * @see Pragma
   *
   * @param directive The actual directive.
   * @param location The pragma's source location.
   */
  public void pragma(String directive, Location location) {
    if (DEBUG) System.out.println("pragma(" + directive + ")");

    Pragma pragma   = new Pragma(directive, null);
    pragma.setLocation(location);
    if (null == annotation) {
      annotation = pragma;
    } else {
      annotation.innerMost().setNode(pragma);
    }
  }

  /**
   * Record an ident directive.
   *
   * @see SourceIdentity
   *
   * @param ident The actual identity marker.
   * @param location The ident directive's source location.
   */
  public void ident(String ident, Location location) {
    if (DEBUG) System.out.println("ident(" + ident + ")");

    SourceIdentity identity = new SourceIdentity(ident, null);
    identity.setLocation(location);
    if (null == annotation) {
      annotation = identity;
    } else {
      annotation.innerMost().setNode(identity);
    }
  }

  /**
   * Mark the current annotation.  This method must be called before
   * recognizing the nonterminals to be annotated.  Furthermore, it
   * must be called within the context of a stateful production.
   */
  public void mark() {
    if (DEBUG) System.out.println("mark()");

    if (null == annotation) {
      top.mark = null;
    } else {
      top.mark = annotation.innerMost();
    }
  }

  /**
   * Annotate the specified node.  If any annotations have been
   * recorded and {@link #mark() marked}, the specified node is
   * wrapped by those annotations and the outer-most annotation is
   * returned.  Otherwise, the specified node is returned.
   *
   * @param node The node.
   * @return The annotated node.
   */
  public Node annotate(Node node) {
    if (DEBUG) System.out.println("annotate(" + node + ")");

    if (null != top.mark) {
      // Find the mark in the next closest context, if it exists.
      Annotation base = null;
      Context    c    = top.next;
      while (null != c) {
        if (null != c.mark) {
          base = c.mark;
          break;
        }
        c = c.next;
      }

      // Apply the annotations between the base and current mark to
      // the specified node, while also preserving any new
      // annotations.
      Annotation a = (Annotation)top.mark.getNode();
      top.mark.setNode(node);
      if (null == base) {
        node        = annotation;
        annotation  = a;
      } else {
        node        = base.getNode();
        base.setNode(a);
      }
      top.mark      = null;
    }

    // Done.
    return node;
  }

}
