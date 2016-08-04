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
package xtc.lang.cpp;

/** This class's purpose is to provide the built-in macros and system includes.
  */
public class Builtins {
  /** The system include directories */
  public static String[] sysdirs = { "/usr/llvm-gcc-4.2/bin/../lib/gcc/i686-apple-darwin11/4.2.1/include", "/usr/local/include", "/Applications/Xcode.app/Contents/Developer/usr/llvm-gcc-4.2/lib/gcc/i686-apple-darwin11/4.2.1/include", "/usr/include", "/System/Library/Frameworks", "/Library/Frameworks" };

  /** A string containing the built-in macro definitions */
  public static final String builtin =
    "#define __DBL_MIN_EXP__ (-1021)\n" +
    "#define __FLT_MIN__ 1.17549435e-38F\n" +
    "#define __DEC64_DEN__ 0.000000000000001E-383DD\n" +
    "#define __CHAR_BIT__ 8\n" +
    "#define __WCHAR_MAX__ 2147483647\n" +
    "#define __NO_MATH_INLINES 1\n" +
    "#define __DBL_DENORM_MIN__ 4.9406564584124654e-324\n" +
    "#define __FLT_EVAL_METHOD__ 0\n" +
    "#define __DBL_MIN_10_EXP__ (-307)\n" +
    "#define __FINITE_MATH_ONLY__ 0\n" +
    "#define __DEC64_MAX_EXP__ 384\n" +
    "#define __SHRT_MAX__ 32767\n" +
    "#define __LDBL_MAX__ 1.18973149535723176502e+4932L\n" +
    "#define __APPLE_CC__ 5658\n" +
    "#define __UINTMAX_TYPE__ long unsigned int\n" +
    "#define __DEC32_EPSILON__ 1E-6DF\n" +
    "#define __block __attribute__((__blocks__(byref)))\n" +
    "#define __SCHAR_MAX__ 127\n" +
    "#define __USER_LABEL_PREFIX__ _\n" +
    "#define __STDC_HOSTED__ 1\n" +
    "#define __DEC64_MIN_EXP__ (-383)\n" +
    "#define __DBL_DIG__ 15\n" +
    "#define __FLT_EPSILON__ 1.19209290e-7F\n" +
    "#define __LDBL_MIN__ 3.36210314311209350626e-4932L\n" +
    "#define __DEC32_MAX__ 9.999999E96DF\n" +
    "#define __strong \n" +
    "#define __APPLE__ 1\n" +
    "#define __DECIMAL_DIG__ 21\n" +
    "#define __LDBL_HAS_QUIET_NAN__ 1\n" +
    "#define __DYNAMIC__ 1\n" +
    "#define __GNUC__ 4\n" +
    "#define __MMX__ 1\n" +
    "#define __FLT_HAS_DENORM__ 1\n" +
    "#define __DBL_MAX__ 1.7976931348623157e+308\n" +
    "#define __DBL_HAS_INFINITY__ 1\n" +
    "#define __DEC32_MIN_EXP__ (-95)\n" +
    "#define OBJC_NEW_PROPERTIES 1\n" +
    "#define __LDBL_HAS_DENORM__ 1\n" +
    "#define __DEC32_MIN__ 1E-95DF\n" +
    "#define __weak __attribute__((objc_gc(weak)))\n" +
    "#define __DBL_MAX_EXP__ 1024\n" +
    "#define __DEC128_EPSILON__ 1E-33DL\n" +
    "#define __SSE2_MATH__ 1\n" +
    "#define __amd64 1\n" +
    "#define __tune_core2__ 1\n" +
    "#define __LONG_LONG_MAX__ 9223372036854775807LL\n" +
    "#define __GXX_ABI_VERSION 1002\n" +
    "#define __FLT_MIN_EXP__ (-125)\n" +
    "#define __x86_64 1\n" +
    "#define __DBL_MIN__ 2.2250738585072014e-308\n" +
    "#define __LP64__ 1\n" +
    "#define __DBL_HAS_QUIET_NAN__ 1\n" +
    "#define __DEC128_MIN__ 1E-6143DL\n" +
    "#define __REGISTER_PREFIX__ \n" +
    "#define __DBL_HAS_DENORM__ 1\n" +
    "#define __NO_INLINE__ 1\n" +
    "#define __DEC_EVAL_METHOD__ 2\n" +
    "#define __DEC128_MAX__ 9.999999999999999999999999999999999E6144DL\n" +
    "#define __FLT_MANT_DIG__ 24\n" +
    "#define __VERSION__ \"4.2.1 (Based on Apple Inc. build 5658) (LLVM build 2336.9.00)\"\n" +
    "#define __DEC64_EPSILON__ 1E-15DD\n" +
    "#define __DEC128_MIN_EXP__ (-6143)\n" +
    "#define __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ 1073\n" +
    "#define __SIZE_TYPE__ long unsigned int\n" +
    "#define __DEC32_DEN__ 0.000001E-95DF\n" +
    "#define __FLT_RADIX__ 2\n" +
    "#define __LDBL_EPSILON__ 1.08420217248550443401e-19L\n" +
    "#define __SSE_MATH__ 1\n" +
    "#define __k8 1\n" +
    "#define __LDBL_DIG__ 18\n" +
    "#define __x86_64__ 1\n" +
    "#define __FLT_HAS_QUIET_NAN__ 1\n" +
    "#define __FLT_MAX_10_EXP__ 38\n" +
    "#define __LONG_MAX__ 9223372036854775807L\n" +
    "#define __FLT_HAS_INFINITY__ 1\n" +
    "#define __DEC64_MAX__ 9.999999999999999E384DD\n" +
    "#define __DEC64_MANT_DIG__ 16\n" +
    "#define __DEC32_MAX_EXP__ 96\n" +
    "#define __DEC128_DEN__ 0.000000000000000000000000000000001E-6143DL\n" +
    "#define __LITTLE_ENDIAN__ 1\n" +
    "#define __LDBL_MANT_DIG__ 64\n" +
    "#define __CONSTANT_CFSTRINGS__ 1\n" +
    "#define __DEC32_MANT_DIG__ 7\n" +
    "#define __k8__ 1\n" +
    "#define __WCHAR_TYPE__ int\n" +
    "#define __pic__ 2\n" +
    "#define __FLT_DIG__ 6\n" +
    "#define __INT_MAX__ 2147483647\n" +
    "#define __FLT_MAX_EXP__ 128\n" +
    "#define __BLOCKS__ 1\n" +
    "#define __DBL_MANT_DIG__ 53\n" +
    "#define __DEC64_MIN__ 1E-383DD\n" +
    "#define __WINT_TYPE__ int\n" +
    "#define __SSE__ 1\n" +
    "#define __LDBL_MIN_EXP__ (-16381)\n" +
    "#define __MACH__ 1\n" +
    "#define __amd64__ 1\n" +
    "#define __LDBL_MAX_EXP__ 16384\n" +
    "#define __SSP__ 1\n" +
    "#define __LDBL_MAX_10_EXP__ 4932\n" +
    "#define __DBL_EPSILON__ 2.2204460492503131e-16\n" +
    "#define _LP64 1\n" +
    "#define __GNUC_PATCHLEVEL__ 1\n" +
    "#define __LDBL_HAS_INFINITY__ 1\n" +
    "#define __INTMAX_MAX__ 9223372036854775807L\n" +
    "#define __FLT_DENORM_MIN__ 1.40129846e-45F\n" +
    "#define __PIC__ 2\n" +
    "#define __FLT_MAX__ 3.40282347e+38F\n" +
    "#define __SSE2__ 1\n" +
    "#define __FLT_MIN_10_EXP__ (-37)\n" +
    "#define __INTMAX_TYPE__ long int\n" +
    "#define __DEC128_MAX_EXP__ 6144\n" +
    "#define __GNUC_MINOR__ 2\n" +
    "#define __DBL_MAX_10_EXP__ 308\n" +
    "#define __LDBL_DENORM_MIN__ 3.64519953188247460253e-4951L\n" +
    "#define __STDC__ 1\n" +
    "#define __PTRDIFF_TYPE__ long int\n" +
    "#define __DEC128_MANT_DIG__ 34\n" +
    "#define __LDBL_MIN_10_EXP__ (-4931)\n" +
    "#define __llvm__ 1\n" +
    "#define __GNUC_GNU_INLINE__ 1\n" +
    "#define __SSE3__ 1\n" +
    "";
    public static void main(String[] args) {
      System.out.println(builtin);
    }
}
