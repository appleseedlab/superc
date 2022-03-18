extern T test_function<T>(inout T z);

control dummy(out bit<16> b) {
    bit<16> a = test_function(b);
    apply {
        a = b;
    }
}