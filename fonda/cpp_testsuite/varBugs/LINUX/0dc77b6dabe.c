#ifdef CONFIG_ANDROID
#define CONFIG_SYSFS
#endif

#define ENOMEM      12  /* Out of memory */
#define EEXIST      17  /* File exists */

#define NULL (void*)0

extern void *malloc (unsigned long __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;

extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));

extern int strcmp (const char *__s1, const char *__s2)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

#ifdef CONFIG_SYSFS
static const char *linked = NULL;

int sysfs_link_sibling(const char *s_name)
{
  if (linked != NULL)
    return (!strcmp(s_name,linked)) ? -EEXIST : -ENOMEM;

  linked = s_name;
  return 0;
}

void sysfs_unlink_sibling(const char *s_name)
{
  if (linked != NULL && !strcmp(s_name,linked))
    linked = NULL;
}

int sysfs_create_dir(const char *name)
{
  return sysfs_link_sibling(name); // (6,13) ERROR
}

int kobject_add(const char *name)
{
  return sysfs_create_dir(name);
}

int *kobject_create_and_add(const char *name)
{
  int *kobj =(int*) malloc(sizeof(int));
  if (!kobj)
    return NULL;

  int retval = kobject_add(name); // (5,12)
  if (retval)
    {
      free(kobj);
      kobj = NULL;
    }

  return kobj;
}

int *class_compat_register(const char *name)
{
  int *kobj;

  kobj = kobject_create_and_add(name); // (4,11)
  if (!kobj)
    return NULL;

  return kobj;
}

void class_compat_unregister(const char *name)
{
  free(name);
}
#endif

#ifdef CONFIG_EXTCON
#if defined(CONFIG_ANDROID)
static int *switch_class;
#endif /* CONFIG_ANDROID */

int create_extcon_class(void)
{
#if defined(CONFIG_ANDROID)
  switch_class = class_compat_register("switch"); // (3,10)
  if (!switch_class)
    return -ENOMEM;
#endif /* CONFIG_ANDROID */
  return 0;
}

int extcon_class_init(void)
{
  return create_extcon_class(); // (2,9)
}

void extcon_class_exit(void)
{
  return;
}
#endif

int main(void)
{
  #ifdef CONFIG_EXTCON
  extcon_class_init(); // (1)
  extcon_class_exit(); // (7)
  extcon_class_init(); // (8)
  #endif
  return 0;
}
