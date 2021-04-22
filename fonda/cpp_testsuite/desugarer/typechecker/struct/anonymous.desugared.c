#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

void __static_initializer_default() {
__static_renaming("__data_2", "data");
__static_renaming("__main_3", "main");


if (0)
{
__static_parse_error("Unable to parse");
}
};
struct __anonymous_tag_0 {
char  __p_1;
};

struct __anonymous_tag_0  __data_2;
int  __main_3 () {
{
 __data_2  . __p_1 ;

return 0 ;

}


}

