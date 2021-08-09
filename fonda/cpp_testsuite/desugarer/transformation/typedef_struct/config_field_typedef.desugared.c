#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_10;
extern const bool __static_condition_default_9;
void __static_initializer_default() {
__static_renaming("__typeAlias_0", "typeAlias");
__static_renaming("__typeAlias_1", "typeAlias");
__static_renaming("__bob_6", "bob");
__static_renaming("__bobStruct_7", "bobStruct");
__static_renaming("__main_8", "main");

__static_condition_renaming("__static_condition_default_9", "(defined CONFIG_A)");
__static_condition_renaming("__static_condition_default_10", "!(defined CONFIG_A)");

};
typedef int  __typeAlias_0;// L2
typedef char  __typeAlias_1;// L4
struct __bob_2 {
__typeAlias_0  __val_3;
__typeAlias_1  __val_4;
char  __otherVal_5;
};
typedef struct __bob_2  __bob_6;// L7:L10

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope
int  __main_8 (void  ) {

{
{



__bob_6  __bobStruct_7;// L13

if (__static_condition_default_9) {
 __bobStruct_7  . __val_3 = 1 ; // L14
}
if (__static_condition_default_10) {
 __bobStruct_7  . __val_4 = 1 ; // L14
}
}
}


}

