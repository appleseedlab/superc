package superc.cdesugarer;

import java.lang.StringBuilder;
import java.util.Iterator;
import java.util.List;
import java.util.LinkedList;
import java.util.Map;
import java.util.HashMap;

import superc.core.PresenceConditionManager.PresenceCondition;

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

  /** The complement of the elements' presence conditions. */
  protected PresenceCondition complement;

  /**
   * The default constructor creates an empty multiverse.  WARNING:
   * this should only be used in cases where the multiverse is
   * immediately populated; an empty multiverse has no meaning, since
   * the complement field is null.  Instead the list should have at
   * least one element.
   */
  public Multiverse() {
    contents = new LinkedList<Element<T>>();
    // start with null, to avoid having to take a presence condition
    // manager
    complement = null;
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
    if (this.contents.size() > 1) {
      complement.delRef();
      complement = null;
    } else {
      assert complement == null;
    }

    // if (null != this.complement) {
    //   this.complement.delRef();
    // }

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
    if (data == null) {
      System.out.println("----Alert: null added to table----\n");
      throw new Error();
    }
    contents.add(new Element<T>(data, cond));
    cond.addRef();
    if (null == complement) {
      assert contents.size() == 1;
      complement = cond.not();
    } else {
      assert contents.size() > 1;
      // make sure the user is not adding an element that overlaps
      // with an existing element's presence condition, i.e., the
      // elements of the multiverse should be mutually-exclusive
      PresenceCondition notcomplement = complement.not(); // the union of existing entry's conditions
      PresenceCondition checkmutex = notcomplement.and(cond);
      notcomplement.delRef();
      if (! checkmutex.isFalse()) {  // the union of existing entry's conditions should be mutex with the new entry
        throw new IllegalStateException("all multiverse entries must have mutually-exclusive presence conditions");
      }
      checkmutex.delRef();

      // update the complement to exclude the new element
      PresenceCondition notcond = cond.not();
      PresenceCondition newcomplement = complement.and(notcond);
      notcond.delRef();
      complement.delRef();
      complement = newcomplement;
    }
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
    if (this.contents.size() == 0) {
      throw new IllegalStateException("multiverse is not initialized");
    }
    
    return contents.get(index);
  }

  /**
   * Get the presence condition of the given data.  This uses the
   * object's equals() method.
   *
   * @param match The data to find in the multiverse.
   * @returns The union of the conditions of all elements that are
   * equal to the given data.
   */
  public PresenceCondition getConditionOf(T match) {
    if (this.contents.size() == 0) {
      throw new IllegalStateException("multiverse is not initialized");
    }
    assert this.complement != null;
    
    PresenceCondition pc = this.complement.presenceConditionManager().newFalse();
    for (Element<T> elem : this.contents) {
      if (elem.getData().equals(match)) {
        PresenceCondition newpc = pc.or(elem.getCondition());
        pc.delRef();
        pc = newpc;
      }
    }

    return pc;
  }

  /**
   * Get the complement of the multiverse, i.e., the negation of the
   * union of the existing element's presence conditions.  The caller
   * is responsible for calling addRef of the result.
   */
  public PresenceCondition getComplement() {
    if (this.contents.size() == 0) {
      throw new IllegalStateException("multiverse is not initialized");
    }
    assert this.complement != null;
    
    return complement;
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
    if (this.contents.size() == 0) {
	throw new IllegalStateException("multiverse is not initialized");
    }
    
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
      throw new IllegalStateException("trying to take cartesian product of empty multiverse");
      // return new Multiverse<T>();
    } else if (other.isEmpty()) {
      throw new IllegalStateException("trying to take cartesian product of empty multiverse");
      // return new Multiverse<T>();
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
   *  Syntactic sugar for productScalar(scalar, op, true);
   */
  public Multiverse<T> prependScalar(T scalar, Operator<T> op) {
    return productScalar(scalar, op, true);
  }

  /**
   *  Syntactic sugar for productScalar(scalar, op, false);
   */
  public Multiverse<T> appendScalar(T scalar, Operator<T> op) {
    return productScalar(scalar, op, false);
  }

  /**
   * This function takes the product of a scalar with this multiverse.
   * It is used, for instance, to preprend/append a string to every
   * element of the multiverse.
   *
   * @param scalar The scalar to prepend/append.
   * @param op The operator to use to combine individual elements of
   * the Multiverse
   * @param prefix Prepend the scalar if true, append if false.
   * @return A new instance of Multiverse holding the cartesian
   * product of the two Multiverses.
   */
  public Multiverse<T> productScalar(T scalar, Operator<T> op, boolean prefix) {
    if (this.isEmpty()) {
      throw new IllegalStateException("trying to take cartesian product of empty multiverse");
    } else {
      Multiverse<T> newmv = new Multiverse<T>();
      for (Element<T> elem : this) {
        T product;
        if (prefix) {
          product = op.product(scalar, elem.getData());
        } else {
          product = op.product(elem.getData(), scalar);
        }
        newmv.add(product, elem.getCondition());
      }
      
      return newmv;
    }
  }

  /**
   * The function signature for combining two individual elements of a
   * Multiverse, where they may be of different types.
   */
  @FunctionalInterface
  interface Joiner<T, U, R> {
    /**
     * A function that combines two elements of the Multiverse's data.
     * This is used to abstract away the cartesian product.
     *
     * @param left The left operand.
     * @param right The right operand.
     */
    R product(T left, U right);
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
  public <U, R> Multiverse<R> join(Multiverse<U> other, Joiner<T, U, R> op) {
    if (this.isEmpty()) {
      throw new IllegalStateException("trying to take cartesian product of empty multiverse");
    } else if (other.isEmpty()) {
      throw new IllegalStateException("trying to take cartesian product of empty multiverse");
    } else {
      Multiverse<R> newmv = new Multiverse<R>();
      /* The computes the following new set, where '*' is the operator:
           newmv = { ( data1 * data2, cond1 and cond2 )
                     for (data1, cond1) in this and (data2, cond2) in other } */
      for (Element<T> elem1 : this) {
        for (Element<U> elem2 : other) {
          PresenceCondition condition = elem1.getCondition().and(elem2.getCondition());
          if (! condition.isFalse()) {
            R data = op.product(elem1.getData(), elem2.getData());
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
   * This function is the same as the cartesian product, except that
   * it also takes the product of the complement of each multiverse
   * with each element of the other multiverse.  The complement is
   * assumed to have empty data.  For instance,
   *
   *   mv1 = [ ("a", A and B), COMPLEMENT=!A or !B ]
   *   mv2 = [ ("b", !A),   COMPLEMENT=A ]
   *
   * product() would yield an empty multiverse, because no combination
   * of elements is satisfiable.  complementedProduct would instead
   * return
   *
   *   [ ("a", A and B), ("b", !A and !B) COMPLEMENT=!B and A ]
   *
   * @param other The other Multiverse.
   * @param op The operator to use to combine individual elements of
   * the Multiverse
   * @return A new instance of Multiverse holding the complemented
   * cartesian product of the two Multiverses.
   */
  public Multiverse<T> complementedProduct(Multiverse<T> other, Operator<T> op) {
    // treat an empty multiverse as having a single element containing
    // empty data with the presence condition True.  filtering with
    // true yields the same multiverse.
    if (this.isEmpty()) {
      return new Multiverse<T>(other);
    } else if (other.isEmpty()) {
      return new Multiverse<T>(this);
    } else {
      // first take the product
      Multiverse<T> newmv = this.product(other, op);
      
      // then add the elements from each set
      // filtered by the other set's complement.  this simulates
      // having an empty operand for the complement that elides taking
      // a product.
      for (Element<T> otherelem : this) {
        PresenceCondition andComplement = otherelem.getCondition().and(this.getComplement());
        // all elements added should be mutually exclusive, since new
        // the multiverse's complement should be (this.complement OR
        // other.complement)
        if (! andComplement.isFalse()) {
          newmv.add(otherelem.getData(), andComplement);
        }
        andComplement.delRef();
      }
      for (Element<T> thiselem : this) {
        PresenceCondition andComplement = thiselem.getCondition().and(other.getComplement());
        // all elements added should be mutually exclusive, since new
        // the multiverse's complement should be (this.complement OR
        // other.complement)
        if (! andComplement.isFalse()) {
          newmv.add(thiselem.getData(), andComplement);
        }
        andComplement.delRef();
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
    if (this.contents.size() == 0) {
      throw new IllegalStateException("multiverse is not initialized");
    }

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
   * Deduplicate the contents of the multiverse.  This does not mutate
   * the object but returns a new one.  It uses the objects "hashCode"
   * function to check for equality.
   *
   * @returns A deduplicated version of the multiverse.
   */
  public Multiverse<T> deduplicate() {
    // loop for through object in the multiverse and either add it or
    // update an existing element's presence condition.

    Map<T, PresenceCondition> dedupmap = new HashMap<T, PresenceCondition>();

    for (Element<T> elem : this) {
      if (dedupmap.containsKey(elem.getData())) {
        PresenceCondition oldCond = dedupmap.get(elem.getData());
        dedupmap.put(elem.getData(), oldCond.or(elem.getCondition())); oldCond.delRef();
      } else {
        dedupmap.put(elem.getData(), elem.getCondition().addRef());
      }
    }

    // create a new multiverse out of the list (data, pc) pairs from the hash map
    Multiverse<T> mv = new Multiverse<T>();

    for (T key : dedupmap.keySet()) {
      mv.add(key, dedupmap.get(key));
    }

    return mv;
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
    if (null == this.contents) {
      assert isEmpty();
      sb.append("  EMPTY\n");
    } else {
      for (Element<T> elem : this.contents) {
        sb.append("  ");
        sb.append(elem);
        sb.append("\n");
      }
    }
    sb.append("  COMPLEMENT: ");
    if (null == complement) {
      assert isEmpty();
      sb.append("1");
    } else{
      sb.append(this.complement);
    }
    sb.append(")");
    sb.append("\n");
    return sb.toString();
  }
}
