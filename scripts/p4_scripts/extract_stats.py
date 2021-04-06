import os
import sys
import re
from pathlib import Path
import collections
import matplotlib.pyplot as plt
import numpy as np
import readline
import copy


def combine(large_set, new_items):
    for new_item in new_items:
        if new_item not in large_set:
            large_set.append(new_item)


def transpose(l1):
    l2 = []
    # iterate over list l1 to the length of an item 
    for i in range(len(l1[0])):
        # print(i)
        row =[]
        for item in l1:
            # appending to new list with values and index positions
            # i contains index position and item contains values
            row.append(item[i])
        l2.append(row)
    return l2


# FLAGS
PRINT_ALL_STATS = True
CREATE_GRAPHS = True
PRINT_RAND_STATS = False

if len(sys.argv) < 2:
    print("""Error: Missing file name. Run the script with the file name at the end as such: \"python3 extract_stats.py file_containing_superp4_output.txt\"""")
    exit(1)

file_name = sys.argv[1]

if not os.path.exists(file_name):
    print("Error: Provided file does not exist. Please check file name and/or path.")
    exit(1)

file = open(file_name, "r")
results = file.readlines()

conditionals_inside = {} # first value is counter, second value is a list of all encounters
conditionals_after = {} # first value is counter, second value is a list of all encounters
retained_construct_locs = {}
current_header = ""
parsing_file = ""
header_stats = {} # 2d dictionary | 1st value contains a dict | dict contains: constructs, number of includes
total_macros = {} # 2d dict | key value is the macro itself, 2nd value is a 2d list whose 1st list is all the places of occurrence and second is list of grammar constructs
location_store_inside = {}
location_store_outside = {}
main_file_name = "fabric.p4" # the file that we did superp4 on
element_counter = [{}, {"conditional" : 0, "undef" : 0, "define" : 0, "include" : 0}] # count how many conditionals, defines, includes, and undef there are
inside_conditional_locations = []
nested_inside_conditional_locations_set = []
set_of_conditional_sizes = []
retained_locations = set()
started_to_parse_file = False

