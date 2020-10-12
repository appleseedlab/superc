import sys
import os
import shutil
import json
import re

import subprocess

def runCommand (cmd):
    proc = subprocess.Popen(cmd,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            shell=True,
                            universal_newlines=True)
    std_out, std_err = proc.communicate()
    return proc.returncode, std_out, std_err

def main():
    os.system('rm metaData.json')
    os.system('touch metaData.json')
    metaDat = open('metaData.json', 'w')
    js = []
    for folderName in  os.listdir(os.getcwd()):
        if os.path.exists(folderName) and os.path.isdir(folderName):
            rootDir = os.getcwd() + "/" + folderName + '/'
            
            inclusionDirList = [rootDir]
            while inclusionDirList:
                curDir = inclusionDirList.pop(0)
                for dirFiles in os.listdir(curDir):
                    if os.path.exists(curDir + '/' + dirFiles) and os.path.isdir(curDir + '/' + dirFiles):
                        inclusionDirList.append(curDir + "/" + dirFiles)
                    elif (dirFiles.endswith('.c') and not dirFiles.endswith('desugared.c')):
                        sumTOut = os.path.relpath(curDir + "/" + dirFiles, os.getcwd())
                        #check if file can be ran with gcc (no configs)
                        print ("gcc -c " + sumTOut)
                        retC, stdO, stdE = runCommand("gcc -c -fdiagnostics-color=never " + sumTOut)
                        jDat = {}
                        if retC == 0:
                          jDat['valid'] = True
                        else:
                          jDat['valid'] = False
                        jDat['stdOut'] = stdO
                        jDat['stdErr'] = stdE
                        jDat['inclusions'] = []
                        fileRead = open(curDir + '/' + dirFiles)
                        for l in fileRead:
                            l = l.rstrip()
                            inclRE = re.compile('#include <(.*)>.*')
                            if inclRE.match(l):
                                found = inclRE.search(l)
                                jDat['inclusions'].append(found.group(1))
                        jEnt = {sumTOut:jDat}
                        js.append(jEnt)
    metaDat.write(json.dumps(js, separators=(',',':'), indent=2))
    metaDat.close()
    os.system('rm *.o')

if __name__ == '__main__':
    main()
