// Breaks generateInstance function
// 1. When childStruct<T, c> t; is added as a structField, the type is stillchildStruct<T, S> since not all the generic values are defined (T)
// 2. When parentHdr is instantiated as a type for variable hdr_var, it passed in value for T
// 2a. So ideally childStruct shouldn't have a problem being created as a regular object as all values are defined
// But breaks in current implementation as the value of c cannot be referred when generating instance of childStruct
// as c is in the AST and cannot be retrieved in the P4LanguageObject generateInstance function
struct childStruct<T, S> {
    T varIt;
    S a;
}

header parentHdr<T> {
    bool c;
    childStruct<T, c> t;
    T a;
}

control test() {
    parentHdr<bit<16>> hdr_var;
    bit<16> value;
    apply { 
    }
}