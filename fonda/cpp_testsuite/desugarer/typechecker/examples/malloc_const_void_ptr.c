# define __attribute_deprecated__ __attribute__ ((__deprecated__))

#ifdef _LIBC
# define __MALLOC_HOOK_VOLATILE
# define __MALLOC_DEPRECATED
#else
# define __MALLOC_HOOK_VOLATILE volatile
# define __MALLOC_DEPRECATED __attribute_deprecated__
#endif

/* Hooks for debugging and user-defined versions. */
extern void (*__MALLOC_HOOK_VOLATILE __free_hook) (void *__ptr,
                                                   const void *)
__MALLOC_DEPRECATED;

int main()
{
  return 0;
}
