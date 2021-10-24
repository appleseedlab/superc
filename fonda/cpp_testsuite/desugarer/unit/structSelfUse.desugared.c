#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
void __static_initializer_default() {

__static_condition_renaming("__static_condition_default_7", "(defined X)");

if (__static_condition_default_7)
{
__static_parse_error("Unable to parse");
}
};
struct ____anonymous_tag_0_1 {
int  __A_2;// L7
int  __B_3;// L8
int  __C_4;// L9
int  __A_1_5;// L10
int  __B_1_6;// L11
};

struct ____anonymous_tag_0_1 ;// L6

