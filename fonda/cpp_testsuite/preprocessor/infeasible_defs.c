#ifdef A
#define BOB 1
#endif

#ifdef A
BOB
#endif

BOB

#ifdef B
#undef BOB
#endif

BOB
