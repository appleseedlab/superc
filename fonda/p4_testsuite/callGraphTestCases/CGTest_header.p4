header header1_test {
    bit<16> a;
    bit<48> test;
}

control test() {
    header1_test hdr_var;
    apply { }
}