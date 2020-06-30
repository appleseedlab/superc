// TODO: need to deal with external linkage, for now using largest bitwidth since linkers don't care
int x() {
  return 1;
}


int main() {
  // TODO: may create two branches, one for each call and cast the result
  x();
}
