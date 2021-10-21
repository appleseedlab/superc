#define ENOMEM      12  /* Out of memory */

#define NULL (void*)0

extern void *malloc (unsigned long __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));

__attribute__ ((noinline)) int nondet() { return 42; }

extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
                     unsigned long __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

#define refptr(mod) (mod[0])
#define module_core(mod) (mod[1])

int load_module()
{
  void *hdr;
  void **mod;
  long err = 0;
  void *ptr = NULL;

  if ((hdr = malloc(2*sizeof(void*))) == NULL) // (2)
    return -ENOMEM;

  mod = (void *)hdr; // (3)

#if defined(CONFIG_MODULE_UNLOAD) && defined(CONFIG_SMP)
  refptr(mod) = malloc(32);
  if (!refptr(mod))
    {
      err = -ENOMEM;
      goto free_mod;
    }
  #endif

  ptr = malloc(512); // (4)
  if (!ptr) {
    err = -ENOMEM;
    goto free_percpu;
  }
  module_core(mod) = ptr; // (5)

  while (nondet()) {
    void *dest = module_core(mod); // (6)
    memcpy(dest, mod, sizeof(2*sizeof(void*))); // (7)
    mod = module_core(mod); // (8) `mod' and `module_core(mod)' are aliases
    if (nondet())
      break;
  }

  if (nondet())
    goto free_unload; // (9)

  return 0;

 free_unload:
 free_core:
  free(module_core(mod)); // (10) frees `module_core(mod)' and thus `mod' too
 free_percpu:
#if defined(CONFIG_MODULE_UNLOAD) && defined(CONFIG_SMP)
  free(refptr(mod)); // (11) ERROR: dereferencing already freed `mod'.
  #endif
 free_mod:
 free_hdr:
  free(hdr);

  return err;
}

int main(void) {
  load_module(); // (1)
  return 0;
}
