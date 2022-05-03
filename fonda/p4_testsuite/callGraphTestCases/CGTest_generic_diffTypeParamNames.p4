struct Child<G> {
    G data;
}

struct Parent<T> {
    Child<T> g;
}

control c() {
    apply {
        Parent<bit<16>> n;
        bit<16> x = n.g.data;
    }
}