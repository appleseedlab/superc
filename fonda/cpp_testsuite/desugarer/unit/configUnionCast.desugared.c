#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_16;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_17;
void __static_initializer_default() {
__static_renaming("__U_6", "U");
__static_renaming("__U_7", "U");
__static_renaming("__wait_8", "wait");
__static_renaming("__wait_9", "wait");
__static_renaming("__wait_10", "wait");
__static_renaming("__wait_11", "wait");
__static_renaming("__i_12", "i");
__static_renaming("__oneit_main_13", "oneit_main");

__static_condition_renaming("__static_condition_default_14", "(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_15", "!(defined A) && (defined B)");
__static_condition_renaming("__static_condition_default_16", "(defined A) && !(defined B)");
__static_condition_renaming("__static_condition_default_17", "!(defined A) && !(defined B)");

};
union __anonymous_tag_0 {
int  (* __a_1);
long  __b_2;
};
union __anonymous_tag_3 {
int  (* __a_4);
long  __b_5;
};
typedef union __anonymous_tag_0  __U_6;// L2:L5
typedef union __anonymous_tag_3  __U_7;// L7:L10

// typedef moved to top of scope
// typedef moved to top of scope
extern int  __wait_8 (__U_6  );// L14
extern int  __wait_9 (__U_7  );// L14
extern int  __wait_10 (__U_6  );// L16
extern int  __wait_11 (__U_7  );// L16
void  __oneit_main_13 (void  ) {

{
{



int  __i_12;// L21

if (__static_condition_default_14) {
while (  __wait_8  ((union __anonymous_tag_0)&  __i_12 ) )// L22
{
 __i_12  ; // L22
}
}
if (__static_condition_default_15) {
while (  __wait_9  ((union __anonymous_tag_3)&  __i_12 ) )// L22
{
 __i_12  ; // L22
}
}
if (__static_condition_default_16) {
while (  __wait_10  ((union __anonymous_tag_0)&  __i_12 ) )// L22
{
 __i_12  ; // L22
}
}
if (__static_condition_default_17) {
while (  __wait_11  ((union __anonymous_tag_3)&  __i_12 ) )// L22
{
 __i_12  ; // L22
}
}
}
}


}

