#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_19;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_14;
void __static_initializer_default() {
__static_renaming("__main_6", "main");
__static_renaming("__usedUnion_7", "usedUnion");
__static_renaming("__usedUnion_8", "usedUnion");
__static_renaming("__x_11", "x");
__static_renaming("__x_12", "x");
__static_renaming("__y_13", "y");
__static_renaming("__z_16", "z");
__static_renaming("__z_17", "z");
__static_renaming("__ch_18", "ch");

__static_condition_renaming("__static_condition_default_9", "A");
__static_condition_renaming("__static_condition_default_10", "!A");
__static_condition_renaming("__static_condition_default_14", "A && B");
__static_condition_renaming("__static_condition_default_15", "!A && B");
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
int  __main_6 (void  ) {
{
union __intCharFloat_0  __usedUnion_7;
union __intCharFloat_4  __usedUnion_8;

{
if (__static_condition_default_9) {
 __usedUnion_7  . __integer_1 = 1 ;

}

if (__static_condition_default_10) {
 __usedUnion_8  . __integer_5 = 1 ;

}

}
{
if (__static_condition_default_9) {
 __usedUnion_7  . __character_2 = 'h' ;

}

if (__static_condition_default_10) {
__static_type_error("type error") ;

}

}int  __x_11=  __usedUnion_7  . __integer_1;
int  __x_12=  __usedUnion_8  . __integer_5;
int  __y_13;

{
if (__static_condition_default_9) {
 __y_13  =  __usedUnion_7  . __integer_1 +  __usedUnion_7  . __character_2 ;

}

if (__static_condition_default_10) {
 __y_13  =  __usedUnion_8  . __integer_5 +  __usedUnion_8  .  ;

}

}
{
if (__static_condition_default_14) {
 __usedUnion_7  . __integer_1 ++ ;

}

if (__static_condition_default_15) {
 __usedUnion_8  . __integer_5 ++ ;

}

}int  __z_16=  __usedUnion_7  . __integer_1 %  __usedUnion_7  . __character_2;
int  __z_17=  __usedUnion_8  . __integer_5 %  __usedUnion_8  . ;
char  __ch_18=  __usedUnion_7  . __character_2;
if (__static_condition_default_19) {
__static_type_error("invalid declaration of ch under this presence condition");
}
return 0 ;

}


}

