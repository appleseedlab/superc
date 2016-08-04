#!/bin/bash

if [ $# -lt 2 ]; then
    echo "USAGE: `basename $0` preprocessor_statistics language_statistics"
    exit
fi

preprocessor_statistics=$1
language_statistics=$2

echo "Macro definitions"
percentile_summary.sh $preprocessor_statistics \
    summary_definitions 2

echo "Macro definitions contained in conditionals"
percentile_summary.sh $preprocessor_statistics \
    summary_definitions 3

echo "Macro redefinitions"
percentile_summary.sh $preprocessor_statistics \
    summary_redefinitions 2

echo "Macro invocations"
percentile_summary.sh $preprocessor_statistics \
    summary_invocations 2

echo "Macro invocations with trimmed definition(s)"
percentile_summary.sh $preprocessor_statistics \
    summary_invocations 3

echo "Hoisted function-like macro invocations"
percentile_summary.sh $preprocessor_statistics \
    summary_hoisted_functions 2

echo "Nested macro invocations"
percentile_summary.sh $preprocessor_statistics \
    summary_nested_invocations 2

echo "Token pasting"
percentile_summary.sh $preprocessor_statistics \
    summary_paste 2

echo "Hoisted token pasting"
percentile_summary.sh $preprocessor_statistics \
    summary_paste 3

echo "Stringification"
percentile_summary.sh $preprocessor_statistics \
    summary_stringify 2

echo "Hoisted stringification"
percentile_summary.sh $preprocessor_statistics \
    summary_stringify 3

echo "Includes"
percentile_summary.sh $preprocessor_statistics \
    summary_include 2

echo "Computed includes"
percentile_summary.sh $preprocessor_statistics \
    summary_include 3

echo "Hoisted includes"
percentile_summary.sh $preprocessor_statistics \
    summary_include 4

echo "Hoisted includes, valid"
percentile_summary.sh $preprocessor_statistics \
    summary_include 5

echo "Reincludes"
percentile_summary.sh $preprocessor_statistics \
    summary_reinclude 2

echo "Conditionals"
percentile_summary.sh $preprocessor_statistics \
    summary_conditionals 2

echo "Hoisted conditionals"
percentile_summary.sh $preprocessor_statistics \
    summary_conditionals 5

echo "Max conditional depth"
percentile_summary.sh $preprocessor_statistics \
    summary_conditionals 4

echo "Conditionals with nonboolean subexpression(s)"
percentile_summary.sh $preprocessor_statistics \
    summary_conditionals 3

echo "Error directives"
percentile_summary.sh $preprocessor_statistics \
    summary_error_directives 2

echo "C Statements and Declarations"
percentile_summary.sh $language_statistics \
    summary_c_statements_and_declarations 2

echo "Conditionals Inside C Statements and Declarations"
percentile_summary.sh $language_statistics \
    summary_c_statements_and_declarations 3

echo "Typedefs"
percentile_summary.sh $language_statistics \
    summary_typedefs 2

echo "Typedef ambiguities"
percentile_summary.sh $language_statistics \
    summary_typedef_ambiguities 2
