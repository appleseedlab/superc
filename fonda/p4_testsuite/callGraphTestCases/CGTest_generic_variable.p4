// example does not compile with p4c
// test case made just to test SuperP4 generics
bit<16> getSum<S>(S a) {
    S b;

    b = a + 5;

    return b;
}

bool isEqual<T, S>(T u, S v) {
    if(u == v) {
        return true;
    }

    return false;
}

control test_control(bit<16> a) {
    bit<16> c = getSum(5);
    bool isEqualAnswer = isEqual<bit<16>, bit<16>>(1, 2);

    apply {}
}