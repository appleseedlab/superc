bool isGreaterThan(bit<16> a, bit<16> b) {
    if(a < b) {
        return false;
    }

    return true;
}

control test_control(bit<16> a) {
    bool c = isGreaterThan(a, 5);

    apply {}
}