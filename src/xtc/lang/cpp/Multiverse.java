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

  /** Create a multiverse containing a single element. */
  public Multiverse(T data, PresenceCondition cond) {
    this();
    add(data, cond);
  }
	
  /** The copy constructor. */
  public Multiverse(Multiverse<T> mv) {
    this();
    addAll(mv);
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
     * @return The data field.
     */
    public T getData() {
      return data;
    }

    /**
     * Get the presence condition.
     *
     * @return The presence condition.
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
      return String.format("%s:%s", getData(), getCondition());
      // return String.format("(%s, %s)", getData(), getCondition());
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
    cond.addRef();
  }

  /**
   * Add all elements from the given Multiverse to this.  It does a
   * shallow copy.
   *
   * @param mv The Multiverse to add elements from.
   */
  public void addAll(Multiverse<T> mv) {
    for (Element<T> elem : mv.contents) {
      this.add(elem.getData(), elem.getCondition());
    }
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
   * @return The size of the Multiverse.
   */
  public int size() {
    return contents.size();
  }

  /**
   * Checks whether the Multiverse is empty.
   *
   * @return true if the Multiverse is empty.
   */
  public boolean isEmpty() {
    return size() == 0;
  }

  /**
   * Creates an iterator over the elements of the Multiverse.
   *
   * @return the iterator.
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
   * @return A new instance of Multiverse holding the cartesian
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
            condition.addRef();
          }
          condition.delRef();
        }
      }
      
      return newmv;
    }
  }

  /**
   * This is a special case of the cartesian product where the other
   * multiverse contains only a single element.
   *
   * @param data The other Multiverse's data.
   * @param cond The other Multiverse's condition.
   * @param op The operator to use to combine individual elements of
   * the Multiverse
   * @return A new instance of Multiverse holding the cartesian
   * product of the two Multiverses.
   */
  public Multiverse<T> product(T data, PresenceCondition cond, Operator<T> op) {
    Multiverse<T> other = new Multiverse<T>();
    other.add(data, cond);
    Multiverse<T> result = product(other, op);
    other.destruct();
    return result;
  }

  /**
   * Return a new Multiverse that conjoins the given condition with
   * each element of the Multiverse, trimming any infeasible elements.
   * Since this is a new instance, the caller should call destruct
   * when done.
   *
   * @param cond The condition.
   * @return The new Multiverse.
   */
  public Multiverse<T> filter(PresenceCondition cond) {
    Multiverse<T> newmv = new Multiverse<T>();
    for (Element<T> elem : this) {
      PresenceCondition condition = elem.getCondition().and(cond);
      if (! condition.isFalse()) {
        newmv.add(elem.getData(), condition);
        condition.addRef();
      }
      condition.delRef();
    }
    return newmv;
  }

  /**
   * The function signature for combining two individual elements of a
   * Multiverse.
   */
  static abstract class Transformer<T, U> {
    /**
     * A function that combines two elements of the Multiverse's data.
     * This is used to abstract away the cartesian product.
     *
     * @param left The left operand.
     * @param right The right operand.
     */
    abstract U transform(T from);
    
    public Multiverse<U> transform(Multiverse<T> from) {
      Multiverse<U> newmv = new Multiverse<U>();
      for (Element<T> elem : from) {
        U data = transform(elem.getData());
        newmv.add(data, elem.getCondition());
      }
      return newmv;
    }
  }

  public String toString() {
    StringBuilder sb = new StringBuilder();

    sb.append("Multiverse(");
    sb.append("\n");
    for (Element<T> elem : this.contents) {
      sb.append("  ");
      sb.append(elem);
      sb.append("\n");
    }
    sb.append(")");
    sb.append("\n");
    return sb.toString();
  }
}
