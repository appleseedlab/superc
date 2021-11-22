control pipe() {
    action Reject(bit<8> rej, bit<8> bar) {
        if (rej == 0) {
            pass = true;
        } else {
            pass = false;
        }
        if (bar == 0) {
            pass = false;
        }
    }
    table t {
        actions = { Reject(); Reject(); }
        // default_action = Reject(1, 0);
    }
    apply {
        bool x = true;
        t.apply();
    }
}