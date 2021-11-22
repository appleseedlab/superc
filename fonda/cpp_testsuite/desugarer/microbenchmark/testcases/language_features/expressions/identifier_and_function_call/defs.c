#include <stdio.h>
#include <stdbool.h>
void __static_parse_error(char *msg)
{
  printf("%s\n",msg);
}
void __static_type_error(char *msg)
{
  printf("%s\n",msg);
}
void __static_renaming(char *renaming, char *original)
{
}
void __static_condition_renaming(char *expression, char *renaming)
{
}

const bool __static_condition_default_34=false;
const bool __static_condition_default_35=false;
const bool __static_condition_default_36=false;
const bool __static_condition_default_37=true;
