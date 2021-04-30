#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_3;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_0;
void __static_initializer_default() {
__static_renaming("__doNothing_1", "doNothing");
__static_renaming("__doNothing_2", "doNothing");
__static_renaming("__main_5", "main");

__static_condition_renaming("__static_condition_default_0", "A");
__static_condition_renaming("__static_condition_default_3", "!A");
__static_condition_renaming("__static_condition_default_4", "!A");

};

void  __doNothing_1 () {

{
if (__static_condition_default_0) {
{

if (__static_condition_default_0) {
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
int  __main_5 (void  ) {
{

{
if (__static_condition_default_0) {
 __doNothing_1  ( ) ;

}

if (__static_condition_default_4) {
 __doNothing_2  ( ) ;

}

}return 0 ;

}


}

