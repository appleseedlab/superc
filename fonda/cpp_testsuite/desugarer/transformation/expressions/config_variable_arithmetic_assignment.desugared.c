#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_21;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_24;
extern const bool __static_condition_default_28;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_23;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_26;
extern const bool __static_condition_default_27;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_11;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_22;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_25;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_17;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__y_4", "y");

__static_condition_renaming("__static_condition_default_5", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))");
__static_condition_renaming("__static_condition_default_6", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))");
__static_condition_renaming("__static_condition_default_7", "(declare-fun B () Bool)(assert B)");
__static_condition_renaming("__static_condition_default_8", "(declare-fun B () Bool)(assert (not B))");
__static_condition_renaming("__static_condition_default_9", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_10", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_11", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_12", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_13", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_14", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_15", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_16", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_17", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_18", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_19", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_20", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_21", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_22", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_23", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_24", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_25", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_26", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (or (and A B) (and A (not B))))(assert (not B))");
__static_condition_renaming("__static_condition_default_27", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert B)");
__static_condition_renaming("__static_condition_default_28", "(declare-fun B () Bool)(declare-fun A () Bool)(assert (not (and A B)))(assert (not (and A (not B))))(assert (not B))");

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

