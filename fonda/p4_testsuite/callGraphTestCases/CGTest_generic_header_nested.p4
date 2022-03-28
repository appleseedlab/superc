// Note: not compiling in p4c if struct if defined before
// (CGTest_generic_header.p4 compiles), need to check why
header parentHdr<T> {
    T t;
}

struct childStruct {
    bit<16> varIt;
    parentHdr<bit<16>> t;
}

header header1_test<T> {
    T a;
    bit<48> test;
    childStruct structTest;
}

const bit<16> a = 2 * 5;

control test() {
    header1_test<bit<16>> hdr_var;
    bit<16> value;
    apply { 
        hdr_var.isValid();
        value = hdr_var.structTest.t.setValid();
    }
}