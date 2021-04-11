# 1 "arith-bmv2.p4"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "arith-bmv2.p4"
# 17 "arith-bmv2.p4"
# 1 "../../../../p4c/p4include/core.p4" 1
# 23 "../../../../p4c/p4include/core.p4"
error {
    NoError,
    PacketTooShort,
    NoMatch,
    StackOutOfBounds,
    HeaderTooShort,
    ParserTimeout,
    ParserInvalidArgument

}

extern packet_in {



    void extract<T>(out T hdr);




    void extract<T>(out T variableSizeHeader,
                    in bit<32> variableFieldSizeInBits);



    T lookahead<T>();

    void advance(in bit<32> sizeInBits);


    bit<32> length();
}

extern packet_out {



    void emit<T>(in T hdr);
}




extern void verify(in bool check, in error toSignal);


@noWarn("unused")
action NoAction() {}




match_kind {

    exact,

    ternary,

    lpm
}
# 18 "arith-bmv2.p4" 2
# 1 "../../../../p4c/p4include/v1model.p4" 1
# 52 "../../../../p4c/p4include/v1model.p4"
# 1 "../../../../p4c/p4include/core.p4" 1
# 53 "../../../../p4c/p4include/v1model.p4" 2





match_kind {
    range,

    optional,

    selector
}

const bit<32> __v1model_version = 20180101;





@metadata @name("standard_metadata")
struct standard_metadata_t {





    bit<9> ingress_port;
    bit<9> egress_spec;
    bit<9> egress_port;

    bit<32> instance_type;
    bit<32> packet_length;
# 94 "../../../../p4c/p4include/v1model.p4"
    @alias("queueing_metadata.enq_timestamp")
    bit<32> enq_timestamp;
    @alias("queueing_metadata.enq_qdepth")
    bit<19> enq_qdepth;
    @alias("queueing_metadata.deq_timedelta")
    bit<32> deq_timedelta;

    @alias("queueing_metadata.deq_qdepth")
    bit<19> deq_qdepth;


    @alias("intrinsic_metadata.ingress_global_timestamp")
    bit<48> ingress_global_timestamp;
    @alias("intrinsic_metadata.egress_global_timestamp")
    bit<48> egress_global_timestamp;

    @alias("intrinsic_metadata.mcast_grp")
    bit<16> mcast_grp;

    @alias("intrinsic_metadata.egress_rid")
    bit<16> egress_rid;


    bit<1> checksum_error;

    error parser_error;

    @alias("intrinsic_metadata.priority")
    bit<3> priority;
}

enum CounterType {
    packets,
    bytes,
    packets_and_bytes
}

enum MeterType {
    packets,
    bytes
}

extern counter



{
# 156 "../../../../p4c/p4include/v1model.p4"
    counter(bit<32> size, CounterType type);
# 174 "../../../../p4c/p4include/v1model.p4"
    void count(in bit<32> index);

}

extern direct_counter {
# 195 "../../../../p4c/p4include/v1model.p4"
    direct_counter(CounterType type);
# 207 "../../../../p4c/p4include/v1model.p4"
    void count();
}





extern meter



{
# 233 "../../../../p4c/p4include/v1model.p4"
    meter(bit<32> size, MeterType type);
# 258 "../../../../p4c/p4include/v1model.p4"
    void execute_meter<T>(in bit<32> index, out T result);

}

extern direct_meter<T> {
# 274 "../../../../p4c/p4include/v1model.p4"
    direct_meter(MeterType type);
# 295 "../../../../p4c/p4include/v1model.p4"
    void read(out T result);
}




extern register<T>

{
# 314 "../../../../p4c/p4include/v1model.p4"
    register(bit<32> size);
# 329 "../../../../p4c/p4include/v1model.p4"
    @noSideEffects



    void read(out T result, in bit<32> index);
# 360 "../../../../p4c/p4include/v1model.p4"
    void write(in bit<32> index, in T value);

}


extern action_profile {
    action_profile(bit<32> size);
}
# 376 "../../../../p4c/p4include/v1model.p4"
extern void random<T>(out T result, in T lo, in T hi);
# 401 "../../../../p4c/p4include/v1model.p4"
extern void digest<T>(in bit<32> receiver, in T data);

enum HashAlgorithm {
    crc32,
    crc32_custom,
    crc16,
    crc16_custom,
    random,
    identity,
    csum16,
    xor16
}

