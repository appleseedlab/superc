parser P(inout int data) { 
    state start {
        int b;
        transition select(b) {
            0: parse_tcp_option_ss;
            1: parse_tcp_option_s;
            2: parse_tcp_option_sack;
        }
    }

    state parse_tcp_option_s {
        transition start;
    }

    state parse_tcp_option_ss {
        transition start;
    }

    state parse_tcp_option_sack {
        transition start;
    }
}
