control process_int_main () {
    apply {
    }
}

function whatis() {}

parser P<H>(inout H data) {
    state itis {

    }
    state parse_tcp_option_s {
        test = 1;
        itis<>(1 || 1);
        check.flag[process_int_main()] = 5;
        check.flag[whatis()] = 5;
        check.flag[.whatis()] = 5;
    }
}