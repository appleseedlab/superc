#define _paste(x, y) x ## y
#define paste(x, y) _paste(x, y)

#ifdef A
#define ma __ma
#else
#define ma ma
#endif

int paste(ma, in)() {
}

