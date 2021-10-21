#include <stdio.h>

#ifdef ULTRA_LCD
//  convert float to string with +1234.5 format
char *ftostr51(float x)
{
  int16_t xx=x*10;
  conv[0]=(xx>=0)?'+':'-';
  xx=abs(xx);
  conv[1]=(xx/10000)%10+'0';
  conv[2]=(xx/1000)%10+'0';
  conv[3]=(xx/100)%10+'0';
  conv[4]=(xx/10)%10+'0';
  conv[5]='.';
  conv[6]=(xx)%10+'0';
  conv[7]=0;
  return conv;
}
#endif

int main(int argc, char **argv)
{
  ftostr51(512.5);
  return 0;
}
