extern packet_in {
    void extract<T>(out T headerLvalue);
    void extract<T>(out T variableSizeHeader, in bit<32> varFieldSizeBits);
    T lookahead<T>();
    bit<32> length();  // This method may be unavailable in some architectures
    void advance(bit<32> bits);
}

typedef bit<9>  PortId_t; 

struct standard_metadata_t {
    PortId_t    ingress_port;
    PortId_t    egress_spec;
    PortId_t    egress_port;
}

header ipv4_t {
    bit<4> version;
    bit<4> ihl;
    bit<6> dscp;
    bit<2> ecn;
    bit<16> total_len;
    bit<16> identification;
    bit<3> flags;
    bit<13> frag_offset;
    bit<8> ttl;
    bit<8> protocol;
    bit<16> hdr_checksum;
    bit<32> src_addr;
    bit<32> dst_addr;
}

header ipv6_t {
    bit<4> next_hdr;
}

header eth_type_t {
    bit<16> value;
}

header ethernet_t {
    eth_type_t eth_type;
}

struct parsed_headers_t {
    ethernet_t ethernet;
    int packet_out;
    ipv4_t ipv4;
    ipv6_t ipv6;
}

struct fabric_metadata_t {
    bit<16>       ip_eth_type;
    int     vlan_id;
    bit<3>        vlan_pri;
    bit<1>        vlan_cfi;
    bit<8>        mpls_ttl;
    bool         skip_forwarding;
    bool         is_ipv4;
    bool         is_ipv6;
    int    fwd_type;
    int     next_id;
    bool         is_multicast;
    bool         is_controller_packet_out;
    bit<8>        ip_proto;
    bit<16>       l4_sport;
    bit<16>       l4_dport;
    bit<32>       ipv4_src_addr;
    bit<32>       ipv4_dst_addr;
    int    slice_id;
    bit<2>        packet_color;
    bit<6>        dscp;
}

