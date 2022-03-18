bool isEqual<S>(S a, S b) {
    if(a == b) {
        return false;
    }

    return true;
}

control test_control(bit<16> a) {
    bool c = isEqual<bit<16>>(a, 5);

    apply {}
}