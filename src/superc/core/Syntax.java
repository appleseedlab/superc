/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2009-2012 New York University
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
package superc.core;

import superc.core.PresenceConditionManager.PresenceCondition;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import xtc.tree.Location;

/**
 * Support for syntax objects.  This class is not yet used.
 *
 * Each syntax object supports a number of flags, efficiently
 * implemented through a bit mask.  Their main usage is by the
 * preprocessor to control macro expansion.
 *
 * @author Robert Grimm, Paul Gazzillo
 * @version $Revision: 1.36 $
 */
public abstract class Syntax extends xtc.tree.Token {

  /** The kinds of syntax objects. */
  public static enum Kind {
    /** Layout. */
    LAYOUT,
      /** A language token. */
      LANGUAGE,
      /** A preprocessor language token. */
      PREPROCESSOR,
      /** A preprocessor directive. */
      DIRECTIVE,
      /** The internal representation of a conditional. */
      CONDITIONAL,
      /** A self-contained conditional block. */
      CONDITIONAL_BLOCK,
      /** The EOF token. */
      EOF,
      /** An error or warning message. */
      ERROR,
      /** A marker. */
      MARKER,
  }

  // --------------------------------------------------------------------------

  /**
   * The maximum flag number.  Flags are numbered from 0 to this
   * number.
   */
  public static final int MAX_FLAGS = 31;

  /** The flags. */
  protected int flags;

  /** Create a new syntax object. */
  public Syntax() {
    // Nothing to do.
  }

  /**
   * Create a copy of the specified syntax object, including its
   * flags.
   *
   * @param other The syntax object to copy.
   */
  protected Syntax(Syntax other) {
    this.flags = other.flags;
    this.setLocation(other.getLocation());
  }

  /**
   * Copy this syntax object, including its flags.
   *
   * @return A copy.
   */
  public abstract Syntax copy();

  /**
   * Get this syntax object's kind.
   *
   * @return The kind.
   */
  public abstract Kind kind();

  /**
   * Convert this syntax object to layout.
   *
   * @return This syntax object as layout.
   * @throws ClassCastException Signals that this syntax object is not
   *   layout.
   */
  public Layout toLayout() {
    throw new ClassCastException("Not layout: " + this);
  }

  /**
   * Convert this syntax object to a language token.
   *
   * @return This syntax object as a language token.
   * @throws ClassCastException Signals that this syntax object is not
   *   a language token.
   */
  public Language<?> toLanguage() {
    throw new ClassCastException("Not a language token: " + this);
  }
  
  /**
   * Convert this syntax object to a preprocessor directive.
   *
   * @return This syntax object as a directive.
   * @throws ClassCastException Signals that this syntax object is not
   *   a directive.
   */
  public Directive toDirective() {
    throw new ClassCastException("Not a directive: " + this);
  }

  /**
   * Convert this syntax object to a conditional.
   *
   * @return This syntax object as a conditional.
   * @throws ClassCastException Signals that this syntax object is not
   *   a conditional.
   */
  public Conditional toConditional() {
    throw new ClassCastException("Not a conditional: " + this);
  }

  /**
   * Convert this syntax object to an error.
   *
   * @return This syntax object as an error.
   * @throws ClassCastException Signals that this syntax object is not
   *   an error.
   */
  public Error toError() {
    throw new ClassCastException("Not an error: " + this);
  }

  private int toMask(int num) {
    if (0 > num || MAX_FLAGS < num) {
      throw new IllegalArgumentException("Invalid flag number: " + num);
    }
    return 1 << num;
  }

  /** Clear all flags. */
  public void clearFlags() {
    flags = 0;
  }

  /**
   * Clear the specified flag.
   *
   * @param num The flag number.
   * @throws IllegalArgumentException Signals an invalid flag number.
   */
  public void clearFlag(int num) {
    flags &= ~toMask(num);
  }

  /**
   * Set the specified flag.
   *
   * @param num The flag number.
   * @throws IllegalArgumentException Signals an invalid flag number.
   */
  public void setFlag(int num) {
    flags |= toMask(num);
  }

