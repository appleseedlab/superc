# collect unit presence conditions using kmax
python $KMAX_ROOT/analysis/collect_buildsystem.py 4.0 x86

# collect functions and their presence conditions.  this produces
# $KMAX_DATA/functions_4.0x86.txt and $KMAX_DATA/functions_pc_4.0x86
python $KMAX_ROOT/analysis/collect_functions.py 4.0 x86

# extract the kconfig feature model
check_dep --autoconf-cnf arch/x86/Kconfig > $KMAX_DATA/clauses_4.0x86.txt

# run from the $KMAX_DATA directory, this executes the analysis to
# check for linker errors
cd $KMAX_DATA
java xtc.lang.cpp.FunctionChecker functions_4.0x86.txt functions_pc_4.0x86 unit_pc_4.0x86.txt clauses_4.0x86.txt

# test with ablkcipher.  these are slices of the above files, except
# for the kconfig model
java xtc.lang.cpp.FunctionChecker functions_4.0x86_slice.txt functions_pc_4.0x86 unit_pc_4.0x86_slice.txt clauses_4.0x86.txt
