#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
extern const bool __static_condition_default_7;
void __static_initializer_default() {
__static_renaming("__bob_3", "bob");
__static_renaming("__main_4", "main");
__static_renaming("__main_5", "main");
__static_renaming("__bobStruct_6", "bobStruct");

__static_condition_renaming("__static_condition_default_7", "(defined A)");
__static_condition_renaming("__static_condition_default_8", "!(defined A)");

};
struct __bob_0 {
int  __val_1;
char  __otherVal_2;
};
typedef struct __bob_0  __bob_3;

// typedef moved to top of scope
int  __main_4 (void  ) {

{
if (__static_condition_default_8) {
{
__bob_3  __bobStruct_6;
}

}

}
}
int  __main_5 (void  ) {

{
if (__static_condition_default_7) {
{
__bob_3  __bobStruct_6;

if (__static_condition_default_7) {
 __bobStruct_6  . __val_1 = 1 ;

}
}

}

}
}

