#if defined BY_ROW || defined BY_COL
int main() {
for (
#ifdef BY_ROW
i = 0; i < R; i++)
s += a[i];
#elif defined BY_COL
j = 0; j < C; j++)
s += a[j];
#endif
}
#endif
