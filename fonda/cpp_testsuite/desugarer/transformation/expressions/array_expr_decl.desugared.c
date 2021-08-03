#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__expressionArr_0", "expressionArr");
__static_renaming("__main_1", "main");


};

int  __main_1 (void  ) {

{



int  (__expressionArr_0[2 + 8]);// L3

return 0 ;// L5
}



}

