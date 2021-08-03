#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__bob_3", "bob");
__static_renaming("__bobStruct_4", "bobStruct");
__static_renaming("__main_5", "main");


};
struct __bob_0 {
int  __val_1;
char  __otherVal_2;
};
typedef struct __bob_0  __bob_3;// L1:L4

// typedef moved to top of scope
int  __main_5 (void  ) {

{



__bob_3  __bobStruct_4;// L7

 __bobStruct_4  . __val_1 = 1 ; // L8
}



}

