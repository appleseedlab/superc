package xtc.lang.cpp;

import java.util.LinkedList;
import java.util.List;

import xtc.type.Type;
import xtc.type.UnitT;
import xtc.type.PointerT;
import xtc.type.ArrayT;
import xtc.type.TypedefT;
import xtc.lang.cpp.Multiverse.Element;
import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

public class DeclBuilder
{
  String identifier;
  int numPointers;
  List<String> arrays;
  DeclBuilder inner;
  boolean isValid;
  TypeBuilderUnit quals;
  Type basicType;

  List<Parameter> parameters;


  /**
     If the type is a function, this only returns the return type. The types of the parameters is in the getParams function.
   */
  // converts the declbuilder to a type object
  public Type toType() {
    if (!isValid) {
      System.err.println("ERROR: attempting to create an invalid type.");
      System.exit(1);
    }

    Type type;

    // recursively gets the inner declbuilder information
    if (inner == null)
      type = basicType;
    else
      type = inner.toType();
      
    for (String arr : arrays) {
      if (arr.equals("")) { // array length has no expression
        // NOTE: array length is internally being set to -1.
        type = new ArrayT(type, false);
      }
      else if (arr.equals("const Expr")) { // array length is a constant expression
        long length = -1; // TODO: possibly evaluate the constant expression, and set length to that
        type = new ArrayT(type, length);
      } else { // array length is a variable expression
        // NOTE: array length is internally being set to -1.
        type = new ArrayT(type, true);
      }
    }
    // continually create new pointerT objects where each one points to the previous one
    for (int i = 0; i < numPointers; i++) {
      if(type instanceof TypedefT)
        ((TypedefT)type).makePointer();
      else
        type = new PointerT(type);
    }

    return type;
  }
  
  public Multiverse<List<Parameter>> getParams(PresenceCondition current)
  {
    Multiverse<List<Parameter>> m = new Multiverse<List<Parameter>>();
    List<Parameter> l = new LinkedList<Parameter>();
    m.add(l, current);
    for (Parameter p : parameters)
      {
         Multiverse<List<Parameter>> newM = new Multiverse<List<Parameter>>();
         if (!p.isEllipsis())
          {
            Multiverse<Universe> mult = p.getMultiverse();
            PresenceCondition gap = p.getGap(current);
            for (Element<Universe> u : mult)
              {
                for (Element<List<Parameter>> lp : m)
                  {
                    if (!lp.exclusiveFrom(u.getCondition()))
                      {
                        List<Parameter> lp2 = new LinkedList<Parameter>();
                        lp2.addAll(lp.getData());
                        Multiverse<Universe> tempM = new Multiverse<Universe>();
                        tempM.add(u);
                        Parameter tempP = new Parameter();
                        tempP.setMultiverse(tempM);
                        lp2.add(tempP);
                        newM.add(new Element(lp2, lp.getCondition().and(u.getCondition())));
                      }
                  }
              }
            for (Element<List<Parameter>> lp : m)
              if (!lp.exclusiveFrom(gap))
                newM.add(new Element(lp.getData(), lp.getCondition().and(gap)));
          }
         else
           for (Element<List<Parameter>> lp : m)
             {
               List<Parameter> lp2 = lp.getData();
               lp2.add(p);
               newM.add(new Element(lp2, lp.getCondition()));
             }
         m = newM;
      }
    return m;
  }

  public DeclBuilder()
  {
    identifier = "";
    numPointers = 0;
    arrays = new LinkedList<String>();
    inner = null;
    isValid = true;
    basicType = new UnitT();
    parameters = null;
  }

  public DeclBuilder(DeclBuilder d)
  {
    identifier = d.identifier;
    numPointers = d.numPointers;
    arrays = new LinkedList<String>();
    for (String x : d.arrays)
	    arrays.add(x);
    if (d.inner != null)
	    inner = new DeclBuilder(d.inner);
    else
	    inner = null;
    isValid = d.isValid;
    basicType = d.basicType.copy();
    parameters = d.parameters;
  }

  public DeclBuilder(String name)
  {
    identifier = name;
    numPointers = 0;
    arrays = new LinkedList<String>();
    inner = null;
    isValid = true;
    basicType = new UnitT();
    parameters = null;
  }

  public void addPointer() {
    numPointers++;
  }

  public void addArray(String i) {
    addArray(i, true);
  }

  public int countArrays() {
    int count = 0;
    count += arrays.size();
    if (inner != null)
	    count += inner.countArrays();
    return count;
  }

  public void addArray(String i, boolean seen) {
    if (!seen)
      if (countArrays() == 0)
        arrays.add("");
      else
        isValid = false;
    else
      arrays.add(i);
  }

  public void addType(Type type) {
    if (basicType instanceof UnitT)
      basicType = type;
    else // invalid: multiple types being added to the same declaration
      isValid = false;
  }

  public void addDeclBuilder(DeclBuilder d) {
    inner = d;
    if (!d.isValid)
      isValid = false;
  }

  public void merge(DeclBuilder d) {
    numPointers += d.numPointers;
    if (inner != null) {
      if (d.inner != null)
        isValid = false;
    }
    else
      inner = d.inner;
    if (!identifier.equals("")) {
      if (!d.identifier.equals(""))
        isValid = false;
    }
    else
      identifier = d.identifier;

    for (int i = 0; i < d.arrays.size(); ++i)
      arrays.add(d.arrays.get(i));
  }

  public String getID() {
    if (identifier.equals("") && inner != null)
      return inner.getID();
    return identifier;
  }

  public String toString() {
    if (!isValid)
      return "Decl Error";
    String output = "";
    for (int i = 0; i < numPointers; ++i)
      output += "*";
    if (!identifier.equals(""))
      output += identifier;
    if (inner != null)
      {
		    if (quals == null)
          output += "(" + inner.toString() + ")";
		    else
          output += quals.qualString() + " " + inner.toString(); 
      }
    for (int i = 0; i < arrays.size(); ++i) {
      output += "[";
      output += arrays.get(i);
      output += "]";
    }
    return output;
  }

  public void addQuals(TypeBuilder t, DeclBuilder d)
  {
    quals = t.getQualTU();
    inner = d;
  }

  public boolean getIsValid()
  {
    return isValid;
  }

  public boolean isFunction()
  {
    return parameters != null;
  }
  
  public void setParams(List<Parameter> p)
  {
    parameters = p;
  }
}
