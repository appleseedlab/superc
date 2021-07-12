#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_9;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__typeAlias_0", "typeAlias");
__static_renaming("__bob_6", "bob");
__static_renaming("__bobStruct_7", "bobStruct");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_5", "!(defined A)");
__static_condition_renaming("__static_condition_default_9", "(defined A)");

};
typedef int  __typeAlias_0;
struct __bob_1 {
__typeAlias_0  __val_2;
char  __otherVal_4;
};
typedef struct __bob_1  __bob_6;

// typedef moved to top of scope
// typedef moved to top of scope
int  __main_8 (void  ) {

{



__bob_6  __bobStruct_7;

if (__static_condition_default_5) {
__static_type_error("invalid declaration of bobStruct under this presence condition");
}

if (__static_condition_default_9) {
 __bobStruct_7  . __val_2 = 1 ; // L14
}
if (__static_condition_default_5) {
__static_type_error("type error") ; // L14
}
}



}