for line in results:
    initial_split = line.split(" ")
    if initial_split[0] == "Parsing":
        # This is usually present only once - when starting to parse the specified file
        started_to_parse_file = True
        main_file_name = initial_split[2].replace('\n', '')
        parsing_file = current_header = os.path.abspath(initial_split[2].replace('\n', ''))
        element_counter[0][parsing_file] = {"conditional" : 0, "undef" : 0, "define" : 0, "include" : 0}
    if started_to_parse_file:
        if initial_split[0] == "conditional_inside":
            #conditional_inside externDeclaration /usr/local/share/p4c/p4include/v1model.p4:214:1 "/usr/local/share/p4c/p4include/v1model.p4:255:1,/usr/local/share/p4c/p4include/v1model.p4:215:1"
            #conditional_inside input /usr/local/share/p4c/p4include/core.p4:23:1 "/usr/local/share/p4c/p4include/v1model.p4:74:1,/usr/local/share/p4c/p4include/v1model.p4:137:1,/usr/local/share/p4c/p4include/v1model.p4:255:1,/usr/local/share/p4c/p4include/v1model.p4:298:1,/usr/local/share/p4c/p4include/v1model.p4:215:1,/usr/local/share/p4c/p4include/v1model.p4:171:1"
            encounters = initial_split[3].replace('"', '').replace('\n', '').split(",")

            # add each cpp conditional location under its respective grammar construct key in conditionals_inside var, and keep count of how many seen
            if initial_split[1] not in conditionals_inside:
                conditionals_inside[initial_split[1]] = [0, []]
                for encounter in encounters:
                    encounter = os.path.abspath(encounter)
                    conditionals_inside[initial_split[1]][1].append(encounter)
                    conditionals_inside[initial_split[1]][0] += 1
            else:
                for encounter in encounters:
                    encounter = os.path.abspath(encounter)
                    if encounter not in conditionals_inside[initial_split[1]][1]:
                        conditionals_inside[initial_split[1]][1].append(encounter)
                        conditionals_inside[initial_split[1]][0] += 1
            
            # keep track of the number of cpp conditionals encountered per file
            if initial_split[1] not in header_stats[current_header]["constructs"]:
                header_stats[current_header]["constructs"][initial_split[1]] = 1
            else:
                header_stats[current_header]["constructs"][initial_split[1]] += 1
            
            # The first time conditional_inside is reported with a production name for a location, that's the "real/actual/true" production under which the conditional is present
            # So we store only the first encounter
            for encounter in encounters:
                encounter = os.path.abspath(encounter)
                if encounter not in location_store_inside:
                    location_store_inside[encounter] = initial_split[1]

        elif initial_split[0] == "entering":
            # Parsing a new file (a new header file)
            current_header = os.path.abspath(initial_split[2].replace('\n', ''))
            if current_header not in header_stats:
                header_stats[current_header] = {"constructs": {}, "includesCount": 0}
                element_counter[0][current_header] = {"conditional" : 0, "undef" : 0, "define" : 0, "include" : 0}
            nested_inside_conditional_locations_set.append(inside_conditional_locations)
            inside_conditional_locations = []

        elif initial_split[0] == "guarded":
            # a file was included using the #include directive
            element_counter[1]["include"] += 1
            element_counter[0][current_header]["include"] += 1
        elif initial_split[0] == "exiting":
            # Done parsing a header file
            if len(inside_conditional_locations) > 0:
                print("hmm at the end of file but haven't cleared the line number stack")
                print("stack: " + str(inside_conditional_locations))
                print(current_header)
                exit(0)
            current_header = parsing_file
            inside_conditional_locations = nested_inside_conditional_locations_set.pop(len(nested_inside_conditional_locations_set)-1)
        elif initial_split[0] == "include":
            # a file was included using the #include directive
            include_address = os.path.abspath(initial_split[2])
            current_address = os.path.abspath(initial_split[3].split(":")[0])
            if current_address not in header_stats:
                header_stats[current_address] = {"constructs": {}, "includesCount": 1}
            else:
                header_stats[current_address]["includesCount"] += 1
            element_counter[1]["include"] += 1
            element_counter[0][current_address]["include"] += 1
        elif initial_split[0] == "undef":
            # undefining a macro flag
            element_counter[1]["undef"] += 1
            element_counter[0][current_header]["undef"] += 1
        elif initial_split[0] == "endif":
            # endif /usr/local/share/p4c/p4include/v1model.p4:70:1 1 1
            # at the end of a cpp conditional block
            element_counter[1]["conditional"] += 1
            element_counter[0][os.path.abspath(initial_split[1].split(":")[0])]["conditional"] += 1

            #calculate line count
            current_line_number = int(initial_split[1].split(":")[-2])
            last_directive, last_line_number, start_address = inside_conditional_locations.pop(len(inside_conditional_locations)-1)
            difference = current_line_number - last_line_number - 1
            while last_directive != "ifdef" and last_directive != "ifndef" and last_directive != "if":
                current_line_number = last_line_number
                last_directive, last_line_number, start_address = inside_conditional_locations.pop(len(inside_conditional_locations)-1)
                difference = max(difference, (current_line_number - last_line_number-1))
            path_split_temp = initial_split[1].split(":")
            set_of_conditional_sizes.append((start_address, difference))
            # print("Number of lines under a conditional in file: " + os.path.abspath(initial_split[1].split(":")[0]) + " is: " + str(difference) + " that starts at line: " + str(last_line_number))
        # conditional ifndef include/control/../int/int_header.p4:17:1 boolean 1 1 []
        # conditional ifndef include/control/../int/../define.p4:26:1 boolean 3 1 [(defined WITHOUT_XCONNECT)]
        # conditional if include/parser.p4:73:1 boolean 1 1 [(defined WITH_XCONNECT),(defined WITHOUT_XCONNECT),(defined WITH_DOUBLE_VLAN_TERMINATION),(defined WITH_BNG)]
        # conditional else include/int/int_transit.p4:30:1 boolean 4 1
        elif initial_split[0] == "conditional":
            # conditional if|ifdef|ifndef|elif|else is emitted with -preprocessorStatistics flag
            # the last section of the emitted line will contain macro variables inside square brackets such as [(defined WITH_XCONNECT)] - reports both flags and macros that expand to value (V1MODEL_VERSION)
                # Sometimes we have a negated define that is inserted in the node to mark the variations such as [!(defined WITH_INT_TRANSIT)]
                # We ignore these flags are they are not used in the source file as we want to track only the macros vars/flags used in the source file
                # If more than one macro var/flag is used in a single file, this will report something like [(defined WITH_XCONNECT),(defined WITHOUT_XCONNECT)] - we store all of them under the same line
            # the third part of this line states which file and which location the macro variable is used
            # [] is emitted when the macro is already reported by preprocessorStatistics or if the variable is a header guard (or if it already defined?)
            # can use this to cross-reference with conditional_inside and conditional_outside locations
                # We will only retain contional_* instances whose location matches with at least one that is reported by conditional (this)
            
            element_counter[1]["conditional"] += 1
            element_counter[0][os.path.abspath(initial_split[2].split(":")[0])]["conditional"] += 1
            macro_list = []
            path_split = initial_split[2].split(":")
            inside_conditional_locations.append((initial_split[1], int(path_split[-2]), os.path.abspath(path_split[0]) + ":" + ":".join(path_split[1:])))

            if len(initial_split) < 7 or initial_split[6] == "[]":
                macro_list.append("[]")
            full_macro_list = ''.join(initial_split[6:]).split(',')
            for macro in full_macro_list:
                macro = re.sub(r"\[|\]|\n", '', macro)
                if not "!(define" in macro:
                    macro = re.sub(r"\[|\]|\(|\)|\n|!|defined| ", '', macro)
                    macro_list.append(macro)
                    if macro:
                        retained_locations.add(os.path.abspath(path_split[0]) + ":" + ":".join(path_split[1:]))
            # macro_list = (re.sub(r"\[|\]|\(|\)|\n|!|defined| ", '', ''.join(initial_split[6:]))).split(',')
            # print(initial_split[6:])
            # print(list)
            for macro in macro_list:
                current_address = os.path.abspath(path_split[0]) + ":" + ":".join(path_split[1:])
                if (macro not in total_macros) and macro != '':
                    total_macros[macro] = [[current_address],[]]
                elif macro != '' and current_address not in total_macros[macro][0]:
                    total_macros[macro][0].append(current_address)

        elif initial_split[0] == "define":
            # we encountered a macro definition
            element_counter[1]["define"] += 1
            element_counter[0][current_header]["define"] += 1

