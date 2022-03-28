// Generic header union
header_union HU<T> {
    bit<16> regular;
    T generic;
}

control test() {
    HU<bit<16>> test;
    apply { 
    }
}
