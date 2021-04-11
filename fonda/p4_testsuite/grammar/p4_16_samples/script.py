import os
import sys

with open("fileswithoutinclude.txt", "r") as file:
    for line in file:
        if line[-3:-1] != "p4":
            continue
        stripped_line = line.strip()
        os.system("echo \"" + stripped_line + "\" && java superc.SuperC -silent -I ../../../../p4c/p4include/ " + stripped_line)
