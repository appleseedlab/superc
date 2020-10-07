int main() {

  #ifdef CONFIG_B
    int x;
    int y;
    #ifdef CONFIG_B
      #ifdef CONFIG_C
        y = 4;
      #endif
    #endif
    #ifdef CONFIG_B
      #ifdef CONFIG_C
        x = y;
      #endif
    #endif
    #ifdef CONFIG_B
      #ifdef CONFIG_A
        x++;
      #endif
    #endif
    #ifdef CONFIG_B
      #ifdef CONFIG_A
        return x;
      #endif
    #endif
  #endif
}

