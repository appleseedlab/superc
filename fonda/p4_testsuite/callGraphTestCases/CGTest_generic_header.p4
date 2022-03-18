header header1_test<T> {
    T a;
    bit<48> test;
}

control test() {
    header1_test<bool> hdr_var;
    apply { }
}