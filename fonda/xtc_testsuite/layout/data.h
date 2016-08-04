/*
 * xtc - The eXTensible Compiler
 * Copyright (C) 2007 Robert Grimm
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

typedef _Bool B;
typedef char C;
typedef signed char SC;
typedef unsigned char UC;
typedef short S;
typedef unsigned short US;
typedef int I;
typedef unsigned int UI;
typedef long L;
typedef unsigned long UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef float F;
typedef double D;
typedef long double LD;

typedef _Bool AB[3];
typedef char AC[3];
typedef signed char ASC[3];
typedef unsigned char AUC[3];
typedef short AS[3];
typedef unsigned short AUS[3];
typedef int AI[3];
typedef unsigned int AUI[3];
typedef long AL[3];
typedef unsigned long AUL[3];
typedef long long ALL[3];
typedef unsigned long long AULL[3];
typedef float AF[3];
typedef double AD[3];
typedef long double ALD[3];

typedef struct {
  _Bool a : 1;
} BFB;

typedef struct __attribute__((packed)) {
  _Bool a : 1;
} BFBP;

typedef struct {
  char a : 1;
} BFC;

typedef struct __attribute__((packed)) {
  char a : 1;
} BFCP;

typedef struct {
  short a : 1;
} BFS;

typedef struct __attribute__((packed)) {
  short a : 1;
} BFSP;

typedef struct {
  int a : 1;
} BFI;

typedef struct __attribute__((packed)) {
  int a : 1;
} BFIP;

typedef struct {
  long a : 1;
} BFL;

typedef struct __attribute__((packed)) {
  long a : 1;
} BFLP;

typedef struct {
  long a : 1;
} BFLL;

typedef struct __attribute__((packed)) {
  long long a : 1;
} BFLLP;

typedef struct __attribute__((aligned(1024))) {
  _Bool b;
} SBA1024;

typedef struct __attribute__((aligned(1024))) {
  _Bool __attribute__((aligned(2048))) b;
} SBA2048;

typedef struct {
  int a : 31;
  int b : 1;
  int c : 31;
  int d : 1;
} BF1;

typedef struct __attribute__((packed)) {
  int a : 31;
  int b : 1;
  int c : 31;
  int d : 1;
} BF1P;

typedef struct {
  int a : 31;
  int b : 31;
  int c : 1;
  int d : 1;
} BF2;

typedef struct __attribute__((packed)) {
  int a : 31;
  int b : 31;
  int c : 1;
  int d : 1;
} BF2P;

typedef struct {
  char a : 7;
  int  b : 31;
  char c : 2;
} BF3;

typedef struct __attribute__((packed)) {
  char a : 7;
  int  b : 31;
  char c : 2;
} BF3P;

typedef struct {
  int a : 8;
  int b : 8;
  int c : 8;
  char : 0;
  int d : 8;
  int e : 8;
} BF4;

typedef struct __attribute__((packed)) {
  int a : 8;
  int b : 8;
  int c : 8;
  char : 0;
  int d : 8;
  int e : 8;
} BF4P;

typedef struct {
  int a : 8;
  int b : 8;
  int c : 8;
  int : 0;
  int d : 31;
  int e : 2;
} BF5;

typedef struct __attribute__((packed)) {
  int a : 8;
  int b : 8;
  int c : 8;
  int : 0;
  int d : 31;
  int e : 2;
} BF5P;

typedef struct {
  int a : 31;
  int b : 9;
  char : 0;
  short c;
} BF6;

typedef struct __attribute__((packed)) {
  int a : 31;
  int b : 9;
  char : 0;
  short c;
} BF6P;

typedef struct {
  int a : 31;
  int b : 9;
  int : 0;
  short c;
} BF7;

typedef struct __attribute__((packed)) {
  int a : 31;
  int b : 9;
  int : 0;
  short c;
} BF7P;

typedef struct {
  char a : 7;
  char b : 7;
  int : 0;
  short c;
} BF8;

typedef struct __attribute__((packed)) {
  char a : 7;
  char b : 7;
  int : 0;
  short c;
} BF8P;

typedef struct {
  char a;
  char b;
  int : 0;
  short c;
} BF9;

typedef struct __attribute__((packed)) {
  char a;
  char b;
  int : 0;
  short c;
} BF9P;

typedef struct {
  char a : 1;
  int b : 2;
  char : 0;
} BF10;

typedef struct __attribute__((packed)) {
  char a : 1;
  int b : 2;
  char : 0;
} BF10P;

typedef struct {
  char a : 1;
  char b : 2;
  char : 0;
} BF11;

typedef struct __attribute__((packed)) {
  char a : 1;
  char b : 2;
  char : 0;
} BF11P;

typedef struct {
  char a : 1;
  char b : 2;
  int : 0;
} BF12;

typedef struct __attribute__((packed)) {
  char a : 1;
  char b : 2;
  int : 0;
} BF12P;

typedef struct {
  char a : 1;
  int b : 8;
} BF13;

typedef struct __attribute__((packed)) {
  char a : 1;
  int b : 8;
} BF13P;

typedef struct {
  int a : 31;
  int b : 31;
  int : 0;
  int c : 2;
} BF14;

typedef struct __attribute__((packed)) {
  int a : 31;
  int b : 31;
  int : 0;
  int c : 2;
} BF14P;

typedef struct {
  char a : 1;
  long long : 0;
} BF15;

typedef struct __attribute__((packed)) {
  char a : 1;
  long long : 0;
} BF15P;

typedef struct {
  char a;
  short b;
  char c;
  int d;
  char e;
  long f;
  char g;
  long long h;
  char i;
  float j;
  char k;
  double l;
  char m;
  long double n;
} S1;

typedef struct __attribute__((packed)) {
  char a;
  short b;
  char c;
  int d;
  char e;
  long f;
  char g;
  long long h;
  char i;
  float j;
  char k;
  double l;
  char m;
  long double n;
} S1P;

typedef struct {
  long double a;
  char b;
  double c;
  char d;
  float e;
  char f;
  long long g;
  char h;
  long i;
  char j;
  int k;
  char l;
  short m;
  char n;
} S2;

typedef struct __attribute__((packed)) {
  long double a;
  char b;
  double c;
  char d;
  float e;
  char f;
  long long g;
  char h;
  long i;
  char j;
  int k;
  char l;
  short m;
  char n;
} S2P;

typedef struct {
  long double a[3];
  char b;
} S3;

typedef struct __attribute__((packed)) {
  long double a[3];
  char b;
} S3P;

typedef struct {
  char a[3];
  union {
    char b[3];
    struct {
      short c;
      char d[3];
    };
  };
  union {
    char a[3];
    struct {
      short a;
      S3 b[3];
    } b;
  } e;
  char f;
} S4;

typedef struct {
  char a[3];
  union {
    char b[3];
    struct {
      short c;
      char d[3];
    };
  };
  union {
    char a[3];
    struct {
      short a;
      S3P b[3];
    } b;
  } e;
  char f;
} S4P;
