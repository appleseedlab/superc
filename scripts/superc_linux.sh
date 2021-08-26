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


# Run SuperC on linux files.  Gets the configuration settings from
# kbuild by running make.

# set -x

################################################################################
##################### Gather command-line parameters ###########################
################################################################################

if [[ $1 == "-?" ]]; then
    help=true;
fi

allArgs=
timeout=
while getopts :l:h:p:S:J:G:cPgDekL:wx:a:m:h:irvts:bTK:o:d:CAE opt; do
    case $opt in
        l)
            fileList=$OPTARG
            allArgs="$allArgs -l"
            ;;
        h)
            host=$OPTARG
            allArgs="$allArgs -h \"$OPTARG\""
            ;;
        p)
            port=$OPTARG
            allArgs="$allArgs -p \"$OPTARG\""
            ;;
        S)
            givenSupercArgs="$OPTARG"
            allArgs="$allArgs -S \"$OPTARG\""
            ;;
        J)
            jvmFlags="$OPTARG"
            allArgs="$allArgs -J \"$OPTARG\""
            ;;
        G)
            gccArgs="$OPTARG"
            allArgs="$allArgs -G \"$OPTARG\""
            ;;
        c)
            compare=true
            allArgs="$allArgs -c"
            ;;
        P)
            checkParser=true
            allArgs="$allArgs -P"
            ;;
        g)
            gccParse=true
            allArgs="$allArgs -g"
            ;;
        D)
            dynamicAnalysis=true
            allArgs="$allArgs -D"
            ;;
        e)
            configInfo=true
            allArgs="$allArgs -e"
            ;;
        k)
            allConfigInfo=true
            allArgs="$allArgs -k"
            ;;
        L)
            configDir="$OPTARG"
            allArgs="$allArgs -L \"$OPTARG\""
            ;;
        w)
            writeConfigDir=true
            allArgs="$allArgs -w"
            ;;
        x)
            makecrossScript="$OPTARG"
            allArgs="$allArgs -x \"$OPTARG\""
            ;;
        a)
            arch="$OPTARG"
            allArgs="$allArgs -a \"$OPTARG\""
            ;;
        m)
            masquerade="$OPTARG"
            allArgs="$allArgs -m \"$OPTARG\""
            ;;
        i)
            saveIntermediate=true
            allArgs="$allArgs -i"
            ;;
        r)
            runtimes=true
            allArgs="$allArgs -r"
            ;;
        v)
            verbose=true
            allArgs="$allArgs -v"
            ;;
        t)
            test=true
            allArgs="$allArgs -t"
            ;;
        s)
            serverList=$OPTARG
            allArgs="$allArgs -s \"$OPTARG\""
            remoteDir=$PWD
            ;;
        b)
            slave=true
            allArgs="$allArgs -b"
            ;;
        T)
            testSlaves=true
            allArgs="$allArgs -T"
            ;;
        K)
            timeout="timeout $OPTARG"
            allArgs="$allArgs -K \"$OPTARG\""
            ;;
        o)
            outFile=$OPTARG
            allArgs="$allArgs -o \"$OPTARG\""
            ;;
        d)
            outDir=$OPTARG
            allArgs="$allArgs -d \"$OPTARG\""
            ;;
        C)
            compress=true
            allArgs="$allArgs -C"
            ;;
        A)
            configAST=true
            allArgs="$allArgs -A"
            ;;
        E)
            configE=true
            allArgs="$allArgs -E"
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

file=$1
files=(${@})

if [[ ! -z "${verbose}" ]]; then
    set -x on
fi

################################################################################
############################## Show Help #######################################
################################################################################

