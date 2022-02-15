#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_8;
void __static_initializer_default() {

__static_condition_renaming("__static_condition_default_8", "(defined X)");

if (__static_condition_default_8)
{
__static_parse_error("Unable to parse");
}
};
enum ____anonymous_tag_6_7 {
__A_0,
__B_1,
__FEATURE_2,
__C_3 = 30,
__A_1_4 = 1 <<  __A_0 ,
__B_1_5 = 1 <<  __B_1 ,
};

enum ____anonymous_tag_6_7 ;// L6

