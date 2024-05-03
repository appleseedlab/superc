import sys
import os
import shutil
import json
import re
WLOC = "/home/kisamefishfry/Documents/Research/SugarCPostWork"
sys.path.append(WLOC)
import warningSolver
import conditionLimiter
import defSearcher

LOC = "/home/kisamefishfry/SystemConfig"
RECLOC = "RecursiveConfig.h"
stdIncREC = "-nostdinc -include " + RECLOC + " -include " + LOC + "/baseInc.h -I " + LOC + "/original/usr/include/ -I " + LOC + "/original/usr/include/x86_64-linux-gnu/ -I " + LOC + "/\original/usr/lib/gcc/x86_64-linux-gnu/9/include/"

stdInc = "-nostdinc -include " + LOC + "/baseInc.h -I " + LOC + "/original/usr/include/ -I " + LOC + "/original/usr/include/x86_64-linux-gnu/ -I " + LOC + "/\original/usr/lib/gcc/x86_64-linux-gnu/9/include/"

idCounter = 1

class Warning:
    def __init__(self):
        global idCounter
        self.msg = ''
        self.line = 0
        self.lineA = 0
        self.lineB = 0
        self.idn = idCounter
        idCounter += 1

    def sanitize(self):
        san = self.msg.rstrip()
        if " '" in san:
            san = re.sub(r" '\S+'", " 'x'", san)
        if san.endswith(']'):
            san = re.sub(r' \[.*\]$', '', san)
        return san

    def tostr(self):
        return ' '.join(['('+self.sanitize()+')',str(self.line),str(self.lineA),str(self.lineB)])
        
    def areEq(self,inner):
        print(self.tostr() + ' ||' + inner.tostr())
        return self.sanitize() == inner.sanitize() and inner.line >= self.lineA and inner.line <= self.lineB

def getClangAlarm(fi,warningsO):
    if len(warningsO) == 0:
        return 'Original file has no warnings\n'
    desug = fi + ".desugared.clangres"
    warningsD = []
    warningsDI = 0
    desugs = warningSolver.main(fi.split('/')[-2],fi.split('/')[-1],fi+".desugared.c")
    warnDStr = ''
    for d in desugs:
        if d['feasible']:
            if d['correNum'] != '-1':
                z = Warning()
                z.msg = d['msg']
                linestr = d['correNum']
                if ':L' in linestr:
                    z.lineA = int(linestr.split(':L')[0])
                    z.lineB = int(linestr.split(':L')[1])
                else:
                    z.lineA = int(linestr)
                    z.lineB = int(linestr)
                warningsD.append(z)
            warnDStr += d['msg'] + ' ' + d['correNum'] + ' ' + str(d['model']) + '\n'
        else:
            warningsDI += 1
    i = 0
    notFound = []
    rep = 'Matches:\n'
    while i < len(warningsO):
        found = False
        for d in warningsD:
            if d.areEq(warningsO[i]):
                found = True
                break
        if not found:
            notFound.append(str(warningsO[i].idn))
        else:
            rep += '\t'+str(warningsO[i].idn) + ' has a match!\n'
        i = i+1
    rep += 'Unmatched ids:\n'
    for x in notFound:
        rep += '\t' + x + '\n'
    if len(notFound) == 0:
        rep += '\tNone!\n'
    return rep

def getInferAlarm(fi,warningsI):
    if len(warningsI) == 0:
        return 'Original file has no warnings\n'
    desug = fi + ".desugared.inferres"
    warningsD = []
    warningsDI = 0
    desugs = warningSolver.main(fi.split('/')[-2],fi.split('/')[-1],fi+".desugared.c")
    warnDStr = ''
    for d in desugs:
        if d['feasible']:
            if d['correNum'] != '-1':
                z = Warning()
                z.msg = d['msg']
                linestr = d['correNum']
                if ':L' in linestr:
                    z.lineA = int(linestr.split(':L')[0])
                    z.lineB = int(linestr.split(':L')[1])
                else:
                    z.lineA = int(linestr)
                    z.lineB = int(linestr)
                warningsD.append(z)
            warnDStr += d['msg'] + ' ' + d['correNum'] + ' ' + str(d['model']) + '\n'
        else:
            warningsDI += 1
    i = 0
    notFound = []
    rep = 'Matches:\n'
    while i < len(warningsI):
        found = False
        for d in warningsD:
            if d.areEq(warningsI[i]):
                found = True
                break
        if not found:
            notFound.append(str(warningsI[i].idn))
        else:
            rep += '\t'+str(warningsI[i].idn) + ' has a match!\n'
        i = i+1
    rep += 'Unmatched ids:\n'
    for x in notFound:
        rep += '\t' + x + '\n'
    if len(notFound) == 0:
        rep += '\tNone!\n'
    return rep


def remove_prefix(text, prefix):
    return text[text.startswith(prefix) and len(prefix):]

