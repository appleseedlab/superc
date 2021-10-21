#if defined(CONFIG_ARCH_OMAP2420)
void omap2_set_globals_242x(void)
{
  return;
}
#endif

#ifdef CONFIG_MACH_OMAP_H4
static void omap_h4_map_io(void)
{
  omap2_set_globals_242x(); // ERROR
}
#endif

int main(int argc, char** argv)
{
  #ifdef CONFIG_MACH_OMAP_H4
  omap_h4_map_io();
  #endif
}