parser FabricParser (packet_in packet,
                     out parsed_headers_t hdr,
                     inout fabric_metadata_t fabric_metadata,
                     inout standard_metadata_t standard_metadata) {

    bit<6> last_ipv4_dscp = 0;

    state start {
        transition select(standard_metadata.ingress_port) {
            1: parse_packet_out;
            default: parse_ethernet;
        }
    }

    state parse_packet_out {
        packet.extract(hdr.packet_out);
        transition parse_ethernet;
    }

    state parse_ethernet {
        packet.extract(hdr.ethernet);
        // fabric_metadata.last_eth_type = hdr.ethernet.eth_type;
        fabric_metadata.vlan_id = DEFAULT_VLAN_ID;
        transition select(hdr.ethernet.eth_type){
            // // ETHERTYPE_QINQ: parse_vlan_tag;
            // ETHERTYPE_QINQ_NON_STD: parse_vlan_tag;
            // ETHERTYPE_VLAN: parse_vlan_tag;
            // ETHERTYPE_MPLS: parse_mpls;
            // ETHERTYPE_IPV4: pre_parse_ipv4;
            // ETHERTYPE_IPV6: pre_parse_ipv6;
            default: accept;
        }
    }


    state parse_mpls {
        // packet.extract(hdr.mpls);
        // fabric_metadata.is_mpls = _TRUE;
        // fabric_metadata.mpls_label = hdr.mpls.label;
        fabric_metadata.mpls_ttl = 5;
        // There is only one MPLS label for this fabric.
        // Assume header after MPLS header is IPv4/IPv6
        // Lookup first 4 bits for version
        transition select(packet.lookahead<bit<5>>()) {
            // The packet should be either IPv4 or IPv6.
            // If we have MPLS, go directly to parsing state without
            // moving to pre_ states, the packet is considered MPLS
            IP_VERSION_4: parse_ipv4;
            IP_VERSION_6: parse_ipv6;
            default: parse_ethernet;
        }
    }

    // Intermediate state to set is_ipv4
    state pre_parse_ipv4 {
        fabric_metadata.is_ipv4 = true;
        transition parse_ipv4;
    }
    state parse_ipv4 {
        packet.extract(hdr.ipv4);
        fabric_metadata.ip_proto = hdr.ipv4.protocol;
        fabric_metadata.ip_eth_type = ETHERTYPE_IPV4;
        last_ipv4_dscp = hdr.ipv4.dscp;
        //Need header verification?
        transition select(hdr.ipv4.protocol) {
            PROTO_TCP: parse_tcp;
            // PROTO_UDP: parse_udp;
            // PROTO_ICMP: parse_icmp;
            default: accept;
        }
    }

    // // Intermediate state to set is_ipv6
    // state pre_parse_ipv6 {
    //     fabric_metadata.is_ipv6 = true;
    //     transition parse_ipv6;
    // }
    state parse_ipv6 {
        packet.extract(hdr.ipv6);
        fabric_metadata.ip_proto = hdr.ipv6.next_hdr;
        fabric_metadata.ip_eth_type = ETHERTYPE_IPV6;
        transition select(hdr.ipv6.next_hdr) {
            // PROTO_TCP: parse_tcp;
            // PROTO_UDP: parse_udp;
            // PROTO_ICMPV6: parse_icmp;
            default: accept;
        }
    }

    state parse_tcp {
        // packet.extract(hdr.tcp);
        // fabric_metadata.l4_sport = hdr.tcp.sport;
        // fabric_metadata.l4_dport = hdr.tcp.dport;
        transition parse_int;
    }

    // state parse_udp {
    //     packet.extract(hdr.udp);
    //     fabric_metadata.l4_sport = hdr.udp.sport;
    //     fabric_metadata.l4_dport = hdr.udp.dport;
    //     transition select(hdr.udp.dport) {
    //         UDP_PORT_GTPU: parse_gtpu;
    //         default: parse_int;
    //     }
    // }

    // state parse_icmp {
    //     packet.extract(hdr.icmp);
    //     transition accept;
    // }

    // state parse_gtpu {
    //     transition select(hdr.ipv4.dst_addr[31:32-S1U_SGW_PREFIX_LEN]) {
    //         // Avoid parsing GTP and inner headers if we know this GTP packet
    //         // is not to be processed by this switch.
    //         // FIXME: use parser value sets when support is ready in ONOS.
    //         // To set the S1U_SGW_PREFIX value at runtime.
    //         S1U_SGW_PREFIX[31:32-S1U_SGW_PREFIX_LEN]: do_parse_gtpu;
    //         default: accept;
    //     }
    // }

    // state do_parse_gtpu {
    //     packet.extract(hdr.gtpu);
    //     transition parse_inner_ipv4;
    // }

    // state parse_inner_ipv4 {
    //     packet.extract(hdr.inner_ipv4);
    //     last_ipv4_dscp = hdr.inner_ipv4.dscp;
    //     transition select(hdr.inner_ipv4.protocol) {
    //         PROTO_TCP: parse_tcp;
    //         PROTO_UDP: parse_inner_udp;
    //         PROTO_ICMP: parse_icmp;
    //         default: accept;
    //     }
    // }

    // state parse_inner_udp {
    //     packet.extract(hdr.inner_udp);
    //     fabric_metadata.l4_sport = hdr.inner_udp.sport;
    //     fabric_metadata.l4_dport = hdr.inner_udp.dport;
    //     transition parse_int;
    // }

    state parse_int {
        transition select(last_ipv4_dscp) {
            // INT_DSCP &&& INT_DSCP: parse_intl4_shim;
            default: accept;
        }
    }

    // state parse_intl4_shim {
    //     packet.extract(hdr.intl4_shim);
    //     transition parse_int_header;
    // }

    // state parse_int_header {
    //     packet.extract(hdr.int_header);
    //     // If there is no INT metadata but the INT header (plus shim and tail)
    //     // exists, default value of length field in shim header should be
    //     // INT_HEADER_LEN_WORDS.
    //     transition select (hdr.intl4_shim.len_words) {
    //         INT_HEADER_LEN_WORDS: parse_intl4_tail;
    //         default: parse_int_data;
    //     }
    // }

    // state parse_int_data {
    //     // Parse INT metadata stack, but not tail
    //     packet.extract(hdr.int_data, (bit<32>) (hdr.intl4_shim.len_words - INT_HEADER_LEN_WORDS) << 5);
    //     transition parse_intl4_tail;
    // }

    // state parse_intl4_tail {
    //     packet.extract(hdr.intl4_tail);
    //     transition accept;
    // }
}
