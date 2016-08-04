
#define bob __LINE__ \
  __LINE__

#ifdef A
#undef bob
#endif

bob
