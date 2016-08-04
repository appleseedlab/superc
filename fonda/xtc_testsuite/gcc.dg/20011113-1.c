/* Copyright (C) 2001  Free Software Foundation.
   by Hans-Peter Nilsson  <hp@axis.com>  */

// {{ dg-checkwhat "c-analyzer" }}

const char foo[] = "fum";
const struct fi
{
  const char *const in;
  const char *const out;
  const int flags;
} fie[] = {
  {"nw", " new", 0},
  {"dl", foo, 1}
};
