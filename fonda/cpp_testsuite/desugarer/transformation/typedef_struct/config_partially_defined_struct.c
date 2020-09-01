#if defined(A)
typedef struct bob {
  int val;

  char otherVal;
} bob;
#endif

int main(void) {
#if defined(A)
  bob bobStruct;
  bobStruct.val = 1;
#endif
}
