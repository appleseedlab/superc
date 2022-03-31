#define INGRESS_MAC_ACL_KEY                    \
    bit<34> bit1; \
    bool h1;

#if defined(EGRESS_IP_ACL_ENABLE) || defined(EGRESS_MIRROR_ACL_ENABLE) \
    || defined(DTEL_FLOW_REPORT_ENABLE)
    const int a = 1;
#endif

#define H int a;

#ifdef HELLO
struct P {
    INGRESS_MAC_ACL_KEY
    H
    bit<32> f1; \
    bit<32> f2;
}
#endif
