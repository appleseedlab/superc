bool isGreaterThan(bit<16> a, bit<16> b) {
    if(a < b) {
        return false;
    }

    return true;
}

bool isGreaterThan(bit<16> c, bit<16> d, bit<16> e) {
    if(c < d && d > e) {
        return false;
    }
    return true;
}

control test_control(bit<16> a) {
    bool c = isGreaterThan(a, 5);
    bool d = isGreaterThan(a, 5, 6);

    apply {}
}