import os
import configparser
import shutil
import sys

from common.run_command import run_command
from common.utils import TEST_CASE_DIR
from tools import logs
from tools.utils import TestReturn, check_gcc_code

class Tool:

  def __init__(self):
    tool_dir = os.path.dirname(__file__)
    config = configparser.ConfigParser()
    config.read(os.path.join(tool_dir, 'Hercules.config'))

    self.working_dir = config.get('paths', 'workingDir')
    self.tool = config.get('paths', 'toolDir')

    if os.path.exists(self.working_dir):
      shutil.rmtree(self.working_dir)
    os.mkdir(self.working_dir)

  def run(self, testcase: str) -> TestReturn:
    '''files in test and ifdeftoif folders are created by docker,
    so remove them with docker to avoid permission issue'''

    rel_test_path = os.path.relpath(testcase, TEST_CASE_DIR)
    reconfig_dir = os.path.join(self.working_dir, rel_test_path.rsplit('.', 1)[0])
    os.makedirs(reconfig_dir, exist_ok=True)

    file_name = os.path.basename(testcase)
    test_dir = os.path.join(reconfig_dir, 'test')
    os.mkdir(test_dir)
    copied_test = os.path.join(test_dir, file_name)
    shutil.copy2(testcase, copied_test)

    os.chdir(test_dir)

    args = [self.tool, copied_test]
    hercules_code, hercules_out, hercules_err = run_command(args)

    with open(os.path.join(test_dir, 'out.log'), 'wb+') as f:
      f.write(hercules_out)
    with open(os.path.join(test_dir, 'err.log'), 'wb+') as f:
      f.write(hercules_err)
    

    ifdeftoif_file_name = file_name.replace('.c', '_ifdeftoif.c')
    ifdeftoif_file_path = os.path.join(test_dir, ifdeftoif_file_name)

    if not os.path.exists(ifdeftoif_file_path):
      return TestReturn(code=1, msg='Hercules output does not exist')

    gcc_args = ['gcc', '-x', 'c', '-c', '-o', '/dev/null', ifdeftoif_file_path]
    gcc_ret, _, _ = run_command(gcc_args)

    return check_gcc_code(gcc_ret)

  def clean(self, keep=False):
    if not keep:
      shutil.rmtree(self.working_dir)

  def stop_docker(self):
    args = ['docker', 'stop', 'hercules']
    run_command(args)
    
