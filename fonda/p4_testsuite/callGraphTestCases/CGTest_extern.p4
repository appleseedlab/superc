extern packet_in {
    void extract(out int headerLvalue);
    T lookahead();
    bit<32> length();  // This method may be unavailable in some architectures
    void advance(bit<32> bits);
    packet_in(int a); // constructor
}