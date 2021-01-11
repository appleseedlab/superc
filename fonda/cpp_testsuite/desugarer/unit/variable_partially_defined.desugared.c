#include <stdbool.h>

extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_5;
extern const bool __static_condition_default_16;
extern const bool __static_condition_default_13;
extern const bool __static_condition_default_15;
extern const bool __static_condition_default_14;
extern const bool __static_condition_default_18;
extern const bool __static_condition_default_12;
extern const bool __static_condition_default_2;
extern const bool __static_condition_default_17;
void __static_initializer_default() {
__static_renaming("__a_0", "a");
__static_renaming("__a_3", "a");
__static_renaming("__a_8", "a");
__static_renaming("__x_9", "x");
__static_renaming("__x_10", "x");
__static_renaming("__main_11", "main");

__static_condition_renaming("__static_condition_default_2", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (or (and |(defined A)| |(defined B)|)    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))    (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (or (and |(defined B)| (not |(defined C)|)) (and |(defined B)| |(defined C)|)))");
__static_condition_renaming("__static_condition_default_5", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (or (and |(defined A)| |(defined B)|)    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))    (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (let ((a!1 (not (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|)))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!2))))(assert |(defined C)|)");
__static_condition_renaming("__static_condition_default_12", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (or (and |(defined A)| |(defined B)|)    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))    (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (let ((a!1 (not (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|)))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!2))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and a!1 (not a!2) (not a!3) |(defined C)|)))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and (not a!1) (not a!2) (not a!3) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_13", "(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(declare-fun |(defined C)| () Bool)(assert (not (and |(defined A)| |(defined B)|)))(assert (not (and |(defined A)| (not |(defined B)|) (not |(defined C)|))))(assert (not (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (or (and |(defined B)| (not |(defined C)|)) (and |(defined B)| |(defined C)|)))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and a!1 (not a!2) (not a!3) |(defined C)|)))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and (not a!1) (not a!2) (not a!3) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_14", "(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(declare-fun |(defined C)| () Bool)(assert (not (and |(defined A)| |(defined B)|)))(assert (not (and |(defined A)| (not |(defined B)|) (not |(defined C)|))))(assert (not (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (let ((a!1 (not (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|)))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!2))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and a!1 (not a!2) (not a!3) |(defined C)|)))))(assert |(defined C)|)");
__static_condition_renaming("__static_condition_default_15", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (not |(defined C)|))(assert (or (and |(defined A)| |(defined B)|)    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))    (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (let ((a!1 (not (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|)))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!2))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and a!1 (not a!2) (not a!3) |(defined C)|)))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and (not a!1) (not a!2) (not a!3) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_16", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert (not |(defined C)|))(assert (not (and |(defined A)| |(defined B)|)))(assert (not (and |(defined A)| (not |(defined B)|) (not |(defined C)|))))(assert (not (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (or (and |(defined B)| (not |(defined C)|)) (and |(defined B)| |(defined C)|)))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and a!1 (not a!2) (not a!3) |(defined C)|)))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and (not a!1) (not a!2) (not a!3) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_17", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert |(defined C)|)(assert (not (and |(defined A)| |(defined B)|)))(assert (not (and |(defined A)| (not |(defined B)|) (not |(defined C)|))))(assert (not (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (or (and |(defined B)| (not |(defined C)|)) (and |(defined B)| |(defined C)|)))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and a!1 (not a!2) (not a!3) |(defined C)|)))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and (not a!1) (not a!2) (not a!3) |(defined C)|)))))");
__static_condition_renaming("__static_condition_default_18", "(declare-fun |(defined C)| () Bool)(declare-fun |(defined B)| () Bool)(declare-fun |(defined A)| () Bool)(assert |(defined C)|)(assert (not (and |(defined A)| |(defined B)|)))(assert (not (and |(defined A)| (not |(defined B)|) (not |(defined C)|))))(assert (not (and |(defined A)| (not |(defined B)|) |(defined C)|)))(assert (let ((a!1 (and (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|))                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!1)))(assert (let ((a!1 (not (or (and |(defined A)| |(defined B)|)                    (and |(defined A)| (not |(defined B)|) (not |(defined C)|))                    (and |(defined A)| (not |(defined B)|) |(defined C)|)))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not a!2))))(assert (let ((a!1 (or (and |(defined A)| |(defined B)|)               (and |(defined A)| (not |(defined B)|) (not |(defined C)|))               (and |(defined A)| (not |(defined B)|) |(defined C)|))))(let ((a!2 (and a!1                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|))))      (a!3 (and (not a!1)                (or (and |(defined B)| (not |(defined C)|))                    (and |(defined B)| |(defined C)|)))))  (not (and a!1 (not a!2) (not a!3) |(defined C)|)))))");

};

int  __a_0;

char  __a_3;

char char  __a_6;

char char  __a_8;
int  __x_9;
int  __x_10;
int  __main_11 () {
{

{
if (__static_condition_default_12) {
 __a_0  ;

}

if (__static_condition_default_13) {
 __a_3  ;

}

if (__static_condition_default_14) {
 __a_8  ;

}

}
{
if (__static_condition_default_15) {
 __x_9  = 7 *  __a_0  + 2 ;

}

if (__static_condition_default_16) {
 __x_9  = 7 *  __a_3  + 2 ;

}

if (__static_condition_default_17) {
 __x_10  = 7 *  __a_3  + 2 ;

}

if (__static_condition_default_18) {
 __x_10  = 7 *  __a_8  + 2 ;

}

}}


}

