// All conditionals are surrounding headerTypeDeclaration
// merges only once (subparser), and second child of the first conditional node is also a conditional node

#ifdef WITH_INT_SINK
header int_data_t {
    varbit<8032> data;
}
#elif define(INT_TRANSIT)
header int_transmit_data {
    varbit<1024> data_transmit;
}
#else
header with_int {
    varbit<64> regular_int;
}
#endif
