#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
void __static_initializer_default() {
__static_renaming("__doNothingOne_0", "doNothingOne");
__static_renaming("__doNothingTwo_1", "doNothingTwo");
__static_renaming("__main_2", "main");

__static_condition_renaming("__static_condition_default_3", "A");
__static_condition_renaming("__static_condition_default_4", "!A");

};

 void  __doNothingOne_0 () {

{



return  ;
}



}
 void  __doNothingTwo_1 () {

{



}



}
 int  __main_2 (void  ) {

{



if (__static_condition_default_3) {
 __doNothingOne_0 ( ) ;
}
if (__static_condition_default_4) {
 __doNothingTwo_1 ( ) ;
}
return 0 ;
}



}

