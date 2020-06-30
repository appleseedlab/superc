#include <stdbool.h>
#include "desugared_macros.h" // configuration macros converted to C variables
extern bool _C_40496; /* renamed from A */
extern bool _C_40496_DEFINED;

struct test { int x ; } ; 

int _F1K4sj1_main /* renamed from main */ ( ) {
if (1) { /* from static conditional around function definition */
{ 
struct test _V2n3sqb_var /* renamed from var */ ; 

int _V3nkcU9_var /* renamed from var */ ; 
if (_C_40496_DEFINED) { /* from static conditional around statement */
_V2n3sqb_var . x = 1 ; 
}
if (!_C_40496_DEFINED) { /* from static conditional around statement */
_V3nkcU9_var . x = 1 ; 
}
} 
}
}

int main(int argc, char **argv) { // multiplexed function
if (1) {
_F1K4sj1_main(argc, argv);
}
}
