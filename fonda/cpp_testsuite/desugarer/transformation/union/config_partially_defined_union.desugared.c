#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_11;
void __static_initializer_default() {
__static_renaming("__usedUnion_5", "usedUnion");
__static_renaming("__usedUnion_6", "usedUnion");
__static_renaming("__main_9", "main");
__static_renaming("__main_10", "main");

__static_condition_renaming("__static_condition_default_7", "A");
__static_condition_renaming("__static_condition_default_8", "!A");
__static_condition_renaming("__static_condition_default_11", "!A");
__static_condition_renaming("__static_condition_default_12", "A");

};
union __intCharFloat_0 {
int  __integer_1;
char  __character_2;
float  __floating_3;
};

union __intCharFloat_0 ;
int  __main_9 (void  ) {

if (__static_condition_default_11) {
{
struct __forward_tag_reference_4 { // generated union of struct variations
union {
};
};

union __intCharFloat_0  __usedUnion_5;
struct __forward_tag_reference_4  __usedUnion_6;

{
if (__static_condition_default_7) {
 __usedUnion_5  . __integer_1 = 1 ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_7) {
 __usedUnion_5  . __character_2 = 'h' ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

}return 0 ;

}

}

}
int  __main_10 (void  ) {

if (__static_condition_default_12) {
{
struct __forward_tag_reference_4 { // generated union of struct variations
union {
};
};

union __intCharFloat_0  __usedUnion_5;
struct __forward_tag_reference_4  __usedUnion_6;

{
if (__static_condition_default_7) {
 __usedUnion_5  . __integer_1 = 1 ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

}
{
if (__static_condition_default_7) {
 __usedUnion_5  . __character_2 = 'h' ;

}

if (__static_condition_default_8) {
__static_type_error("type error") ;

}

}return 0 ;

}

}

}

