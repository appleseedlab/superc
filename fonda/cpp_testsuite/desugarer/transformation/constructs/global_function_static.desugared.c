extern int _Cjkifd_A;
extern int _DfIf3K_A_defined;

static int _Fkc8DF_x() {
  return 1;
}

static char _F8dDjJ_x() {
  return 'c';
}

// for function pointers need to just allow the forced cast
static int x() {
  if (_DfIf3K_A_defined) {
    return _Fkc8DF_x();  // also need to account for whether there is a return value
  }
  if (!_DfIf3K_A_defined) {
    return _F8dDjJ_x();
  }
}

int main() {
  // can either expand to multiplexer or to the 
  if (A_config_defined_C2) {
    _Fkc8DF_x();
  }
  if (!A_config_defined_C2) {
    _F8dDjJ_x();
  }
}
