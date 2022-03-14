extern test {
    test();
    void extract();
}

// parserTypeDeclaration can be generic
// but not parserDeclaration
parser with_generics<T, U>(in T a, U externObj);

control top()(with_generics<bit<16>, test> hello) {
    test() e;
    apply {
        e.extract();
    }
}