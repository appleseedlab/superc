parser parser_decl(out bit<16> b) {
    bit<16> a = 1;
    state start {
        b = a + b;
        transition accept;
    }
}

parser parser_type_decl<T>(out T b);
package only_package<T>(T _p);

only_package<parser_type_decl<bit<16>>>(parser_decl()) test;