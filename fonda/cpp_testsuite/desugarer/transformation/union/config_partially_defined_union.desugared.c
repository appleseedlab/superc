#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_12;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__main_4", "main");
__static_renaming("__main_5", "main");
__static_renaming("__usedUnion_7", "usedUnion");
__static_renaming("__usedUnion_8", "usedUnion");

__static_condition_renaming("__static_condition_default_9", "A");
__static_condition_renaming("__static_condition_default_10", "!A");
__static_condition_renaming("__static_condition_default_11", "!A");
__static_condition_renaming("__static_condition_default_12", "A");

};
union __intCharFloat_0 {
int  __integer_1;
char  __character_2;
float  __floating_3;
};

union __intCharFloat_0 ;
int  __main_4 (void  ) {

if (__static_condition_default_11) {
{
struct __forward_tag_reference_6 { // generated union of struct variations
union {
};
};

union __intCharFloat_0  __usedUnion_7;
struct __forward_tag_reference_6  __usedUnion_8;

{
if (__static_condition_default_9) {
 __usedUnion_7  . __integer_1 = 1 ;

}

if (__static_condition_default_10) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_9) {
 __usedUnion_7  . __character_2 = 'h' ;

}

if (__static_condition_default_10) {
__static_type_error("type error") ;

}

}return 0 ;

}

}

}
int  __main_5 (void  ) {

if (__static_condition_default_12) {
{
struct __forward_tag_reference_6 { // generated union of struct variations
union {
};
};

union __intCharFloat_0  __usedUnion_7;
struct __forward_tag_reference_6  __usedUnion_8;

{
if (__static_condition_default_9) {
 __usedUnion_7  . __integer_1 = 1 ;

}

if (__static_condition_default_10) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_9) {
 __usedUnion_7  . __character_2 = 'h' ;

}

if (__static_condition_default_10) {
__static_type_error("type error") ;

}

}return 0 ;

}

}

}