if [[ ! -z $help || (-z $file && -z $fileList && -z $host && -z $port && -z $serverList) ]]; then
    echo "USAGE:"
    echo "  `basename $0` -?"
    echo "    Show an extended help message."
    echo ""
    echo "  `basename $0` [OPTIONS] file"
    echo "    Run on one file."
    echo ""
    echo "  `basename $0` [OPTIONS] -l files.txt"
    echo "    Get files from files.txt."
    echo ""
    echo "  `basename $0` [OPTIONS] -h host -p port"
    echo "    Get filenames from host:port.  See"
    echo "    java superc.util.FilenameServer about usage."
    echo ""
    echo "OPTIONS:"
    echo "  TOOLS"
    echo "    -S \"args\"        (S)uperC command-line arguments."
    echo "    -J \"args\"        Extra (J)VM arguments."
    echo "    -G \"args\"        Extra (G)CC preprocessor arguments for -c."
    echo ""
    echo "  OPERATIONS"
    echo "    -c               (c)ompare SuperC output to configured file."
    echo "    -P               (P)arse the preprocessed file with SuperC."
    echo "    -g               Parse with (g)cc and get timings."
    echo "    -D               (D)ynamic analysis of collected statistics."
    echo "    -r               Show per-file (r)untimes.  Depends on \"bc\"."
    echo "    -E               Configure SuperC-preprocessed source with Linux config*"
    echo "    -A               Configure SuperC-parsed (A)ST with Linux config*"
    echo "    -e               (e)xtract SuperC's kbuild settings."
    echo "    -k               Extract all (k)build configuration information."
    echo "    -L dir           Get (L)inux configuration from dir."
    echo "    -w               (w)rite configuration to -L dir."
    echo "    -x               make.cross script for the config. Defaults to \"make\"."
    echo "    -a               (a)rchitecture to get the config for."
    echo "    -m file          (m)asquerade as file to use its configuration."
    echo "    -K seconds       (K)ill after a timeout.  Depends on \"timeout\"."
    echo "    -t               (t)est command-line args, but don't run SuperC."
    echo ""
    echo "      * Requires configured Linux kernel, e.g., with \"make allyesconfig\""
    echo ""
    echo "  DISTRIBUTED OPERATION"
    echo "    -s servers.txt   Run on slave (s)ervers, not locally."
    echo "    -b               Run as slave, so ignore -s."
    echo "    -T               (T)est slave servers' SuperC installations."
    echo ""
    echo "  OUTPUT"
    echo "    -o out           Write to out."
    echo "    -d dir           Write per-file output to dir/file."
    echo "    -C               Compress output with bzip2."
    echo "    -i               Save (i)ntermediate files."
    # echo "    -v               (v)erbose output."
    echo ""

    if [ ! -z $help ]; then
        echo "OUTPUT"
        echo "comparison_succeded filename  SuperC output match configured file."
        echo "comparison_failed filename    SuperC output did not match."
        echo "comparions_error filename     There was a problem, should try comparing again."
        echo ""
        echo "NOTES"
        echo "To extract kbuild's configuration information, it must be"
        echo "configured first, e.g. \"make allyesconfig ARCH=x86\"."
        echo "Using -h will read configuration information from cached files"
        echo "instead of using kbuild."
        echo ""
        echo "Slave servers will append their hostname to their out files."
    fi

    exit 0
fi


################################################################################
################# Check Environment and Command-Line Arguments #################
################################################################################

if [ -z "$JAVA_DEV_ROOT" ]
then
    "Please run xtc/scripts/env.sh before `basename $0`."
fi

if [ ! -z $runtimes ]; then
    which bc >/dev/null 2>&1
    if [[ $? -eq 0 ]]; then
        calc="bc -lq"
    else
        calc= #empty
        echo "Calculator program \"bc\" not found on system, reporting start and end times instead."
    fi
fi

if [ ! -z $file ]; then
    if [ ! -f $file ]; then
        echo "\"$file\" does not exist."
        exit
    fi

    if [ ! -z $fileList ]; then
        echo "Cannot specify \"-l\" and provide a filename on the command-line."
        exit
    fi

    if [[ ! -z $serverList || ! -z $host || ! -z $port ]]; then
        echo "Cannot specify \"-s\", \"-h\", or \"-p\" and provide a filename on the command-line."
        exit
    fi
fi

if [ ! -z $fileList ]; then
    if [ ! -f $fileList ]; then
        echo "\"$fileList\" does not exist."
        exit
    fi


    if [[ ! -z $serverList || ! -z $host || ! -z $port ]]; then
        echo "Cannot specify \"-s\", \"-h\", or \"-p\" and provide a file list with \"-l\"."
        exit
    fi
fi

if [[ ! -z $host || ! -z $port ]]; then
    if [[ -z $host || -z $port ]]; then
        echo "Must specify \"-h\" and \"-p\" with \"-s\"."
        exit
    fi
fi

