#ifdef CONFIG_REGULATOR_MAX8660
#ifdef CONFIG_OF
int max8660_pdata_from_dt(int *pdata)
{
  *pdata++;
  return 0;
}
#else
int max8660_pdata_from_dt(int **pdata)
{
  return 0;
}
#endif

int max8660_probe()
{
  int pdata_of = 0;
  max8660_pdata_from_dt(&pdata_of); // ERROR
  return 0;
}
#endif

int main() {
    #ifdef CONFIG_REGULATOR_MAX8660
  max8660_probe();
    #endif
  return 0;
}
