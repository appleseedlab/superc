import filecmp
import os

files = []
tmp_output_file_name = "tmp.out"
for file in os.listdir('output_files/'):
    # print(file)
    if(file[-3:] == "out"):
        # print(file)
        files.append(file[:-4])

print(files)

for file in files:
    os.system("java superc.SuperP4 -printCallGraph " + file + ".p4 > " + tmp_output_file_name)
    result = filecmp.cmp('output_files/' + file + ".out", tmp_output_file_name)
    if result != True:
        print("FAILED: " + file + " output differs")
    else:
        print("Passed: " + file)