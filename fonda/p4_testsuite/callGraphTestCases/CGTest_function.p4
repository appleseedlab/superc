bit<16> max(in bit<16> left, in bit<16> right) {
    if (left > right)
        left = right;
    // return right;
}

control c(out bit<16> b) {
    apply {
        max(10, 12);
    }
}

// change functionProtype usage to make name as identifier for extern and functiondeclaration
