#define INGRESS_MAC_ACL_KEY                    \
    bit<16> bit1; \
    bool h1;

struct P {
    INGRESS_MAC_ACL_KEY
}