/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2004 Robert Grimm
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package xtc.tree;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.InvocationTargetException;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * A node visitor. In contrast to the basic visitor pattern (which
 * only works for a fixed set of object types), the node visitor is
 * extensible.  As described in <a
 * href="http://www.javaworld.com/javaworld/javatips/jw-javatip98.html">this
 * JavaWorld tip</a>, the implementation relies on Java reflection to
 * dispatch to the appropriate <code>visit()</code> method. Note that
 * the node visitor does not recognize method names that append the
 * object type to the word "visit", rather it relies on the argument
 * type alone to identify the appropriate <code>visit()</code> method.
 *
 * <p>Note that to improve performance of dynamic dispatch, this class
 * uses a static method lookup cache.  As a result, dispatch is not
 * thread-safe.
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public abstract class Visitor {

  /** Key for the method lookup cache. */
  static class CacheKey {

    /** The visitor. */
    public Visitor visitor;

    /** The class of the node. */
    public Class nodeT;

    /**
     * Create a new cache key.
     *
     * @param visitor The visitor.
     * @param nodeT The class of the node.
     */
    public CacheKey(Visitor visitor, Class nodeT) {
      this.visitor = visitor;
      this.nodeT   = nodeT;
    }

    public int hashCode() {
      return (37 * System.identityHashCode(visitor)
              + System.identityHashCode(nodeT));
    }

    public boolean equals(Object o) {
      if (! (o instanceof CacheKey)) return false;
      CacheKey other = (CacheKey)o;
      if (visitor != other.visitor) return false;
      return (nodeT == other.nodeT);
    }

  }

  /** Flag for whether to use the method lookup cache. */
  private static final boolean USE_CACHE = true;

  /** The size of the method lookup cache. */
  private static final int CACHE_SIZE = 300;

  /** The capacity of the method lookup cache. */
  private static final int CACHE_CAPACITY = 400;

  /** The load factor of the method lookup cache. */
  private static final float CACHE_LOAD = (float)0.75;

  /** The method lookup cache. */
  private static final LinkedHashMap theCache;

  /** The pre-allocated cache key for looking up methods. */
  private static final CacheKey theKey;

  /** The pre-allocated array for passing the node to invoke(). */
  private static final Object[] theNode;

  /** The pre-allocated array for passing the node type to getMethod(). */
  private static final Class[] theNodeType;

  static {
    if (USE_CACHE) {
      theCache = new LinkedHashMap(CACHE_CAPACITY, CACHE_LOAD, true) {
          protected boolean removeEldestEntry(Map.Entry e) {
            return size() > CACHE_SIZE;
          }
        };
      theKey    = new CacheKey(null, null);
    } else {
      theCache  = null;
      theKey    = null;
    }
    theNode     = new Object[] { null };
    theNodeType = new Class[] { null };
  }

  /** Create a new visitor. */
  public Visitor() {
  }

  /**
   * Find the closest matching <code>visit()</code> method for the
   * specified node and invoke it. Optionally, a <code>visit()</code>
   * method may return a value, thus making it possible, for example,
   * to replace nodes or to construct entirely new trees.  If the
   * <code>visit()</code> method does not return a value, this method
   * returns <code>null</code>.
   *
   * @param node The node.
   * @return The (optional) return value.
   * @throws VisitorException
   *   Signals that this visitor does not have a matching 
   *   <code>visit()</code> method.
   * @throws VisitingException
   *   Signals an exceptional condition while visiting the specified
   *   node. 
   */
  public Object dispatch(Node node) {
    Class  nodeT = node.getClass();
    Method m;

    if (USE_CACHE) {
      theKey.visitor = this;
      theKey.nodeT   = nodeT;
      m              = (Method)theCache.get(theKey);

      if (null == m) {
        m            = getMethod(nodeT);
        theCache.put(new CacheKey(this, nodeT), m);
      }
    } else {
      m              = getMethod(nodeT);
    }

    theNode[0]       = node;
    try {
      return m.invoke(this, theNode);
    } catch (IllegalAccessException x) {
      // Shouldn't happen b/c m is public.
      throw new
        VisitingException("Exceptional condition while visiting node " +
                          node + " with visitor " + this, x);
    } catch (IllegalArgumentException x) {
      // Shouldn't happen b/c this must be an instance of its own class.
      throw new
        VisitingException("Exceptional condition while visiting node " +
                          node + " with visitor " + this, x);
    } catch (ClassCastException x) {
      throw new VisitingException("Invalid result while from visiting node " +
                                  node + " with visitor " + this, x);
    } catch (InvocationTargetException x) {
      Throwable cause = x.getCause();

      if (cause instanceof VisitingException) {
        // Rethrow.
        throw (VisitingException)cause;
      } else if (cause instanceof VisitorException) {
        // Rethrow.
        throw (VisitorException)cause;
      } else if (null != cause) {
        throw new
          VisitingException("Exceptional condition while visiting node " +
                            node + " with visitor " + this, cause);
      } else {
        throw new
          VisitingException("Exceptional condition while visiting node " +
                            node + " with visitor " + this, x);
      }
    }
  }
  
  /**
   * Find the closest matching <code>visit()</code> method for the
   * specified type of node. The implementation of this method walks
   * the class chain until it finds an appropriate method.
   *
   * @param node The node's class (which must be a subtype of Node).
   * @throws VisitorException
   *   Signals that this visitor does not have a matching
   *   <code>visit()</code> method.
   */
  private Method getMethod(Class nodeT) {
    Class  visiT = getClass();
    Class  c     = nodeT;
    Method m     = null;
    
    do {
      theNodeType[0] = c;
      try {
        m = visiT.getMethod("visit", theNodeType);
      } catch (NoSuchMethodException x) {
        // Try the interfaces implemented by c.
        Class[] interfaces = c.getInterfaces();
        for (int i=0; i<interfaces.length; i++) {
          theNodeType[0] = interfaces[i];
          try {
            m = visiT.getMethod("visit", theNodeType);
          } catch (NoSuchMethodException xx) {
            // Ignore.
          }
          if (null != m) {
            break;
          }
        }

        if (null == m) {
          c = c.getSuperclass();
        }
      }
    } while ((null == m) && (Object.class != c));
    
    if (null == m) {
      throw new VisitorException("No method to visit nodes of type " +
                                 nodeT.toString() +
                                 " in visitor " + this.toString());
    } else {
      return m;
    }
  }

}
