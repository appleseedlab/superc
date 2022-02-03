parser P<H>(inout H data) { 
    state start {
        transition select(b) {
            5: parse_tcp_option_sack;
            0: parse_tcp_option_end;
            1: parse_tcp_option_nop;
            2: parse_tcp_option_ss;
            3: parse_tcp_option_s;
        }
    }

// Some states omitted

    state parse_tcp_option_sack {
        transition start;
    }
}