file.close()
file = open(file_name, "r")
results = file.readlines()
for line in results:
    initial_split = line.split(" ")
    if initial_split[0] == "conditional_after":
            #conditional_inside externDeclaration /usr/local/share/p4c/p4include/v1model.p4:214:1 "/usr/local/share/p4c/p4include/v1model.p4:255:1,/usr/local/share/p4c/p4include/v1model.p4:215:1"
            #conditional_inside input /usr/local/share/p4c/p4include/core.p4:23:1 "/usr/local/share/p4c/p4include/v1model.p4:74:1,/usr/local/share/p4c/p4include/v1model.p4:137:1,/usr/local/share/p4c/p4include/v1model.p4:255:1,/usr/local/share/p4c/p4include/v1model.p4:298:1,/usr/local/share/p4c/p4include/v1model.p4:215:1,/usr/local/share/p4c/p4include/v1model.p4:171:1"
            encounters = initial_split[3].replace('"', '').replace('\n', '').split(",")
            for encounter in encounters:
                encounter = os.path.abspath(encounter)
                if encounter in location_store_inside:
                    continue
                location_store_outside[encounter] = initial_split[1]
            if initial_split[1] not in conditionals_after:
                conditionals_after[initial_split[1]] = [0, []]
                for encounter in encounters:
                    encounter = os.path.abspath(encounter)
                    conditionals_after[initial_split[1]][1].append(encounter)
                    conditionals_after[initial_split[1]][0] += 1
            else:
                for encounter in encounters:
                    encounter = os.path.abspath(encounter)
                    if encounter not in conditionals_after[initial_split[1]][1]:
                        conditionals_after[initial_split[1]][1].append(encounter)
                        conditionals_after[initial_split[1]][0] += 1


