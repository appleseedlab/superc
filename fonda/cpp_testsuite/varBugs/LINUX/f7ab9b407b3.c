#ifdef CONFIG_TMPFS
#define CONFIG_SHMEM
#endif

#define NULL ((void*)0)

typedef int filler_t(int);

int some_fun(int n)
{
  return n;
}

#ifdef CONFIG_TMPFS
filler_t *f = &some_fun;
#else
filler_t *f = NULL; // (1)
#endif

#ifdef CONFIG_SHMEM
filler_t* shmem_get_inode()
{
  return f; // (11)
}
#else
filler_t* ramfs_get_inode()
{
  return &some_fun;
}

#define shmem_get_inode()ramfs_get_inode()
#endif /* CONFIG_SHMEM */

filler_t* shmem_file_setup()
{
  return shmem_get_inode(); // (10)
}

#ifdef CONFIG_DRM_I915
int drm_gem_object_init(filler_t **readpage)
{
  *readpage = shmem_file_setup(); // (9)
  return 0;
}

void i915_gem_alloc_object(filler_t **readpage)
{
  if (drm_gem_object_init(readpage) != 0) // (8)
    ;
}

void do_read_cache_page(filler_t *filler)
{
  filler(0); // ERROR (18)
}

void read_cache_page_gfp(filler_t **readpage)
{
  filler_t *filler = *readpage; // (15) filler = NULL
  do_read_cache_page(filler); // (17)
}

int i915_gem_object_get_pages_gtt(filler_t **readpage)
{
  read_cache_page_gfp(readpage); // (15)
  return 0;
}

int i915_gem_object_bind_to_gtt(filler_t **readpage)
{
  return i915_gem_object_get_pages_gtt(readpage); // (14)
}

int i915_gem_object_pin(filler_t **readpage)
{
  return i915_gem_object_bind_to_gtt(readpage); // (13)
}

int intel_init_ring_buffer(filler_t **readpage)
{
  i915_gem_alloc_object(readpage); // (7) *readpage = NULL
  return i915_gem_object_pin(readpage); // (12)
}

int intel_init_render_ring_buffer(filler_t **readpage)
{
  return intel_init_ring_buffer(readpage); // (6)
}

int i915_gem_init_ringbuffer(filler_t **readpage)
{
  return intel_init_render_ring_buffer(readpage); // (5)
}

int i915_load_modeset_init(filler_t **readpage)
{
  return i915_gem_init_ringbuffer(readpage); // (4)
}

int i915_driver_load()
{
  filler_t *readpage;
  return i915_load_modeset_init(&readpage); // (3)
}
#endif

int main()
{
  #ifdef CONFIG_DRM_I915
  i915_driver_load(); // (2)
  #endif
  return 0;
}
