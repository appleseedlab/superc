control process_int_main () {
    apply {
    }
}
control process_int_main () {
    apply {
    }
}
control process_int_main2 () {
    apply {
    }
}
// control, apply - use APPLY as namespace of fegress, directapplication
// future - use PC scope
control FabricEgress () {
    apply {
        process_int_main.apply();
    }
}

control FabricEgress () {
    apply {
        process_int_main.apply();
        process_int_main2.apply();
    }
}
