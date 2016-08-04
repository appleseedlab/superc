#define  WARN_IF(EXP) do { if (EXP) fprintf(stderr, "Warning: " #EXP "\n"); } while (0)
WARN_IF (x == 0);
