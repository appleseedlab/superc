#include <stdbool.h>
#include "desugared_macros.h" // configuration macros converted to C variables
extern bool _C_40496; /* renamed from A */
extern bool _C_40496_DEFINED;

static int _V0zWAm4_x /* renamed from x */ ; 

static char _V1fl0Eo_x /* renamed from x */ ; 

int _F2lROXB_main /* renamed from main */ ( ) {
if (1) { /* from static conditional around function definition */
{ if (_C_40496_DEFINED) { /* from static conditional around statement */
_V0zWAm4_x ++ ; 
}
if (!_C_40496_DEFINED) { /* from static conditional around statement */
_V1fl0Eo_x ++ ; 
}
} 
}
}

int main(int argc, char **argv) { // multiplexed function
if (1) {
_F2lROXB_main(argc, argv);
}
}
