// Conditional surrounding method prototype

extern Crc16 <T> {
    #ifdef TOKEN
    // method prototype
    void hash<U>(in U input_data);
    #else
    void hash<U>(in U output_data);
    #endif
    U id<U>(in U x);
}