def alarmsBase(fpa,macros):
    rep = ''
    cFile = fpa[:len(fpa) - 2] + '.clangres'
    iFile = fpa[:len(fpa) - 2] + '.inferres'
    warningsOc = []
    warningsOi = []
    for i in range(len(macros)**2):
        inc = ''
        for m in range(len(macros)):
            if int(i/(2**m)) % 2 == 1:
                inc += '-D' + macros[m] + '=1 '
            else:
                inc += '-U' + macros[m] + ' '
        rep += '['+inc+']\n'
        os.system('clang --analyze ' + inc + ' ' + fpa + " 2> " + cFile)
        os.system('infer --pulse-only -- clang -c ' + inc + ' ' + fpa + " > " + iFile)
        fc = open(cFile, 'r')
        txtc = fc.read()
        fc.close()
        fi = open(iFile, 'r')
        txti = fi.read()
        fi.close()
        for x in txtc.split('\n'):
            if fpa.split('/')[-1] in x and 'warning:' in x:
                x = x.rstrip()
                y = Warning()
                y.msg = x.split('warning: ')[1]
                y.line = int(x.split(':')[1])
                warningsOc.append(y)
                rep += 'clang :: ' + str(y.idn) + ' :: Line:' + str(y.line) + '\n\t' + y.msg + '\n'
        for x in txti.split('\n'):
            if fpa.split('/')[-1] in x and 'error:' in x:
                x = x.rstrip()
                y = Warning()
                y.msg = x.split('error: ')[1]
                y.line = int(x.split(':')[1])
                warningsOi.append(y)
                rep += 'infer :: ' + str(y.idn) + ' :: Line:' + str(y.line) + '\n\t' + y.msg + '\n'
   
    return rep, warningsOc, warningsOi
        

def main(toinclude):
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
                    elif (dirFiles.endswith('.c') and not dirFiles.endswith('desugared.c')) and realFile not in ranFiles and not dirFiles.endswith('expected.c') and toinclude in realFile:
                        ranFiles.append(realFile)
                        sumTOut = os.path.relpath(curDir, os.getcwd()) + '/' + dirFiles[:len(dirFiles) - 2]
                        key = sumTOut + ".c"
                        print(curDir + '/' + dirFiles)
                        report = ''
                        listOfMacros = defSearcher.getAllMacros(realFile)
                        report += realFile.split('/')[-2] + ' ' + realFile.split('/')[-1] + '\nMacros:\n'
                        for lm in listOfMacros:
                            report += '\t' + lm + "\n"
                        rep, warningsC, warningsI = alarmsBase(realFile, listOfMacros)
                        
                        report += rep
                        #------------------------------------------
                        '''
                        os.system('echo | gcc -dM -E - > ' + RECLOC)
                        toAppend = ['']
                        while len(toAppend) > 0:
                            for d in toAppend:
                                os.system('echo "' + d + '" >> ' + RECLOC)
                            
                            os.system( 'java superc.SugarC -keep-mem ' + stdIncREC + " " + curDir + '/' + dirFiles + ' > ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c 2> ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.Log')
                            toAppend = conditionLimiter.getBadConstraints(curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c')
                            print(toAppend)
                        #'''
                        #------------------------------------------
                        #ABOVE IS USING A RECURSIVE METHOD
                        #BELOW IS WITH STANDARD INCLUSIONS
                        #------------------------------------------
                        #'''
                        os.system( 'java superc.SugarC -keep-mem ' + stdInc + " -I " + curDir + " " + curDir + '/' + dirFiles + ' > ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c 2> ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.Log')
                        #'''
                        #------------------------------------------
                        '''
                        filewobase = (curDir + '/' + dirFiles)[len(os.getcwd()):]
                        if filewobase in js:
                            inc = js[filewobase]
                        else:
                            print('condition for ' + filewobase + ':\n')
                            inc = sys.stdin.readline().rstrip()
                            js[filewobase] = inc
                        ''' 
                        
                        if os.path.getsize(curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c') <= 32:
                            sumTable.write(sumTOut + (maxC - len(sumTOut))*' ' + 'SuperC failed\n')
                            
                        else:
                            os.system('clang -Wno-everything -emit-llvm -c ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c')
                            os.system('clang --analyze ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c 2> ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.clangres')
                            os.system('infer --pulse-only -- clang -c ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.c > ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.inferres')
                        if os.path.exists(os.getcwd() + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc'):
                            report += 'Desugared Clang Results:\n'
                            ff = open (curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.clangres','r')
                            report += ff.read()
                            ff.close()
                            report += 'Desugared Infer Results:\n'
                            ff = open (curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.inferres','r')
                            report += ff.read()
                            ff.close()
                            os.system('mv ' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc ' + curDir + '/' + dirFiles[:len(dirFiles) - 2] + '.desugared.bc')
                            report += getClangAlarm(realFile[:-2], warningsC)
                            report += getInferAlarm(realFile[:-2], warningsI)
                        else:
                            report += 'File Failed\n'
                        sumTable.write(report)
                        fff = open(realFile.split('/')[-2] + '-' + realFile.split('/')[-1][:-2]+'.report','w')
                        fff.write(report)
                        fff.close()
                                
    with open('configs.json','w') as json_file:
      json.dump(js,json_file,sort_keys=True)
    sumTable.close()
    os.system('rm *.plist; rm *.o')
    
if __name__ == '__main__':
    if len(sys.argv) < 2:
        main('')
    else:
        main(sys.argv[1])
            
