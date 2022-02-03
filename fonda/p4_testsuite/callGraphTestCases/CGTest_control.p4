control process_int_main () {
    apply {
        if(hdr.int_header == 1) {
            hdr = hdr - 1;
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
