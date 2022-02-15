#ifdef CONFIG_BLK_CGROUP
#define CFQ_WEIGHT_DEFAULT500
#endif

#ifdef CONFIG_IOSCHED_CFQ
static long cfq_scale_slice()
{
  long d = 1;
  d = d * CFQ_WEIGHT_DEFAULT; // ERROR
  return d;
}
#endif


int main()
{
  #ifdef CONFIG_IOSCHED_CFQ
  cfq_scale_slice();
  #endif
  return 0;
}
