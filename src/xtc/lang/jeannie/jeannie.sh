#! /usr/bin/env bash
# (C) Copyright IBM Corp 2007

# self detection for diagnostic messages later in script
SCRIPT_NAME=$(
  declare -a h1=( $( history 1) )
  me=$0
  if [[ ${h1[1]} == "source" || ${h1[1]} == "." ]]; then me=${h1[2]}; fi
  if [[ $me == */* ]]; then cd ${me%/*}; fi
  echo $( pwd )/${me##*/}
)
shopt -s expand_aliases
alias printlnPos='echo >&2 $SCRIPT_NAME:$LINENO:'

# --------------------------------------------------------------------
# documentation
USAGE=$(cat <<EOF
Usage: jeannie [options] file...
For details, see http://cs.nyu.edu/rgrimm/xtc/.
Options:
  -cc <path>               File name of your C compiler.
  -cp | -classpath <paths> Search existing user class files in <paths>.
  -d | -destpath <dir>     Write output generated files to <dir>.
  -flattenSmap             Rewrite line numbers with SMAP, do not stratify.
  -g                       Produce debugging symbols.
  -h | -help               Print this message.
  -I<dir>                  Search header files in <dir>.
  -javaHome <dir>          Use the JDK installed in <dir>.
  -jniCall <qualifier>     Prepend generated C JNI functions with <qualifier>.
  -l<library>              Search <library> when linking with the C compiler.
  -nowarn                  Disable compiler warning messages.
  -platform <platform>     Compile for <platform>.
  -pretty                  Optimize generated code for human readability.
  -underscores             Require leading underscore in keywords, e.g., _with.
  -in | -sourcepath <dir>  Read input source files from <dir>.
  -showFilePaths           Show paths in line markers in generated Java code.
  -stopAfter <stage>       Stop compiling after reaching <stage>.
  -v | -verbose            Print commands executed by this bash script.
  -verboseSettings         Print internal settings of this bash script.
  --                       Treat remainder of command line as file names.
EOF
)

# --------------------------------------------------------------------
# defaults for options
case $OSTYPE in
  cygwin)   PLATFORM=Cygwin;;
  *linux*)  PLATFORM=Linux;;
  *darwin*) PLATFORM=MacOS;;
esac
DEBUG_INFO=false
FLATTEN_SMAP=false
INCLUDE_ARGS=""
LINK_ARGS=""
PRETTY=false
SHOW_FILE_PATHS=false
SHOW_WARNINGS=true
SOURCEPATH=.
STOP_AFTER=all_the_way
UNDERSCORES=false
VERBOSE=false
VERBOSE_SETTINGS=false

# --------------------------------------------------------------------
# process command line arguments
while [ 0 -lt $# ]; do
  case "$1" in
    -cc)                 shift; CC=$1;;
    -cp | -classpath)    shift; CLASSPATH=$1;;
    -d | -destpath)      shift; DESTPATH=$1;;
    -flattenSmap)        FLATTEN_SMAP=true;;
    -g)                  DEBUG_INFO=true;;
    -h | -help)          echo "$USAGE"; exit 0;;
    -I*)                 INCLUDE_ARGS="$INCLUDE_ARGS $1";;
    -javaHome)           shift; JAVA_HOME=$1;;
    -jniCall)            shift; JNI_CALL=$1;;
    -l*)                 LINK_ARGS="$LINK_ARGS $1";;
    -nowarn)             SHOW_WARNINGS=false;;
    -platform)           shift; PLATFORM=$1;;
    -pretty)             PRETTY=true;;
    -underscores)        UNDERSCORES=true;;
    -in | -sourcepath)   shift; SOURCEPATH=$1;;
    -showFilePaths)      SHOW_FILE_PATHS=true;;
    -stopAfter)          shift; STOP_AFTER=$1;;
    -v | -verbose)       VERBOSE=true;;
    -verboseSettings)    VERBOSE_SETTINGS=true;;
    --)                  shift; break;;
    -*)                  echo "Unknown option $1."; echo "$USAGE"; exit 1;;
    *)                   break;;
  esac
  shift
done

