control MyDeparser(in int packet, out int hdr) {
    #ifdef APPLY_1
    apply {
        packet.emit(hdr.ethernet);
        packet.emit(hdr.ipv4);
    }
    #endif
    #ifndef APPLY_1
    apply {
        packet.emit(hdr.ipv4);
        packet.emit(hdr.ethernet);
    }
    #endif
}