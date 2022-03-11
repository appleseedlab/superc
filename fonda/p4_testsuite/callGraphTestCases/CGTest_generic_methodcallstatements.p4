extern test<T> {
    test();
    T getTheDifference<H>(in H a, bit<16> b);
}
parser name(bit<16> a) {
    test<bit<16>>() e;

    state State {
        e.getTheDifference(a, 5);
    }
}