  /**
   * Test the specified flag.
   *
   * @param num The flag number.
   * @return true if the flag is set.
   * @throws IllegalArgumentException Signals an invalid flag number.
   */
  public boolean testFlag(int num) {
    final int mask = toMask(num);
    return (flags & mask) == mask;
  }

  /**
   * Test flags against given syntax object's.
   *
   * @param s The other syntax object.
   * @return true If the same.
   * @throws IllegalArgumentException Signals an invalid flag number.
   */
  public boolean flagsEqual(Syntax s) {
    return flags == s.flags;
  }

  // --------------------------------------------------------------------------

  /** Layout. */
  public static class Layout extends Syntax {
    
    private final String text;

    private final boolean newline;

    /**
     * Create a new layout object.
     *
     * @param text The text.
     */
    public Layout(String text) {
      this(text, text.contains("\n"));
    }

    /**
     * Create a new layout object, given the text and whether that
     * text contains a newline.
     *
     * @param text The text.
     * @param newline Whether the text contains a newline.
     */
    public Layout(String text, boolean newline) {
      this.text = text;
      this.newline = newline;
    }

    private Layout(Layout other) {
      super(other);
      this.text = other.text;
      this.newline = other.newline;
    }

    public Layout copy() {
      return new Layout(this);
    }

    public Kind kind() {
      return Kind.LAYOUT;
    }

    public Layout toLayout() {
      return this;
    }

    public boolean hasNewline() {
      return newline;
    }

    public String getTokenText() {
      return text;
    }

    public String toString() {
      return getTokenText();
    }
  }

  // --------------------------------------------------------------------------

  public static enum PreprocessorTag {
    NONE,
    OPEN_PAREN,
    CLOSE_PAREN,
    COMMA,
    ELLIPSIS,
    HASH,
    DOUBLE_HASH,
    NUMBER
  }

  /** The interface for language tags. */
  public static interface LanguageTag {

    /**
     * Get the tag's ID.  The returned number is used by the LR parser
     * to identify the language token.
     *
     * @return The ID.
     */
    public int getID();

    /**
     * Get the tag's text.  For language tokens with a fixed text,
     * this method returns that text.  Otherwise, it returns null.
     *
     * @return The text.
     */
    public String getText();

    /**
     * Determine whether the tag has a name.  Keywords and identifiers
     * have names and thus can be replaced by macro expansion in the
     * preprocessor.  Punctuation does not have a name.
     *
     * @return true if the tag has a name.
     */
    public boolean hasName();

    /**
     * Return the preprocessor token tag.
     *
     * @return The preprocessor token tag.
     */
    public PreprocessorTag ppTag();
  }

  /** A language token. */
  public static class Language<Tag extends Enum<Tag> & LanguageTag>
    extends Syntax {

    protected final Tag tag;

    /**
     * Create a new language token.
     *
     * @param tag The tag.
     */
    public Language(Tag tag) {
      this.tag = tag;
    }

    /**
     * Create a copy of another language token.
     *
     * @param other The other language token.
     */
    protected Language(Language<Tag> other) {
      super(other);
      this.tag = other.tag;

    }

    public Language<Tag> copy() {
      return new Language<Tag>(this);
    }

    public Kind kind() {
      return Kind.LANGUAGE;
    }

    @Override
    public Language<Tag> toLanguage() {
      return this;
    }

    /**
     * Get the tag.
     *
     * @return The tag.
     */
    public Tag tag() {
      return tag;
    }

    public String getTokenText() {
      return tag.getText();
    }

    public String toString() {
      return getTokenText();
    }
  }

  /**
   * A language token with variable text, such as identifiers and
   * literals.
   */
  public static class Text<Tag extends Enum<Tag> & LanguageTag>
    extends Language<Tag> {

    private final String text;

    /**
     * Create a new text token.
     *
     * @param tag The tag.
     * @param text The text.
     */
    public Text(Tag tag, String text) {
      super(tag);
      this.text = text;
    }

    private Text(Text<Tag> other) {
      super(other);
      this.text = other.text;
    }

    public Text<Tag> copy() {
      return new Text<Tag>(this);
    }

    public Text<Tag> replaceText(String newText) {
      return new Text<Tag>(tag(),newText);
    }

    public String getTokenText() {
      return text;
    }

  }

