#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_2;
extern const bool __static_condition_default_1;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__main_3", "main");

__static_condition_renaming("__static_condition_default_1", "A");
__static_condition_renaming("__static_condition_default_2", "!A");

if (0)
{
__static_parse_error("Unable to parse");
}
};

int  __main_3 () {
{
int  __a_0;

{
if (__static_condition_default_1) {
 __a_0  = 0 ;

}

if (__static_condition_default_2) {
 __a_0  = 1 ;

}

}return 0 ;

}


}

