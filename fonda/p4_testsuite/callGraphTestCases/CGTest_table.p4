control pipe() {
    action Reject(bit<8> rej, bit<8> bar) {
        if (rej == 0) {
            pass = true;
        } else {
            pass = false;
        }
    }
    action NotAccpet(bit<8> rej, bit<8> bar) {
        if (rej == 0) {
            pass = false;
        } else {
            pass = true;
        }
    }
    table t {
        actions = { 
            Reject(); 
            NotAccpet(); 
        }
        default_action = Reject(1, 0);
    }
    apply {
        bool x = true;
        t.apply();
    }
}