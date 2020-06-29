package xtc.lang.cpp;

import java.lang.StringBuilder;
import java.util.Iterator;
import java.util.List;
import java.util.LinkedList;

import xtc.lang.cpp.PresenceConditionManager.PresenceCondition;

/**
 * This is a multiverse, which stores a set of data tagged by presence
 * conditions.  It takes a type parameter to indicate the type of data
 * it contains.
 *
 * @author Paul Gazzillo
 * @version $Revision: 1.272 $
 */
public class Multiverse<T> implements Iterable<Multiverse.Element<T>> {

  /** The set of (data, condition) pairs. */
  protected List<Element<T>> contents;

  /** The default constructor creates an empty multiverse. */
  public Multiverse() {
    contents = new LinkedList<Element<T>>();
  }
	
  /** The copy constructor. */
  public Multiverse(Multiverse<T> mv) {
    this();
    for (Element<T> elem : mv.contents) {
      this.add(elem.getData(), elem.getCondition());
    }
  }

  /**
   * This is one element of the multiverse, i.e., a pair containing
   * the data and the presence condition representing the
   * configuration under which that version of the data appears.
   */
  public static class Element<T> {
    /** The data field. */
    protected T data;

    /** The presence condition field. */
    protected PresenceCondition cond;

    /**
     * This constructor creates a new element.
     *
     * @param data The data field.
     * @param data The presence condition.
     */
    public Element(T data, PresenceCondition cond) {
      this.data = data;
      this.cond = cond;
      this.cond.addRef();
    }

    /**
     * Decrement the presence condition's reference counter.
     */
    public void destruct() {
      this.cond.delRef();
    }

    /**
     * Get the data field.
     *
     * @returns The data field.
     */
    public T getData() {
      return data;
    }

    /**
     * Get the presence condition.
     *
     * @returns The presence condition.
     */
    public PresenceCondition getCondition() {
      return cond;
    }

    /**
     * Set the data field.
     *
     * @param data The new data field.
     */
    public void setData(T data) {
      this.data = data;
    }
    
    // public void setCondition(PresenceCondition p) {
    //   this.cond.delRef();
    //   this.cond = p;
    //   this.cond.addRef();
    // }

    public String toString() {
      StringBuilder sb = new StringBuilder();

      sb.append("(");
      sb.append(this.data);
      sb.append(", ");
      sb.append(this.cond);
      sb.append(")");
      
      return sb.toString();
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
    for (Element<T> elem : contents) {
      elem.destruct();
    }
    contents.clear();
    contents = null;
  }

  /**
   * Add a new element to the multiverse.
   *
   * @param elem the new element.
   */
  public void add(Element<T> elem) {
    this.add(elem.getData(), elem.getCondition());
  }

  /**
   * Add a new element to the multiverse.
   *
   * @param data The data field.
   * @param cond The presence condition.
   */
  public void add(T data, PresenceCondition cond) {
    contents.add(new Element<T>(data, cond));
  }

  /**
   * Get an element of the list.  Warning, the backing storage is a
   * linked list, so this may only be efficient for get(0).
   *
   * @param index The index to retrieve.
   */
  public Element<T> get(int index) {
    return contents.get(0);
  }

  /**
   * Return the size of the Multiverse.
   *
   * @returns The size of the Multiverse.
   */
  public int size() {
    return contents.size();
  }

  /**
   * Checks whether the Multiverse is empty.
   *
   * @returns true if the Multiverse is empty.
   */
  public boolean isEmpty() {
    return size() == 0;
  }

  /**
   * Creates an iterator over the elements of the Multiverse.
   *
   * @returns the iterator.
   */
  public Iterator<Element<T>> iterator() {
    return contents.iterator();
  }

  /**
   * The function signature for combining two individual elements of a
   * Multiverse.
   */
  @FunctionalInterface
  interface Operator<U> {
    /**
     * A function that combines two elements of the Multiverse's data.
     * This is used to abstract away the cartesian product.
     *
     * @param left The left operand.
     * @param right The right operand.
     */
    U product(U left, U right);
  }

  /**
   * This function takes the cartesian product of this Multiverse with
   * another, given an operator to combine individuals elements.
   *
   * @param other The other Multiverse.
   * @param op The operator to use to combine individual elements of
   * the Multiverse
   * @returns A new instance of Multiverse holding the cartesian
   * product of the two Multiverses.
   */
  public Multiverse<T> product(Multiverse<T> other, Operator<T> op) {
    if (this.isEmpty()) {
      return new Multiverse<T>(other);
    } else if (other.isEmpty()) {
      return new Multiverse<T>(this);
    } else {
      Multiverse<T> newmv = new Multiverse<T>();
      /* The computes the following new set, where '*' is the operator:
           newmv = { ( data1 * data2, cond1 and cond2 )
                     for (data1, cond1) in this and (data2, cond2) in other } */
      for (Element<T> elem1 : this) {
        for (Element<T> elem2 : other) {
          PresenceCondition condition = elem1.getCondition().and(elem2.getCondition());
          if (! condition.isFalse()) {
            T data = op.product(elem1.getData(), elem2.getData());
            newmv.add(data, condition);
          }
        }
      }
      
      return newmv;
    }
  }  
  public String toString() {
    StringBuilder sb = new StringBuilder();
    
    sb.append(this.contents);
    return sb.toString();
  }
}
