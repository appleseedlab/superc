parser parser_decl(bit<16> b) {
    bit<16> a = 1;
    state start {
        a = a + b;
        transition accept;
    }
}

parser parser_type_decl(bit<16> b);
package only_package(parser_type_decl _p);

only_package(parser_decl()) test;