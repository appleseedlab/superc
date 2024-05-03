/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2005-2007 Robert Grimm
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
package superc.cdesugarer;

import xtc.type.Type;
import xtc.type.FunctionT;
import xtc.type.VariableT;
import xtc.type.FunctionOrMethodT;

import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;

/**
 * This is a slight modification of xtc.type.FunctionT so that it can
 * use the underlying FunctionOrMethodT's name.  This name field is
 * used to store the renaming as with VariableT and AliasT.
 */
public class NamedFunctionT extends FunctionOrMethodT {

  /**
   * Create a new function type.
   *
   * @param result The result type.
   */
  public NamedFunctionT(Type result, String name) {
    super(null, result, name, new LinkedList<Type>(), false, null);
  }

  /**
   * Create a new function type.
   *
   * @param result The result type.
   * @param parameters The list of parameter types.
   * @param varargs The flag for accepting a variable number of arguments.
   */
  public NamedFunctionT(Type result, String name, List<Type> parameters, boolean varargs) {
    super(null, result, name, parameters, varargs, null);
  }

  /**
   * Create a new function type.
   *
   * @param template The type whose annotations to copy.
   * @param result The result type.
   * @param parameters The list of parameter types.
   * @param varargs The flag for accepting a variable number of arguments.
   */
  public NamedFunctionT(Type template, Type result, String name, List<Type> parameters,
                   boolean varargs) {
    super(template, result, name, parameters, varargs, null);
  }

  /**
   * Use the same tag as FUNCTION, since tag() is abstract, with the
   * understanding that we need to cast to NamedFunctionT instead of
   * use FunctionT, which will yield a runtime error.
   */
  public Type.Tag tag() {
    return Type.Tag.FUNCTION;
  }

  public NamedFunctionT copy() {
    NamedFunctionT copy =
      new NamedFunctionT(this, result.copy(), name, copy(parameters), varargs);
    if (null != exceptions) {
      copy.exceptions = copy(exceptions);
    }
    return copy;
  }

  public String getParamNames() {
    String r = "";
    int count = 0;
    if (parameters.size() == 1 && parameters.get(0).toVariable().getType().isVoid()) {
      return "";
    }
      for (Iterator<Type> iter = parameters.iterator(); iter.hasNext(); ) {
      Type t = iter.next();
      if (!t.isVariable()) {System.err.println("illegal parameter print"); System.exit(-99); }
      VariableT v = t.toVariable();
      if (v.hasName()) r += v.getName();
      else r += "x"+ String.valueOf(count);
	    if (iter.hasNext() || varargs) {
        r +=", ";
      }
      count++;        
    }
    return r;
  }

  
  /**
   * Create a FunctionT.  This is done to support comparing types
   * using the existing xtc infrastructure.
   */
  protected FunctionT toFunctionT() {
    return new FunctionT(this,
                         getResult(),
                         getParameters(),
                         isVarArgs());
  }

  public FunctionT toFunction() {
    return this.toFunctionT();
  }
  
  public NamedFunctionT toNamedFunction() {
    return this;
  }

  public boolean isNamedFunction() {
    return true;
  }

}
