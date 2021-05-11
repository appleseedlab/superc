// Second child of the conditional node after merging subparser 
// for the first time is optAnnotations() that is present under parserState
// because it is merging constructs as far as possible (reduction on parent vs child of sibling)

// parser declaration
@hello parser starting (in bool k) {
    // parserLocalElements
    #ifdef V6
    bit<12> last_ipv6_dscp = 0;
    #endif

    // parserStates
    state parse_packet_out {
        k.extract(hdr.packet_out);
        #ifdef DIRECT_APPLY
        k.apply();
        #endif
        transition parse_ethernet;
    }
}