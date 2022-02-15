import os
import sys
import configparser
import shutil
import time
import logging

from common.run_command import run_command
from common import utils
from tools import logs
from tools.utils import TestReturn, check_gcc_code

class Tool:

  def __init__(self):
    tool_dir = os.path.dirname(__file__)
    config = configparser.ConfigParser()
    config.read(os.path.join(tool_dir, 'creconfigurator.config'))

    self.test_dir = config.get('paths', 'creconfTestFolder')
    self.jar = config.get('paths', 'creconfJar')

    self.xms = config.get('values', 'javaXms')
    self.xmx = config.get('values', 'javaXmx')

    if os.path.exists(self.test_dir):
      shutil.rmtree(self.test_dir)
    os.mkdir(self.test_dir)
    self.source_dir = os.path.join(self.test_dir, 'source')

    '''workaround as creconfigurator takes a batch of c files as input'''
    self.run_creconfig()

  def run(self, testcase: str) -> TestReturn:
    rel_testcase_path = os.path.relpath(testcase, utils.TEST_CASE_DIR)
    target_dir = os.path.join(self.test_dir, 'target')
    reconfig_testcase = os.path.join(target_dir, rel_testcase_path)

    if not os.path.isfile(reconfig_testcase):
      return TestReturn(code=1, msg='reconfigured file does not exist')

    gcc_args = ['gcc', '-x', 'c', '-c', '-o', '/dev/null', reconfig_testcase]
    gcc_ret, _, _ = run_command(gcc_args)

    return check_gcc_code(gcc_ret)

  def clean(self, keep=False):
    if not keep:
      shutil.rmtree(self.test_dir)

  def run_creconfig(self):
    shutil.copytree(utils.TEST_CASE_DIR, self.source_dir)
  
    # make sure each macro starts with "ENABLE_"
    for root, _, files in os.walk(self.source_dir):
      for filename in files:
        if filename.endswith('.c'):
          filepath = os.path.join(root, filename)
          with open(filepath, 'r') as f:
            lines = f.readlines()

          for i in range(len(lines)):
            if '#ifdef' in lines[i]:
              lines[i] = self.rename_macro(lines[i], '#ifdef')
            if 'defined' in lines[i]:
              lines[i] = self.rename_macro(lines[i], 'defined')
          
          with open(filepath, 'w+') as f:
            f.writelines(lines)

    for i in range(1):
      os.chdir(self.test_dir)
      args = ['java',
                f'-Xms{self.xms}',
                f'-Xmx{self.xmx}',
                '-jar',
                self.jar]
      start_time = time.time()
      #run_command(args)
      # weird errors with subprocess.run, use os.opoen as workaround
      reconfig_process = os.popen(' '.join(args))
      out = reconfig_process.read()
      reconfig_process.close()

      logging.debug(f'total running time is {time.time() - start_time} seconds')

  def rename_macro(self, line, key_word):
    line_split = line.split(' ')
    index = line_split.index(key_word)
    line_split[index+1] = 'ENABLE_' + line_split[index+1]
    return ' '.join(line_split)


