struct list {
  int data;
  struct list { char data; } nested;  // illegal nested redef
};