#merging conditional_inside and conditional_after
conditionals = {}
for cond in conditionals_inside:
    if cond not in conditionals:
        conditionals[cond] = conditionals_inside[cond]
    elif conditionals_inside[cond][1] not in conditionals[cond][1]:
        conditionals[cond][0] += conditionals_inside[cond][0]
        conditionals[cond][1].append(conditionals_inside[cond][1])
for cond in conditionals_after:
    if cond not in conditionals:
        conditionals[cond] = conditionals_after[cond]
    elif conditionals_after[cond][1] not in conditionals[cond][1]:
        conditionals[cond][0] += conditionals_after[cond][0]
        conditionals[cond][1].append(conditionals_after[cond][1])

locations_final = {}
for address in location_store_inside:
    if location_store_inside[address] not in locations_final:
        locations_final[location_store_inside[address]] = [1, [address]]
    else:
        locations_final[location_store_inside[address]][0] += 1
        locations_final[location_store_inside[address]][1].append(address)
for address in location_store_outside:
    if location_store_outside[address] not in locations_final:
        locations_final[location_store_outside[address]] = [1, [address]]
    else:
        locations_final[location_store_outside[address]][0] += 1
        locations_final[location_store_outside[address]][1].append(address)

locations_final = {k: v for k, v in sorted(locations_final.items(), key=lambda item: item[1], reverse=True)}
for gmc in locations_final:
    for location in locations_final[gmc][1]:
        for macro in total_macros:
            if location in total_macros[macro][0]:
                total_macros[macro][1].append(gmc)
                if gmc not in retained_construct_locs:
                    retained_construct_locs[gmc] = [location]
                else:
                    retained_construct_locs[gmc].append(location)
                # retained_locations.add(location)

# for file in set_of_conditional_sizes:
#     print(file)

retained_set_of_conditional_sizes = set()
for count_tuple in set_of_conditional_sizes:
    address, size = count_tuple
    if address in retained_locations:
        retained_set_of_conditional_sizes.add(count_tuple)

# taking the avg cpp lines in a file
file_line_freq = {}
for count_tuple in retained_set_of_conditional_sizes:
    address, size = count_tuple
    address = address.split(":")[0]
    if address not in file_line_freq:
        file_line_freq[address] = [1, size]
    else:
        file_line_freq[address][0] += 1
        file_line_freq[address][1] += size
for cur_file in file_line_freq:
    file_line_freq[cur_file] = file_line_freq[cur_file][1] / file_line_freq[cur_file][0]

if PRINT_ALL_STATS == True:
    print("\nAll Unfiltered Conditionals Combined\n")
    for macro in conditionals:
        print(macro)
        print(conditionals[macro])
    print()
    # print("\n all unfiltered conditionals_inside inside\n")
    # for element in conditionals_inside:
    #     print(element, conditionals_inside[element], sep=' ')
    # print("\n all unfiltered conditionals_after inside\n")
    # print()
    # for element in conditionals_after:
    #     print(element, conditionals_after[element], sep=' ')
    # print()
    # print("\nlocation inside\n")
    # for element in location_store_inside:
    #     print(element, location_store_inside[element], sep=' ')
    # print()
    # print("\nlocation outside\n")
    # for element in location_store_outside:
    #     print(element, location_store_outside[element], sep=' ')
    # print()
    print("\nHeader Stats\n")
    for element in header_stats:
        print(element, header_stats[element], sep=' ')
    print()
    print("\nlocation final var\n")
    for element in locations_final:
        print(element, locations_final[element], sep=' ')
    print()
    print("\nMacros with their locations and gm\n")
    for element in total_macros:
        print(element, total_macros[element], sep= ' ')
    print()
    print("\nAll retained constructs and locations\n")
    for element in retained_construct_locs:
        print(element, retained_construct_locs[element], sep=' ')
    print("\nRetained Locations:\n")
    print(retained_locations)
    print()
    print("Average number of CPP lines per file: ")
    for file in file_line_freq:
        print(file + " " + str(file_line_freq[file]))

