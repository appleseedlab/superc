#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__main_1", "main");
__static_renaming("__main_2", "main");
__static_renaming("__x_3", "x");

__static_condition_renaming("__static_condition_default_4", "(defined A)");
__static_condition_renaming("__static_condition_default_5", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_7", "(defined A)");

};

static int  __x_0;
int  __main_1 () {

if (__static_condition_default_6) {
{
char  __x_3;

{
if (__static_condition_default_4) {
 __x_0  ++ ;

}

if (__static_condition_default_5) {
 __x_3  ++ ;

}

}
{
if (__static_condition_default_5) {
return  __x_3  ;

}

if (__static_condition_default_4) {
return  __x_0  ;

}

}}

}

}
int  __main_2 () {

if (__static_condition_default_7) {
{
char  __x_3;

{
if (__static_condition_default_4) {
 __x_0  ++ ;

}

if (__static_condition_default_5) {
 __x_3  ++ ;

}

}
{
if (__static_condition_default_5) {
return  __x_3  ;

}

if (__static_condition_default_4) {
return  __x_0  ;

}

}}

}

}

