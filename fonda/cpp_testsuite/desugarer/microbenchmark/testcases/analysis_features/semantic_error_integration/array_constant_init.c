int x = 2;
#ifdef CONSTANT
static const int data[] = {1,5,6+2,x+5 };
#else
static const int data[] = {1,5,6+2,5 };
#endif

int main() {
  return data[3];
}
