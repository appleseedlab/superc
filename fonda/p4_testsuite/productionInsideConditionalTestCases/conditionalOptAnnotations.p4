// conditional nodes surrounding optAnnotations (-> annotations -> annotation)
// for some reason conditional nodes surround productions inside other productions as well
// (guessing because how the grammar is annotated) 

#ifdef HELLO_ANNT
@hello 
#elif defined(NOT_HELLO_ANNT)
@not_hello
#else
@dummy_annts
#endif
parser starting (in bool k) {
    bit<6> last_ipv4_dscp = 0;
    bit<12> last_ipv6_dscp = 0;

    state parse_packet_out {
        k.extract(hdr.packet_out);
        transition parse_ethernet;
    }
}
