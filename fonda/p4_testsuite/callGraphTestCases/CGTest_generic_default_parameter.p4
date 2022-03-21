// Need to check how this works as new instance of generic_value is still of type T
// rather than bit<16> from dummy
control dummy(out bit<16> b) {
    apply {
    }
}

control generic_value<T>(out T b);

package default_value<T>(generic_value<T> control_as_param = dummy());