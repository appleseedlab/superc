#if defined(A)
typedef int typeAlias;
#endif


typedef struct bob {
  typeAlias val;

  char otherVal;
} bob;

int main(void) {
  bob bobStruct;
  bobStruct.val = 1;
}
