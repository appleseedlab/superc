#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_12;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_16;
void __static_initializer_default() {
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__x_3", "x");
__static_renaming("__x_4", "x");
__static_renaming("__b_5", "b");
__static_renaming("__main_11", "main");

__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined B)| () Bool)(assert |(defined B)|)");
__static_condition_renaming("__static_condition_default_7", "(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (not |(defined B)|))(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_8", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (not (and (not |(defined B)|) |(defined A)|)))(assert (not |(defined B)|))(assert (not |(defined A)|))");
__static_condition_renaming("__static_condition_default_9", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (not (and (not |(defined B)|) |(defined A)|)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))  (not a!1)))(assert |(defined B)|)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_10", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (not (and (not |(defined B)|) |(defined A)|)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))  (not a!1)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))  (not a!2))))(assert |(defined B)|)");
__static_condition_renaming("__static_condition_default_12", "(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (not |(defined B)|))(assert |(defined A)|)(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))  (not a!1)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))  (not a!2))))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))(let ((a!3 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                (not a!2))))  (not a!3)))))");
__static_condition_renaming("__static_condition_default_13", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (not (and (not |(defined B)|) |(defined A)|)))(assert (not |(defined B)|))(assert (not |(defined A)|))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))  (not a!2))))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))(let ((a!3 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                (not a!2))))  (not a!3)))))");
__static_condition_renaming("__static_condition_default_14", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (not (and (not |(defined B)|) |(defined A)|)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))  (not a!1)))(assert |(defined B)|)(assert |(defined A)|)(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))(let ((a!3 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                (not a!2))))  (not a!3)))))");
__static_condition_renaming("__static_condition_default_15", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (not (and (not |(defined B)|) |(defined A)|)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))  (not a!1)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))  (not a!2))))");
__static_condition_renaming("__static_condition_default_16", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (not (and (not |(defined B)|) |(defined A)|)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))  (not a!1)))(assert |(defined B)|)(assert |(defined A)|)(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))(let ((a!3 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                (not a!2))))  (not a!3)))))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))(let ((a!3 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                (not a!2))))  (not (and (not |(defined B)|) |(defined A)| (not a!1) (not a!2) (not a!3)))))))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))(let ((a!3 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                (not a!2))))(let ((a!4 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|)                (not a!2)                (not a!3))))  (not a!4))))))");
__static_condition_renaming("__static_condition_default_17", "(declare-fun |(defined A)| () Bool)(declare-fun |(defined B)| () Bool)(assert (not (and (not |(defined B)|) |(defined A)|)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))  (not a!1)))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))  (not a!2))))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))(let ((a!3 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                (not a!2))))  (not (and (not |(defined B)|) |(defined A)| (not a!1) (not a!2) (not a!3)))))))(assert (let ((a!1 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|))))(let ((a!2 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                |(defined B)|                |(defined A)|)))(let ((a!3 (and (not (and (not |(defined B)|) |(defined A)|))                (not a!1)                (not a!2))))(let ((a!4 (and (not (and (not |(defined B)|) |(defined A)|))                (not |(defined B)|)                (not |(defined A)|)                (not a!2)                (not a!3))))  (not a!4))))))");

};

int  __x_1 () {

if (__static_condition_default_7) {
{
int  __b_5= 1;

if (__static_condition_default_6) {
 __b_5  =  __b_5  +  __y_0  ;

}
return  __b_5  ;

}

}

}
char  __x_2 () {

if (__static_condition_default_8) {
{
int  __b_5= 1;

if (__static_condition_default_6) {
 __b_5  =  __b_5  +  __y_0  ;

}
return  __b_5  ;

}

}

}
int  __x_3 (int  __y_0) {

if (__static_condition_default_9) {
{
int  __b_5= 1;

if (__static_condition_default_6) {
 __b_5  =  __b_5  +  __y_0  ;

}
return  __b_5  ;

}

}

}
char  __x_4 (int  __y_0) {

if (__static_condition_default_10) {
{
int  __b_5= 1;

if (__static_condition_default_6) {
 __b_5  =  __b_5  +  __y_0  ;

}
return  __b_5  ;

}

}

}
int  __main_11 () {
{

{
if (__static_condition_default_12) {
 __x_1  ( ) ;

}

if (__static_condition_default_13) {
 __x_2  ( ) ;

}

if (__static_condition_default_14) {
 __x_3  ( ) ;

}

if (__static_condition_default_15) {
 __x_4  ( ) ;

}

}
{
if (__static_condition_default_12) {
__static_type_error("too many arguments to function") ;

}

if (__static_condition_default_13) {
__static_type_error("too many arguments to function") ;

}

if (__static_condition_default_16) {
 __x_3  ( 2 ) ;

}

if (__static_condition_default_17) {
 __x_4  ( 2 ) ;

}

}}


}

