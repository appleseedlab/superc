int main() {
  struct s* local_var;

  struct s {
    char y;
  };

  return local_var->y;
}

struct s {
  int x;
};

/* struct s { */
/*   int x; */
/* }; */
