#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__main_4", "main");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_2", "(defined A)");
__static_condition_renaming("__static_condition_default_3", "!(defined A)");
__static_condition_renaming("__static_condition_default_6", "!(defined A)");
__static_condition_renaming("__static_condition_default_7", "(defined A)");

};

static int  __x_0;
int  __main_4 () {

if (__static_condition_default_6) {
{
char  __x_1;

{
if (__static_condition_default_2) {
 __x_0  ++ ;

}

if (__static_condition_default_3) {
 __x_1  ++ ;

}

}
{
if (__static_condition_default_3) {
return  __x_1  ;

}

if (__static_condition_default_2) {
return  __x_0  ;

}

}}

}

}
int  __main_5 () {

if (__static_condition_default_7) {
{
char  __x_1;

{
if (__static_condition_default_2) {
 __x_0  ++ ;

}

if (__static_condition_default_3) {
 __x_1  ++ ;

}

}
{
if (__static_condition_default_3) {
return  __x_1  ;

}

if (__static_condition_default_2) {
return  __x_0  ;

}

}}

}

}

