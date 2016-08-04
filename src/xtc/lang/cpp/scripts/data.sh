################################################################################
###############################  Introduction  #################################
################################################################################

# This document describes how to replicate all experiments on SuperC
# and comparison to TypeChef.  It assumes that SuperC is install, but
# provides directions on installing and setting up TypeChef.
                                                                        
# Also, it assumes that xtc's JAVA_DEV_ROOT environment variable is
# set and that SuperC's scripts directory,
# $JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts, is in the shell's search
# path and that other environment variables,
# e.g. $JAVA_DEV_ROOT/data/cpp, are properly set.  See and run the
# script env.sh in xtc-root/src/xtc/lang/cpp/scripts (where xtc-root
# is the root of the xtc source tree) to set up these environment
# variables.


echo "Don't actually execute this script.  It is for documentation purposes."
exit

#############################################################################
################  1. Performance Test SuperC and TypeChef  ##################
#############################################################################

# Download and patch TypeChef to remove print statements (see SuperC's
# manual.pdf for details) and use SuperC's scripts to run the
# performance tests.

# Get TypeChef, go to the right commit-id and patch it.
git clone https://github.com/ckaestne/TypeChef.git
cd TypeChef
# From 2012-02-17
git checkout -b remove_printlns 785febc704615044ad1e5e2cf74c13c6bbc05389
git apply $JAVA_DEV_ROOT/data/cpp/0001-remove-printlns.patch
java -jar sbt-launch.jar clean update compile publish-local mkrun
cd ..

# Get TypeChef-LinuxAnalysis and go to the right commit-id.
git clone https://github.com/ckaestne/TypeChef-LinuxAnalysis.git
# From 2012-02-13
git checkout -b tested_version 714e8da623c26748a1ba8cd5b6fca2dc71fa40f8
cd TypeChef-LinuxAnalysis
java -jar ../TypeChef/sbt-launch.jar clean update compile mkrun

# Get Linux source.
wget http://www.kernel.org/pub/linux/kernel/v2.6/linux-2.6.33.3.tar.gz
tar -zxvf linux-2.6.33.3.tar.gz

# Run TypeChef’s preparation script.
./prepareLinuxTestCase.sh

# Run this because the prepareLinuxTestCase.sh script is broken.
./run.sh de.fosd.typechef.linux.ProcessFileList linux_2.6.33.3_pcs.txt l/

# Get the RedHat system headers.  Needed for TypeChef test case.
cp $JAVA_DEV_ROOT/data/cpp/typechef/systems.tar .
tar -xvf systems.tar

# SuperC parser performance.  Writes to
# performance.SuperC.YYYY-MM-DD_HH-MM-SS.txt.
nohup typechef_test.sh SuperC &

# TypeChef parser performance.  Writes to
# performance.TypeChef.YYYY-MM-DD_HH-MM-SS.txt.
nohup typechef_test.sh TypeChef &

# Graph the performance cdf.
graph_performance_cdf.sh performance_cdf.pdf /home/paul/work/SuperC/TypeChef-LinuxAnalysis/performance.txt /home/paul/work/SuperC/TypeChef-LinuxAnalysis/performance_typechef.txt

# Unconstrained kernel performance.
nohup superc_linux.sh -r -l typechef_files.txt -L configurations/ -o performance_full_kernel.txt &

# Get subparsers of constrained linux-2.6.33.3 kernel.
sed 's/^\(.*\)$/linux-2.6.33.3\/\1.c/' linux_files.lst | sort | uniq > typechef_files.txt
nohup java xtc.lang.cpp.FilenameService -server 7001 typechef_files.txt &
for server in `cat $JAVA_DEV_ROOT/data/cpp/server_list.txt`; do
    echo "Starting slave $server"
    ssh $server "source $JAVA_DEV_ROOT/src/xtc/lang/cpp/scripts/env.sh; cd $PWD; typechef_test.sh -h beaker-2.news.cs.nyu.edu -p 7001 -a-parserStatistics -o subparsers1_fullopt.txt.$server SuperC" &
done &


################################################################################
##########################  2. Performance Breakdown  ##########################
################################################################################

# Run the performance test, collecting the timings broken down by
# lexer, preprocessor, and parser.
nohup typechef_test.sh -a-time -o performance_breakdown.txt SuperC &

