extern test {
    test();
    T getTheDifference<T>(in T a, bit<16> b);
}

parser name(bit<16> a) {
    test() e;

    state State {
        bit<16> c = e.getTheDifference(a, 5);
    }
}