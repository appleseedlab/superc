#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__typeAlias_0", "typeAlias");
__static_renaming("__typeAlias_1", "typeAlias");
__static_renaming("__bob_6", "bob");


};
typedef int  __typeAlias_0;// L2
typedef char  __typeAlias_1;// L4
struct __bob_2 {
__typeAlias_0  __val_3;// L0
__typeAlias_1  __val_4;// L0
char  __otherVal_5;// L9
};
typedef struct __bob_2  __bob_6;// L7:L10

// typedef moved to top of scope
// typedef moved to top of scope
// typedef moved to top of scope

