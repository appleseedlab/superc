#include <stdbool.h>
#include "desugared_macros.h" // configuration macros converted to C variables
extern bool _C_40496; /* renamed from A */
extern bool _C_40496_DEFINED;

static int _V0NWK0Y_x /* renamed from x */ ; 

int _F1DGKM9_main /* renamed from main */ ( ) {
if (1) { /* from static conditional around function definition */
{ 
char _V2fh8Co_x /* renamed from x */ ; 
if (_C_40496_DEFINED) { /* from static conditional around statement */
_V0NWK0Y_x ++ ; 
}
if (!_C_40496_DEFINED) { /* from static conditional around statement */
_V2fh8Co_x ++ ; 
}
if (_C_40496_DEFINED) { /* from static conditional around statement */
return _V0NWK0Y_x ; 
}
if (!_C_40496_DEFINED) { /* from static conditional around statement */
return _V2fh8Co_x ; 
}
} 
}
}

int main(int argc, char **argv) { // multiplexed function
if (1) {
_F1DGKM9_main(argc, argv);
}
}
