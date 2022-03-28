struct childStruct<T, S> {
    T varIt;
    S a;
}

const childStruct<bit<16>, bool> a = { varIt = 5, a = false };