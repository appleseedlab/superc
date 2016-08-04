#!/bin/bash

# Print help message.

echo "SDF2 Performance Measurement, v. 1.0, (C) 2006 Robert Grimm"
echo

if [ ! $1 ]; then
    echo "Usage: <option>* <file-name>+"
    echo
    echo "Options are:"
    echo "  -noast   Do not generate an AST (default)."
    echo "  -ast     Generate an AST."
    echo "  -java14  Recognize Java 1.4 (default)."
    echo "  -java15  Recognize Java 1.5."
    echo
    exit
fi

# Define the total number of iterations per file and the number of
# warm-up runs.
TOTAL_RUNS=12
WARMUP_RUNS=2

# The name of the parser table.
TABLE=Java14.tbl

# The names of the helper files to collect statistics.
STATS=sglr-stats.txt
LATENCY=latency.txt
LATENCIES=latencies.txt
SUMMARY=summary.txt

# Redirect statistics output of sglri to file
export STRATEGO_LOG=$STATS

# The flag for whether to build or not to build the AST.
BUILD_AST="no"

# Global clean up.
rm -f $SUMMARY

echo "Legend: file name, size (bytes), average parse time (seconds)"
echo

for FILE in $*
do
    # Process any command line options.
    if [ $FILE = "-noast" ]; then
	BUILD_AST="no"
	continue
    elif [ $FILE = "-ast" ]; then
	BUILD_AST="yes"
	continue
    elif [ $FILE = "-java14" ]; then
	TABLE=Java14.tbl
	continue
    elif [ $FILE = "-java15" ]; then
	TABLE=Java15.tbl
	continue
    fi

    # Clean up.
    rm -f $LATENCY
    rm -f $LATENCIES

    # Set up variables.
    SIZE=`ls -l $FILE | awk '{ print $5 }'`

    # Run experiments.
    if [ $BUILD_AST = "no" ]; then
	COUNTER=0
	while [ $COUNTER -lt $TOTAL_RUNS ]; do
	    if [ $COUNTER -lt $WARMUP_RUNS ]; then
		sglr -p $TABLE -n -i $FILE > /dev/null
	    else
		sglr -p $TABLE -l -n -i $FILE > /dev/null
		grep "Read "        $STATS | awk '{ print $8 }' > $LATENCY
		grep "Parse time: " $STATS | awk '{ print $3 }' >> $LATENCY
		awk '{ s += $1 } END { print s }' $LATENCY >> $LATENCIES
	    fi
	    let COUNTER=COUNTER+1
	done
    else
	COUNTER=0
	while [ $COUNTER -lt $TOTAL_RUNS ]; do
	    if [ $COUNTER -lt $WARMUP_RUNS ]; then
		sglri -p $TABLE -i $FILE > /dev/null
	    else
		rm -f $STATS
		sglri -p $TABLE --statistics 1 -i $FILE > /dev/null
		grep "Reading stream o" $STATS | awk '{ print $5 }' > $LATENCY
		grep "Parse time: "     $STATS | awk '{ print $3 }' >> $LATENCY
		grep "Filtering took "  $STATS | awk '{ print $3 }' >> $LATENCY
		grep "Aprod expansion " $STATS | awk '{ print $4 }' >> $LATENCY
		grep "Implode parse tr" $STATS | awk '{ print $4 }' >> $LATENCY
		awk '{ s += $1 } END { print s }' $LATENCY >> $LATENCIES
	    fi
	    let COUNTER=COUNTER+1
	done
    fi

    # Collect and print statistics.
    AVERAGE=`awk '{ s+= $1 } END { print s/NR }' $LATENCIES`
    echo $FILE $SIZE $AVERAGE
    echo $SIZE $AVERAGE >> $SUMMARY
done

echo
java xtc.util.Throughput $SUMMARY

rm -f $STATS
rm -f $LATENCY
rm -f $LATENCIES
rm -f $SUMMARY
