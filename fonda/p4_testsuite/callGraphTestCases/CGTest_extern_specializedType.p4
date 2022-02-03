extern packet_in<T> {
    void extract<T>(out T headerLvalue);
    T lookahead<T>();
    bit<32> length();  // This method may be unavailable in some architectures
    void advance(bit<32> bits);
    packet_in(int a); // constructor
}