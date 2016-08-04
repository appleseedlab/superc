#!/bin/bash

# Print help message.

echo "Build SDF parser tables, v. 1.0, (C) 2006 Robert Grimm"
echo

# Configuration.

PACK_SDF=pack-sdf
SDF2TABLE=sdf2table
TABLES="Java14 Java15"

# Do the work.

for NAME in $TABLES
do
    echo "Building $NAME.tbl"

    $PACK_SDF -i $NAME.sdf -o $NAME.def
    $SDF2TABLE -m $NAME -i $NAME.def -o $NAME.tbl
    mv $NAME.tbl ../data
done

echo "Done"