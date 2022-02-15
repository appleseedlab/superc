SuperC, v. 2.4.0, (C) 2009-2012 New York University
Portions Copyright (c) 1989, 1990 James A. Roskind
Processing implicit_param.c ...
void * __type_error(char *message); /* this method should halt */
#include <stdbool.h>
extern bool _C_65; /* renamed from A */
extern bool _C_65_DEFINED;
typedef signed int  __a_0;
typedef unsigned int  __a_1;

// typedef moved to top of scope
// typedef moved to top of scope
int  __foo_4 (__a_0 __x_2) {


{
if (_C_65_DEFINED) {
 __x_2  ++ ;
}

if (!_C_65_DEFINED) {
 __x_3  ++ ;
}

}
{
if (_C_65_DEFINED) {
 return __x_2  ;
}

if (!_C_65_DEFINED) {
 return __x_3  ;
}

}
}

int  __foo_5 (__a_1 __x_3) {


{
if (_C_65_DEFINED) {
 __x_2  ++ ;
}

if (!_C_65_DEFINED) {
 __x_3  ++ ;
}

}
{
if (_C_65_DEFINED) {
 return __x_2  ;
}

if (!_C_65_DEFINED) {
 return __x_3  ;
}

}
}

int  __main_7 () {

int  __z_6;

{
if (_C_65_DEFINED) {
 __z_6  = __foo_4  ( 1 ) ;
}

if (!_C_65_DEFINED) {
 __z_6  = __foo_5  ( 1 ) ;
}

} return __z_6  ;

}

