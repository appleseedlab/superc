#ifdef CONFIG_A
header int_data_t {
    varbit<8032> data;
}
#endif

#ifdef CONFIG_B
action ac1 (int j, int i) {
    int j = 5;
}
#endif


action ac2 () {
    int j = 5;
}