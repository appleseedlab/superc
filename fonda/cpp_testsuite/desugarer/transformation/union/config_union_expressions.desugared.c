#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_14;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__usedUnion_6", "usedUnion");
__static_renaming("__usedUnion_7", "usedUnion");
__static_renaming("__x_10", "x");
__static_renaming("__x_11", "x");
__static_renaming("__y_12", "y");
__static_renaming("__z_16", "z");
__static_renaming("__ch_18", "ch");
__static_renaming("__main_20", "main");

__static_condition_renaming("__static_condition_default_8", "A");
__static_condition_renaming("__static_condition_default_9", "!A");
__static_condition_renaming("__static_condition_default_13", "!A");
__static_condition_renaming("__static_condition_default_14", "A && B");
__static_condition_renaming("__static_condition_default_15", "!A && B");
__static_condition_renaming("__static_condition_default_17", "!A && (defined C)");
__static_condition_renaming("__static_condition_default_19", "!A && !(defined C)");

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
int  __main_20 (void  ) {
{
union __intCharFloat_0  __usedUnion_6;
union __intCharFloat_4  __usedUnion_7;

{
if (__static_condition_default_8) {
 __usedUnion_6  . __integer_1 = 1 ;

}

if (__static_condition_default_9) {
 __usedUnion_7  . __integer_5 = 1 ;

}

}
{
if (__static_condition_default_8) {
 __usedUnion_6  . __character_2 = 'h' ;

}

if (__static_condition_default_9) {
__static_type_error("type error") ;

}

}int  __x_10=  __usedUnion_6  . __integer_1;
int  __x_11=  __usedUnion_7  . __integer_5;
int  __y_12;

{
if (__static_condition_default_8) {
 __y_12  =  __usedUnion_6  . __integer_1 +  __usedUnion_6  . __character_2 ;

}

if (__static_condition_default_13) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_14) {
 __usedUnion_6  . __integer_1 ++ ;

}

if (__static_condition_default_15) {
 __usedUnion_7  . __integer_5 ++ ;

}

}int  __z_16=  __usedUnion_6  . __integer_1 %  __usedUnion_6  . __character_2;
if (__static_condition_default_17) {
__static_type_error("invalid declaration of z under this presence condition");
}
char  __ch_18=  __usedUnion_6  . __character_2;
if (__static_condition_default_19) {
__static_type_error("invalid declaration of ch under this presence condition");
}
return 0 ;

}


}

