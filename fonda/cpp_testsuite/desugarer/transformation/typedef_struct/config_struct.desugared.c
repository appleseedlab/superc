#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__bob_4", "bob");
__static_renaming("__bob_5", "bob");


};
struct __bob_0 {
char  __otherVal_1;// L3
};
struct __bob_2 {
char  __otherVal_3;// L7
};
typedef struct __bob_0  __bob_4;// L2:L4
typedef struct __bob_2  __bob_5;// L6:L8

// typedef moved to top of scope
// typedef moved to top of scope

