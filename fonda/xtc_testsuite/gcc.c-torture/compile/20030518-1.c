/* Test case from PR middle-end/10472  */

// Declare to avoid warnings.
extern char * __builtin_stpcpy(char *, const char *);
extern void * __builtin_mempcpy(void *, const void *, unsigned long);

extern void f (char *);

void foo (char *s)
{
  f (__builtin_stpcpy (s, "hi"));
}

void bar (char *s)
{
  f (__builtin_mempcpy (s, "hi", 3));
}

