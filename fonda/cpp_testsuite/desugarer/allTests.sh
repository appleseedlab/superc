#!/bin/bash
rm allTests.out
touch allTests.out
cd typechecker
folders="compound configurable declarators examples functions struct"
for b in $folders;do
  cd $b
  for f in *; do
    if [[ $# == 1 && $1 == "-all" && $f == *".c" ]]; then
        clear
			  java xtc.lang.cpp.SuperC "$f"
        echo ""
        echo "---file:"
        echo ""
        cat "$f"
        echo "$b : $f"
        read -s -n 1 -p "Press any key to continue . . ."
		elif [[ $f == "PASS"*".c" ]]; then
        clear
			  java xtc.lang.cpp.SuperC "$f"
        java xtc.lang.cpp.SuperC "$f" >> ../../../allTests.out 2>&1
        echo ""
        echo "" >> ../../../allTests.out 2>&1
        echo "---file:"
        echo "---file:" >> ../../../allTests.out 2>&1
        echo ""
        echo "" >> ../../../allTests.out 2>&1
        cat "$f"
        cat "$f" >> ../../../allTests.out 2>&1
        echo "$b : $f"
        echo "$b : $f" >> ../../../allTests.out 2>&1
        if [[ $# == 1 && $1 == "-pause" && $f == *".c" ]]; then
            read -s -n 1 -p "Press any key to continue . . ."
        fi
	  fi
	done
  cd ..
done
cd ../..
