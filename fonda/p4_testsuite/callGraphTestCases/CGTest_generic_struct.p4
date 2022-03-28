// Breaks generateInstance function
struct childStruct<T, S> {
    T varIt;
    S a;
}

control test() {
    childStruct<bit<16>, bool> struct_var;
    bit<16> value;
    apply { 
    }
}