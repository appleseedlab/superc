control process_int_main () {
    apply {
        if(hdr.int_header == 1) {
            hdr = hdr - 1;
        }
    }
}

control FabricEgress () {
    apply {
        process_int_main.apply(hdr);
    }
}

parser P<H>(inout H data) { 
    state start {
        transition select() {
            5: parse_tcp_option_sack;
        }
    }

// Some states omitted

    state parse_tcp_option_sack {
        FabricEgress.apply();
        transition start;
    }
}
