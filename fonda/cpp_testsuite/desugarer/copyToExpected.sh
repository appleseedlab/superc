#!/bin/bash
cd $1
for f in *; do
  if [[ $f == *".c" && $f != *"desugared"* && $f != *"expected"* ]]; then
      echo "copying:$f"
      newName=${f::-2}".expected.c"
      cp "$f" "$newName"
  fi
done
