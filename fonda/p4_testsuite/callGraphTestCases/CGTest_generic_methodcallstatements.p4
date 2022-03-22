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
// Note: output is:
// getTheDifference: a(PARAMETER, BASETYPE), b(PARAMETER, BASETYPE)
// getTheDifference: H(TYPEPARAMETER), a(PARAMETERGENERATOR, TYPEPARAMETER), b(PARAMETER, BASETYPE)
// getTheDifference: H(TYPEPARAMETER), a(PARAMETERGENERATOR, TYPEPARAMETER), b(PARAMETER, BASETYPE)
// Need to differentiate the first two
