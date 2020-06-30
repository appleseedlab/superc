extern bool CONFIG_SMP; /* originally a macro */

// will need to check for conflicts across compilation units or do renaming across compilation units
extern void cpu_load_update_active(int this_rq);

// static function needs no external linkage
static void cpu_load_update_active_R1(int this_rq) { }

int main() {
  if (CONFIG_SMP) {
    cpu_load_update_active();
  }
  if (! CONFIG_SMP) {
    cpu_load_update_active_R1();
  }
}
