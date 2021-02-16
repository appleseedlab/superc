#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_5();

extern const bool __static_condition_4;
extern const bool __static_condition_3;
void __static_initializer_5() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");

__static_condition_renaming("__static_condition_3", "A");
__static_condition_renaming("__static_condition_4", "(not A)");

};
int  __main_0 (void  );

int  __main_0 (void  ) {
{
int  __x_1= 2;
char  __x_2= 3;

{
if (__static_condition_3) {
if (  __x_1  == 2 ) {

{
if (__static_condition_3) {
 __x_1  ++ ;

}

if (__static_condition_4) {
 __x_2  ++ ;

}

}}



}

if (__static_condition_4) {
if (  __x_2  == 2 ) {

{
if (__static_condition_3) {
 __x_1  ++ ;

}

if (__static_condition_4) {
 __x_2  ++ ;

}

}}



}

}return 0 ;

}


}

