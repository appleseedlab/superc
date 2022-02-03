header int_data_t {
    #ifdef CONFIG_A
        bit<4> flag;
    #else
        bit<4> flag;
    #endif
}
