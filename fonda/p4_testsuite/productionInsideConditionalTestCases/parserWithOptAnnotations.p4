// conditional surrounding parserLocalElement
// also prints optAnnotations are second child of stack after it merges subparser (it merges a total of once)

parser starting (in bool k) {
    bit<6> last_ipv4_dscp = 0;

    #ifdef V6
    bit<12> last_ipv6_dscp = 0;
    #endif

    state parse_packet_out {
        k.extract(hdr.packet_out);
        transition parse_ethernet;
    }
}