if PRINT_ALL_STATS == True or CREATE_GRAPHS == True:
    line_count = readline.count_wrapper(main_file_name)
    total_number_of_lines = sum(line_count[x] for x in line_count)

if PRINT_ALL_STATS == True:
    for file in line_count:
        print(file + " has " + str(line_count[file]) + " lines")
    print("Total number of non-blank, non-comment lines starting with fabric.p4: " + str(total_number_of_lines))

if CREATE_GRAPHS == True:
    # A dict that keeps track of how many conditionals are used inside the construct
    grammar_constructs = {}
    for macro in total_macros:
        for construct in total_macros[macro][1]:
            if construct not in grammar_constructs:
                grammar_constructs[construct] = 1
            else:
                grammar_constructs[construct] += 1

    aggregated = []
    for ele in grammar_constructs:
        for i in range(grammar_constructs[ele]):
            aggregated.append(ele)
    aggregated.sort()

    #plotting
    # print(bins)
    f, ax = plt.subplots(figsize=(19,8))
    labels, counts = np.unique(aggregated, return_counts=True)
    plt.xticks(rotation=90)
    bins = len(grammar_constructs)+1

    # 2A dict that keeps track of how many conditionals are used inside the construct
    grammar_constructs2 = {}
    for macro in conditionals:
        if macro not in grammar_constructs2:
            grammar_constructs2[macro] = conditionals[macro][0]

    aggregated2 = []
    for ele in grammar_constructs2:
        for i in range(grammar_constructs2[ele]):
            aggregated2.append(ele)
    aggregated2.sort()

    plt.hist(aggregated, rwidth=0.9, alpha=0.9, bins=np.arange(bins)-0.45, label='filtered')
    plt.ylabel("Number of conditional macros")
    plt.savefig('filtered.png', bbox_inches='tight')
    plt.close()
    bins = len(grammar_constructs2)+1
    f, ax = plt.subplots(figsize=(19,8))
    plt.xticks(rotation=90)
    plt.hist(aggregated2, rwidth=0.9, alpha=0.75, bins=np.arange(bins)-0.45, label='unfiltered')
    plt.ylabel("Number of conditional macros")
    plt.savefig('unfiltered.png', bbox_inches='tight')
    plt.hist(aggregated, rwidth=0.9, alpha=0.9, bins=np.arange(bins)-0.45, label='filtered')
    plt.legend(loc='upper right')
    plt.savefig('combined.png', bbox_inches='tight')


    #bar plot
    file_values = [[], []] #first is count, second is file names
    print("\nPreprocessor count per file: ")
    for file in element_counter[0]:
        # print(file)
        file_values[1].append(file.split("/")[-1])
        test = {"conditional" : 0, "undef" : 0, "define" : 0, "include" : 0}
        for pp_case in element_counter[0][file]:
            print("\t" + pp_case + ": " + str(element_counter[0][file][pp_case]))
            test[pp_case] += element_counter[0][file][pp_case]
        file_values[0].append(list(map(lambda x: test[x]/line_count[file.split("/")[-1]], test)))
    # print(file_values)
    f, ax = plt.subplots(figsize=(30,20))
    labels = list(map(lambda x: x, element_counter[1]))
    X = np.arange(len(labels))
    values = list(map(lambda x: element_counter[1][x]/total_number_of_lines, element_counter[1]))
    file_values[0].append(values)
    file_values[1].append("total")

    for i in range(len(file_values[1])):
        ax.bar([j+(i*0.03) for j in X], file_values[0][i], width=0.03, label=file_values[1][i])

    plt.xticks(X+((22*0.03)/2), labels, fontsize=20)
    ax.legend(fontsize=15)
    vals = ax.get_yticks()
    ax.set_yticklabels(['{:.0f}%'.format(x*100) for x in vals])
    plt.yticks(fontsize=17)
    # non-blank, non-comment lines
    ax.set_ylabel("Percentage of lines", fontsize=20)
    plt.savefig('barplot.png', bbox_inches='tight')
    plt.close()

        # bar plot to plot avg CPP lines per file
    file_line_freq = {k: v for k, v in sorted(file_line_freq.items(), key=lambda item: item, reverse=True)}
    # print(file_line_freq)
    # for file in file_line_freq:
    #     print(file)
    file_names = list(map(lambda x: x.split("/")[-1] ,file_line_freq))  

    avg_lines = list(map(lambda x: file_line_freq[x], file_line_freq))

    fig = plt.figure()
    ax = fig.add_axes([0,0,1,1])
    ax.bar(file_names,avg_lines)
    plt.xticks(rotation=90)
    plt.ylabel("Avg. number of lines inside conditional PP block")
    plt.xlabel("File names")
    plt.savefig('avgCPPLines_onlyOneConditionalBlock.png', bbox_inches='tight')
    plt.close()
    

