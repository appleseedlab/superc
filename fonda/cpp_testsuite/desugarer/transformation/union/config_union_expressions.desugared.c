#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_14;
extern const bool __static_condition_default_20;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_19;
void __static_initializer_default() {
__static_renaming("__usedUnion_6", "usedUnion");
__static_renaming("__usedUnion_7", "usedUnion");
__static_renaming("__x_8", "x");
__static_renaming("__x_9", "x");
__static_renaming("__y_10", "y");
__static_renaming("__z_11", "z");
__static_renaming("__ch_13", "ch");
__static_renaming("__main_15", "main");

__static_condition_renaming("__static_condition_default_12", "!A && (defined C)");
__static_condition_renaming("__static_condition_default_14", "!A && !(defined C)");
__static_condition_renaming("__static_condition_default_16", "A");
__static_condition_renaming("__static_condition_default_17", "!A");
__static_condition_renaming("__static_condition_default_18", "!A");
__static_condition_renaming("__static_condition_default_19", "A && B");
__static_condition_renaming("__static_condition_default_20", "!A && B");

};
union __intCharFloat_0 {
int  __integer_1;// L3
char  __character_2;// L4
float  __floating_3;// L5
};
union __intCharFloat_4 {
char  __integer_5;// L9
};

union __intCharFloat_0 ;// L2
union __intCharFloat_4 ;// L8
int  (__main_15) (void  ) {

{
{



union __intCharFloat_0  __usedUnion_6;// L14

union __intCharFloat_4  __usedUnion_7;// L14

if (__static_condition_default_16) {
 __usedUnion_6  . __integer_1 = 1 ; // L16
}
if (__static_condition_default_17) {
 __usedUnion_7  . __integer_5 = 1 ; // L16
}
if (__static_condition_default_16) {
 __usedUnion_6  . __character_2 = 'h' ; // L17
}
if (__static_condition_default_17) {
__static_type_error("type error") ; // L17
}
int  __x_8=  __usedUnion_6  . __integer_1;// L19

int  __x_9=  __usedUnion_7  . __integer_5;// L19

int  __y_10;// L21

if (__static_condition_default_16) {
 __y_10  =  __usedUnion_6  . __integer_1 +  __usedUnion_6  . __character_2 ; // L23
}
if (__static_condition_default_18) {
__static_type_error("type error") ; // L23
}
if (__static_condition_default_19) {
 __usedUnion_6  . __integer_1 ++ ; // L26
}
if (__static_condition_default_20) {
 __usedUnion_7  . __integer_5 ++ ; // L26
}
int  __z_11=  __usedUnion_6  . __integer_1 %  __usedUnion_6  . __character_2;// L30

if (__static_condition_default_12) {
__static_type_error("invalid declaration of z under this presence condition");
}

char  __ch_13=  __usedUnion_6  . __character_2;// L32

if (__static_condition_default_14) {
__static_type_error("invalid declaration of ch under this presence condition");
}

return 0 ;// L35
}
}


}

