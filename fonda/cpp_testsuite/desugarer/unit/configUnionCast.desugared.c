#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_18;
extern const bool __static_condition_default_17;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_19;
void __static_initializer_default() {
__static_renaming("__U_8", "U");
__static_renaming("__U_9", "U");
__static_renaming("__wait_10", "wait");
__static_renaming("__wait_11", "wait");
__static_renaming("__wait_12", "wait");
__static_renaming("__wait_13", "wait");
__static_renaming("__i_14", "i");
__static_renaming("__oneit_main_15", "oneit_main");

__static_condition_renaming("__static_condition_default_16", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_17", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_18", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_19", "!(defined A) && !(defined B)");

};
union ____anonymous_tag_0_1 {
int  (* __a_2);
long  __b_3;
};
union ____anonymous_tag_4_5 {
int  (* __a_6);
long  __b_7;
};
typedef union ____anonymous_tag_0_1  __U_8;// L2:L5
typedef union ____anonymous_tag_4_5  __U_9;// L7:L10

// typedef moved to top of scope
// typedef moved to top of scope
extern int  __wait_10 (__U_8  );// L14
extern int  __wait_11 (__U_9  );// L14
extern int  __wait_12 (__U_8  );// L16
extern int  __wait_13 (__U_9  );// L16
void  __oneit_main_15 (void  ) {

{
{



int  __i_14;// L21

if (__static_condition_default_16) {
while (  __wait_10  ((union ____anonymous_tag_0_1)&  __i_14 ) )// L22
{
 __i_14  ; // L22
}
}
if (__static_condition_default_17) {
while (  __wait_11  ((union ____anonymous_tag_4_5)&  __i_14 ) )// L22
{
 __i_14  ; // L22
}
}
if (__static_condition_default_18) {
while (  __wait_12  ((union ____anonymous_tag_0_1)&  __i_14 ) )// L22
{
 __i_14  ; // L22
}
}
if (__static_condition_default_19) {
while (  __wait_13  ((union ____anonymous_tag_4_5)&  __i_14 ) )// L22
{
 __i_14  ; // L22
}
}
}
}


}

