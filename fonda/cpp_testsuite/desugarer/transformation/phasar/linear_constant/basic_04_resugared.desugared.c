#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__x_0", "x");
__static_renaming("__main_1", "main");


if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __main_1 () {
{
int  __x_0;
 __x_0  = 300 ;

 __x_0  ++ ;

return  __x_0  ;

}


}

