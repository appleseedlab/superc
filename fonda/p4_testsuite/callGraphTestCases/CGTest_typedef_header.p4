header GH<T> {
    T data;
}

typedef GH<bit<16>>[3] Stack;

control c(out bit x) {
    GH<bool> g;
    apply {
        Stack s;
        bool b = s[0].isValid();
        b = g.isValid();
    }
}