if [ ! -z $slave ]; then
    serverList=
    if [ ! -z $outFile ]; then
        outFile=$outFile.$HOSTNAME
    fi
fi

if [ ! -z $serverList ]; then
    if [ ! -f $serverList ]; then
        echo "\"$serverList\" does not exist."
        exit
    fi

    echo $allArgs
    servers=`cat $serverList`
    if [ ! -z $testSlaves ]; then
        for server in $servers; do
            echo "Checking $server:$remoteDir"
            ssh $server "source $JAVA_DEV_ROOT/scripts/env.sh; cd $remoteDir;superc_linux.sh -c -S-printSource arch/x86/kernel/acpi/realmode/regs.c" 2>&1 | grep comparison_succeeded
            if [ $? -ne 0 ]; then
                echo $retval
                echo "$server failed."
                exit
            fi
        done
    fi
fi

if [[ ! -z $outFile && -f $outFile ]]; then
    echo "The output file \"$outFile\" already exists."
    exit
fi

if [ ! -z $outDir ]; then
    if [ ! -z $compare ]; then
        echo "-d has no effect with -c."
        exit
    fi
fi

if [[ ! -z "$runtimes" && (! -z "$outDir" || ! -z "$compare") ]]; then
    echo "-r has no effect with -c and -d."
    exit
fi

if [[ ! -z "$writeConfigDir" && -z "$configDir" ]]; then
    echo "-w only applies when using -L"
    exit
fi

if [[ ! -z "$makecrossScript" && -z "$writeConfigDir" ]]; then
    echo "-x only applies when using -w"
    exit
fi

if [[ ! -z "$arch" && -z "$writeConfigDir" ]]; then
    echo "-a only applies when using -w"
    exit
fi

if [[ ! -z $test ]]; then
    echo "Parameters passed tests.  Run again without \"-t\"."
    exit
fi

if [[ ! -z $timeout ]]; then
    which timeout > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "The timeout utility was not found.  Can't use -K."
        exit
    fi
fi

if [[ ! -z $compress && -z $outDir ]]; then
    echo "-C can only be used with -d"
    exit
fi

################################################################################
############################## Setup Files #####################################
################################################################################

filesToProcess=
length=0
if [ ! -z $file ]; then
    filesToProcess[0]=$file
    length=1

# if [ ! -z $files ]; then
#     filesToProcess=(${files[@]})
#     length=${#files[@]}

elif [ ! -z $fileList ]; then
    for file in `cat $fileList`; do
        filesToProcess[length]=$file
        length=$length+1
    done
fi

tempfilebase=$($JAVA_DEV_ROOT/scripts/tempfile.sh -p super) || exit
tempfiles="$tempfilebase"
header_args=$tempfilebase.headers || exit
config_args=$tempfilebase.configs || exit
superc_out=
superc_out_E=
if [ -z $saveIntermediate ]; then
    tempfiles="$tempfiles $header_args $config_args"
fi

if [ ! -z $compare ]; then
    superc_out=$tempfilebase.super.c || exit
    superc_out_E=$tempfilebase.super.E || exit
    gcc_E=$tempfilebase.gcc.E || exit
    superc_diff=$tempfilebase.diff || exit

    if [ -z $saveIntermediate ]; then
        tempfiles="$tempfiles $superc_out $superc_out_E $gcc_E $header_args $superc_diff"
    fi
elif [ ! -z "$checkParser" ]; then
    gcc_E=$tempfilebase.gcc.E || exit
    superc_out=$tempfilebase.super.c || exit

    if [ -z $saveIntermediate ]; then
        tempfiles="$tempfiles $gcc_E $superc_out"
    fi
fi

if [ ! -z "$tempfiles" ]; then
    trap "rm -f -- $tempfiles" EXIT
fi


################################################################################
############################### Run SuperC #####################################
################################################################################

if [ ! -z $outFile ]; then
    # Redirect all output from the script to standard out and
    # $outFile.
    # exec 2>&1 | tee > $outFile
    exec > $outFile 2>&1
fi



