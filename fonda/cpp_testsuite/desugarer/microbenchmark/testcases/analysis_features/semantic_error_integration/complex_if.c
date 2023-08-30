struct x {
  int revents;
};

int x
#ifdef A
() 
#endif
  ;

#ifdef A
int x () { return 2; }
#endif

int main()
{
  struct x *pfd;
  if ( (  pfd[2].revents & 0x010 ) && x() == 0 ) {
  }
  return 3;
}