  // --------------------------------------------------------------------------

  /** The directive tag. */
  public static enum DirectiveTag {
    IF("#if"),
    IFDEF("#ifdef"),
    IFNDEF("#ifndef"),
    ELIF("#elif"),
    ELSE("#else"),
    ENDIF("#endif"),
    INCLUDE("#include"),
    INCLUDE_NEXT("#include_next"),
    DEFINE("#define"),
    UNDEF("#undef"),
    LINE("#line"),
    LINEMARKER("#"),
    ERROR("#error"),
    WARNING("#warning"),
    PRAGMA("#pragma"),
    INVALID("#"),
    ;

    private String text;

    private DirectiveTag(String text) {
      this.text = text;
    }

    public String getText() {
      return text;
    }

  }

  /** A preprocessor directive. */
  public static class Directive extends Syntax {

    private final DirectiveTag tag;
    private final List<Language<?>> tokens;

    public Directive(DirectiveTag tag, List<Language<?>> tokens) {
      this.tag = tag;
      this.tokens = tokens;
    }

    private Directive(Directive other) {
      super(other);
      this.tag = other.tag;
      this.tokens = new ArrayList<Language<?>>(other.tokens);
    }

    public Directive copy() {
      return new Directive(this);
    }

    public Kind kind() {
      return Kind.DIRECTIVE;
    }

    public Directive toDirective() {
      return this;
    }

    public DirectiveTag tag() {
      return tag;
    }

    public int size() {
      return 1 + tokens.size();
    }

    public Object get(int index) {
      if (0 == index) {
        return tag.getText();
      } else if (1 <= index && index < size()) {
        return tokens.get(index - 1);
      } else {
        throw new IndexOutOfBoundsException("Index: " + index + 
                                            ", Size: " + tokens.size());
      }
    }

    public String getTokenText() {
      StringBuilder buf = new StringBuilder();
      buf.append(tag.getText());

      Iterator<Language<?>> iter = tokens.iterator();
      while (iter.hasNext()) {
        buf.append(' ');
        buf.append(iter.next().getTokenText());
      }

      buf.append('\n');

      return buf.toString();
    }

    public String toString() {
      return getTokenText();
    }

  }

  // --------------------------------------------------------------------------

  /** The conditional tag. */
  public static enum ConditionalTag {
    /** The start of a conditional. */
    START,
    /** The next branch of a conditional. */
    NEXT,
    /** The end of a conditional. */
    END
  }

  /**
   * A conditional.  This class provides the internal, normalized
   * representation of preprocessor conditional directives.
   */
  public static class Conditional extends Syntax {

    public final ConditionalTag tag;
    public final PresenceCondition presenceCondition;

    /**
     * Create a new conditional token with location.
     *
     * @param tag The tag.
     * @param presenceCondition The presenceCondition.
     * @param location The location.
     * @throws IllegalArgumentException Signals that the presenceCondition is
     *   not null for an end conditional.
     */
    public Conditional(ConditionalTag tag, PresenceCondition presenceCondition, Location location) {
      if (ConditionalTag.END == tag && null != presenceCondition) {
        throw new IllegalArgumentException("End conditional with presenceCondition");
      }
      this.tag = tag;
      this.presenceCondition = presenceCondition;
      this.setLocation(location);
    }

    /**
     * Create a new conditional token.
     *
     * @param tag The tag.
     * @param presenceCondition The presenceCondition.
     * @throws IllegalArgumentException Signals that the presenceCondition is
     *   not null for an end conditional.
     */
    public Conditional(ConditionalTag tag, PresenceCondition presenceCondition) {
      this(tag, presenceCondition, null);
    }

    private Conditional(Conditional other) {
      super(other);
      this.tag = other.tag;
      this.presenceCondition = other.presenceCondition.addRef();
    }

