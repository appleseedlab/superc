const bit<16> TYPE_IPV4 = 0x800;
#ifdef CONFIG_A
    const bit<16> TYPE_IPV6 = 0x900;
#endif

parser MyParser (in bool k) {
    state start {
        transition parse_ethernet;
    }

    state parse_ethernet {
        packet.extract(hdr.ethernet);
        transition select(hdr.ethernet.etherType){
            TYPE_IPV4: parse_ipv4;
            #ifdef CONFIG_A
                TYPE_IPV6: parse_ipv6;
            #endif
            default: accept;
        }
    }
}