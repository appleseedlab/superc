control process_int_main () {
    apply {
        if(hdr.int_header == 1) {
            hdr = hdr - 1;
        }
    }
}
control process_int_main () {
    apply {
        if(hdr.int_header == 1) {
            hdr = hdr - 2;
        }
    }
}
control process_int_main2 () {
    apply {
        if(hdr.int_header == 1) {
            hdr = hdr - 2;
        }
    }
}
// control, apply - use APPLY as namespace of fegress, directapplication
// future - use PC scope
control FabricEgress () {
    apply {
        process_int_main.apply(hdr);
    }
}

control FabricEgress () {
    apply {
        process_int_main.apply(hdr);
        process_int_main2.apply(hdr);
    }
}
