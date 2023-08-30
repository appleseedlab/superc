#ifdef ENABLE_A
struct {
  char p;
} data;
#endif

int main() {
#ifdef ENABLE_A

#else
  struct s;
  
  struct s {
    int y;
  } data;
#endif
  
#ifdef ENABLE_A
  data.p;
#endif

  return sizeof(data);
}

// sizeof(data)
