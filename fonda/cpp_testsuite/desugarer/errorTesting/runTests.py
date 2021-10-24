import sys
import os
import shutil
import json

def remove_prefix(text, prefix):
    return text[text.startswith(prefix) and len(prefix):]

def main():
    for fileName in  os.listdir(os.getcwd()):
        if (fileName.endswith('.c') and not fileName.endswith('desugared.c')) and not fileName.endswith('expected.c'):
            os.system( 'java superc.SugarC ' + fileName + ' > ' + fileName[:len(fileName) - 2] + '.desugared.c 2> ' + fileName[:len(fileName) - 2]  + '.Log')
                        
if __name__ == '__main__':
    main()
            
