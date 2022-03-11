extern test<T> {
    test();
    // getTheDifference is a generator function even when
    // extern is resolved with generic (because of H)
    T getTheDifference<H>(in H a, bit<16> b);

    // getTheSum wouldn't be an instance when extern
    // resolved - so wouldn't be generated again
    T getTheSum(in T a, bit<16> b);
}
parser name(bit<16> a) {
    test<bit<16>>() e;

    state State {
        e.getTheDifference(a, 5);
        bit<16> c = e.getTheSum(a, 5);
    }
}