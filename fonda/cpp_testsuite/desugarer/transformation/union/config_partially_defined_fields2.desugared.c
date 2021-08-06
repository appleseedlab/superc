#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__usedUnion_5", "usedUnion");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "A");
__static_condition_renaming("__static_condition_default_8", "!A");

};
union __intCharFloat_0 {
int  __integer_1;
char  __character_2;
float  __floating_3;
float  __floating_4;
};

union __intCharFloat_0 ;// L2
int  __main_6 (void  ) {

{



union __intCharFloat_0  __usedUnion_5;// L11

 __usedUnion_5  . __integer_1 = 1 ; // L13
if (__static_condition_default_7) {
 __usedUnion_5  . __character_2 = 'h' ; // L15
}
if (__static_condition_default_8) {
__static_type_error("type error") ; // L15
}
return 0 ;// L17
}



}

