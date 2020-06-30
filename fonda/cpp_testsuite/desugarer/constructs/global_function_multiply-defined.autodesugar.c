#include <stdbool.h>
#include "desugared_macros.h" // configuration macros converted to C variables
extern bool _C_40496; /* renamed from A */
extern bool _C_40496_DEFINED;

int _F0iceH4_x /* renamed from x */ ( ) {
if (_C_40496_DEFINED) { /* from static conditional around function definition */
{ if (_C_40496_DEFINED) { /* from static conditional around statement */
return 1 ; 
}
} 
}
}


char _F1yFZOZ_x /* renamed from x */ ( ) {
if (!_C_40496_DEFINED) { /* from static conditional around function definition */
{ if (!_C_40496_DEFINED) { /* from static conditional around statement */
return 2 ; 
}
} 
}
}


int _F2JFFUV_main /* renamed from main */ ( ) {
if (1) { /* from static conditional around function definition */
{ if (_C_40496_DEFINED) { /* from static conditional around statement */
_F0iceH4_x ( ) ; 
}
if (!_C_40496_DEFINED) { /* from static conditional around statement */
_F1yFZOZ_x ( ) ; 
}
} 
}
}

int main(int argc, char **argv) { // multiplexed function
if (1) {
_F2JFFUV_main(argc, argv);
}
}