# Get the compilation unit sizes and config vars.
nohup typechef_test.sh -a"-size -configurationVariables -headerGuards -preprocessor" -o sizes_and_configs.txt SuperC &

# Graph the performance breakdown sorted by size.
graph_performance_breakdown.sh size performance_breakdown_sorted_by_size.pdf $CPPDEV/TypeChef-LinuxAnalysis/performance_breakdown.txt $CPPDEV/TypeChef-LinuxAnalysis/sizes_and_configs.txt

# Graph the performance breakdown sorted by configs.
graph_performance_breakdown.sh configs performance_breakdown_sorted_by_configs.pdf $CPPDEV/TypeChef-LinuxAnalysis/performance_breakdown.txt $CPPDEV/TypeChef-LinuxAnalysis/sizes_and_configs.txt 

# Graph a scatter plot of size vs latency, broken down.
graph_performance_scatterplot.sh size performance_scatterplot.pdf $CPPDEV/TypeChef-LinuxAnalysis/performance_breakdown.txt $CPPDEV/TypeChef-LinuxAnalysis/sizes_and_configs.txt

# Graph a scatter plot of size vs latency, broken down with configs.
graph_performance_scatterplot_with_configs.sh size performance_scatterplot_with_configs.pdf $CPPDEV/TypeChef-LinuxAnalysis/performance_breakdown.txt $CPPDEV/TypeChef-LinuxAnalysis/sizes_and_configs.txt

# Graph histograms of size vs latency, broken down.
graph_performance_histograms.sh size performance_histograms.pdf $CPPDEV/TypeChef-LinuxAnalysis/performance_breakdown.txt $CPPDEV/TypeChef-LinuxAnalysis/sizes_and_configs.txt

# Time gcc parser.
nohup superc_linux.sh -l typechef_files.txt -L configurations/ -g -o gcc.txt &

cat gcc.txt | gcc_summary.pl > gcc_summary.txt

percentile_summary.sh -p ".5 .9 1" gcc_summary.txt gcc_time 3
percentile_summary.sh -p ".5 .9 1" gcc_summary.txt gcc_time 4
percentile_summary.sh -p ".5 .9 1" gcc_summary.txt gcc_time 5

cat gcc_summary.txt | sum.sh gcc_time 2
cat gcc_summary.txt | sum.sh gcc_time 3
cat gcc_summary.txt | sum.sh gcc_time 4


#############################################################################
##################  3. Getting the Configuration Settings  ##################
#############################################################################

# Get the 2.6.33.3 linux kernel.
wget http://www.kernel.org/pub/linux/kernel/v2.6/linux-2.6.33.3.tar.gz
tar -zxvf linux-2.6.33.3.tar.gz
cd linux-2.6.33.3

# Put the .c extension onto the list of compilation units.
cat ../TypeChef-LinuxAnalysis/linux_files.lst | awk '{print $0".c"}' | sort | uniq > typechef_files.txt

# Cache configuration settings.
make allyesconfig
make
nohup superc_linux.sh -l typechef_files.txt -w -L configurations/ | tee get_configs.txt

# Get the 3.2.9 linux kernel.
wget http://www.kernel.org/pub/linux/kernel/v3.0/linux-3.2.9.tar.bz2
tar -xvf linux-3.2.9.tar.bz2
cd linux-3.2.9

# Put the .c extension onto the list of compilation units and only
# take the files that still exist in the 3.2.9 kernel.
cat ../TypeChef-LinuxAnalysis/linux_files.lst | awk '{print $0".c"}' | while read file; do if [ -f $file ]; then echo $file; fi; done | sort | uniq > typechef_files.txt

# Construct a list of compilation units for the new kernel based on
# both the configuration variables of the constrained kernel and the
# list of files, some of which may no longer exist under the same name
# in the new kernel.

# Get the configuration variables encountered while processing the
# constrained kernel.
cat ../TypeChef-LinuxAnalysis/sizes_and_configs.txt | grep "^config_var CONFIG_" | awk '{print$2}' | sort | uniq > constrained_vars.txt

