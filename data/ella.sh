#!/bin/bash

# Print help message.

echo "Ella Performance Measurement, v. 1.0, (C) 2006 Robert Grimm"
echo

if [ ! $1 ]; then
    echo "Usage: <option>* <file-name>+"
    echo
    echo "Options are:"
    echo "  -noast   Do not generate an AST (default)."
    echo "  -ast     Generate an AST."
    echo
    exit
fi

# Define the total number of iterations per file and the number of
# warm-up runs.
TOTAL_RUNS=12
WARMUP_RUNS=2

# The Ella binary
ELLA=../glr/ella/javaparse

# The names of the helper files to collect statistics.
LATENCIES=latencies.txt
SUMMARY=summary.txt

# The command line option for building or not building the AST.
BUILD_AST="-tr noTree"

# Global clean up.
rm -f $SUMMARY

echo "Legend: file name, size (bytes), average parse time (seconds)"
echo

for FILE in $*
do
    # Process any command line options.
    if [ $FILE = "-noast" ]; then
	BUILD_AST="-tr noTree"
	continue
    elif [ $FILE = "-ast" ]; then
	BUILD_AST=""
	continue
    fi

    # Clean up.
    rm -f $LATENCIES

    # Set up variables.
    SIZE=`ls -l $FILE | awk '{ print $5 }'`

    # Run experiments.
    COUNTER=0
    while [ $COUNTER -lt $TOTAL_RUNS ]; do
	if [ $COUNTER -lt $WARMUP_RUNS ]; then
	    $ELLA $BUILD_AST $FILE > /dev/null
	else
	    $ELLA $BUILD_AST $FILE | grep "Parsing " | \
		awk '{ print $4 }' >> $LATENCIES
	fi
	let COUNTER=COUNTER+1
    done

    # Collect and print statistics.
    AVERAGE=`awk '{ s+= $1 } END { print s/NR }' $LATENCIES`
    echo $FILE $SIZE $AVERAGE
    echo $SIZE $AVERAGE >> $SUMMARY
done

echo
java xtc.util.Throughput $SUMMARY

rm -f $LATENCIES
rm -f $SUMMARY
