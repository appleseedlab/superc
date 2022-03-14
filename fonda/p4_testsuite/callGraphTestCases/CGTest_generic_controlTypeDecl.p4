control type_decl<T>(out T b);

control dummy(out bit<16> b) {
    bit<16> a;
    apply {
        a = b;
    }
}

package final_package(type_decl<bit<16>> input_obj);

final_package(dummy()) test;