# Extract the configuration variables from the Makefiles that control
# the directories that the typechef list of files are found in.
cat typechef_files.txt | xargs -L 1 dirname | sort | uniq | while read dir; do
    makefile="`dirname $dir`/Makefile"
    if [ ! -f $makefile ]; then
        makefile="`dirname $dir | xargs -L 1 dirname`/Makefile"
    fi
    cat $makefile | grep `basename $dir`/ | grep "obj-\$(CONFIG_"
done | egrep -o "CONFIG_[A-Za-z0-9_]+" > makefile_vars.txt

# Configure the kernel with the above configuration variables used by
# the constrained kernel.  This takes a subset of the allyesconfig.
make ARCH=x86 allyesconfig
cat constrained_vars.txt makefile_vars.txt | sort | uniq | while read var; do grep $var .config; done > constrained_vars.config
make KCONFIG_ALLCONFIG=constrained_vars.config allnoconfig

# Get list of files while building the kernel.
make CHECK="echo gcc_args " C=2 2>&1 | tee makeout.txt
cat makeout.txt | awk '{if ($1 == "gcc_args") {print $NF}}' | sort | uniq > allyesconfig_files.txt

# Combine typechef files with allyesconfig files.
cat allyesconfig_files.txt typechef_files.txt | sort | uniq > all.txt

# Cache configuration settings.
make allyesconfig
make
nohup superc_linux.sh -l all.txt -w -L configurations/ | tee get_configs.txt

# Get the list of files not in the typechef list.
diff typechef_files.txt all.txt | grep "^>" | cut -c3- > extra_files.txt


#############################################################################
#################  4. Dynamic Analysis of Preprocessor Usage  ###############
#############################################################################

# Collect preprocessor statistics as well as compilation unit size,
# configuration variables, and header guards.
nohup java xtc.lang.cpp.FilenameService -server 4000 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 4000 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-preprocessor -preprocessorStatistics -size -configurationVariables -headerGuards" -d preprocessorStatistics/

# Collect language statistics and subparser counts.
nohup java xtc.lang.cpp.FilenameService -server 4001 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 4001 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-languageStatistics -parserStatistics" -d languageStatistics/

# Compute subparsers
find languageStatistics/ -type f | xargs cat | egrep "^subparsers |^iterations " > subparsers.txt
subparser_cdf.sh subparsers.txt > subparsers.csv
table_subparser_cdf.sh subparsers.csv

# # Distributing summary stats computation hogs NFS resources because
# # of grep.

# # Compute summary stats, distributed.
# find preprocessorStatistics/ -type f > preprocessor_data_files.txt
# nohup java xtc.lang.cpp.FilenameService -server 4002 preprocessor_data_files.txt &
# nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 4002 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -D -o preprocessor_statistics.txt

# find languageStatistics/ -type f > language_data_files.txt
# nohup java xtc.lang.cpp.FilenameService -server 4003 language_data_typechef_files.txt &
# nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 4003 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -D -o language_statistics.txt

# Compute summary stats, single-machine.

for i in `find preprocessorStatistics/ -name "*.c"`; do dynamic_analysis.sh $i; done > preprocessor_statistics.txt

for i in `find languageStatistics/ -name "*.c"`; do dynamic_analysis.sh $i; done > language_statistics.txt

# Compute percentiles for the SuperC paper's data table.  This calls
# percentile_summary.sh to do it's job.
datatable.sh preprocessor_statistics.txt language_statistics.txt > datatable.txt

# Extract sizes and config_vars
find preprocessorStatistics/ -type f | xargs egrep "^Processing |^size |^config_var " > sizes_and_configs.txt


#############################################################################
#################  5. Static Analysis of Preprocessor Usage  ################
#############################################################################

# Get the closure of headers included by all compilation units.
nohup find preprocessorStatistics/ -type f | xargs cat | grep ^include > all_typechef_headers.txt
cat all_typechef_headers.txt | awk '{print $3}' | sort -k2 | uniq > typechef_headers.txt

# Find the number of preprocessor directives and source lines of code.
preprocessor_static_usage.sh typechef_files.txt typechef_headers.txt > preprocessor_static_usage.txt &

# Find the top ten included headers.
top_includes.sh typechef_files.txt typechef_headers.txt > top_includes.txt &


#############################################################################
###########################  6. Subparser Count  ############################
#############################################################################

# All optimizations.  No need to run if dynamic analysis was run.
nohup java xtc.lang.cpp.FilenameService -server 6001 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6001 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics" -o subparsers01_all.txt