if PRINT_RAND_STATS == True:
    # print("\nPreprocessor count: ")
    # for pp_case in element_counter[1]:
    #     print(pp_case + ": " + str(element_counter[1][pp_case]))
    # # test = {"conditional" : 0, "undef" : 0, "define" : 0, "include" : 0}
    # # print("\nPreprocessor count per file: ")
    # # for file in element_counter[0]:
    # #     print(file)
    # #     for pp_case in element_counter[0][file]:
    # #         print("\t" + pp_case + ": " + str(element_counter[0][file][pp_case]))
    # #         test[pp_case] += element_counter[0][file][pp_case]
    # # print(test)
    # print(element_counter[1])
    largest_set = []
    cleaned_up_macros = {} # to remove values that don't have a reported grammar construct
    combine(largest_set, ['structTypeDeclaration', 'structFieldList', 'structField', 'parserState', 'parserStates', 'controlLocalDeclarations', 'controlLocalDeclaration', 'actionList', 'externDeclaration', 'methodPrototypes', 'methodPrototype'])
    for macro in total_macros:
        if not total_macros[macro][1]:
            continue
        print(macro)
        print(total_macros[macro][1])
        cleaned_up_macros[macro] = copy.copy(total_macros[macro])
    for macro in cleaned_up_macros:
        print(macro)
        macros_sorted = copy.copy(cleaned_up_macros[macro][1])
        # macros_sorted.sort()
        # print(macros_sorted)
        # print()
        combine(largest_set, macros_sorted)
        # largest_set.update(set(macros_sorted))
    # largest_set.sort()
    indices = {}
    counter = 0
    max_val = 0
    for macro_indv in largest_set:
        indices[macro_indv] = 2 ** counter
        counter += 1
        max_val = max(max_val, indices[macro_indv])
    print(max_val)
    max_val = len(([int(i) for i in list('{0:0b}'.format(max_val))]))
    print(max_val)
    # print(indices)
    tracker = {}
    print("asdfasdfasdfasdf")
    for i, v in enumerate(cleaned_up_macros):
        # print("hello " + str(i) + " " + str(v))
        cleaned_up_macros[v][1] = list(set(cleaned_up_macros[v][1]))
        print(v)
        print(cleaned_up_macros[v][1])
        for macro in cleaned_up_macros[v][1]:
            # print(indices[macro])
            if v not in tracker:
                tracker[v] = indices[macro]
            else:
                tracker[v] += indices[macro]
        # print(tracker[i])
    print("indices")
    print(indices)
    print("largest set sorted")
    print(largest_set)
    print(tracker)
    final_list = {}
    
    for i, v in enumerate(cleaned_up_macros):
        # print(str(v) + " " + str(bin(tracker[i])))
        final_list[v] = tracker[v]
    print("final list")
    print(final_list)
    final_list = locations_final = {k: v for k, v in sorted(final_list.items(), key=lambda item: item[1], reverse=True)}
    print()
    print("sorted final list")
    print(final_list)
    # for i, v in enumerate(cleaned_up_macros):
        # print(str(v) + " " + str(bin(final_list[v])))

    list_it_is = {}
    for i, v in enumerate(cleaned_up_macros):
        # print(str(v) + " " + str(bin(final_list[v])))
        list_it_is[v] = [0] * max_val
        list_it_is[v] = list_it_is[v] + ([int(i) for i in list('{0:0b}'.format(final_list[v]))])
        size_now = len(list_it_is[v])
        # print(list_it_is[v])
        # print(size_now)
        # print(size_now-max_val)
        list_it_is[v] = list_it_is[v][size_now-max_val:size_now]
        list_it_is[v].reverse()
    
    print("binary list")
    print(list_it_is)
    print("sorted it is")
    list_it_is = dict(sorted(list_it_is.items(), key=lambda x:x[1], reverse=True))
    print(list_it_is)

    f, ax = plt.subplots(figsize=(30,20))
    # ax[0].axis('tight')
    # ax[0].axis('off')
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
    plt.box(on=None)
    plt.subplots_adjust(left=0.2, bottom=0.2)

    macro_labels = [x for x in list_it_is]
    # macro_labels.reverse()
    print("macro_labels")
    print(macro_labels)
    construct_labels = [x for x in largest_set]
    # construct_labels.reverse()
    print("construct labels")
    print(construct_labels)
    # construct_labels.reverse()
    data_binary = [list_it_is[x] for x in list_it_is]
    # for data in data_binary:
    #     data = data.reverse()
    data_colors = []
    #setting colors:
    for i, out_val in enumerate(data_binary):
        temp = []*len(data_binary[i])
        for i, v in enumerate(data_binary[i]):
            if v == 1:
                temp.append("#007aa6")
            else:
                temp.append("w")
        data_colors.append(temp)
    print("colors")
    print(data_colors)
    col_width = 0.015
    table = plt.table(rowLabels=macro_labels, loc='center', cellColours=data_colors, colWidths=[col_width]*len(data_colors[0]))

    # table.auto_set_font_size(False)
    # table.set_column_widths(col=len(largest_set))
    # table.set_fontsize(10)
    # table.auto_set_column_width(col=list(range(len([x for x in list_it_is])+10)))
    #custom heading titles - new portion
    hoffset=0.3515 #find this number from trial and error
    voffset=0.6223 #find this number from trial and error
    line_fac=0.30 #controls the length of the dividing line
    width = 5
    height = 3
    count=0
    for string in construct_labels:
        ax.annotate('  '+string, xy=(hoffset+count*col_width,voffset),
            xycoords='axes fraction', ha='left', va='bottom', 
            rotation=47, size=10)

    #add a dividing line
        ax.annotate('', xy=(hoffset+(count+0.4)*col_width,voffset), 
            xytext=(hoffset+(count+0.4)*col_width+line_fac/width,voffset+line_fac/height),
            xycoords='axes fraction', arrowprops={'arrowstyle':'-'})

        count+=1

    # for cell in table._cells:
    #     if cell[0] == 0:
    #         table._cells[cell].get_text().set_rotation(90)
    #         table._cells[cell].get_text().set_verticalalignment('center')
    #         table._cells[cell].set_height(0.2)
    # plt.subplots_adjust(left=0.2, top=0.8)
    plt.savefig('freq.png', bbox_inches='tight')

