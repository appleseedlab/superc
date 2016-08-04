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
package xtc.util;

import java.util.Arrays;

/**
 * Unit tests for utilities.
 *
 * @author Robert Grimm
 * @version $Revision: 1.5 $
 */
public class UtilitiesTest extends junit.framework.TestCase {

  /** Create a new test class. */
  public UtilitiesTest() { /* Nothing to do. */ }

  /** Test {@link Utilities#isQualified(String)}. */
  public void testIsQualified() {
    assertFalse(Utilities.isQualified(""));
    assertFalse(Utilities.isQualified("a"));
    assertFalse(Utilities.isQualified("aa"));
    assertFalse(Utilities.isQualified("aaa"));
    assertFalse(Utilities.isQualified("a()"));
    assertFalse(Utilities.isQualified("a(a)"));
    assertFalse(Utilities.isQualified("a(.)"));
    assertFalse(Utilities.isQualified("a(..)"));
    assertFalse(Utilities.isQualified("a(...)"));
    assertFalse(Utilities.isQualified("a(...)()"));
    assertFalse(Utilities.isQualified("a(...)(.)"));
    assertFalse(Utilities.isQualified("a(...)(..)"));
    assertFalse(Utilities.isQualified("a(...)(...)"));
    assertTrue(Utilities.isQualified("."));
    assertTrue(Utilities.isQualified("a."));
    assertTrue(Utilities.isQualified(".b"));
    assertTrue(Utilities.isQualified("a.b"));
    assertTrue(Utilities.isQualified("aa.bb"));
    assertTrue(Utilities.isQualified("aaa.bbb"));
    assertTrue(Utilities.isQualified("().()"));
    assertTrue(Utilities.isQualified("()().()()"));
    assertTrue(Utilities.isQualified("()()().()()()"));
    assertTrue(Utilities.isQualified("aaa.bbb."));
    assertTrue(Utilities.isQualified(".aaa.bbb"));
  }

  /** Test {@link Utilities#getQualifier(String)}. */
  public void testGetQualifier() {
    assertNull(Utilities.getQualifier(""));
    assertNull(Utilities.getQualifier("a"));
    assertNull(Utilities.getQualifier("aa"));
    assertNull(Utilities.getQualifier("aaa"));
    assertEquals("", Utilities.getQualifier("."));
    assertEquals("", Utilities.getQualifier(".a"));
    assertEquals("", Utilities.getQualifier(".aa"));
    assertEquals("", Utilities.getQualifier(".aaa"));
    assertEquals(".", Utilities.getQualifier("..a"));
    assertEquals("..", Utilities.getQualifier("...aa"));
    assertEquals("...", Utilities.getQualifier("....aa"));
    assertEquals("..(.)", Utilities.getQualifier("..(.).aa"));
    assertEquals("..", Utilities.getQualifier("...(.)"));
    assertEquals("..", Utilities.getQualifier("...(.)a"));
    assertEquals("..", Utilities.getQualifier("...(.)aa"));
    assertEquals("..", Utilities.getQualifier("...(.)(.)"));
    assertEquals("..", Utilities.getQualifier("...(.)(.)a"));
  }

  /** Test {@link Utilities#getName(String)}. */
  public void testGetName() {
    assertEquals("", Utilities.getName(""));
    assertEquals("a", Utilities.getName("a"));
    assertEquals("aa", Utilities.getName("aa"));
    assertEquals("aaa", Utilities.getName("aaa"));
    assertEquals("", Utilities.getName("."));
    assertEquals("", Utilities.getName("a."));
    assertEquals("", Utilities.getName("aa."));
    assertEquals("", Utilities.getName("aaa."));
    assertEquals("a", Utilities.getName(".a"));
    assertEquals("aa", Utilities.getName(".aa"));
    assertEquals("aaa", Utilities.getName(".aaa"));
    assertEquals("aaa", Utilities.getName("..aaa"));
    assertEquals("aaa", Utilities.getName("...aaa"));
    assertEquals("(.)", Utilities.getName("..(.)"));
    assertEquals("(.)a", Utilities.getName("..(.)a"));
    assertEquals("(.)aa", Utilities.getName("..(.)aa"));
    assertEquals("(.)aaa", Utilities.getName("..(.)aaa"));
    assertEquals("(..)aaa", Utilities.getName(".(..)aaa"));
    assertEquals("()", Utilities.getName("..()"));
    assertEquals("()()", Utilities.getName("..()()"));
    assertEquals("(.)(.)", Utilities.getName("..(.)(.)"));
  }