#Oshared
nohup java xtc.lang.cpp.FilenameService -server 6006 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6006 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oshared" -o subparsers06_shared.txt

#Onone
nohup java xtc.lang.cpp.FilenameService -server 6008 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6008 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Onone" -o subparsers08_none.txt

#Oshared and Olazy
nohup java xtc.lang.cpp.FilenameService -server 6002 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6002 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oshared -Olazy" -o subparsers02_shared_lazy.txt

#Olazy
nohup java xtc.lang.cpp.FilenameService -server 6005 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6005 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Olazy" -o subparsers05_lazy.txt

# Generate CDFs
subparser_cdf.sh subparsers01*.txt* > subparsers01_all.csv
subparser_cdf.sh subparsers06*.txt* > subparsers06_shared.csv
subparser_cdf.sh subparsers08*.txt* > subparsers08_none.csv
subparser_cdf.sh subparsers02*.txt* > subparsers02_shared_lazy.csv
subparser_cdf.sh subparsers05*.txt* > subparsers05_lazy.csv

# Graph generation.
graph_subparser_cdf.sh subparser_cdf.pdf \
    $CPPDEV/linux-2.6.33.3/subparser_data/subparsers06_shared.csv \
    "Shared" \
    $CPPDEV/linux-2.6.33.3/subparser_data/subparsers01_all.csv \
    "Shared, Lazy, & Early;\nsimilarly Shared & Lazy" \
    $CPPDEV/linux-2.6.33.3/subparser_data/subparsers08_none.csv \
    "Follow-Set Only; similarly Lazy"

graph_subparser_cdf.sh subparser_cdf_all.pdf \
    $CPPDEV/linux-2.6.33.3/subparser_data/subparsers01_all.csv \
    "All Optimizations" \
    $CPPDEV/linux-2.6.33.3/subparser_data/subparsers02_shared_lazy.csv \
    "Shared and Lazy" \
    $CPPDEV/linux-2.6.33.3/subparser_data/subparsers06_shared.csv \
    "Shared" \
    $CPPDEV/linux-2.6.33.3/subparser_data/subparsers05_lazy.csv \
    "Lazy" \
    $CPPDEV/linux-2.6.33.3/subparser_data/subparsers08_none.csv \
    "Follow-Set Only"

# Table of 50th, 99th, and 100th percentiles.
table_subparser_cdf.sh \
    subparsers01_all.csv \
    subparsers02_shared_lazy.csv \
    subparsers06_shared.csv \
    subparsers05_lazy.csv \
    subparsers08_none.csv

#naive and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6500 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6500 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -naiveFMLR -platoffOrdering -killswitch 16000" -o naive1_platoff.txt

#naive
nohup java xtc.lang.cpp.FilenameService -server 6501 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6501 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -naiveFMLR -killswitch 16000" -o naive2_none.txt

# Get percentage of files tripping the killswitch for naiveFMLR.
echo "`grep killswitch naive1_platoff.txt* | wc -l` / `grep Processing naive1_platoff.txt* | wc -l`" | bc -lq
echo "`grep killswitch naive2_none.txt* | wc -l` / `grep Processing naive2_none.txt* | wc -l`" | bc -lq


# Other combinations of optimizations.

#Olazy and Oearly
nohup java xtc.lang.cpp.FilenameService -server 6003 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6003 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Olazy -Oearly" -o subparsers03_lazy_early.txt

#Oshared and Oearly
nohup java xtc.lang.cpp.FilenameService -server 6004 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6004 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oshared -Oearly" -o subparsers04_shared_early.txt

#Oearly
nohup java xtc.lang.cpp.FilenameService -server 6007 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6007 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oearly" -o subparsers07_early.txt

# Generate CDFs
subparser_cdf.sh subparsers03*.txt* > subparsers03_lazy_early.csv
subparser_cdf.sh subparsers04*.txt* > subparsers04_shared_early.csv
subparser_cdf.sh subparsers07*.txt* > subparsers07_early.csv

# Table of 50th, 99th, and 100th percentiles.
table_subparser_cdf.sh \
    subparsers03_lazy_early.csv \
    subparsers04_shared_early.csv \
    subparsers07_early.csv \


# Check early shifts.

