#if A
typedef struct bob {
  int val;

  char otherVal;
} bob;
#endif

int main(void) {
  #if A
  bob bobStruct;
  bobStruct.val = 1;
  #endif
}