@deprecated("Please use mark_to_drop(standard_metadata) instead.")
extern void mark_to_drop();
# 434 "../../../../p4c/p4include/v1model.p4"
@pure
extern void mark_to_drop(inout standard_metadata_t standard_metadata);
# 452 "../../../../p4c/p4include/v1model.p4"
@pure
extern void hash<O, T, D, M>(out O result, in HashAlgorithm algo, in T base, in D data, in M max);

extern action_selector {
    action_selector(HashAlgorithm algorithm, bit<32> size, bit<32> outputWidth);
}

enum CloneType {
    I2E,
    E2E
}

@deprecated("Please use verify_checksum/update_checksum instead.")
extern Checksum16 {
    Checksum16();
    bit<16> get<D>(in D data);
}
# 492 "../../../../p4c/p4include/v1model.p4"
extern void verify_checksum<T, O>(in bool condition, in T data, in O checksum, HashAlgorithm algo);
# 513 "../../../../p4c/p4include/v1model.p4"
@pure
extern void update_checksum<T, O>(in bool condition, in T data, inout O checksum, HashAlgorithm algo);
# 525 "../../../../p4c/p4include/v1model.p4"
extern void verify_checksum_with_payload<T, O>(in bool condition, in T data, in O checksum, HashAlgorithm algo);
# 536 "../../../../p4c/p4include/v1model.p4"
@noSideEffects
extern void update_checksum_with_payload<T, O>(in bool condition, in T data, inout O checksum, HashAlgorithm algo);
# 561 "../../../../p4c/p4include/v1model.p4"
extern void resubmit<T>(in T data);
# 585 "../../../../p4c/p4include/v1model.p4"
extern void recirculate<T>(in T data);
# 594 "../../../../p4c/p4include/v1model.p4"
extern void clone(in CloneType type, in bit<32> session);
# 633 "../../../../p4c/p4include/v1model.p4"
extern void clone3<T>(in CloneType type, in bit<32> session, in T data);

extern void truncate(in bit<32> length);
# 661 "../../../../p4c/p4include/v1model.p4"
extern void assert(in bool check);
# 696 "../../../../p4c/p4include/v1model.p4"
extern void assume(in bool check);






extern void log_msg(string msg);
extern void log_msg<T>(string msg, in T data);
# 717 "../../../../p4c/p4include/v1model.p4"
parser Parser<H, M>(packet_in b,
                    out H parsedHdr,
                    inout M meta,
                    inout standard_metadata_t standard_metadata);






control VerifyChecksum<H, M>(inout H hdr,
                             inout M meta);
@pipeline
control Ingress<H, M>(inout H hdr,
                      inout M meta,
                      inout standard_metadata_t standard_metadata);
@pipeline
control Egress<H, M>(inout H hdr,
                     inout M meta,
                     inout standard_metadata_t standard_metadata);






control ComputeChecksum<H, M>(inout H hdr,
                              inout M meta);





@deparser
control Deparser<H>(packet_out b, in H hdr);

package V1Switch<H, M>(Parser<H, M> p,
                       VerifyChecksum<H, M> vr,
                       Ingress<H, M> ig,
                       Egress<H, M> eg,
                       ComputeChecksum<H, M> ck,
                       Deparser<H> dep
                       );
# 19 "arith-bmv2.p4" 2

header hdr {
    bit<32> a;
    bit<32> b;
    bit<64> c;
}

# 1 "arith-skeleton.p4" 1
# 22 "arith-skeleton.p4"
struct Headers {
    hdr h;
}

struct Meta {}

parser p(packet_in b, out Headers h, inout Meta m, inout standard_metadata_t sm) {
    state start {
        b.extract(h.h);
        transition accept;
    }
}

control vrfy(inout Headers h, inout Meta m) { apply {} }
control update(inout Headers h, inout Meta m) { apply {} }

control egress(inout Headers h, inout Meta m, inout standard_metadata_t sm) { apply {} }

control deparser(packet_out b, in Headers h) {
    apply { b.emit(h.h); }
}
# 27 "arith-bmv2.p4" 2

control ingress(inout Headers h, inout Meta m, inout standard_metadata_t sm) {
    action add()
    { h.h.c = (bit<64>)(h.h.a + h.h.b); sm.egress_spec = 0; }
    table t {
        actions = { add; }
        const default_action = add;
    }
    apply { t.apply(); }
}

V1Switch(p(), vrfy(), ingress(), egress(), update(), deparser()) main;
