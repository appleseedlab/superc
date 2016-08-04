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

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.NoSuchElementException;

/**
 * A node in an abstract syntax tree or DAG.
 *
 * @author Robert Grimm
 * @version $Revision: 1.1 $
 */
public abstract class Node {

  /** The properties. */
  private Map properties;
  
  /** The optional source location. */
  public Location location;

  /** Create a new node. */
  public Node() {
  }

  /**
   * Create a new node.
   *
   * @param location The source location for the new node.
   */
  public Node(Location location) {
    this.location = location;
  }

  /**
   * Accept the specified visitor.
   *
   * <p />Optionally, a visitor may return a value, thus making it
   * possible, for example, to replace nodes or to construct entirely
   * new trees. If the specified visitor does not return a value, this
   * method returns <code>null</code>.
   *
   * @param v The visitor.
   * @return The (optional) return value.
   * @throws VisitorException
   *   Signals that the specified visitor does not have a matching
   *   <code>visit()</code> method.
   * @throws VisitingException
   *   Signals an exceptional condition while applying the specified
   *   visitor on this node.
   */
  public Object accept(Visitor v) {
    return v.dispatch(this);
  }

  /**
   * Set the value of a property.
   *
   * @param name The property name.
   * @param value The new property value.
   * @return The property's old value or <code>null</code> if the
   * property didn't have a value.
   */
  public Object setProperty(String name, Object value) {
    if (null == properties) {
      properties = new HashMap();
    }
    return properties.put(name, value);
  }

  /**
   * Test if this node has a property.
   *
   * @param name The property name.
   * @return <code>true</code> if this node has a property with the
   *   specified name.
   */
  public boolean hasProperty(String name) {
    if (null == properties) {
      return false;
    } else {
      return properties.containsKey(name);
    }
  }

  /**
   * Get a property value.
   *
   * @param name The property name.
   * @return The property's value or <code>null</code> if the
   *   property doesn't have a value.
   */
  public Object getProperty(String name) {
    if (null == properties) {
      return null;
    } else {
      return properties.get(name);
    }
  }

  /**
   * Remove a property.
   *
   * @param name The property name.
   * @return The property's old value or <code>null</code> if the
   *   property didn't have a value.
   */
  public Object removeProperty(String name) {
    if (null == properties) {
      return null;
    } else {
      return properties.remove(name);
    }
  }

  /**
   * Get an iterator over this node's property names.
   *
   * @return An iterator over this node's property names.
   */
  public Iterator properties() {
    if (null == properties) {
      return new Iterator() {
          public boolean hasNext() {
            return false;
          }
          public Object next() {
            throw new NoSuchElementException();
          }
          public void remove() {
            throw new IllegalStateException();
          }
        };
    } else {
      return properties.keySet().iterator();
    }
  }

  /**
   * Set the location of this node to the specified values,
   * <code>iff</code> the location has not been set before.
   *
   * @param file The file.
   * @param line The line number.
   * @param column The column number.
   */
  public void setLocation(String file, int line, int column) {
    if (null == location) {
      location = new Location(file, line, column);
    }
  }

}
