#!/bin/bash
cd fonda/cpp_testsuite
folders="declChecker funcChecker staticConfig typechecker"
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
cd ../..