if [ -z "$servers" ]; then
    i=0
    while :; do
        # Get next file.
        if [ -z $host ]; then
            if [[ $i -eq $length ]]; then
                exit;
            fi
            file=${filesToProcess[$i]}
            i=$i+1
        else
            file=`java superc.util.FilenameService -client $host $port`
            errcode=$?
            if [[ $errcode -eq 3 ]]; then
                echo "No more files."
                exit
            elif [[ $errcode -eq 4 ]]; then
                echo "No server available."
                exit
            elif [[ $errcode -ne 0 || -z $file ]]; then
                echo "Unknown file server error."
                exit
            fi
        fi

        echo "Processing $file"

        if [ ! -z "$dynamicAnalysis" ]; then
            dynamic_analysis.sh $file
        else
            # Extract configuration settings from kbuild.
            if [ ! -z "$masquerade" ]; then
                config_file=$masquerade
                obj_file=${masquerade%.*}.o
            else
                config_file=$file
                obj_file=${file%.*}.o
            fi

            if [[ ! -z "$configE" ]]; then
                supercArgs="$givenSupercArgs -E"
            elif [[ ! -z "$configAST" ]]; then
                supercArgs="$givenSupercArgs -configFile .config -configureExceptions \"$(java superc.util.GCCShunt --emit-exceptions $(superc_linux.sh -k "$config_file" | grep ^configs_all) none)\""
            else
                supercArgs="$givenSupercArgs"
            fi
            
            if [ ! -z "$configDir" ]; then
                cacheConfigArgs=$configDir/$config_file.configs_all
                cacheSuperCArgs=$configDir/$config_file.configs_superc

                if [ -z "$writeConfigDir" ]; then
                    config_args=$cacheConfigArgs
                    header_args=$cacheSuperCArgs
                    if [[ -f $config_args && -f $header_args ]]; then
                        getConfigResult=0
                    else
                        echo "excluded $file no configuration from $configDir"
                        getConfigResult=1
                    fi
                fi
            fi

            if [[ -f $cacheConfigArgs && -f $cacheSuperCArgs && ! -z "$writeConfigDir" ]]; then
                echo "excluded $file already written"
                getConfigResult=0;
            elif [[ -z "$configDir" || ! -z "$writeConfigDir" ]]; then
                # Can't override CC since it is used to emit compiler
                # information
                if [[ -z "$makecrossScript" ]]; then
                    makeScript="make"
                else
                    makeScript="$makecrossScript"
                fi
                which $makeScript
                if [[ -z "$arch" ]]; then
                    archParam=""
                else
                    archParam="ARCH=$arch"
                fi
                $makeScript $archParam CHECK="java superc.util.GCCShunt --shunt-filename $config_file --shunt-superc $header_args --shunt-kbuild --shunt-config $config_args" C=2 $obj_file
                getConfigResult=$?
                # if [ $getConfigResult -ne 0 ]; then
                # # Try overriding CC instead of CHECK, since the file
                # # may not be compiling.
                #     make CC="java superc.util.GCCShunt --shunt-filename $config_file --shunt-superc $header_args --shunt-kbuild --shunt-config $config_args" C=2 $obj_file
                #     getConfigResult=$?
                # fi
                # make -i -f $JAVA_DEV_ROOT/scripts/Makefile.kcu ARCH=x86 \
                #     CC="java superc.util.GCCShunt --shunt-filename $config_file --shunt-superc $header_args --shunt-kbuild --shunt-config $config_args" \
                #     LD="echo ld" ar="echo ar" $obj_file
                # getConfigResult=$?
                cat $config_args
                cat $header_args
                echo $getConfigResult
                if [[ ! -e $config_args && ! -e $header_args ]]; then
                    echo "excluded $file no configuration from make"
                else
                    getConfigResult=0
                fi
            fi

            if [ $getConfigResult -eq 0 ]; then
                if [ ! -z "$writeConfigDir" ]; then
                    mkdir -p `dirname $cacheConfigArgs` `dirname $cacheSuperCArgs`
                    if [[ -f $config_args && -f $header_args ]]; then
                        cp $config_args $cacheConfigArgs
                        cp $header_args $cacheSuperCArgs
                    fi
                elif [ ! -z "$configInfo" ]; then
                    echo "configs_superc $file`cat $header_args`"
                elif [ ! -z "$allConfigInfo" ]; then
                    echo "configs_all $file`cat $config_args`"
                elif [ ! -z "$checkParser" ]; then
                    gcc -E `cat $config_args` $gccArgs $file > $gcc_E 2>/dev/null
                    java -ea $JAVA_ARGS $jvmFlags superc.SuperC -enc-in UTF-8 -silent -showAccepts $supercArgs $gcc_E 2>&1 | tee $superc_out
                    cat $superc_out | grep ACCEPT
                    if [ $? -ne 0 ]; then
                        echo "grammar_failed $file"
                    else
                        echo "grammar_succeeded $file"
                    fi

                    if [ ! -z $saveIntermediate ]; then
                        echo $gcc_E
                        echo $superc_out
                        echo $header_args
                        echo $config_args
                    fi
                elif [ ! -z "$gccParse" ]; then
                    gcc -ftime-report -fsyntax-only `cat $config_args` $file
                else
                    # bash is simply a terrible programming language.
                    # that's why this mess below is needed.  it
                    # handles quoted command-line arguments,
                    # preventing bash from separating them into
                    # tokens.
                    cmd=(java -ea $JAVA_ARGS $jvmFlags superc.SuperC -enc-in UTF-8 -silent)
                    saveifs=$IFS
                    IFS='
