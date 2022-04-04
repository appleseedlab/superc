X getSum<X>(X a) {
    X b;

    return b;
}

bool isEqual<T>(T a, bit<16> u) {
    bit<16> c = getSum(u);
    // bit<16> c = getSum<T>(a); // this does not compile
    return false;
}

control test_control(bit<16> a) {
    
    bool isEqualAnswer = isEqual<bit<16>>(16w1, 16w12);

    apply {}
}