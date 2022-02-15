#!/bin/bash
rm allTests.out
touch allTests.out
folders="constructs declaringlists enum expressions functions icse19nier ifelsewhile misc phasar typedef_struct union"
for b in $folders;do
  cd $b
  for f in *; do
    if [[ $f == *".c" && $f != *"desugar"* ]]; then
        clear
			  java superc.SugarC "$f"
        echo ""
        echo "---file:"
        echo ""
        cat "$f"
        echo "$b : $f"
        read -s -n 1 -p "Press any key to continue . . ."
	  fi
	done
  cd ..
done
