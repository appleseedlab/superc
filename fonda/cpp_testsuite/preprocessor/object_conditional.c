#define BUFFER_SIZE 1024
#if A
  #define BUFFER_SIZE 2048
#endif
foo = (char *) malloc (BUFFER_SIZE);
