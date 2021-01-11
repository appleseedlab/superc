#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_9;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_3;
extern const bool __static_condition_default_5;
extern const bool __static_condition_default_7;
extern const bool __static_condition_default_4;
extern const bool __static_condition_default_6;
void __static_initializer_default() {
__static_renaming("__main_0", "main");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");

__static_condition_renaming("__static_condition_default_3", "(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(assert (let ((a!1 (or (not |(defined CONFIG_B)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|))))))(let ((a!2 (or (and a!1                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))               (and a!1 (not |(defined CONFIG_B)|)))))(let ((a!3 (or (and a!2                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!2 (not |(defined CONFIG_B)|)))))(let ((a!4 (or (and a!3                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!3 (not |(defined CONFIG_B)|)))))(let ((a!5 (or (and a!4                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))               (and a!4 (not |(defined CONFIG_B)|)))))(let ((a!6 (or (and a!5                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!5 (not |(defined CONFIG_B)|)))))(let ((a!7 (or (and a!6                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!6 (not |(defined CONFIG_B)|)))))(let ((a!8 (or (and a!7                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!7 (not |(defined CONFIG_B)|)))))(let ((a!9 (or (and a!8                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!8 (not |(defined CONFIG_B)|)))))(let ((a!10 (or (and a!9                     |(defined CONFIG_B)|                     (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))                (and a!9 (not |(defined CONFIG_B)|)))))  (or (and |(defined CONFIG_B)| |(defined CONFIG_C)|)      (and |(defined CONFIG_B)| a!10)      (and |(defined CONFIG_B)| a!2 |(defined CONFIG_A)|)))))))))))))(assert |(defined CONFIG_B)|)(assert |(defined CONFIG_C)|)");
__static_condition_renaming("__static_condition_default_4", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(assert |(defined CONFIG_B)|)(assert |(defined CONFIG_C)|)");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_B)|)(assert (let ((a!1 (or (not |(defined CONFIG_B)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|))))))  (or (and a!1           |(defined CONFIG_B)|           (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))      (and a!1 (not |(defined CONFIG_B)|)))))(assert |(defined CONFIG_A)|)(assert (let ((a!1 (or (not |(defined CONFIG_B)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|))))))(let ((a!2 (or (and a!1                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))               (and a!1 (not |(defined CONFIG_B)|)))))  (or (and |(defined CONFIG_B)| a!2 |(defined CONFIG_A)|)      (and |(defined CONFIG_B)| |(defined CONFIG_C)| |(defined CONFIG_A)|)))))");
__static_condition_renaming("__static_condition_default_6", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(declare-fun |(defined CONFIG_A)| () Bool)(assert |(defined CONFIG_B)|)(assert |(defined CONFIG_C)|)(assert |(defined CONFIG_A)|)(assert (let ((a!1 (or (not |(defined CONFIG_B)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|))))))(let ((a!2 (or (and a!1                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))               (and a!1 (not |(defined CONFIG_B)|)))))  (or (and |(defined CONFIG_B)| a!2 |(defined CONFIG_A)|)      (and |(defined CONFIG_B)| |(defined CONFIG_C)| |(defined CONFIG_A)|)))))");
__static_condition_renaming("__static_condition_default_7", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(assert |(defined CONFIG_B)|)(assert (let ((a!1 (or (not |(defined CONFIG_B)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|))))))(let ((a!2 (or (and a!1                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))               (and a!1 (not |(defined CONFIG_B)|)))))  (or (and |(defined CONFIG_B)| a!2 |(defined CONFIG_A)|)      (and |(defined CONFIG_B)| |(defined CONFIG_C)| |(defined CONFIG_A)|)))))");
__static_condition_renaming("__static_condition_default_8", "(declare-fun |(defined CONFIG_B)| () Bool)(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(assert (let ((a!1 (or (not |(defined CONFIG_B)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))))      (a!11 (or (not |(defined CONFIG_B)|)                (and |(defined CONFIG_B)|                     (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|))))))(let ((a!2 (or (and a!1                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))               (and a!1 (not |(defined CONFIG_B)|))))      (a!12 (or (and a!11                     |(defined CONFIG_B)|                     (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))                (and a!11 (not |(defined CONFIG_B)|)))))(let ((a!3 (or (and a!2                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!2 (not |(defined CONFIG_B)|))))      (a!13 (or (and a!12                     |(defined CONFIG_B)|                     (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))                (and a!12 (not |(defined CONFIG_B)|)))))(let ((a!4 (or (and a!3                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!3 (not |(defined CONFIG_B)|)))))(let ((a!5 (or (and a!4                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))               (and a!4 (not |(defined CONFIG_B)|)))))(let ((a!6 (or (and a!5                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!5 (not |(defined CONFIG_B)|)))))(let ((a!7 (or (and a!6                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!6 (not |(defined CONFIG_B)|)))))(let ((a!8 (or (and a!7                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!7 (not |(defined CONFIG_B)|)))))(let ((a!9 (or (and a!8                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))               (and a!8 (not |(defined CONFIG_B)|)))))(let ((a!10 (or (and a!9                     |(defined CONFIG_B)|                     (not (and |(defined CONFIG_B)| |(defined CONFIG_A)|)))                (and a!9 (not |(defined CONFIG_B)|)))))  (or (not |(defined CONFIG_B)|)      (and |(defined CONFIG_B)| a!10)      (and |(defined CONFIG_B)| |(defined CONFIG_C)| a!13)))))))))))))");
__static_condition_renaming("__static_condition_default_9", "(declare-fun |(defined CONFIG_A)| () Bool)(declare-fun |(defined CONFIG_C)| () Bool)(declare-fun |(defined CONFIG_B)| () Bool)(assert (let ((a!1 (or (not |(defined CONFIG_B)|)               (and |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|))))))(let ((a!2 (or (and a!1                    |(defined CONFIG_B)|                    (not (and |(defined CONFIG_B)| |(defined CONFIG_C)|)))               (and a!1 (not |(defined CONFIG_B)|)))))  (or (and |(defined CONFIG_B)| a!2 |(defined CONFIG_A)|)      (and |(defined CONFIG_B)| |(defined CONFIG_C)| |(defined CONFIG_A)|)))))");

};

int  __main_0 () {

{
if (__static_condition_default_8) {
{
int  __x_1;
int  __y_2;

if (__static_condition_default_3) {
 __y_2  = 4 ;

}

if (__static_condition_default_4) {
 __x_1  =  __y_2  ;

}

{
if (__static_condition_default_5) {
 __x_1  ++ ;

}

if (__static_condition_default_6) {
 __x_1  ++ ;

}

}}

}

if (__static_condition_default_9) {
{
int  __x_1;
int  __y_2;

if (__static_condition_default_3) {
 __y_2  = 4 ;

}

if (__static_condition_default_4) {
 __x_1  =  __y_2  ;

}

{
if (__static_condition_default_5) {
 __x_1  ++ ;

}

if (__static_condition_default_6) {
 __x_1  ++ ;

}

}
if (__static_condition_default_7) {
return  __x_1  ;

}
}

}

}
}

