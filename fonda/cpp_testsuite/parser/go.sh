opts="-Oshared -Olazy -earlyShift"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Oshared -Olazy"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Oshared -Olazy -Oearly"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Oshared -earlyShift"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Oshared"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Oshared -Oearly"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Olazy -earlyShift"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Olazy"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Olazy -Oearly"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Onone -earlyShift"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Onone"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Onone -Oearly"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo

opts="-Olazy"
echo $opts
java xtc.lang.cpp.SuperC $opts -parserStatistics array.c 2>&1 | grep max_subparsers
echo