  /**
   * Test {@link Utilities#toIdentifier(String)}.  Note that {@link
   * Utilities#toPath(String)} and {@link
   * Utilities#toPath(String,String)} build on the same internal
   * helper method.
   */
  public void testToIdentifier() {
    assertEquals("", Utilities.toIdentifier(""));
    assertEquals("$", Utilities.toIdentifier("."));
    assertEquals("$$", Utilities.toIdentifier(".."));
    assertEquals("$$$", Utilities.toIdentifier("..."));
    assertEquals("$a", Utilities.toIdentifier(".a"));
    assertEquals("$$a", Utilities.toIdentifier("..a"));
    assertEquals("$$$a", Utilities.toIdentifier("...a"));
    assertEquals("a$", Utilities.toIdentifier("a."));
    assertEquals("a$$", Utilities.toIdentifier("a.."));
    assertEquals("a$$$", Utilities.toIdentifier("a..."));
    assertEquals("a$a", Utilities.toIdentifier("a.a"));
    assertEquals("a$$a", Utilities.toIdentifier("a..a"));
    assertEquals("a$$$a", Utilities.toIdentifier("a...a"));
    assertEquals("$aa", Utilities.toIdentifier(".aa"));
    assertEquals("aa$", Utilities.toIdentifier("aa."));
    assertEquals("aa$aa", Utilities.toIdentifier("aa.aa"));
    assertEquals("$aaa", Utilities.toIdentifier(".aaa"));
    assertEquals("aaa$", Utilities.toIdentifier("aaa."));
    assertEquals("aaa$aaa", Utilities.toIdentifier("aaa.aaa"));
    assertEquals("()", Utilities.toIdentifier("()"));
    assertEquals("(.)", Utilities.toIdentifier("(.)"));
    assertEquals("(.)(.)", Utilities.toIdentifier("(.)(.)"));
    assertEquals("$(.)(.)", Utilities.toIdentifier(".(.)(.)"));
    assertEquals("(.)$(.)", Utilities.toIdentifier("(.).(.)"));
    assertEquals("(.)(.)$", Utilities.toIdentifier("(.)(.)."));
  }

  /** Test {@link Utilities#toComponents(String)}. */
  public void testToComponents() {
    assertTrue(Arrays.equals(new String[] { "" },
                             Utilities.toComponents("")));
    assertTrue(Arrays.equals(new String[] { "a" },
                             Utilities.toComponents("a")));
    assertTrue(Arrays.equals(new String[] { "aa" },
                             Utilities.toComponents("aa")));
    assertTrue(Arrays.equals(new String[] { "aaa" },
                             Utilities.toComponents("aaa")));
    assertTrue(Arrays.equals(new String[] { "()" },
                             Utilities.toComponents("()")));
    assertTrue(Arrays.equals(new String[] { "(.)" },
                             Utilities.toComponents("(.)")));
    assertTrue(Arrays.equals(new String[] { "(.)(.)" },
                             Utilities.toComponents("(.)(.)")));
    assertTrue(Arrays.equals(new String[] { "", "" },
                             Utilities.toComponents(".")));
    assertTrue(Arrays.equals(new String[] { "", "", "" },
                             Utilities.toComponents("..")));
    assertTrue(Arrays.equals(new String[] { "", "", "", "" },
                             Utilities.toComponents("...")));
    assertTrue(Arrays.equals(new String[] { "a", "" },
                             Utilities.toComponents("a.")));
    assertTrue(Arrays.equals(new String[] { "", "a" },
                             Utilities.toComponents(".a")));
    assertTrue(Arrays.equals(new String[] { "a", "a" },
                             Utilities.toComponents("a.a")));
    assertTrue(Arrays.equals(new String[] { "a", "a", "a" },
                             Utilities.toComponents("a.a.a")));
    assertTrue(Arrays.equals(new String[] { "a", "a", "a", "a" },
                             Utilities.toComponents("a.a.a.a")));
  }

  /** Test {@link Pair#append(Pair)} and {@link Pair#setLastTail(Pair)}. */
  public void testAppendix() {
    Pair<Integer> l1 = Pair.empty();
    l1 = new Pair<Integer>(2, l1);
    l1 = new Pair<Integer>(1, l1);

    Pair<Integer> l2 = Pair.empty();
    l2 = new Pair<Integer>(4, l2);
    l2 = new Pair<Integer>(3, l2);

    Pair<Integer> l3 = Pair.empty();
    l3 = new Pair<Integer>(4, l3);
    l3 = new Pair<Integer>(3, l3);
    l3 = new Pair<Integer>(2, l3);
    l3 = new Pair<Integer>(1, l3);

    Pair<Integer> l4 = Pair.empty();
    l4 = new Pair<Integer>(2, l4);
    l4 = new Pair<Integer>(1, l4);

    Pair<Integer> l5 = l1.append(l2);
    assertTrue(l5 != l1);
    assertTrue(l5.equals(l3));
    assertTrue(l1.equals(l4));

    l1.setLastTail(l2);
    assertTrue(l1.equals(l3));
  }

}
