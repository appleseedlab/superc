#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {


};
union __intCharFloat_0 {
int  __integer_1;
char  __character_2;
float  __floating_3;
};

union __intCharFloat_0 ;

