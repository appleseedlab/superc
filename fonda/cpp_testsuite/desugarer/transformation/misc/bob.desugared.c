#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_6;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");

__static_condition_renaming("__static_condition_default_3", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(assert |(defined CONFIG_B)|)(assert (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_C)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))))");
__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(assert |(defined CONFIG_B)|)(assert |(defined CONFIG_C)|)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_C)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))))");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined CONFIG_C)| () Bool)(declare-fun |(defined CONFIG_B)| () Bool)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_C)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))))(assert |(defined CONFIG_B)|)(assert |(defined CONFIG_C)|)(assert (let ((a!1 (or (and |(defined CONFIG_B)| |(defined CONFIG_C)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|))))))  (not (and a!1 (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|))))))");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined CONFIG_C)| () Bool)(declare-fun |(defined CONFIG_B)| () Bool)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_C)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))))");
__static_condition_renaming("__static_condition_default_7", "(declare-fun |(defined CONFIG_C)| () Bool)(declare-fun |(defined CONFIG_B)| () Bool)(assert (or (and |(defined CONFIG_B)| |(defined CONFIG_C)|)    (and |(defined CONFIG_B)|         (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))))");

};

int  __main_0 () {

if (__static_condition_default_7) {
{
int  __x_1;
int  __y_2;

{
if (__static_condition_default_3) {
__static_type_error("type error");

}

if (__static_condition_default_4) {
 __y_2  = 4 ;

}

}
if (__static_condition_default_5) {
 __x_1  =  __y_2  ;

}

if (__static_condition_default_6) {
 __x_1  ++ ;

}

if (__static_condition_default_6) {
return  __x_1  ;

}
}

}

}

