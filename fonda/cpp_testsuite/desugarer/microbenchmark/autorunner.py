import os
import sys
import re
import threading
from subprocess import PIPE, Popen

CONDHEADERSTR = 'CondHeader.c'

def getFileList(loc):
  fs = []
  dirList = [loc]
  while dirList:
    curDir = dirList.pop(0)
    for dirFiles in os.listdir(curDir):
      realFile = os.path.abspath(curDir + '/' + dirFiles)
      if os.path.exists(realFile) and os.path.isdir(realFile):
        dirList.append(realFile)
      elif (realFile.endswith('.c') and not realFile.endswith('desugared.c')) and realFile not in fs:
        fs.append(realFile)
  return fs

def getMacroList(f):
  ms = []
  o = open(f,'r')
  for l in o:
    if "ifdef" in l or "elif" in l:
      words = (re.sub(' +', ' ', l)).split(' ')
      for w in words:
        if 'ifdef' in w or ( "elif" in l and "defined" in w):
          conf = words[words.index(w)+1]
          conf = conf.rstrip().lstrip()
          if conf not in ms:
            ms.append(conf)
  o.close()
  return ms

def hasInclude(f):
  o = open(f,'r')
  bad = False;
  for l in o:
    if '#' in l and 'include' in l:
      bad = True
  o.close()
  return bad

def runBase(f,ms):
  sz = len(ms)
  res = []
  for i in range(0,2**sz):
    defs = ''
    for m in ms:
      if int(i/(2**ms.index(m)))%2 == 1:
        defs += ' -D ' + m + '=1 '
      else:
        defs += ' -U ' + m + ' '
    executeCmd = ' '.join(['gcc',defs,f])
    p = Popen(executeCmd, shell=True, stdout=PIPE, stderr=PIPE)
    stdout, stderr = p.communicate()
    if 'error:' in stderr.decode():
      res.append('157')
    else:
      result = os.popen('./a.out; echo $?')
      resStr = result.read().strip('\n')
      if '\n' in resStr:
        resStr = resStr.split('\n')[1]
      res.append(resStr)
  return res

def getExprList(f):
  fi = open(f,'r')
  res = []
  for l in fi:
    if '__static_condition_renaming("__static_condition_default_' in l:
      words = l.split('"')
      n = {}
      n['var'] = words[1]
      n['cond'] = words[3]
      res.append(n)
  fi.close()
  return res

def writeHeader(defs,name,el):
  fiName = name + CONDHEADERSTR
  os.system('rm ' + fiName)
  head = open(fiName,'w')
  head.write('#include <stdbool.h>\n')
  for e in el:
    head.write('const bool ')
    head.write(e['var'])
    head.write('() { return ')
    c = e['cond']
    for d in defs.keys():
      c = c.replace('defined ' + d + ')', '1)' if defs[d] else '0)')
    head.write(c)
    head.write('; }\n')
      
def runDesug(f,ms,el):
  sz = len(ms)
  res = []
  for i in range(0,2**sz):
    defs = {}
    for m in ms:
      if int(i/(2**ms.index(m)))%2 == 1:
        defs[m] = True
      else:
        defs[m] = False
    writeHeader(defs,f[:len(f)-2],el)
    executeCmd = ' '.join(['gcc','functionsHeader.c', f[:len(f)-2] + CONDHEADERSTR,f])
    p = Popen(executeCmd, shell=True, stdout=PIPE, stderr=PIPE)
    stdout, stderr = p.communicate()
    if 'error:' in stderr.decode():
      res.append('777')
    else:
      result = os.popen('./a.out; echo $?')
      resStr = result.read().strip('\n')
      if '\n' in resStr:
        resStr = resStr.split('\n')[1]
      res.append(resStr)
  return res

def comp(expect,reality,ms,f):
  size = len(expect)
  matches = 0
  fails = []
  for i in range(0,size):
    if expect[i] == reality[i]:
      matches = matches + 1
    else:
      fail = ''
      for m in ms:
        if int(i/(2**ms.index(m)))%2 == 1:
          fail = fail + ' ' + m
      fails.append(fail + '::'+expect[i]+'/'+reality[i])
  if len(fails) == 0:
    return f + ' :: match'
  return f + ' :: ' + str(matches) + '/' + str(size) + '\n\t' + str(expect) + '/' + str(reality) + '\n\t' + str(fails)

def printStatus(s):
  st = ""
  for a in s:
    if ':: match' in a:
      st += a + "\n"
  for a in s:
    if ':: match' not in a:
      st += a + "\n"
  return st

def printRes(s):
  res = printStatus(s)
  res = "~~~Results~~~\n" + res
  ff = open("autoRunnerResults.txt","w")
  ff.write(res)
  ff.close()
  print(res)

def runFiles(fileList,results):
  for f in fileList:
    absFile = os.path.abspath(f)
    hasInc = hasInclude(absFile)
    if hasInc:
      continue
    #get list of macros
    macros = getMacroList(absFile)
    #run each variant of macros -> store results
    baseRes = runBase(absFile,macros)
    #desugar file
    os.system('rm ' + absFile[:len(absFile)-2]+".desugared.c")
    cmd = " ".join(["nohup", "java", "superc.SugarC", "-keep-mem", "-make-main", "-showActions", "-useBDD", absFile, ">", absFile[:len(absFile)-2]+".desugared.c", "2>", absFile[:len(absFile)-2]+".Log"])
    os.system(cmd)
    if not os.path.exists(absFile[:len(absFile)-2]+".desugared.c"):
      results.append(f + " :: did not desug")
      continue
    #get static condition expressions
    expressionList = getExprList(absFile[:len(absFile)-2]+".desugared.c")
    #run each variant of macros -> store results
    desugRes = runDesug(absFile[:len(absFile)-2]+".desugared.c",macros,expressionList)
    #compare results
    results.append(comp(baseRes,desugRes,macros,f))

    
def main():
  #get list of files
  fileList = getFileList("/home/kisamefishfry/Documents/xtc-dev/fonda/cpp_testsuite/desugarer/microbenchmark/testcases")
  #for each file...
  results = []
  runFiles(fileList,results)
  printRes(results)

if __name__ == '__main__':
  main()