    public Conditional copy() {
      return new Conditional(this.tag, this.presenceCondition, this.getLocation());
    }

    public Kind kind() {
      return Kind.CONDITIONAL;
    }

    public Conditional toConditional() {
      return this;
    }

    /**
     * Get the tag.
     *
     * @return The tag.
     */
    public ConditionalTag tag() {
      return tag;
    }

    /**
     * Get the presenceCondition.
     *
     * @return The presenceCondition.
     * @throws IllegalStateException Signals that this conditional
     *   token terminates a conditional.
     */
    public PresenceCondition presenceCondition() {
      if (ConditionalTag.END == tag) {
        throw new IllegalStateException("End conditional has no presenceCondition");
      }
      return presenceCondition;
    }

    public String getTokenText() {
      StringBuilder sb = new StringBuilder();

      sb.append("#");
      switch (tag()) {
      case START:
        sb.append("if ");
        sb.append(presenceCondition.toString());
        break;

      case NEXT:
        sb.append("elif ");
        sb.append(presenceCondition.toString());
        break;

      case END:
        sb.append("endif");
        break;

      default:
        throw new UnsupportedOperationException("unsupported conditional tag");
      }

      sb.append("\n");

      return sb.toString();
    }

    public String toString() {
      return getTokenText();
    }
  }

  /**
   * Conditional blocks.  SuperC is stream-based, but some operations
   * require conditional blocks.  Specifically, hoisting requires
   * them.
   */
  public static class ConditionalBlock extends Syntax {
    List<List<Syntax>> branches;
    List<PresenceCondition> presenceConditions;
    
    public ConditionalBlock(List<List<Syntax>> branches,
                            List<PresenceCondition> presenceConditions,
                            Location location) {
      this.branches = branches;
      this.presenceConditions = presenceConditions;
      for (PresenceCondition presenceCondition : presenceConditions) {
        presenceCondition.addRef();
      }
      this.setLocation(location);
    }
    
    public ConditionalBlock(List<List<Syntax>> branches,
                            List<PresenceCondition> presenceConditions) {
      this(branches, presenceConditions, null);
    }
    
    public ConditionalBlock(ConditionalBlock c) {
      super(c);
      this.branches = c.branches;
      this.presenceConditions = c.presenceConditions;
      for (PresenceCondition presenceCondition : presenceConditions) {
        presenceCondition.addRef();
      }
    }
    
    /**
     * Free the conditional presenceConditions contained in this block.  This is
     * necessary because the implementation of conditional presenceConditions is
     * reference-counting BDDs.
     */
    public void free() {
      branches.clear();
      for (PresenceCondition c : presenceConditions) {
        c.delRef();
      }
    }

    public Syntax copy() {
      return new ConditionalBlock(this);
    }

    public Kind kind() {
      return Kind.CONDITIONAL_BLOCK;
    }

    public String getTokenText() {
      return "CONDITIONAL_BLOCK" + branches;
    }
  }

  public static enum ErrorType {
    ERROR,
    FATAL,
    WARNING
  }

  public static class Error extends Syntax {
    public final String message;
    public final ErrorType type;

    public Error(String message, ErrorType type) {
      this.message = message;
      this.type = type;
    }

    public Error(String message, boolean fatal) {
      this(message, fatal ? ErrorType.FATAL : ErrorType.ERROR);
    }

    public Syntax copy() {
      throw new UnsupportedOperationException();
    }

    public Kind kind() {
      return Kind.ERROR;
    }

    public String getTokenText() {
      StringBuilder sb = new StringBuilder();

      sb.append("#error ");
      sb.append(message);
      sb.append("\n");

      return sb.toString();
    }

    public Error toError() {
      return this;
    }

    public String toString() {
      return this.getTokenText();
    }
  }

  public static class EOF extends Syntax {
    public Syntax copy() {
      throw new UnsupportedOperationException();
    }

    public Kind kind() {
      return Kind.EOF;
    }

    public String getTokenText() {
      return "EOF";
    }
  }
}
