#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__usedUnion_5", "usedUnion");
__static_renaming("__usedUnion_6", "usedUnion");
__static_renaming("__main_7", "main");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_9", "!A");
__static_condition_renaming("__static_condition_default_10", "A");

};
union __intCharFloat_0 {
int  __integer_1;// L3
char  __character_2;// L4
float  __floating_3;// L5
};

union __intCharFloat_0 ;// L2
int  (__main_7) (void  ) {

if (__static_condition_default_9) {

{
{


struct __forward_tag_reference_4 { // generated union of struct variations
union {
};
};


struct __forward_tag_reference_4  __usedUnion_6;// L10

__static_type_error("type error") ; // L12
__static_type_error("type error") ; // L14
return 0 ;// L16
}
}


}
}
int  (__main_8) (void  ) {

if (__static_condition_default_10) {

{
{


struct __forward_tag_reference_4 { // generated union of struct variations
union {
};
};


union __intCharFloat_0  __usedUnion_5;// L10

 __usedUnion_5  . __integer_1 = 1 ; // L12
 __usedUnion_5  . __character_2 = 'h' ; // L14
return 0 ;// L16
}
}


}
}

