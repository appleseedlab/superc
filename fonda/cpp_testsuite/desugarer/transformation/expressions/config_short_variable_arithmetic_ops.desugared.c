#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");
__static_renaming("__y_3", "y");
__static_renaming("__z_4", "z");

__static_condition_renaming("__static_condition_default_5", "(declare-fun A () Bool)(assert A)");
__static_condition_renaming("__static_condition_default_6", "(declare-fun A () Bool)(assert (not A))");

};

int  __main_0 (void  ) {
{
int  __x_1;
char  __x_2;
int  __y_3;
int  __z_4;

{
if (__static_condition_default_5) {
 __x_1  = 1 ;

}

if (__static_condition_default_6) {
 __x_2  = 1 ;

}

} __y_3  = 2 ;

 __z_4  = 3 ;


{
if (__static_condition_default_5) {
 __x_1  =  __y_3  +  __z_4  ;

}

if (__static_condition_default_6) {
 __x_2  =  __y_3  +  __z_4  ;

}

}
{
if (__static_condition_default_5) {
 __x_1  =  __y_3  -  __z_4  ;

}

if (__static_condition_default_6) {
 __x_2  =  __y_3  -  __z_4  ;

}

}
{
if (__static_condition_default_5) {
 __x_1  =  __y_3  *  __z_4  ;

}

if (__static_condition_default_6) {
 __x_2  =  __y_3  *  __z_4  ;

}

}
{
if (__static_condition_default_5) {
 __x_1  =  __y_3  /  __z_4  ;

}

if (__static_condition_default_6) {
 __x_2  =  __y_3  /  __z_4  ;

}

}
{
if (__static_condition_default_5) {
 __x_1  =  __y_3  %  __z_4  ;

}

if (__static_condition_default_6) {
 __x_2  =  __y_3  %  __z_4  ;

}

}return 0 ;

}


}

