extern packet_in {
    void extract<T>(out T headerLvalue);
    T fillin<T>(int number);
}

extern packet_out_fake {
    void compile<O, T>(out O hello, in T hi);
    int fake2();
}

header ipv6_t {
    bit<4> next_hdr;
    packet_out_fake packet_out_test;
}

struct parsed_headers_t {
    int ethernet;
    ipv6_t ipv6;
}

struct fabric_metadata_t {
    bit<8>        ip_proto;
}

parser FabricParser (packet_in packet,
                     out parsed_headers_t hdr,
                     inout fabric_metadata_t fabric_metadata) {

    bit<6> last_ipv4_dscp = 0;

    state start {
        transition select(hdr.ethernet) {
            8w6: empty;
        }
    }

    state empty {

    }

    state parse_packet_out {
        // call made to packet (packet_in type)
        // lvalue construct based namespacing for packet.extract()
        packet.extract(hdr.ethernet);
        // type checking next_dr under ipv6 scope under the hdr scope
        fabric_metadata.ip_proto = hdr.ipv6.next_hdr;
        // call made to packet_out_fake construct
        // namespacing parsed_headers_t -> ipv6_t -> packet_out_fake -> compile
        // (expression construct for hdr.ipv6.packet_out_test.compile())
        packet.extract(hdr.ipv6.packet_out_test.compile());
        transition select(packet.fillin<packet_out_fake>(2).fake2()) {
            default : start;
        }
    }
}