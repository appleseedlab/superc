#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_4;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");

__static_condition_renaming("__static_condition_default_2", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_B)|)(assert (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_A)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))))");
__static_condition_renaming("__static_condition_default_3", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_B)|)(assert |(defined CONFIG_A)|)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_A)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))))");
__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_B)|)(assert |(defined CONFIG_A)|)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_A)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))))");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_B)|)(assert |(defined CONFIG_A)|)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_A)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))))");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun |(defined CONFIG_B)| () Bool)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_A)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))))(assert (let ((a!1 (or (and |(defined CONFIG_B)| |(defined CONFIG_A)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|))))))  (not (and |(defined CONFIG_B)| |(defined CONFIG_A)| a!1))))");
__static_condition_renaming("__static_condition_default_7", "(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun |(defined CONFIG_B)| () Bool)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_A)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))))");

};

int  __main_0 () {

if (__static_condition_default_7) {
{
int  __x_1;

{
if (__static_condition_default_2) {
__static_type_error("type error");

}

if (__static_condition_default_3) {
 __x_1  = 2 ;

}

}
if (__static_condition_default_4) {
 __x_1  ++ ;

}

{
if (__static_condition_default_5) {
return  __x_1  ;

}

if (__static_condition_default_6) {
__static_type_error("invalid type found in return expression");

}

}}

}

}

