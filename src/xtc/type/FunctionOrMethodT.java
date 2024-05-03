/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2006-2007 Robert Grimm
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
package xtc.type;

import java.io.IOException;

import java.util.Iterator;
import java.util.List;
import superc.core.PresenceConditionManager;
import superc.core.PresenceConditionManager.PresenceCondition;

/**
 * The superclass of function and method types.
 *
 * @author Robert Grimm
 * @version $Revision: 1.22 $
 */
public abstract class FunctionOrMethodT extends DerivedT {

    
  //  private PresenceCondition isDefined;
  
    
  /** The result type. */
  protected Type result;

  /** The optional name. */
  protected String name;

  /** The list of parameter types. */
  protected List<Type> parameters;

  /**
   * The flag for whether the function accepts a variable number of
   * arguments.
   */
  protected boolean varargs;

  /** The optional list of exceptions. */
  protected List<Type> exceptions;

  /**
   * Create a new function or method type.
   *
   * @param template The type whose annotations to copy.
   * @param result The result type.
   * @param name The name.
   * @param parameters The list of parameter types.
   * @param varargs The flag for accepting a variable number of arguments.
   * @param exceptions The list of exception types.
   */
  public FunctionOrMethodT(Type template, Type result, String name,
                           List<Type> parameters, boolean varargs,
                           List<Type> exceptions) {
    super(template);
    this.result     = result;
    this.name       = name;
    this.parameters = parameters;
    this.varargs    = varargs;
    this.exceptions = exceptions;
    //isDefined = (new PresenceConditionManager()).newFalse();
  }

  public Type seal() {
    if (! isSealed()) {
      super.seal();
      result.seal();
      parameters = Type.seal(parameters);
      exceptions = Type.seal(exceptions);
    }
    return this;
  }

  /**
   * Get the result type.
   *
   * @return The result type.
   */
  public Type getResult() {
    return result;
  }

  /**
   * Set the result type.
   *
   * @param result The new result type.
   * @throws IllegalStateException Signals that this type is sealed.
   */
  public void setResult(Type result) {
    checkNotSealed();
    this.result = result;
  }

  /**
   * Get the name.
   *
   * @return The name.
   */
  public String getName() {
    return name;
  }

  /**
   * Get the list of parameter types.
   *
   * @return The parameter types.
   */
  public List<Type> getParameters() {
    return parameters;
  }

  /**
   * Set the list of parameter types.
   *
   * @param parameters The list of parameter types.
   * @throws IllegalStateException Signals that this type is sealed.
   */
  public void setParameters(List<Type> parameters) {
    checkNotSealed();
    this.parameters = parameters;
  }

  /**
   * Determine whether this function accepts a variable number of
   * arguments.
   *
   * @return <code>true</code> if this function accepts a variable
   *   number of arguments.
   */
  public boolean isVarArgs() {
    return varargs;
  }

  /**
   * Get the list of exceptions.
   *
   * @return The list of exceptions.
   */
  public List<Type> getExceptions() {
    return exceptions;
  }

  /**
   * Set the list of parameter types.
   *
   * @param exceptions The list of exception types.
   * @throws IllegalStateException Signals that this type is sealed.
   */
  public void setExceptions(List<Type> exceptions) {
    checkNotSealed();
    this.exceptions = exceptions;
  }

  public int hashCode() {
    return parameters.hashCode() * 37 + result.hashCode();
  }

  public boolean equals(Object o) {
    if (! (o instanceof Type)) return false;
    Type t = resolve(o);

    if (this == t) return true;
    if (! getClass().equals(t.getClass())) return false;
    FunctionOrMethodT other = (FunctionOrMethodT)t;

    if (varargs != other.varargs) return false;
    if (! result.equals(other.result)) return false;
    if (null == exceptions) {
      if (null != other.exceptions) return false;
    } else {
      if (! exceptions.equals(other.exceptions)) return false;
    }
    return parameters.equals(other.parameters);
  }

  public void write(Appendable out) throws IOException {
    out.append(name + ":(");
    for (Iterator<Type> iter = parameters.iterator(); iter.hasNext(); ) {
      iter.next().write(out);
      if (iter.hasNext() || varargs) {
        out.append(", ");
      }
    }
    if (varargs) out.append("...");
    out.append(") -> ");
    if (result.resolve().isFunction()) {
      out.append('(');
      result.write(out);
      out.append(')');
    } else {
      result.write(out);
    }
  }

  public void printType(TypeString t) {
    if (t.inReturn) {
      t.coreType = printType();
      return;
    }
    t.inReturn = true;
    result.printType(t);
    t.inReturn = false;
    t.corePost += "(";
    t.id = name;
    int count = 0;
    if (parameters.size() == 1 && parameters.get(0).toVariable().getType().isVoid()) {
      t.corePost += "void)";
    } else {
      for (Iterator<Type> iter = parameters.iterator(); iter.hasNext(); ) {
        Type type = iter.next();
        if (!type.isVariable()) {System.err.println("illegal parameter print"); System.exit(-99); }
        VariableT v = type.toVariable();
        if (v.hasName()){
          t.corePost += v.printType();
        }else{
          t.corePost += v.printType("x"+ String.valueOf(count));
        }
        if (iter.hasNext() || varargs) {
          t.corePost +=", ";
        }
        count++;
      }
      if (varargs) {
        t.corePost += "...";
      }
      t.corePost += ")";
    }
  }
  
}
