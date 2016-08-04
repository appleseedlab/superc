#!/bin/bash

# xtc - The eXTensible Compiler
# Copyright (C) 2009-2012 New York University
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
# USA.

# Regression tester.

# Gather command-line parameters.

cppTool="gcc -E"
while getopts :S:J:G:C:gaek:s:mMi opt; do
    case $opt in
        S)
            supercArgs="$OPTARG"
            ;;
        J)
            jvmFlags="$OPTARG"
            ;;
        G)
            gccArgs="$OPTARG"
            ;;
        C)
            cppTool="$OPTARG"
            ;;
        g)
            gccCompare=true
            ;;
        E)
            errCompare=true
            ;;
        a)
            allCompare=true
            ;;
        e)
            allErrCompare=true
            ;;
        k)
            knownCompare=true
            extension="$OPTARG"
            ;;
        s)
            maxCompare=true
            extension="$OPTARG"
            ;;
        m)
            makeCompare=true
            ;;
        M)
            makeCompare=true
            interactiveMake=true
            ;;
        i)
            saveIntermediate=true
            ;;
        \?)
            echo "(`basename $0`)" "Invalid argument: -$OPTARG"
            ;;
        :)
            echo "(`basename $0`)" "-$OPTARG requires an argument."
            ;;
    esac
done

shift $(($OPTIND - 1))

files=$@
numfiles=$#

