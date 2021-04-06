// Surrounding parserTypeDeclaration
// Second child after merging (mergers subparser only one) is optAnnotations()
// second stackframe after merging is not a conditional node - list propert similar to headerAndAction

#ifdef STARTING_PARSER
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
#endif
