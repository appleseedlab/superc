import sys
import os
import shutil
import json
import re

LOC = "/home/kisamefishfry/SystemConfig"
stdInc = "-nostdinc -include " + LOC + "/baseInc.h -I " + LOC + "/original/usr/include/ -I " + LOC + "/original/usr/include/x86_64-linux-gnu/ -I " + LOC + "/\original/usr/lib/gcc/x86_64-linux-gnu/9/include/"

class Warning:
    def __init__(self):
        self.msg = ''
        self.line = 0
        self.lineA = 0
        self.lineB = 0

    def sanitize(self):
        if " '" in self.msg:
            return re.sub(r" '\S+'", " 'x'", self.msg.rstrip())
        return self.msg.rstrip()

    def tostr(self):
        return ' '.join([self.sanitize(),str(self.line),str(self.lineA),str(self.lineB)])
    
    
    def areEq(self,inner):
        print(self.tostr() + ' ||' + inner.tostr())
        return self.sanitize() == inner.sanitize() and inner.line >= self.lineA and inner.line <= self.lineB

def getAlarm(fi):
    orig = fi + ".clangres"
    desug = fi + ".desugared.clangres"
    warningsO = []
    warningsD = []
    f = open(orig)
    for x in f:
        if fi in x and 'warning:' in x:
            x = x.rstrip()
            y = Warning()
            y.msg = x.split('warning:')[1]
            y.line = int(x.split(':')[1])
            warningsO.append(y)
    f.close()
    f = open(desug)
    lines = []
    for x in f:
        lines.append(x.rstrip())
    i = 0
    while i < len(lines) - 1:
        l = lines[i]
        if fi in l and 'warning:' in l and '// L' in lines[i+1]:
            z = Warning()
            z.msg = l.split('warning:')[1]
            linestr = lines[i+1].split('// L')[1]
            if ':L' in linestr:
                z.lineA = int(linestr.split(':L')[0])
                z.lineB = int(linestr.split(':L')[1])
            else:
                z.lineA = int(linestr)
                z.lineB = int(linestr)
            warningsD.append(z)
            i = i+1
        i = i+1
    f.close()
    i = 0
    while i < len(warningsO):
        found = False
        for d in warningsD:
            if d.areEq(warningsO[i]):
                found = True
                break
        if not found:
            return 'missing: ' + warningsO[i].msg
        i = i+1
    return 'match'

def remove_prefix(text, prefix):
    return text[text.startswith(prefix) and len(prefix):]

def main():
    os.system('rm summaryTable.txt')
    os.system('touch summaryTable.txt')
    sumTable = open('summaryTable.txt', 'w')
    maxC = 14
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

    sumTable.write('File' + (maxC - 4)*' ' + 'Status        Clang\n'+(4)*'-'+ (maxC - 4)*' '+'------        -----\n')

    jsFile = open('configs.json','r+')
    if os.stat('configs.json').st_size == 0:
        js = {}
    else:
        js = json.loads(jsFile.read())
    jsFile.close()
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
                        print(curDir + '/' + dirFiles)
                        os.system( 'java superc.SugarC -keep-mem ' + stdInc + " -I " + curDir + " " + curDir + '/' + dirFiles + ' > ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c 2> ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.Log')
                        filewobase = (curDir + '/' + dirFiles)[len(os.getcwd()):]
                        if filewobase in js:
                            inc = js[filewobase]
                        else:
                            print('condition for ' + filewobase + ':\n')
                            inc = sys.stdin.readline().rstrip()
                            js[filewobase] = inc
                            
                        os.system('clang --analyze ' + inc + ' ' + curDir + '/' + dirFiles + " 2> " + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.clangres')

                        if os.path.getsize(curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c') <= 32:
                            sumTable.write(sumTOut + (maxC - len(sumTOut))*' ' + 'SuperC failed *\n')
                            
                        else:
                            os.system('clang -Wno-everything -emit-llvm -c ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c')
                            os.system('clang --analyze ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c 2> ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.clangres')
                        if os.path.exists(os.getcwd() + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc'):
                            os.system('mv ' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc')
                            alarm = getAlarm(curDir + '/' + dirFiles[:len(dirFiles) - 2])
                            sumTable.write(sumTOut + (maxC - len(sumTOut))*' ' +'BC generated  ' + alarm + '\n')
                        else:
                            sumTable.write(sumTOut + (maxC - len(sumTOut))*' ' +'BC failed     *\n')
                                
    with open('configs.json','w') as json_file:
      json.dump(js,json_file,sort_keys=True)
    sumTable.close()
if __name__ == '__main__':
    main()
            
