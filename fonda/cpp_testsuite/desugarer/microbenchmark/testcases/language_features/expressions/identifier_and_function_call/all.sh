#!/bin/bash
for f in *; do
  if [[ $f == *".c" ]]; then
      clear
      java xtc.lang.cpp.SuperC "$f" > "$f.desugared.c"
      echo ""
      echo "---file:"
      echo ""
      cat "$f"
      echo "$b : $f"
  fi
done
