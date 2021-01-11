#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_4;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");

__static_condition_renaming("__static_condition_default_2", "(declare-fun |(defined A)| () Bool)(assert |(defined A)|)");
__static_condition_renaming("__static_condition_default_3", "(declare-fun |(defined B)| () Bool)(assert |(defined B)|)");
__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined A)| () Bool)(assert (not |(defined A)|))");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined B)| () Bool)(assert (not |(defined B)|))");

};

int  __main_0 () {
{
int  __x_1;
if (  __x_1  ) 
{
if (__static_condition_default_4) {
{
}

}

if (__static_condition_default_2) {
{

if (__static_condition_default_2) {
 __x_1  ++ ;

}
}

}

} 
{
if (__static_condition_default_5) {
{
}

}

if (__static_condition_default_3) {
{

if (__static_condition_default_3) {
 __x_1  -- ;

}
}

}

}

return 0 ;

}


}

