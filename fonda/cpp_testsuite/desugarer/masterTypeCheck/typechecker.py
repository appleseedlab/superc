import os
import sys
import regex
import threading
import json
from pathlib import Path
import subprocess as subp
import time

UNRUN = 'unrun'
ERROR = 'error'
TYPEERROR = 'typeError'
PASSES = 'passes'


class Counter(object):
  def __init__(self,start=0):
    self.lock = threading.Lock()
    self.count = start
  def get(self):
    self.lock.acquire()
    try:
      val = self.count
    finally:
      self.lock.release()
    return val
  def inc(self):
    self.lock.acquire()
    try:
      val = self.count
      self.count = self.count + 1
    finally:
      self.lock.release()
    return val


def runFile(fs,js,counter):
  v = counter.inc()
  while v < len(fs):
    x = fs[v]
    p = subp.Popen(['gcc','-w','-c',x+'.c'], stdout=subp.PIPE, stderr=subp.PIPE)
    p_stdout, p_stderr = p.communicate()
    if len(p_stderr) > 0:
      js[x]['gcc'] = TYPEERROR
    else:
      js[x]['gcc'] = PASSES
    cmd = " ".join(['java','superc.SugarC', x+'.c', '>', x+'.desugared.c'])
    os.system(cmd)
    if Path(x+'.desugared.c').stat().st_size < 256:
      js[x]['sugarc'] = ERROR
    else:
      p = subp.run(['grep','static_type_error',x+'.desugared.c'], stdout=subp.PIPE)
      p_stdout = p.stdout
      if str(p_stdout.decode('utf-8')).count('\n') > 1:
        js[x]['sugarc'] = TYPEERROR
      else:
        js[x]['sugarc'] = PASSES
    
    v = counter.inc()

def generate():
  types = [['char','char'],['unsigned char','uchar'],['short','short'],['unsigned short','ushort'],['short','short'],['unsigned short','ushort'],['long','long'],['unsigned long','ulong'],['int','int'],['unsigned int','uint'],['float','float'],['double','double'],['struct dummys','struct'],['union dummyu','union'],['enum dummye','enum'],['void*','voidptr']]
  pointers = [['*','pointer'],['','']]
  arrays = [['[3]','array'],['','']]
  unarys = [['+','pos'],['-','neg'],['!','not'],['~','tild'],['++','inc'],['--','dec'],['','cast'],['*','deref'],['&','ref'],['sizeof','sizeof']]
  binaries = [['*','mult'],['/','div'],['%','mod'],['+','plus'],['-','minus'],['<<','lshift'],['>>','rshift'],['<','ls'],['>','gtr'],['<=','lseq'],['>=','gtreq'],['==','eq'],['!=','noteq'],['&','bitand'],['^','bitxor'],['|','bitor'],['&&','and'],['||','bitor'],['=','asn']]
  INIT = "struct dummys {int AA; int BB;};\nunion dummyu {int AA;char BB;};\nenum dummye {eAA=1,eBB};\n"
  MAIN = "void main() {\n"
  END = "}\n"

  mass = {}
  for op in unarys:
    opstr = op[0]
    for t in types:
      for p in pointers:
        for a in arrays:
          fname = 'unary/'+op[1]+t[1]+p[1]+a[1]
          newFile = open(fname+'.c','w')
          newFile.write(INIT)
          newFile.write(t[0] + " " + p[0] + " x " + a[0] + ";\n")
          newFile.write(MAIN)
          newFile.write(opstr + " x;\n")
          newFile.write(END)
          newFile.close()
          s = {}
          s['gcc'] = UNRUN
          s['sugarc'] = UNRUN
          mass[fname] = s
  for op in binaries:
    opstr = op[0]
    for t1 in types:
      for p1 in pointers:
        for a1 in arrays:
          for t2 in types:
            for p2 in pointers:
              for a2 in arrays:

                fname = 'binary/'+t1[1]+p1[1]+a1[1]+op[1]+t2[1]+p2[1]+a2[1]
                newFile = open(fname+'.c','w')
                newFile.write(INIT)
                newFile.write(t1[0] + " " + p1[0] + " x " + a1[0] + ";\n")
                newFile.write(t2[0] + " " + p2[0] + " y " + a2[0] + ";\n")
                newFile.write(MAIN)
                newFile.write("x " + opstr + " y;\n")
                newFile.write(END)
                newFile.close()
                s = {}
                s['gcc'] = UNRUN
                s['sugarc'] = UNRUN
                mass[fname] = s
  with open('files.json','w') as json_file:
    json.dump(mass,json_file)
                
  
def examine(mode):
  jsFile = open('files.json','r+')
  js = json.loads(jsFile.read())
  jsFile.close()
  files = []
  for j in js.keys():
    if mode == "-e":
      files.append(j)
    elif mode == "-d":
      if js[j]['sugarc'] != js[j]['gcc']:
        files.append(j)
    elif mode == j:
      files.append(j)
  counter = Counter()
  processes = []
  for x in range(10):
    p = threading.Thread(target=runFile,args=(files, js, counter,))
    processes.append(p)
  for p in processes:
    p.start()
  for p in processes:
    p.join()
  with open('files.json','w') as json_file:
    json.dump(js,json_file)
  return

def printFile(js,x,max):
   result = ""
   result = (result + x + ":").ljust(max+1)
   result = (result).ljust(max+10)+ js[x]['gcc']
   result = (result).ljust(max+20)+ js[x]['sugarc']
   result = (result).ljust(max+30)+ str(js[x]['sugarc'] == js[x]['gcc'])
   return result
  
def printRes():
  jsFile = open('files.json','r+')
  js = json.loads(jsFile.read())
  jsFile.close()
  max = 0
  for x in js:
    if max < len(x):
      max = len(x)
  equals = 0
  notequals = 0
  for x in sorted(js):
    if js[x]['gcc'] == js[x]['sugarc']:
      print(printFile(js,x,max))
      equals = equals + 1
  for x in sorted(js):
    if js[x]['gcc'] != js[x]['sugarc']:
      print(printFile(js,x,max))
      notequals = notequals + 1
  print("Equals: " + str(equals) + "\nNot Equals: " + str(notequals) + "\n")
  return

if __name__ == '__main__':
  if len(sys.argv) != 2:
    print ('-g generate all files\n-e examine (-d for only failures)\n-l list results\n')
  else:
    command = sys.argv[1]
    if command == "-g":
      generate()
    elif command == "-e":
      examine("-e")
    elif command == "-d":
      examine("-d")
    elif command == "-l":
      printRes()
    else:
      examine(command)
