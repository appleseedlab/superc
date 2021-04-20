#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_2;
void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__x_1", "x");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "A");
__static_condition_renaming("__static_condition_default_3", "!A");

};

int  __main_4 (void  ) {
{
int  __x_0= 2;
char  __x_1= 3;

{
if (__static_condition_default_2) {
if (  __x_0  == 2 ) {

{
if (__static_condition_default_2) {
 __x_0  ++ ;

}

if (__static_condition_default_3) {
 __x_1  ++ ;

}

}}



}

if (__static_condition_default_3) {
if (  __x_1  == 2 ) {

{
if (__static_condition_default_2) {
 __x_0  ++ ;

}

if (__static_condition_default_3) {
 __x_1  ++ ;

}

}}



}

}return 0 ;

}


}

