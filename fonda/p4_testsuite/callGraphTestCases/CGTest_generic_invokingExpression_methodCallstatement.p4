extern test<T> {
    test();
    // getTheDifference is a generator function even when
    // extern is resolved with generic (because of H)
    T getTheDifference<H>(in H a, bit<16> b);

    // getTheSum wouldn't be an instance when extern
    // resolved - so wouldn't be generated again
    T getTheSum(in T a, bit<16> b);

    // no generic return type
    bool isEqual(in bit<16> a, T b);
}

// doesn't have global type parameter (extern declaration parent of method prototype)
extern parentNotGeneric {
    parentNotGeneric();
    bool isEqual2<T>(in bit<16> a, T b);
}

parser name(bit<16> a) {
    test<bit<16>>() e;
    parentNotGeneric() f;

    bool isEqual = e.isEqual(5, 6);
    bool isEqual2 = f.isEqual2(5, 10w6);

    state State {
        e.getTheDifference(a, 5);
        bit<16> c = e.getTheSum(a, 5);
    }
}