typedef unsigned long __u64;

#ifdef CONFIG_S390_PRNG
static unsigned char parm_block[32] = {
0x0F,0x2B,0x8E,0x63,0x8C,0x8E,0xD2,0x52,0x64,0xB7,0xA0,0x7B,0x75,0x28,0xB8,0xF4,
0x75,0x5F,0xD2,0xA6,0x8D,0x97,0x11,0xFF,0x49,0xD8,0x23,0xF3,0x7E,0x21,0xEC,0xA0,
};

void prng_seed(int nbytes)
{
  char buf[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int i = 0;

  if (nbytes > 16)
      return;

  while (nbytes >= 8) {
      *((__u64 *)parm_block) ^= *((__u64 *)buf+i*8); // ERROR
          i += 8;
              nbytes -= 8;
                }
                }
                #endif

int main(int argc, char *argv[])
{
#ifdef CONFIG_S390_PRNG
  prng_seed(16);
  #endif
    return 0;
    }
    