extern int A_config_C1;
extern int A_config_defined_C2;

// may not be able to handle multiply-defined externs without dealing with external linkage
extern int x();
// extern float x();

int main() {
  x();
}