#earlyShift, Oshared, Olazy.
nohup java xtc.lang.cpp.FilenameService -server 6017 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6017 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oshared -Olazy -earlyShift" -o subparsers17_shared_lazy_shift.txt

#earlyShift Oshared
nohup java xtc.lang.cpp.FilenameService -server 6018 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6018 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oshared -earlyShift" -o subparsers18_shared_shift.txt

#earlyShift Olazy
nohup java xtc.lang.cpp.FilenameService -server 6019 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6019 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Olazy -earlyShift" -o subparsers19_lazy_shift.txt

#earlyShift
nohup java xtc.lang.cpp.FilenameService -server 6020 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6020 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Onone -earlyShift" -o subparsers20_none_shift.txt

# Generate CDFs
subparser_cdf.sh subparsers17*.txt* > subparsers17_shared_lazy_shift.csv
subparser_cdf.sh subparsers18*.txt* > subparsers18_shared_shift.csv
subparser_cdf.sh subparsers19*.txt* > subparsers19_lazy_shift.csv
subparser_cdf.sh subparsers20*.txt* > subparsers20_none_shift.csv

# Table of 50th, 99th, and 100th percentiles.
table_subparser_cdf.sh \
    subparsers17_shared_lazy_shift.csv \
    subparsers18_shared_shift.csv \
    subparsers19_lazy_shift.csv \
    subparsers20_none_shift.csv

# Compare early shifts and reduces with each other and without either.
join subparsers02_shared_lazy.csv subparsers01_all.csv | join - subparsers17_shared_lazy_shift.csv | awk '{ print $1, $2, $2-$3, $2-$4 }'
join subparsers06_shared.csv subparsers04_shared_early.csv | join - subparsers18_shared_shift.csv | awk '{ print $1, $2, $2-$3, $2-$4 }'
join subparsers05_lazy.csv subparsers03_lazy_early.csv | join - subparsers19_lazy_shift.csv | awk '{ print $1, $2, $2-$3, $2-$4 }'
join subparsers08_none.csv subparsers07_early.csv | join - subparsers20_none_shift.csv | awk '{ print $1, $2, $2-$3, $2-$4 }'

# Compare early shifts and reduces with each other and without either.
join subparsers02_shared_lazy.csv subparsers17_shared_lazy_shift.csv | awk '{ print $1, $2, $3, $2-$3 }'
join subparsers06_shared.csv subparsers18_shared_shift.csv | awk '{ print $1, $2, $3, $2-$3 }'
join subparsers05_lazy.csv subparsers19_lazy_shift.csv | awk '{ print $1, $2, $3, $2-$3 }'
join subparsers08_none.csv subparsers20_none_shift.csv | awk '{ print $1, $2, $3, $2-$3 }'

graph_subparser_cdf.sh compare_shared_lazy.pdf subparsers02_shared_lazy.csv "Shared and Lazy" subparsers01_all.csv "With Early Reduces" subparsers17_shared_lazy_shift.csv "With Early Shifts"
graph_subparser_cdf.sh compare_shared.pdf subparsers06_shared.csv "Shared" subparsers04_shared_early.csv "With Early Reduces" subparsers18_shared_shift.csv "With Early Shifts"
graph_subparser_cdf.sh compare_lazy.pdf subparsers05_lazy.csv "Lazy" subparsers03_lazy_early.csv "With Early Reduces" subparsers19_lazy_shift.csv "With Early Shifts"
graph_subparser_cdf.sh compare_none.pdf subparsers08_none.csv "None" subparsers07_early.csv "With Early Reduces" subparsers20_none_shift.csv "With Early Shifts"


# With Platoff ordering.

# All optimizations and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6009 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6009 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -platoffOrdering" -o subparsers09_all_platoff.txt

#Oshared, Olazy, and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6010 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6010 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oshared -Olazy -platoffOrdering" -o subparsers10_shared_lazy_platoff.txt

#Olazy, Oearly, and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6011 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6011 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Olazy -Oearly -platoffOrdering" -o subparsers11_lazy_early_platoff.txt

#Oshared, Oearly, and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6012 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6012 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oshared -Oearly -platoffOrdering" -o subparsers12_shared_early_platoff.txt

#Olazy and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6013 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6013 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Olazy -platoffOrdering" -o subparsers13_lazy_platoff.txt

