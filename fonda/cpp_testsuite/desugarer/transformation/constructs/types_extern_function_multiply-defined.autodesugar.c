#include <stdbool.h>
#include "desugared_macros.h" // configuration macros converted to C variables
extern bool _C_40496; /* renamed from A */
extern bool _C_40496_DEFINED;

extern int _V0y6ixj_x /* renamed from x */ ( ) ; 

extern float _V1Imfho_x /* renamed from x */ ( int ) ; 

int _F2UnsOl_main /* renamed from main */ ( ) {
if (1) { /* from static conditional around function definition */
{ if (_C_40496_DEFINED) { /* from static conditional around statement */
_V0y6ixj_x ( ) ; 
}
if (!_C_40496_DEFINED) { /* from static conditional around statement */
_V1Imfho_x ( ) ; 
}
} 
}
}

int main(int argc, char **argv) { // multiplexed function
if (1) {
_F2UnsOl_main(argc, argv);
}
}