# Help.
if [[ $# -eq 0 ]]; then
    echo "USAGE:"
    echo "  `basename $0` [opts] file file file ..."
    echo ""
    echo "OPTIONS"
    echo "  -g               Compare SuperC output to (g)cc output."
    # echo "  -e               Also compare (e)rror out for -g."
    echo "  -a               Compare (a)ll configurations to gcc output."
    echo "  -e               Compare all configs of error messages to gcc."
    echo "  -k extension     Compare SuperC output to (k)nown correct output."
    echo "  -s extension     Check that max (s)ubparsers are the same."
    echo "  -m               (m)ake test files for -k and -s."
    echo "  -M               (M)ake test files, asking for confirmation."
    echo "  -i               Save (i)ntermediate files."
    echo ""
    echo "TOOLS OPTIONS"
    echo "  -S \"args\"        (S)uperC command-line arguments."
    echo "  -J \"args\"        Extra (J)VM arguments."
    echo "  -G \"args\"        Extra (G)CC (or other) preprocessor arguments."
    echo "  -C \"cpp tool\"    Specify the (C)PP incantation.  Default is \"gcc -E\"."
    echo ""

    exit 0
fi

# Validate arguments.
commands=0
if [ ! -z "$gccCompare" ]; then commands=$((commands+1)); fi;
if [ ! -z "$allCompare" ]; then commands=$((commands+1)); fi;
if [ ! -z "$allErrCompare" ]; then commands=$((commands+1)); fi;
if [ ! -z "$knownCompare" ]; then commands=$((commands+1)); fi;
if [ ! -z "$maxCompare" ]; then commands=$((commands+1)); fi;

if [ $commands -eq 0 ]; then
    echo "Please specify one of -g, -a, -e, -k, or -s."
    exit
elif [ $commands -gt 1 ]; then
    echo "Please specify no more than one of -g, -a, -e, -k, or -s."
    exit
fi

if  [[ ! -z "$makeCompare" && (! -z "$gccCompare" || ! -z "$allCompare" || ! -z "$saveIntermediate") ]]; then
    echo "-g, -a, and -i cannot be used with -m and -M."
    exit
fi

if [[ ! -z "$allCompare" && ! -z "$saveIntermediate" ]]; then
    echo "-i cannot be used with -a because it produces many files.  Instead rerun with"
    echo "-g and a single configuration setting with -G."
    exit
fi

if [[ ! -z "$errCompare" && -z "$gccCompare" ]]; then
    echo "-e requires -g"
    exit
fi

if [[ ! -z "$supercArgs" && ! -z "$knownCompare" && -z "$makeCompare" ]]; then
    echo "-S cannot be used with -k, since SuperC args are stored with the -k file."
    exit
fi

if [[ ! -z "$makeCompare" && -z "$supercArgs" ]]; then
    echo "Must set -S with -m, so that SuperC will output something."
    exit
fi

# Run the tests.
errors=0
skipped=0
passed=0
made=0
for file in $files
do
    if [ ! -f $file ]; then
        echo "File not found: $file"
        skipped=$((skipped+1))
    else

        if [ ! -z "$gccCompare" ]; then
            tempfilebase=$($JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/tempfile.sh -p gcmp) || exit
            tempfiles=$tempfilebase
            superc=$tempfilebase.super.c
            supercE=$tempfilebase.super.E
            supercEerr=$tempfilebase.super.C.err
            supercEerr_stripped=$tempfilebase.super.C.err_stripped
            gccE=$tempfilebase.gcc.E
            gccEerr=$tempfilebase.gcc.E.err
            gccEerr_stripped=$tempfilebase.gcc.E.err_stripped
            diff=$tempfilebase.diff
            differr=$tempfilebase.diff
            if [ -z "$saveIntermediate" ]; then
                tempfiles="$tempfiles $superc $supercE $supercEerr \
$supercEerr_stripped $gccE $gccEerr $gccEerr_stripped $diff $differr"
            fi
            trap "rm -f -- $tempfilebase $tempfiles" EXIT

            echo "Testing $file"
            java $jvmFlags xtc.lang.cpp.SuperC \
                -silent $supercArgs $file > $superc 2>$supercEerr
            $cppTool $gccArgs $superc > $supercE 2>/dev/null
            $cppTool $gccArgs $file > $gccE 2>$gccEerr
            java xtc.lang.cpp.cdiff $gccE $supercE > $diff
            if [ $? -ne 0 ]; then
                cat $diff
                echo "failed $file"
                errors=$((errors+1))
            else
                if [ ! -z "$errCompare" ]; then
                    # Ignore line numbers for now.  Remove xtc
                    # Runtime's "## errors" line
                    cat $supercEerr | egrep -v "^[[:digit:]]+ (error|errors)$" \
                        | sed 's/^.*\(error:.*\)$/\1/' > $supercEerr_stripped
                    sed 's/^.*\(error:.*\)$/\1/' $gccEerr > $gccEerr_stripped
                    diff $supercEerr_stripped $gccEerr_stripped > $differr
                    if [ $? -ne 0 ]; then
                        cat $differr
                        echo "failed $file (error output)"
                        errors=$((errors+1))
                    else
                        passed=$((passed+1))
                    fi
                else
                    passed=$((passed+1))
                fi
            fi
            if [ ! -z "$saveIntermediate" ]; then
                echo "intermediate files $tempfilebase*"
            fi
        elif [ ! -z "$knownCompare" ]; then
            tempfilebase=$($JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/tempfile.sh -p gcmp) || exit
            superc=$tempfilebase.super.c
            if [ -z "$saveIntermediate" ]; then
                tempfiles="$tempfiles $superc"
            fi
            trap "rm -f -- $tempfilebase $tempfiles" EXIT

            known=$file$extension
            if [ ! -z "$makeCompare" ]; then
                if [ ! -f $known ]; then
                    echo "Making comparison file: $known"
                    java $jvmFlags xtc.lang.cpp.SuperC \
                        -silent $supercArgs $file > $superc
                    if [ ! -z "$interactiveMake" ]; then
                        cat $superc
                        read -p "Set comparison file $known? [y/N] " yn
                        case $yn in
                            [Yy]* )
                              echo "#superc_args $supercArgs" > $known
                              cat $superc >> $known
                                ;;
                            * )
                                ;;
                        esac
                    else
                        echo "#superc_args $supercArgs" > $known
                        cat $superc >> $known
                    fi
                    made=$((made+1))
                else
                    echo "Comparison file already exists: $known"
                fi
            else
                if [ ! -f $known ]; then
                    echo "Missing known file; make it with -m or -M: $known"
                    skipped=$((skipped+1))
                else
                    echo "Testing $file against $known"
                    knownArgs=`cat $known | grep "#superc_args " | cut -c14-`
                    java $jvmFlags \
                        xtc.lang.cpp.SuperC -silent $knownArgs $file > $superc
                    cat $known | grep -v "#superc_args" | diff - $superc
                    if [ $? -ne 0 ]; then
                        errors=$((errors+1))
                        if [ ! -z "$saveIntermediate" ]; then
                            echo "intermediate files $superc"
                        fi
                        echo "failed $file"
                    else
                        passed=$((passed+1))
                    fi
                fi
            fi
        elif [ ! -z "$allCompare" ]; then
            tempfilebase=$($JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/tempfile.sh -p gcmp) || exit
            tempfiles=$tempfilebase
            powerset=$($JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/tempfile.sh) || exit
            superc=$tempfilebase.super.c
            supercE=$tempfilebase.super.E
            gccE=$tempfilebase.gcc.E
            diff=$tempfilebase.diff
            alldiff=$tempfilebase.alldiff
            if [ -z "$saveIntermediate" ]; then
                tempfiles="$tempfiles $powerset $superc $supercE $gccE $diff \
$alldiff"
            fi
            trap "rm -f -- $tempfilebase $tempfiles" EXIT

            # Get all combinations of configuration variables.
            java xtc.lang.cpp.SuperC \
                -silent -configurationVariables -preprocessor $file 2>&1 \
                | grep "config_var" | awk '{print $2}' \
                | python $JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/powerset.py \
                > $powerset

            if [ $? -ne 0 ]; then
                echo "Testing $file with none (too many configurations to test)"
                java $jvmFlags xtc.lang.cpp.SuperC -silent $supercArgs \
                    $file > $superc 2>/dev/null
                $cppTool $gccArgs $superc > $supercE 2>/dev/null
                $cppTool $gccArgs $file > $gccE 2>/dev/null
                java xtc.lang.cpp.cdiff $gccE $supercE > $diff
                if [ $? -ne 0 ]; then
                    cat $diff
                    echo "failed $file"
                    errors=$((errors+1))
                else
                    passed=$((passed+1))
                fi
            else
                java $jvmFlags xtc.lang.cpp.SuperC -silent $supercArgs \
                    $file > $superc 2>/dev/null
                cat $powerset | while read set; do
                    if [ -z "$set" ]; then
                        echo "Testing $file with none"
                    else
                        echo "Testing $file with $set"
                    fi
                    $cppTool $gccArgs $set $superc > $supercE 2>/dev/null
                    $cppTool $gccArgs $set $file > $gccE 2>/dev/null
                    java xtc.lang.cpp.cdiff $gccE $supercE > $diff
                    if [ $? -ne 0 ]; then
                        cat $diff
                        cat $diff >> $alldiff
                    fi
                done

                if [ -s $alldiff ]; then
                    errors=$((errors+1))
                    echo "failed $file"
                else
                    passed=$((passed+1))
                fi
            fi
        elif [ ! -z "$allErrCompare" ]; then
            tempfilebase=$($JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/tempfile.sh -p gcmp) || exit
            tempfiles=$tempfilebase
            powerset=$($JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/tempfile.sh) || exit
            superc=$tempfilebase.super.c
            supercE=$tempfilebase.super.E
            supercEstrip=$tempfilebase.super.E.strip
            gccE=$tempfilebase.gcc.E
            gccEall=$tempfilebase.gcc.E.all
            gccEallsorted=$tempfilebase.gcc.E.all.sorted
            diff=$tempfilebase.diff
            if [ -z "$saveIntermediate" ]; then
                tempfiles="$tempfiles $powerset $superc $supercE $gccE \
$gccEall $gccEallsorted $diff"
            fi
            trap "rm -f -- $tempfilebase $tempfiles" EXIT

            # Get all combinations of configuration variables.
            java xtc.lang.cpp.SuperC \
                -silent -configurationVariables -preprocessor $file 2>&1 \
                | grep "config_var" | awk '{print $2}' \
                | python $JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/powerset.py \
                > $powerset

            if [ $? -ne 0 ]; then
                echo -e "Skipping $file, because there are too many \
configuration variables to test all\ncombinations."
                skipped=$((skipped+1))
            else
                java $jvmFlags xtc.lang.cpp.SuperC -silent $supercArgs \
                    $file >/dev/null 2>$supercE
                # Strip xtc "## errors" message.  And strip line
                # numbers for now.
                cat $supercE | egrep -v "^[[:digit:]]+ (error|errors)$" \
                    | sort | sed 's/^.*\(error:.*\)$/\1/' > $supercEstrip

                cat $powerset | while read set; do
                    $cppTool $gccArgs $set $file >/dev/null 2>$gccE
                    cat $gccE | sed 's/^.*\(error:.*\)$/\1/' >> $gccEall
                done

                cat $gccEall | sort | uniq > $gccEallsorted

                diff $gccEallsorted $supercEstrip > $diff
                if [ $? -ne 0 ]; then
                    cat $diff
                    errors=$((errors+1))
                    echo "failed $file"
                else
                    passed=$((passed+1))
                fi
                if [ ! -z "$saveIntermediate" ]; then
                    echo "intermediate files $tempfilebase*"
                fi
            fi
        fi
    fi
