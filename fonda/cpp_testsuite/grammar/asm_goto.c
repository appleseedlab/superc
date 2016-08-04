// asm goto argument
// From linux-3.3-rc4/arch/x86/include/asm/cpufeature.h:L337
int main() {
  int bit = 4096;
  asm goto("1: jmp %l[t_no]\n"
           "2:\n"
           ".section .altinstructions,\"a\"\n"
           " .long 1b - .\n"
           " .long 0\n"           /* no replacement */
           " .word %P0\n"         /* feature bit */
           " .byte 2b - 1b\n"     /* source len */
           " .byte 0\n"           /* replacement len */
           ".previous\n"
           /* skipping size check since replacement size = 0 */
           : : "i" (bit) : : t_no);
  return 0;
 t_no :
  return 1;
}
