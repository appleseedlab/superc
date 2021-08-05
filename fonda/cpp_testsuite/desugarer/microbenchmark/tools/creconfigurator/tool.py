from common.run_command import run_command
from common import utils
import os
import configparser
import shutil

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

  def run(self, testcase: str):
    rel_testcase_path = os.path.relpath(testcase, utils.TEST_CASE_DIR)
    target_dir = os.path.join(self.test_dir, 'target')
    reconfig_testcase = os.path.join(target_dir, rel_testcase_path)

    if not os.path.isfile(reconfig_testcase):
      return 1

    gcc_args = ['gcc', '-x', 'c', '-c', '-o', '/dev/null', reconfig_testcase]
    gcc_ret, _, _ = run_command(gcc_args)

    return gcc_ret

  def clean(self):
    shutil.rmtree(self.test_dir)

  def run_creconfig(self):
    shutil.copytree(utils.TEST_CASE_DIR, self.source_dir)
    args = ['java', f'-Xms{self.xms}', f'-Xmx{self.xmx}', '-jar', self.jar]
    run_command(args)

