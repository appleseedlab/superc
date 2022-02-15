#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__bob_3", "bob");


};
enum __bob_2 {
__x_0,
__y_1,
};

enum __bob_2  __bob_3;// L1

