#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_1;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__doNothing_0", "doNothing");
__static_renaming("__doNothing_2", "doNothing");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_1", "A");
__static_condition_renaming("__static_condition_default_3", "!A");
__static_condition_renaming("__static_condition_default_5", "!A");

};

void  __doNothing_0 () {

{
if (__static_condition_default_1) {
{

if (__static_condition_default_1) {
return  ;

}
}

}

}
}
void  __doNothing_2 () {

{
if (__static_condition_default_3) {
{
}

}

}
}
int  __main_4 (void  ) {
{

{
if (__static_condition_default_1) {
 __doNothing_0  ( ) ;

}

if (__static_condition_default_5) {
 __doNothing_2  ( ) ;

}

}return 0 ;

}


}
