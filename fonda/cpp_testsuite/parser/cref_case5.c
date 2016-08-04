int main() {
while (
#if _C1
n != 0
#else
(n - 2) != 0
#endif
) {
n = n
#if _C2
- 3;
#else
/ 2;
#endif
}
}
