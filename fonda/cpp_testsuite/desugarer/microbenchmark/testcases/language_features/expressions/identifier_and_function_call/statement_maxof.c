#define maxof(a,b) ({typeof(a)aa=a;typeof(b)bb=b;aa>bb?aa:bb;})
#ifdef A
extern int get(char*,char*);
#else
extern int get(const char*,const char*);
#endif
int main()
{
  char * x;
  int a = maxof(5,get(x,"44"));
  return 0;
}
