// Conditionals surrounding headerTypeDeclaration
// Differs from other examples as the conditionals are not back to back

#ifdef WITH_INT_SINK
header int_data_t {
    varbit<8032> data;
}
#endif

action helloThere (int j, int i) {
    int j = 5;
}

#if define(INT_TRANSIT)
header int_transmit_data {
    varbit<1024> data_transmit;
}
#endif

header with_int {
    varbit<64> regular_int;
}