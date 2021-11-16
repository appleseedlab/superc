parser P<H>(inout H data) { 
    state start {
        transition select(b.lookahead<bit<8>>()) {
            0: parse_tcp_option_end;
            1: parse_tcp_option_nop;
            2: parse_tcp_option_ss;
            3: parse_tcp_option_s;
            5: parse_tcp_option_sack;
        }
    }

// Some states omitted

    state parse_tcp_option_sack {
        transition start;
    }
}
