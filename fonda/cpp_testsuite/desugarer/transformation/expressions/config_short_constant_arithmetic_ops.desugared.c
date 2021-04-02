#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__x_2", "x");

__static_condition_renaming("__static_condition_default_3", "A");
__static_condition_renaming("__static_condition_default_4", "!A");

};

int  __main_0 (void  ) {
{
int  __x_1;
char  __x_2;

{
if (__static_condition_default_3) {
 __x_1  = 3 + 5 ;

}

if (__static_condition_default_4) {
 __x_2  = 3 + 5 ;

}

}
{
if (__static_condition_default_3) {
 __x_1  = 2 - 1 ;

}

if (__static_condition_default_4) {
 __x_2  = 2 - 1 ;

}

}
{
if (__static_condition_default_3) {
 __x_1  = 6 * 4 ;

}

if (__static_condition_default_4) {
 __x_2  = 6 * 4 ;

}

}
{
if (__static_condition_default_3) {
 __x_1  = 8 / 2 ;

}

if (__static_condition_default_4) {
 __x_2  = 8 / 2 ;

}

}
{
if (__static_condition_default_3) {
 __x_1  = 10 % 5 ;

}

if (__static_condition_default_4) {
 __x_2  = 10 % 5 ;

}

}return 0 ;

}


}

