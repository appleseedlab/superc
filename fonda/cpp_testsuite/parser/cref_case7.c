int main() {
if (
#ifdef CONFIG_C3
a != 0) a++;
#else
b !=
#ifdef CONFIG_C1
0
#else
1
#endif
) b++;
#endif
else
#ifdef CONFIG_C2
b--
#else
c++
#endif
;
}
