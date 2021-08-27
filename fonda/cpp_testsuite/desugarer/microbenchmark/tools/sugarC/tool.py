import os
import configparser
import shutil
import tempfile

from common.run_command import run_command
from common.utils import TEST_CASE_DIR
from tools.utils import TestReturn, check_gcc_code

class Tool:

  def __init__(self):
    tool_dir = os.path.dirname(__file__)
    config = configparser.ConfigParser()
    config.read(os.path.join(tool_dir, 'sugarC.config'))

    self.working_dir = config.get('paths', 'workingDir')
    self.run_dir = config.get('paths', 'runDir')


  def run(self, testcase: str) -> TestReturn:

    os.chdir(self.run_dir)
    args = ['java', 'superc.SugarC', testcase]
    sugarC_code, sugarC_out, _ = run_command(args)

    # sugarC fails itself
    if sugarC_code == 124:
      return TestReturn(code=sugarC_code, msg='sugarC reaches running timeout')
    elif sugarC_code:
      return TestReturn(code=sugarC_code, msg='sugarC returns non-zero code')

    fd, path = tempfile.mkstemp()

    rel_test_path = os.path.relpath(testcase, TEST_CASE_DIR)
    reconfig_dir = os.path.join(self.working_dir, os.path.dirname(rel_test_path))
    os.makedirs(reconfig_dir, exist_ok=True)

    path = os.path.join(reconfig_dir, \
      os.path.basename(rel_test_path).replace('.c', '_desugared.c'))
    with open(path, 'wb+') as tmp:
      tmp.write(sugarC_out)
      gcc_args = ['gcc', '-x', 'c', '-c', '-o', '/dev/null', path]
      gcc_ret, _, _ = run_command(gcc_args, stdin=tmp)

    return check_gcc_code(gcc_ret)


  def clean(self, keep=False):
    return
