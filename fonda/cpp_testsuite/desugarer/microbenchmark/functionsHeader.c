#include <stdio.h>
#include <stdlib.h>
void __static_parse_error(char *msg) {
  //printf("parse error: %s\n", msg);
  exit(-99);
}
void __static_type_error(char *msg) {
  //printf("type error: %s\n", msg);
  exit(-99);
}
void __static_renaming(char *renaming, char *original) {
  //printf("renaming: %s -> %s\n", original, renaming);
}

void __static_condition_renaming(char *expression, char *renaming) {
  //printf("condition renaming: %s -> %s\n", expression, renaming);
}
