#include <stdbool.h>
#include "desugared_macros.h" // configuration macros converted to C variables
extern bool _C_n1583398147; /* renamed from CONFIG_A */
extern bool _C_n1583398147_DEFINED;

int _F0cClHB_main /* renamed from main */ ( ) {
if (1) { /* from static conditional around function definition */
{ 
int _V1GQ30P_x /* renamed from x */ ; 

char _V25ZLJX_x /* renamed from x */ ; 
if (_C_n1583398147_DEFINED) { /* from static conditional around statement */
_V1GQ30P_x ++ ; 
}
if (!_C_n1583398147_DEFINED) { /* from static conditional around statement */
_V25ZLJX_x ++ ; 
}
if (_C_n1583398147_DEFINED) { /* from static conditional around statement */
return _V1GQ30P_x ; 
}
if (!_C_n1583398147_DEFINED) { /* from static conditional around statement */
return _V25ZLJX_x ; 
}
} 
}
}

int main(int argc, char **argv) { // multiplexed function
if (1) {
_F0cClHB_main(argc, argv);
}
}
