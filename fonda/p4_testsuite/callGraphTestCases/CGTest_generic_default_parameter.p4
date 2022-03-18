control dummy(out bit<16> b) {
    apply {
    }
}

control generic_value<T>(out T b);

package default_value<T>(generic_value<T> control_as_param = dummy());