done

# Report number of files processed and number of errors.
if [ -z "$makeCompare" ]; then
    if [ $numfiles -eq 1 ]; then
        echo "$numfiles file processed"
    else
        echo "$numfiles files processed"
    fi
    if [ $passed -gt 0 ]; then
        if [ $passed -eq 1 ]; then
            echo "$passed file passed"
        else
            echo "$passed files passed"
        fi
    fi
    if [ $errors -gt 0 ]; then
        if [ $errors -eq 1 ]; then
            echo "$errors error"
        else
            echo "$errors errors"
        fi
    fi
    if [ $made -gt 0 ]; then
        if [ $made -eq 1 ]; then
            echo "$made $extension file made"
        else
            echo "$made $extension files made"
        fi
    fi
    if [ $skipped -gt 0 ]; then
        if [ ! -z "$makeCompare" ]; then
            if [ $skipped -eq 1 ]; then
                echo "$skipped with a missing $extension file"
            else
                echo "$skipped with missing $extension files"
            fi
        else
            if [ $skipped -eq 1 ]; then
                echo "$skipped file not done"
            else
                echo "$skipped files not done"
            fi
        fi
    fi
fi

# Exit with the right error code.
if [ $errors -gt 0 ]; then
    exit 1
else
    exit 0
fi
