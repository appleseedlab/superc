import sys
import os
import shutil
import json

def remove_prefix(text, prefix):
    return text[text.startswith(prefix) and len(prefix):]

def main():
    os.system('rm summaryTable.txt')
    os.system('touch summaryTable.txt')
    sumTable = open('summaryTable.txt', 'w')
    maxC = 10
    jF = open('metaDataGT.json')
    js = json.load(jF)
    jF.close()
    for folderName in  os.listdir(os.getcwd()):
        if os.path.exists(folderName) and os.path.isdir(folderName):
            rootDir = os.getcwd() + "/" + folderName + '/'
            
            inclusionDirList = [rootDir]
            inclusionList = "-I " + rootDir + " "
            while inclusionDirList:
                curDir = inclusionDirList.pop(0)
                for dirFiles in os.listdir(curDir):
                    if os.path.exists(curDir + '/' + dirFiles) and os.path.isdir(curDir + '/' + dirFiles):
                        inclusionDirList.append(curDir + "/" + dirFiles)
                        inclusionList = inclusionList + "-I " + curDir + '/' + dirFiles + " "
                    elif (dirFiles.endswith('.c') and not dirFiles.endswith('desugared.c')):
                        sumTOut = os.path.relpath(curDir, os.getcwd()) + '/'
                        if len(sumTOut + dirFiles) > maxC:
                            maxC = len(sumTOut + dirFiles)

    sumTable.write('File' + (maxC - 4)*' ' + 'Status\n'+(4)*'-'+ (maxC - 4)*' '+'------\n')
        
    for folderName in  os.listdir(os.getcwd()):
        if os.path.exists(folderName) and os.path.isdir(folderName):
            rootDir = os.getcwd() + "/" + folderName + '/'
            rootDir = os.getcwd() + "/" + folderName + '/'
            relFN = os.path.relpath(folderName, os.getcwd())
            dirList = [rootDir[:-1]]
            ranFiles = []
            while dirList:
                curDir = dirList.pop(0)
                for dirFiles in os.listdir(curDir):
                    realFile = os.path.abspath(curDir + '/' + dirFiles)
                    if os.path.exists(curDir + '/' + dirFiles) and os.path.isdir(curDir + '/' + dirFiles):
                        dirList.append(curDir + '/' + dirFiles)
                        print (curDir + '/' + dirFiles)
                    elif (dirFiles.endswith('.c') and not dirFiles.endswith('desugared.c')) and realFile not in ranFiles and not dirFiles.endswith('expected.c'):
                        ranFiles.append(realFile)
                        sumTOut = os.path.relpath(curDir, os.getcwd()) + '/' + dirFiles[:len(dirFiles) - 2]
                        key = sumTOut + ".c"
                        if js[key]['valid'] == False:
                            sumTable.write(sumTOut + (maxC - len(sumTOut))*' ' + 'File isn\'t valid\n')
                        else:
                            if len(js[key]['inclusions']) > 0:
                                os.system( 'java superc.SugarC -D "_Noreturn=" -D "Pragma(x)=" -D __extension__= -restrictFreeToPrefix CONFIG_ ' + curDir + '/' + dirFiles + ' > ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c 2> ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.Log')
                            else:
                                os.system( 'java superc.SugarC ' + curDir + '/' + dirFiles + ' > ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c 2> ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.Log')
                            
                            if os.path.getsize(curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c') <= 32:
                                sumTable.write(sumTOut + (maxC - len(sumTOut))*' ' + 'SuperC failed\n')
                            
                            else:
                                os.system('clang -emit-llvm -c ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c')
                            if os.path.exists(os.getcwd() + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc'):
                                os.system('mv ' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc')
                                sumTable.write(sumTOut + (maxC - len(sumTOut))*' ' +'BC generated\n')
                            else:
                                sumTable.write(sumTOut + (maxC - len(sumTOut))*' ' + 'BC failed\n')
                                
                        
    sumTable.close()
if __name__ == '__main__':
    main()
            
