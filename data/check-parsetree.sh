#!/bin/bash

# Print header

echo "Parse tree test, v. 1.0, (C) 2007 Robert Grimm"
echo

# Set up variables

SRC=source.txt
AST=ast.txt
PT=parse-tree.txt

let "testCount = 0"
let "errorCount = 0"

# Process Java files

for FILE in `ls *.java`
do
    echo Testing $FILE ...

    let "testCount = testCount + 1"

    rm -f $SRC $AST $PT

    java xtc.lang.Java -silent -parsetree -printSource $FILE > $SRC
    java xtc.lang.Java -silent -ast -printAST $FILE > $AST
    java xtc.lang.Java -silent -parsetree -strip -printAST $FILE > $PT

    diff -s $FILE $SRC > /dev/null
    if [ $? -ne 0 ]; then
	echo "   " FAILURE source comparison
	let "errorCount = errorCount + 1"
    fi

    diff -s $AST $PT > /dev/null
    if [ $? -ne 0 ]; then
	echo "   " FAILURE ast comparison
	let "errorCount = errorCount + 1"
    fi
done

# Process C files

for FILE in `ls *.E`
do
    echo Testing $FILE ...

    let "testCount = testCount + 1"

    rm -f $SRC $AST $PT

    java xtc.lang.C -silent -parsetree -printSource $FILE > $SRC
    java xtc.lang.C -silent -printAST $FILE > $AST
    java xtc.lang.C -silent -parsetree -strip -printAST $FILE > $PT

    diff -s $FILE $SRC > /dev/null
    if [ $? -ne 0 ]; then
	echo "   " FAILURE source comparison
	let "errorCount = errorCount + 1"
    fi

    diff -s $AST $PT > /dev/null
    if [ $? -ne 0 ]; then
	echo "   " FAILURE ast comparison
	let "errorCount = errorCount + 1"
    fi
done

# Clean up

rm -f $SRC $AST $PT

# Summarize results

if [ $errorCount -ne 0 ]
then
    echo
    echo $errorCount / $testCount tests failed.
    echo
    exit 1
else
    echo
    echo All $testCount tests succeeded.
    echo
    exit 0
fi
