import sys
from sys import argv
import subprocess

if len(argv) < 3:
    print "USAGE"
    print "  " + argv[0] + " -all statistics.txt"
    print "  " + argv[0] + " -preprocessor preprocessor_statistics.txt"
    print "  " + argv[0] + " -language language_statistics.txt"
    exit(0)

stats = argv[1]
filename = argv[2]

percentiles = (.5, .9, 1)

preprocessor_data = [
    ('Macro definitions', 'summary_definitions', 2),
    ("Macro definitions contained in conditionals", 'summary_definitions', 3),
    ("Macro redefinitions", 'summary_redefinitions', 2),
    ("Macro invocations", 'summary_invocations', 2),
    ("Macro invocations with trimmed definition(s)", 'summary_invocations', 3),
    ("Hoisted function-like macro invocations", 'summary_hoisted_functions', 2),
    ("Nested macro invocations", 'summary_nested_invocations', 2),
    ("Token pasting", 'summary_paste', 2),
    ("Hoisted token pasting", 'summary_paste', 3),
    ("Stringification", 'summary_stringify', 2),
    ("Hoisted stringification", 'summary_stringify', 3),
    ("Includes", 'summary_include', 2),
    ("Computed includes", 'summary_include', 3),
    ("Hoisted includes", 'summary_include', 4),
    ("Hoisted includes, valid", 'summary_include', 5),
    ("Reincludes", 'summary_reinclude', 2),
    ("Conditionals", 'summary_conditionals', 2),
    ("Hoisted conditionals", 'summary_conditionals', 5),
    ("Max conditional depth", 'summary_conditionals', 4),
    ("Conditionals with nonboolean subexpression(s)", 'summary_conditionals', 3),
    ("Error directives", 'summary_error_directives', 2), ]

language_data = [
    ("C Statements and Declarations", 'summary_c_statements_and_declarations', 2),
    ("Conditionals Inside C Statements and Declarations", 'summary_c_statements_and_declarations', 3),
    ("Typedefs", 'summary_typedefs', 2),
    ("Typedef ambiguities", 'summary_typedef_ambiguities', 2), ]

if stats == "-preprocessor":
    data_def = preprocessor_data
elif stats == "-language":
    data_def = language_data
elif stats == "-all":
    data_def = preprocessor_data + language_data
else:
    sys.stderr.write("invalid args\n")
    exit(1)

# data = []

for field_name, row_name, col_num in data_def:
    for percentile in percentiles:
        pctl_name = str(int(percentile * 100)) + 'th percentile'
        command = 'percentile_summary.sh -q ' + str(percentile) + ' ' + filename + ' ' + row_name + ' ' + str(col_num)
        popen = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
        stdout_, stderr_ = popen.communicate()
        if popen.returncode == 0:
            result = stdout_.strip()
            # data.append(('"' + field_name + ' ' + pctl_name + '"', result))
            print '"' + field_name.replace(',', '') + ' ' + pctl_name + '",' + result

# data = zip(*data)

# for row in data:
#     delim = ''
#     for elem in row:
#         sys.stdout.write(delim + elem)
#         delim = ','
#     print
