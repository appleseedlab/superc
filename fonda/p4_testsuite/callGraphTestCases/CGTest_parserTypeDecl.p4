extern test {
    test();
    void extract();
}

// parserTypeDeclaration can be generic
// but not parserDeclaration
parser normal_parser(in bit<16> a, test externObj);

control top()(normal_parser hello) {
    test() e;    
    apply {
    }
}