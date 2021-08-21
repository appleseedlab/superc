#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__doNothing_0", "doNothing");
__static_renaming("__doNothing_1", "doNothing");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_2", "A");
__static_condition_renaming("__static_condition_default_3", "!A");
__static_condition_renaming("__static_condition_default_5", "!A");

};

void  (__doNothing_0) () {

{
if (__static_condition_default_2) {

{
{



return  ;// L3
}
}


}

}}
void  (__doNothing_1) () {

{
if (__static_condition_default_3) {

{
{



}
}


}

}}
int  (__main_4) (void  ) {

{
{



if (__static_condition_default_2) {
 __doNothing_0 ( ) ; // L11
}
if (__static_condition_default_5) {
 __doNothing_1 ( ) ; // L11
}
return 0 ;// L13
}
}


}

