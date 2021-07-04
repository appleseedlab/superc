#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__usedUnion_6", "usedUnion");
__static_renaming("__usedUnion_7", "usedUnion");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_9", "A");
__static_condition_renaming("__static_condition_default_10", "!A");

};
union __intCharFloat_0 {
int  __integer_1;
char  __character_2;
float  __floating_3;
};
union __intCharFloat_4 {
char  __integer_5;
};

union __intCharFloat_0 ;
union __intCharFloat_4 ;
int  __main_8 (void  ) {

{



union __intCharFloat_0  __usedUnion_6;

union __intCharFloat_4  __usedUnion_7;

if (__static_condition_default_9) {
 __usedUnion_6  . __integer_1 = 1 ;
}
if (__static_condition_default_10) {
 __usedUnion_7  . __integer_5 = 1 ;
}
return 0 ;
}



}

