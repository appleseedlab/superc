action Forward_a(out bit<9> outputPort, bit<9> port) {
    outputPort = port;
}

control ActionInvoker() {
    apply {
        Forward_a(5, 10);
    }
}