int foo(
#ifdef ENABLE_A
#ifdef ENABLE_B
        int x,
        #endif
        #endif
        #ifdef ENABLE_A
        #ifdef ENABLE_C
        int y,
        #endif
        #endif
        #ifdef ENABLE_A
        int z,
        #endif
        int w)
{
  int res = 0;
  #ifdef ENABLE_A
  #ifdef ENABLE_B
  res += x;
  #endif
  #endif

  #ifdef ENABLE_A
  #ifdef ENABLE_C
  res += y;
  #endif
  #endif

  #ifdef ENABLE_A
  res += z;
  #endif
  res += w;
  return res;
}

int main() {
return foo(
#ifdef ENABLE_A
#ifdef ENABLE_B
        1,
        #endif
        #endif
        #ifdef ENABLE_A
        #ifdef ENABLE_C
        2,
        #endif
        #endif
        #ifdef ENABLE_A
        3,
        #endif
        4);
}

/*
  foo(w)                  -!ENABLE_A && (!ENABLE_B || ENABLE_B) && (!ENABLE_C || ENABLE_C)
  foo(x,z,w)              -ENABLE_A && ENABLE_B && !ENABLE_C
  foo(y,z,w)              -ENABLE_A && !ENABLE_B && ENABLE_C
  foo(x,y,z,w)            -ENABLE_A && ENABLE_B && ENABLE_C
  foo(z,w)                -ENABLE_A && !ENABLE_B && !ENABLE_C
 */
