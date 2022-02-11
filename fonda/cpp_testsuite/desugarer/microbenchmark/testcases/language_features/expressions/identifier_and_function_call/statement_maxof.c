#define maxof(a,b) ({typeof(a)aa=a;typeof(b)bb=b;aa>bb?aa:bb;})

int main()
{
#ifdef ENABLE_A
  return maxof(5, 6);
#else
  return maxof(4, 5);
#endif
}
