// From linux-3.2.9/drivers/scsi/t128.c

static inline int NCR5380_pread (struct Scsi_Host *instance, unsigned char *dst,
                                 int len) {
#if MACRO // was actually 0, but this makes it more interesting :)
  for (; i; --i) {
    while (!(readb(base+T_STATUS_REG_OFFSET) & T_ST_RDY)) barrier();
#else
    while (!(readb(base+T_STATUS_REG_OFFSET) & T_ST_RDY)) barrier();
    for (; i; --i) {
#endif
      *d++ = readb(reg);
    }
}
