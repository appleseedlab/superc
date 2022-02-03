action Forward_a(out bit<9> outputPort, bit<9> port) {
    outputPort = port;
}

control ActionInvoker() {
    action Forward_a(bit<9> port) {
        port = 1;
    }
    apply {
        Forward_a(5);
    }
}