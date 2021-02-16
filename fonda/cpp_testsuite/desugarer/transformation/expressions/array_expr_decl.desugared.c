#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__expressionArr_1", "expressionArr");


};

int  __main_0 (void  ) {
{
int  (__expressionArr_1[2 + 8]);
return 0 ;

}


}