if [ 0 == $# ]; then echo "Missing file name."; echo "$USAGE"; exit 1; fi

SOURCE_FILE=$1; shift
OTHER_C_FILES="$*"

SOURCE_BASE=${SOURCE_FILE##*/} # base name (file name without directory)
if [[ $SOURCE_FILE == */* ]]; then
  SOURCE_DIR=${SOURCE_FILE%/*} # directory (relative to SOURCEPATH)
else
  SOURCE_DIR=.
fi
SOURCE_EXT=${SOURCE_FILE##*.}  # extension (e.g., .jni)
SOURCE_STEM=${SOURCE_BASE%.*}  # stem      (base name without extension)

# --------------------------------------------------------------------
# validate configuration and set variables
if [[ $DEBUG_INFO == true && $PRETTY == true ]]; then
  printlnPos "The options -g and -pretty are mutually exclusive."
  echo $USAGE; exit 1
fi

if [[ ${CC:+x} != x ]]; then CC=`which gcc`; fi
if [[ ! (-x $CC) ]]; then CC=`which cc`; fi
if [[ ! (-x $CC) ]]; then
  printlnPos "Could not find gcc or cc. Set PATH or specify -cc.";
  echo $USAGE; exit 1
fi
if [ $DEBUG_INFO == true ]; then CC="$CC -g"; fi
if [ $SHOW_WARNINGS == true ]; then CC="$CC -Wall"; else CC="$CC -O2"; fi
if [[ ${CFLAGS:+x} != x ]]; then CC="$CC $CFLAGS"; fi
if [[ ${INCLUDE_ARGS:+x} == x ]]; then CC="$CC $INCLUDE_ARGS"; fi

if [[ ${CLASSPATH:+x} != x ]]; then CLASSPATH=''; fi

if [[ ${JAVA_HOME:+x} != x ]]; then
  WHICHJAVA=`which java`
  if [[ ! (-x $WHICHJAVA) ]]; then
    printlnPos "Could not find java. Set PATH or specify -javaHome.";
    echo $USAGE; exit 1
  fi
  JAVA_HOME=${WHICHJAVA%/bin/java}
fi
JAVA="$JAVA_HOME/bin/java -ea"
JAVAC="$JAVA_HOME/bin/javac"
if [[ ! (-x $JAVAC) ]]; then JAVAC=`which javac`; fi
if [[ ! (-x $JAVAC) ]]; then
  printlnPos "Could not find javac. Set PATH or specify -javaHome.";
  echo $USAGE; exit 1
fi
if [ $DEBUG_INFO == true ]; then JAVAC="$JAVAC -g"; fi
if [ $SHOW_WARNINGS == false ]; then JAVAC="$JAVAC -nowarn"; fi

case $PLATFORM in
  Cygwin)
    JNI_HDRDIR=$JAVA_HOME/include
    CC_JNI="$CC -mno-cygwin -I$JNI_HDRDIR -I$JNI_HDRDIR/win32"
    CC_DLL="$CC_JNI -Wl,--add-stdcall-alias -shared"
    PATH_SEP=';'
    DLL_PREFIX=''
    DLL_SUFFIX=.dll
    DLL_SUFFIX_JNI=$DLL_SUFFIX
    ;;
  Linux)
    JNI_HDRDIR=$JAVA_HOME/include
    CC_JNI="$CC -I$JNI_HDRDIR -I$JNI_HDRDIR/linux"
    CC_DLL="$CC_JNI -shared -fPIC"
    PATH_SEP=':'
    DLL_PREFIX=lib
    DLL_SUFFIX=.so
    DLL_SUFFIX_JNI=$DLL_SUFFIX
    ;;
  MacOS)
    JNI_HDRDIR=/System/Library/Frameworks/JavaVM.framework/Headers
    CC_JNI="$CC -DSPECIALIZE_RELPROD -DSPECIALIZE_AND -DSPECIALIZE_OR -DSMALL_NODES -fomit-frame-pointer -U__BLOCKS__ -fno-common -I$JNI_HDRDIR"
    CC_DLL="$CC_JNI -dynamiclib -framework JavaVM"
    DLL_PREFIX=lib
    DLL_SUFFIX=.dylib
    DLL_SUFFIX_JNI=.jnilib
    PATH_SEP=':'
    ;;
  *)
    printlnPos "Unknown platform $PLATFORM. Specify -platform."
    echo $USAGE; exit 1;;
esac

if [[ ${LINK_ARGS:+x} == x ]]; then CC_DLL="$CC_DLL $LINK_ARGS"; fi

if [[ ${DESTPATH:+x} != x ]]; then DESTPATH=$SOURCEPATH; fi

if [[ ${JNI_CALL:+x} != x ]]; then
  JNI_CALL=$( $CC_JNI -E -x c - <<EOF
#include <jni.h>
MACRO_JNICALL/JNICALL
EOF
)
  JNI_CALL=${JNI_CALL##*MACRO_JNICALL/}
fi

if [ $VERBOSE_SETTINGS == true ]; then
  printlnPos "Settings:"
  echo "  CC_JNI              == $CC_JNI"
  echo "  CC_DLL              == $CC_DLL"
  echo "  CLASSPATH           == $CLASSPATH"
  echo "  DEBUG_INFO          == $DEBUG_INFO"
  echo "  DESTPATH            == $DESTPATH"
  echo "  DLL_PREFIX          == $DLL_PREFIX"
  echo "  DLL_SUFFIX          == $DLL_SUFFIX"
  echo "  DLL_SUFFIX_JNI      == $DLL_SUFFIX_JNI"
  echo "  INCLUDE_ARGS        == $INCLUDE_ARGS"
  echo "  JAVA                == $JAVA"
  echo "  JAVAC               == $JAVAC"
  echo "  JNI_CALL            == $JNI_CALL"
  echo "  LINK_ARGS           == $LINK_ARGS"
  echo "  PATH_SEP            == $PATH_SEP"
  echo "  PLATFORM            == $PLATFORM"
  echo "  PRETTY              == $PRETTY"
  echo "  UNDERSCORES         == $UNDERSCORES"
  echo "  SHOW_WARNINGS       == $SHOW_WARNINGS"
  echo "  SOURCEPATH          == $SOURCEPATH"
  echo "  SOURCE_DIR          == $SOURCE_DIR"
  echo "  SOURCE_EXT          == $SOURCE_EXT"
  echo "  SOURCE_STEM         == $SOURCE_STEM"
  echo "  STOP_AFTER          == $STOP_AFTER"
  echo "  VERBOSE             == $VERBOSE"
fi

STAGE=$SOURCE_EXT

if [ $STAGE == $STOP_AFTER ]; then
  if [ $VERBOSE == true ]; then printlnPos "Done."; fi
  exit 0
fi

# --------------------------------------------------------------------
testStageSuccess() {
  LINE_NUMBER=$1; shift
  COMMAND=$1; shift
  STATUS=$1; shift
  if [ $STATUS != 0 ]; then
    echo >&2 "$SCRIPT_NAME:$LINE_NUMBER: Error exit status $STATUS. Aborting."
    echo >&2 "  Failed stage: $COMMAND."
    exit $STATUS
  fi
  while [ 0 -lt $# ]; do
    if [[ ! (-r "$1") ]]; then
      echo >&2 "$SCRIPT_NAME:$LINE_NUMBER: File $1 was not created. Aborting."
      echo >&2 "  Failed stage: $COMMAND."
      exit 1
    fi
    shift
  done
}

# --------------------------------------------------------------------
# run Jeannie preprocessor
if [ $STAGE == jni ]; then
  SOURCE=$SOURCEPATH/$SOURCE_DIR/$SOURCE_STEM.$STAGE
  STAGE=jni.pp
  SOURCEPATH=$DESTPATH
  DEST=$DESTPATH/$SOURCE_DIR/$SOURCE_STEM.$STAGE
  mkdir -p $DESTPATH/$SOURCE_DIR

  COMMAND="$JAVA xtc.lang.jeannie.Preprocessor"
  if [ $VERBOSE != true ]; then COMMAND="$COMMAND -silent"; fi
  if [ $UNDERSCORES == true ]; then COMMAND="$COMMAND -underscores"; fi
  COMMAND="$COMMAND $SOURCE"
  COMMAND_PRINT="$COMMAND > $DEST"

  if [ $VERBOSE == true ]; then printlnPos "$COMMAND_PRINT"; fi
  $COMMAND > $DEST
  testStageSuccess $LINENO "$COMMAND_PRINT" $? $DEST
fi

if [ $STAGE == $STOP_AFTER ]; then
  if [ $VERBOSE == true ]; then printlnPos "Done."; fi
  exit 0
fi

# --------------------------------------------------------------------
# run C preprocessor
if [ $STAGE == jni.pp ]; then
  SOURCE=`cd $SOURCEPATH/$SOURCE_DIR; pwd`
  SOURCE=$SOURCE/$SOURCE_STEM.$STAGE
  STAGE=jni.i
  SOURCEPATH=$DESTPATH
  DEST=$DESTPATH/$SOURCE_DIR/$SOURCE_STEM.$STAGE
  mkdir -p $DESTPATH/$SOURCE_DIR

  COMMAND="$CC_JNI -E -x c $SOURCE"
  COMMAND_PRINT="$COMMAND > $DEST"

  if [ $VERBOSE == true ]; then printlnPos "$COMMAND_PRINT"; fi
  $COMMAND > $DEST
  testStageSuccess $LINENO "$COMMAND_PRINT" $? $DEST
fi

if [ $STAGE == $STOP_AFTER ]; then
  if [ $VERBOSE == true ]; then printlnPos "Done."; fi
  exit 0
fi

# --------------------------------------------------------------------
# run Jeannie compiler
if [ $STAGE == jni.i ]; then
  SOURCE=$SOURCEPATH/$SOURCE_DIR/$SOURCE_STEM.$STAGE
  STAGE=i,java
  SOURCEPATH=$DESTPATH
  DEST1=$DESTPATH/$SOURCE_DIR/$SOURCE_STEM.i
  DEST2=$DESTPATH/$SOURCE_DIR/$SOURCE_STEM.java
  mkdir -p $DESTPATH/$SOURCE_DIR

  COMMAND="$JAVA xtc.lang.jeannie.Jeannie -analyze -translate -builtins"
  COMMAND="$COMMAND -in $SOURCEPATH -out $DESTPATH"
  if [[ ${JNI_CALL:+x} == x ]]; then COMMAND="$COMMAND -jniCall $JNI_CALL"; fi
  if [ $VERBOSE != true ]; then COMMAND="$COMMAND -silent"; fi
  if [ $PRETTY == true ]; then
    COMMAND="$COMMAND -pretty";
  elif [ $SHOW_FILE_PATHS == true ]; then
    COMMAND="$COMMAND -showFilePaths";
  fi
  COMMAND="$COMMAND $SOURCE"

  if [ $VERBOSE == true ]; then printlnPos "$COMMAND"; fi
  $COMMAND
  testStageSuccess $LINENO "$COMMAND" $? $DEST1 $DEST2
fi

if [ $STAGE == $STOP_AFTER ]; then
  if [ $VERBOSE == true ]; then printlnPos "Done."; fi
  exit 0
fi

# --------------------------------------------------------------------
# run C compiler
if [[ $STAGE == i || $STAGE == i,* || $STAGE == *,i || $STAGE == *,i,* ]]; then
  SOURCE=$SOURCEPATH/$SOURCE_DIR/$SOURCE_STEM.i
  if     [ $STAGE == i   ]; then STAGE='';
    elif [ $STAGE == i,* ]; then STAGE=${STAGE#i,};
    elif [ $STAGE == *,i ]; then STAGE=${STAGE%,i};
    else                         STAGE=${STAGE/,i,/,};
  fi
  DEST=$DESTPATH/$SOURCE_DIR/$DLL_PREFIX$SOURCE_STEM$DLL_SUFFIX_JNI
  mkdir -p $DESTPATH/$SOURCE_DIR

  COMMAND="$CC_DLL -o $DEST $SOURCE $OTHER_C_FILES"

  if [ $VERBOSE == true ]; then printlnPos "$COMMAND"; fi
  $COMMAND
  testStageSuccess $LINENO "$COMMAND" $? $DEST
fi

if [ $STAGE == $STOP_AFTER ]; then
  if [ $VERBOSE == true ]; then printlnPos "Done."; fi
  exit 0
fi

# --------------------------------------------------------------------
# run java compiler
if [[ $STAGE == java || $STAGE == java,*
      || $STAGE == *,java || $STAGE == *,java,* ]]
then
  SOURCE=$SOURCEPATH/$SOURCE_DIR/$SOURCE_STEM.java
  STAGE=${STAGE/java/class}
  DEST=$DESTPATH/$SOURCE_DIR/$SOURCE_STEM.class
  mkdir -p $DESTPATH

  COMMAND="$JAVAC -sourcepath $SOURCEPATH -d $DESTPATH $SOURCE"

  if [ $VERBOSE == true ]; then printlnPos "$COMMAND"; fi
  $COMMAND
  testStageSuccess $LINENO "$COMMAND" $? $DEST
fi

# --------------------------------------------------------------------
# run Java line number postprocessor
if [[ $PRETTY == false && ( $STAGE == class || $STAGE == class,*
                            || $STAGE == *,class || $STAGE == *,class,* ) ]]
then
  SYMBOLS=$SOURCEPATH/$SOURCE_DIR/$SOURCE_STEM.jni.symbols
  TOPLEVEL=$( grep -e '^TopLevelClassesOrInterfaces: ' $SYMBOLS )
  CLASS_FILES=""
  for t in ${TOPLEVEL##TopLevelClassesOrInterfaces: }; do
    t=${t%%[[:space:]]*} # get rid of spurious Windows line break if any
    CLASS_FILES="$CLASS_FILES $DESTPATH/$SOURCE_DIR/$t.class"
    CLASS_FILES="$CLASS_FILES $DESTPATH/$SOURCE_DIR/$t"'$'*.class
  done

  SOURCE=$SOURCEPATH/$SOURCE_DIR/$SOURCE_STEM.java

  for f in $CLASS_FILES; do
    if [ -r $f ]; then
      COMMAND="$JAVA xtc.lang.ClassfileSourceRemapper"
      if [ $FLATTEN_SMAP == true ]; then COMMAND="$COMMAND -flatten"; fi
      COMMAND="$COMMAND $SOURCE $f"

      if [ $VERBOSE == true ]; then printlnPos "$COMMAND"; fi
      $COMMAND
      testStageSuccess $LINENO "$COMMAND" $?
    fi
  done
fi
