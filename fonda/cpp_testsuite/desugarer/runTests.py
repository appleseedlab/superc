import sys
import os
import shutil

def remove_prefix(text, prefix):
    return text[text.startswith(prefix) and len(prefix):]

def main():
    os.system('rm summaryTable.txt')
    os.system('touch summaryTable.txt')
    sumTable = open('summaryTable.txt', 'w')
    for folderName in  os.listdir(os.getcwd()):
        maxC = 10
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
                        sumTOut = os.path.relpath(curDir, os.getcwd()+'/'+folderName) + '/'
                        if len(sumTOut + dirFiles) > maxC:
                            maxC = len(sumTOut + dirFiles)

            relFN = os.path.relpath(folderName, os.getcwd())
            sumTable.write(relFN + ':File' + (maxC - len(relFN)-5)*' ' + 'Status\n'+(len(relFN)+5)*'-'+ (maxC - len(relFN)-5)*' '+'------\n')
            dirList = [rootDir[:-1]]
            ranFiles = []
            while dirList:
                curDir = dirList.pop(0)
                for dirFiles in os.listdir(curDir):
                    realFile = os.path.abspath(curDir + '/' + dirFiles)
                    if os.path.exists(curDir + '/' + dirFiles) and os.path.isdir(curDir + '/' + dirFiles):
                        dirList.append(curDir + '/' + dirFiles)
                        print (curDir + '/' + dirFiles)
                    elif (dirFiles.endswith('.c') and not dirFiles.endswith('desugared.c')) and realFile not in ranFiles:
                        ranFiles.append(realFile)
                        os.system( 'java superc.SugarC -D "_Noreturn=" -D "Pragma(x)=" -D __extension__= -restrictFreeToPrefix CONFIG_ ' + inclusionList + ' ' + curDir + '/' + dirFiles + ' > ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c 2> ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.Log')
                        sumTOut = os.path.relpath(curDir, os.getcwd()+'/'+folderName) + '/' + dirFiles[:len(dirFiles) - 2]
                        if os.path.getsize(curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c') <= 32:
                            #os.system('rm ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c')
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
            