#Oshared and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6014 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6014 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oshared -platoffOrdering" -o subparsers14_shared_platoff.txt

#Oearly and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6015 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6015 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Oearly -platoffOrdering" -o subparsers15_early_platoff.txt

#Onone and platoffOrdering
nohup java xtc.lang.cpp.FilenameService -server 6016 typechef_files.txt &
nohup superc_linux.sh -h beaker-2.news.cs.nyu.edu -p 6016 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -S"-parserStatistics -Onone -platoffOrdering" -o subparsers16_none_platoff.txt

# Generate CDFs
subparser_cdf.sh subparsers09*.txt* > subparsers09_all_platoff.csv
subparser_cdf.sh subparsers10*.txt* > subparsers10_shared_lazy_platoff.csv
subparser_cdf.sh subparsers11*.txt* > subparsers11_lazy_early_platoff.csv
subparser_cdf.sh subparsers12*.txt* > subparsers12_shared_early_platoff.csv
subparser_cdf.sh subparsers13*.txt* > subparsers13_lazy_platoff.csv
subparser_cdf.sh subparsers14*.txt* > subparsers14_shared_platoff.csv
subparser_cdf.sh subparsers15*.txt* > subparsers15_early_platoff.csv
subparser_cdf.sh subparsers16*.txt* > subparsers16_none_platoff.csv

# Table of 50th, 99th, and 100th percentiles.
table_subparser_cdf.sh \
    subparsers09_all_platoff.csv \
    subparsers10_shared_lazy_platoff.csv \
    subparsers11_lazy_early_platoff.csv \
    subparsers12_shared_early_platoff.csv \
    subparsers13_lazy_platoff.csv \
    subparsers14_shared_platoff.csv \
    subparsers15_early_platoff.csv \
    subparsers16_none_platoff.csv


#############################################################################
############################  7. Testing  ###################################
#############################################################################

# Regression tests, preprocessor and parser. (make check-cpp).
regression.sh -a \
		-S"-E -I $(FONDA_DIR)/cpp_testsuite/cpp/include1 \
					-I $(FONDA_DIR)/cpp_testsuite/cpp/include2 \
					-I $(FONDA_DIR)/cpp_testsuite/cpp/sys" \
		-G"   -I $(FONDA_DIR)/cpp_testsuite/cpp/include1 \
					-I $(FONDA_DIR)/cpp_testsuite/cpp/include2 \
					-I $(FONDA_DIR)/cpp_testsuite/cpp/sys" \
		$(FONDA_DIR)/cpp_testsuite/cpp/*.c \
		$(FONDA_DIR)/cpp_testsuite/preprocessor/*.c

regression.sh -k .ast -S-printAST \
		$(FONDA_DIR)/cpp_testsuite/grammar/*.c \
		$(FONDA_DIR)/cpp_testsuite/parser/*.c

# Check new interactions. (make check-cpp).
regression.sh -a -S-E $(FONDA_DIR)/cpp_testsuite/new_interactions/*.c

# Checking typechef breaking on interactions.
ls $(FONDA_DIR)/cpp_testsuite/new_interactions/*.c | xargs -L 1 typechef_run_file.sh -w -r -t TypeChef

# C torture test.  Check that grammar parses them.
c_torture.sh

# Test SuperC's preprocessor against allyesconfig.
nohup java xtc.lang.cpp.FilenameService -server 7000 typechef_files.txt &
nohup superc_linux.sh -c -S-E -h beaker-2 -p 7000 -s $JAVA_DEV_ROOT/data/cpp/server_list.txt -L configurations/ -o preprocessor_test_leftover.txt

# Collect the results.
cat preprocessor_test.txt* | egrep "^comparison_succeeded" | wc -l
cat preprocessor_test.txt* | egrep "^comparison_failed" | wc -l

# Parse the allyesconfig version of the kernel.
nohup java xtc.lang.cpp.FilenameService -server 7001 typechef_files.txt &
nohup superc_linux.sh -P -h beaker-2 -p 7001 -s $CPPDATA/server_list.txt -L configurations/ -o linux_torture.txt

# Collect the results.
cat linux_torture.txt* | egrep "^grammar_succeeded" | wc -l
cat linux_torture.txt* | egrep "^grammar_failed" | wc -l
