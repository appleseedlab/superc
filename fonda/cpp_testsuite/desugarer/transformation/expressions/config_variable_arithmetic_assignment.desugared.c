#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_22;
extern const bool __static_condition_default_25;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_26;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_28;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_24;
extern const bool __static_condition_default_27;
extern const bool __static_condition_default_21;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__y_4", "y");

__static_condition_renaming("__static_condition_default_5", "A");
__static_condition_renaming("__static_condition_default_6", "!A");
__static_condition_renaming("__static_condition_default_7", "B");
__static_condition_renaming("__static_condition_default_8", "!B");
__static_condition_renaming("__static_condition_default_9", "A && B");
__static_condition_renaming("__static_condition_default_10", "A && !B");
__static_condition_renaming("__static_condition_default_11", "!A && B");
__static_condition_renaming("__static_condition_default_12", "!A && !B");
__static_condition_renaming("__static_condition_default_13", "A && B");
__static_condition_renaming("__static_condition_default_14", "A && !B");
__static_condition_renaming("__static_condition_default_15", "!A && B");
__static_condition_renaming("__static_condition_default_16", "!A && !B");
__static_condition_renaming("__static_condition_default_17", "A && B");
__static_condition_renaming("__static_condition_default_18", "A && !B");
__static_condition_renaming("__static_condition_default_19", "!A && B");
__static_condition_renaming("__static_condition_default_20", "!A && !B");
__static_condition_renaming("__static_condition_default_21", "A && B");
__static_condition_renaming("__static_condition_default_22", "A && !B");
__static_condition_renaming("__static_condition_default_23", "!A && B");
__static_condition_renaming("__static_condition_default_24", "!A && !B");
__static_condition_renaming("__static_condition_default_25", "A && B");
__static_condition_renaming("__static_condition_default_26", "A && !B");
__static_condition_renaming("__static_condition_default_27", "!A && B");
__static_condition_renaming("__static_condition_default_28", "!A && !B");

};

int  __main_0 (void  ) {
{
int  __x_1;
char  __x_2;
int  __y_3;
char  __y_4;

{
if (__static_condition_default_5) {
 __x_1  = 1 ;

}

if (__static_condition_default_6) {
 __x_2  = 1 ;

}

}
{
if (__static_condition_default_7) {
 __y_3  = 2 ;

}

if (__static_condition_default_8) {
 __y_4  = 2 ;

}

}
{
if (__static_condition_default_9) {
 __x_1  +=  __y_3  ;

}

if (__static_condition_default_10) {
 __x_1  +=  __y_4  ;

}

if (__static_condition_default_11) {
 __x_2  +=  __y_3  ;

}

if (__static_condition_default_12) {
 __x_2  +=  __y_4  ;

}

}
{
if (__static_condition_default_13) {
 __x_1  -=  __y_3  ;

}

if (__static_condition_default_14) {
 __x_1  -=  __y_4  ;

}

if (__static_condition_default_15) {
 __x_2  -=  __y_3  ;

}

if (__static_condition_default_16) {
 __x_2  -=  __y_4  ;

}

}
{
if (__static_condition_default_17) {
 __x_1  *=  __y_3  ;

}

if (__static_condition_default_18) {
 __x_1  *=  __y_4  ;

}

if (__static_condition_default_19) {
 __x_2  *=  __y_3  ;

}

if (__static_condition_default_20) {
 __x_2  *=  __y_4  ;

}

}
{
if (__static_condition_default_21) {
 __x_1  /=  __y_3  ;

}

if (__static_condition_default_22) {
 __x_1  /=  __y_4  ;

}

if (__static_condition_default_23) {
 __x_2  /=  __y_3  ;

}

if (__static_condition_default_24) {
 __x_2  /=  __y_4  ;

}

}
{
if (__static_condition_default_25) {
 __x_1  %=  __y_3  ;

}

if (__static_condition_default_26) {
 __x_1  %=  __y_4  ;

}

if (__static_condition_default_27) {
 __x_2  %=  __y_3  ;

}

if (__static_condition_default_28) {
 __x_2  %=  __y_4  ;

}

}return 0 ;

}


}
