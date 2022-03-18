extern Balancer {
    Balancer();
    // get the number of active flows
    bit<32> getFlowCount();
    // return port index used for load-balancing
    // @param address: IPv4 source address of flow
    abstract bit<4> on_new_flow(in bit<32> address);
}

control test() {
    // Instantiate a balancer
    Balancer() b = {  // provide an implementation for the abstract methods
        bit<4> on_new_flow(in bit<32> address) {
            // uses the address and the number of flows to load balance
            bit<32> count = this.getFlowCount();  // call method of the same instance
            return (address + count)[3:0];
        }
    };   
    apply {}
}