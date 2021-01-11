void AES256_CTR_DRBG_Update(unsigned char *provided_data, unsigned char *Key, unsigned char *V) {
 unsigned char temp[48];
 for (int i = 0; i < 3; i++) {
  for (int j = 15; j >= 0; j--) {
  }
 }
 if (provided_data != ((void *)0))
  for (int i = 0; i < 48; i++) {
   temp[i] ^= provided_data[i];
 }
}
