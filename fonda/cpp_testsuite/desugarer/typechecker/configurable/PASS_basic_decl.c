int main() {

#if A
	int a;
#else
	int b;
#endif

int
  #ifdef A
  *
  #else
  **
  #endif
    c;
   
  
	return 0;
}