'
                    for cmd_i in $(grep -Eo '"[^"]*"|[^" ]*' <<< "$supercArgs"); do
                      cmd_i="${cmd_i%\"}"
                      cmd_i="${cmd_i#\"}"
                      cmd+=("$cmd_i")
                    done
                    IFS=$saveifs
                    cmd+=(`cat $header_args` -include $JAVA_DEV_ROOT/data/cpp/nonbooleans.h $file)
                    # # debugging output
                    # for (( cmd_i=0; cmd_i<${#cmd[@]}; cmd_i++ )); do
                    #   echo ${cmd[cmd_i]}
                    # done
                    # exit
                    # cmd="java -ea $JAVA_ARGS $jvmFlags superc.SuperC -enc-in UTF-8 -silent $supercArgs `cat $header_args` -include $JAVA_DEV_ROOT/data/cpp/nonbooleans.h $file"
                    if [ -z $compare ]; then
                        if [ -z $outDir ]; then
                            before=`date +%s.%N`
                            $timeout "${cmd[@]}"
                            if [ $? -eq 124 ]; then
                                echo "killed $file"
                            fi
                            after=`date +%s.%N`

                            if [ ! -z "$runtimes" ]; then
                                if [[ ! -z $calc ]]; then
                                    time=`echo "$after - $before" | $calc`
                                    echo "performance $file $time"
                                else
                                # If there's no calculator program,
                                # output raw start and end times.
                                    echo "performance_raw $file $before $after"
                                fi
                            fi
                        else
                            outDirCombined=$outDir/`dirname $file`
                            mkdir -p $outDirCombined
                            outFile=$outDir/$file
                            $timeout "${cmd[@]}" > $outFile.part 2>&1
                            if [ $? -eq 124 ]; then
                                echo "killed $file" | tee -a $outFile.part
                            fi
                            mv $outFile.part $outFile
                            if [ ! -z $compress ]; then
                                bzip2 $outFile
                            fi
                        fi
                    else
                        $timeout "${cmd[@]}" | grep -v "^Resizing node table" > $superc_out
                        if [ $? -eq 124 ]; then
                            echo "killed $file" | tee -a $superc_out
                        fi
                        gcc -E `cat $config_args` $gccArgs $superc_out > $superc_out_E
                        gcc -E `cat $config_args` $gccArgs $file > $gcc_E 2>/dev/null
                        java superc.util.cdiff -s $superc_out_E $gcc_E > $superc_diff 2>&1
                        retval=$?

                        cat $superc_diff
                        if [ $retval -eq 0 ]; then
                            echo "comparison_succeeded $file"
                        elif [ $retval -eq 1 ]; then
                            echo "comparison_failed $file"
                        else
                            echo "comparison_error $file"
                        fi

                        if [ ! -z $saveIntermediate ]; then
                            echo $superc_diff
                            echo $gcc_E
                            echo $superc_out
                            echo $superc_out_E
                            echo $header_args
                            echo $config_args
                        fi
                    fi
                fi
            fi
        fi
    done
else
    # Run SuperC on remote servers, not locally.
    for server in $servers; do
        echo "Starting slave $server:$remoteDir"
        ssh $server "source .profile; cd $remoteDir; superc_linux.sh -b $allArgs" &
    done
fi
