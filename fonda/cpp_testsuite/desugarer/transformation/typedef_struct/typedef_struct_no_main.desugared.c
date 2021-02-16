#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__bob_3", "bob");


};
struct __bob_0 {
int  __val_1;
char  __otherVal_2;
};
typedef struct __bob_0  __bob_3;

// typedef moved to top of scope

