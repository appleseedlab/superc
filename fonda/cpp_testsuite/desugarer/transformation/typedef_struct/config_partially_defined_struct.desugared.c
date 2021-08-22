#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_8;
void __static_initializer_default() {
__static_renaming("__bob_3", "bob");
__static_renaming("__bobStruct_4", "bobStruct");
__static_renaming("__main_5", "main");
__static_renaming("__main_6", "main");

__static_condition_renaming("__static_condition_default_7", "!(defined A)");
__static_condition_renaming("__static_condition_default_8", "(defined A)");

};
struct __bob_0 {
int  __val_1;// L3
char  __otherVal_2;// L5
};
typedef struct __bob_0  __bob_3;// L2:L6

// typedef moved to top of scope
int  (__main_5) (void  ) {

{
if (__static_condition_default_7) {

{
{



}
}


}

}}
int  (__main_6) (void  ) {

{
if (__static_condition_default_8) {

{
{



__bob_3  __bobStruct_4;// L11

 __bobStruct_4  . __val_1 = 1 ; // L12
}
}


}

}}

