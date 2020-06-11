package xtc.lang.cpp;

import java.lang.StringBuilder;
import java.util.Iterator;
import java.util.List;
import java.util.LinkedList;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

/**
 * This is an abstract multiverse, which stores a set of data tagged
 * by presence conditions.  It can be subclassed to create a
 * multiverse of any type.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.272 $
 */
public class Multiverse<T> implements Iterable<Multiverse.Element<T>> {
  protected List<Element<T>> contents;
  
  public Multiverse()
  {
    contents = new LinkedList<Element<T>>();
  }

  /**
   * This is one element of a multiple, i.e., a pair containing the
   * data and the presence condition representing the configuration
   * under which that version of the data appears.
   */
  public static class Element<T> {
    T data;
    PresenceCondition cond;

    public Element(T data, PresenceCondition cond) {
      this.data = data;
      this.cond = cond;
      this.cond.addRef();
    }

    public Element(T data) {
      this.data = data;
      cond = null;
    }
    public Element(PresenceCondition cond) {
      this.data = null;
      this.cond = cond;
      this.cond.addRef();
    }

    public Element()
    {
      data = null;
      cond = null;
    }
    public void destruct() {
      this.cond.delRef();
    }

    public void setData(T t)
    {
      this.data = t;
    }
    public void setCondition(PresenceCondition p)
    {
      if (cond != null)
	      {
          cond.delRef();
	      }
      this.cond = p;
      this.cond.addRef();
    }

    public boolean exclusiveFrom(PresenceCondition p)
    {
      return cond.isMutuallyExclusive(p);
    }
      
    public String toString() {
      StringBuilder sb = new StringBuilder();

      sb.append("(");
      sb.append(this.data);
      sb.append(", ");
      sb.append(this.cond);
      sb.append(")");
      
      return sb.toString();
    }

    public T getData()
    {
      return data;
    }

    public PresenceCondition getCondition()
    {
      return cond;
    }
  }

  /**
   * Decrement the references of all presence conditions and remove
   * the string builders.  Be sure to do this once you no longer
   * need the multiverse, e.g., after constructing a new multiverse
   * using this one.  The multiverse will no longer be useable after
   * calling this function.
   */
  public void destruct() {
    if (contents != null)
      {
	      for (Element<T> elem : contents) {
          elem.destruct();
	      }
	      contents.clear();
      }
    contents = null;
  }

  /**
   * Add a new element to the multiverse.
   */
  public void add(Element<T> elem) {
    contents.add(elem);
  }

  /**
   * Add a new element to the multiverse.
   */
  public void add(T data, PresenceCondition cond) {
    contents.add(new Element<T>(data, cond));
  }

  /**
   * Get an element of the list.  Warning, the backing storage is a
   * linked list, so this may only be efficient for get(0).
   */
  public Element<T> get(int index) {
    return contents.get(0);
  }

  public int size() {
    return contents.size();
  }

  public Iterator<Element<T>> iterator() {
    return contents.iterator();
  }

  public String toString() {
    StringBuilder sb = new StringBuilder();
    
    sb.append(this.contents);
    return sb.toString();
  }
}
