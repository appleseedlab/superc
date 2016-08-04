/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007-2009 Robert Grimm
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

#define stringify(s) xstringify(s)
#define xstringify(s) #s

#define offset1(type, member) \
  (unsigned long)((__SIZE_TYPE__)(&((type *)0)->member))
#define offset2(type, member) \
  (unsigned long)__builtin_offsetof(type, member)

#define offset_sym(alias, desc) alias ## _ ## desc ## _OFFSET

#define bug_on(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#define def(alias)                                                      \
  printf("#define " stringify(alias ## _SIZE) " %lu\n",                 \
         (unsigned long)sizeof(alias));                                 \
  printf("#define " stringify(alias ## _ALIGN) " %lu\n", \
         (unsigned long)__alignof(alias))

#define test(alias)                             \
  bug_on(alias ## _SIZE != sizeof(alias));      \
  bug_on(alias ## _ALIGN != __alignof(alias))

#define def_offset(alias, desc, member)                         \
  printf("#define " stringify(offset_sym(alias, desc)) " %lu\n", \
         offset1(alias, member))

#define test_offset(alias, desc, member)                        \
  bug_on(offset_sym(alias, desc) != offset1(alias, member));    \
  bug_on(offset_sym(alias, desc) != offset2(alias, member))
