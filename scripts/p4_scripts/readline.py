import os
import re

def count_wrapper(file_name, current_path = "/mnt/onos-satellite/pipelines/fabric/src/main/resources/"):
    file_paths = {current_path+file_name : 1}
    line_counts_per_file = {}
    count_file(file_name, line_counts_per_file, file_paths, current_path)
    return line_counts_per_file

def count_file(file_name, line_counts_per_file, file_paths, current_path):
    cwd = os.getcwd()
    os.chdir(current_path)
    file = open(file_name, mode='r')
    counter = 0
    all_of_it = file.read()
    #remove all comments
    all_of_it = re.sub("(\/\*(\*(?!\/)|[^*])*\*\/)|(\/\/.*)",'',all_of_it)
    for line in all_of_it.split('\n'):
        line = line.lstrip()
        if line:
            # print(line)
            if re.compile("#[\s]*include[\s]*").search(line):
                # points to the directory of the header file
                next_file_path = ""
                # extract the filename for the include
                header_file = re.sub("#[\s]*include[\s]*", '', line)

                if re.compile("<").search(header_file):
                    header_file = re.sub("<", '', header_file)
                    header_file = re.sub(">", '', header_file)
                    # if "<FILENAME>", then use the system path to include system files
                    next_file_path = "/usr/local/share/p4c/p4include/"
                elif re.compile("\"").search(header_file):
                    header_file = re.sub("\"", '', header_file)
                    header_file = re.sub("\"", '', header_file)
                    # might be a nested path, so extract the filename from the path
                    paths = header_file.split("/")
                    header_file = paths[-1]
                    # append the nested path that we extracted to the next_file_path
                    next_file_path = os.getcwd() + "/" + '/'.join(paths[:-1]) + "/"
                # get the absolute path
                abs_file_path = os.path.abspath(next_file_path + header_file)
                # check if it is a valid file
                if not os.path.isfile(abs_file_path):
                        print(abs_file_path + " - not a valid file")
                        exit(code=0)
                # make sure we aren't scanning the header files more than once
                if abs_file_path not in file_paths:
                    count_file(header_file, line_counts_per_file, file_paths, next_file_path)
                    file_paths[abs_file_path] = 1
                else:
                    file_paths[abs_file_path] += 1
            counter += 1
    # add the line count to the global dictionary
    line_counts_per_file[file_name] = counter

    # close the file
    file.close()

    os.chdir(cwd)

if __name__ == '__main__':
    line_counts_per_file = count_wrapper("fabric.p4", os.getcwd()+"/")
    for file in line_counts_per_file:
        print(file + " has " + str(line_counts_per_file[file]) + " lines")

    print("Total number of non-blank, non-comment lines starting with fabric.p4: " + str(sum(line_counts_per_file[x] for x in line_counts_per_file)))
