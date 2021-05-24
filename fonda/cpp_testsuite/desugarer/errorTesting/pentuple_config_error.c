typedef
#ifdef A
long int
#else
int
#endif
#ifdef B
unsigned
#endif
ourType;
#ifdef C
ourType
#else
short
#endif
foo( int x,
#ifdef D
     int y
#endif
     ,
#ifdef E
     char z,
#else
#ifdef A
     ourType z
#endif
#endif
)
{
  return 0;
}

int main()
{
  return 0;
}

