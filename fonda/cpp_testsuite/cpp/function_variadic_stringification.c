#define X86_FEATURE_POPCNT      (4*32+23)
#define call(feature) __stringify(feature)
#define __stringify_1(x...)     #x
#define __stringify(x...)       __stringify_1(x)

int main() {
  __stringify_1(X86_FEATURE_POPCNT)
  __stringify(X86_FEATURE_POPCNT)
  call(X86_FEATURE_POPCNT)
}
