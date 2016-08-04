// {{ dg-preprocess "Need preprocessing" }}

// Hack to circumvent Mac OS X error
#define __AVAILABILITY__
#define __OSX_AVAILABLE_STARTING(x,y)

// Declare GCC builtins
#include <stddef.h>
void* __builtin___memcpy_chk(void *, const void *, size_t, size_t);
void* __builtin___memmove_chk(void *, const void *, size_t, size_t);
void* __builtin___memset_chk(void *, int, size_t, size_t);
char* __builtin___strcpy_chk(char * __restrict, const char * __restrict, size_t);
char* __builtin___stpcpy_chk(char *, const char *, size_t);
char* __builtin___stpncpy_chk(char * __restrict, const char * __restrict,
                              size_t, size_t);
char* __builtin___strncpy_chk(char * __restrict, const char * __restrict,
                              size_t, size_t);
char* __builtin___strcat_chk(char * __restrict, const char * __restrict, size_t);
char* __builtin___strncat_chk(char * __restrict, const char * __restrict,
                               size_t, size_t);

#define __USE_STRING_INLINES
#include <string.h>

void test()
{
        char *p, *a;
        const char *s;

        while ( (s = a) )
          p = strcpy(strcpy(p,"/"), s);
}

