/*
The kernel source uses nonboolean configuration variables in
C code.  Without these being defined, the parser will see an
identifier where a constant should be and throw an error.
*/
#define CONFIG_ILLEGAL_POINTER_VALUE 0xdead000000000000
