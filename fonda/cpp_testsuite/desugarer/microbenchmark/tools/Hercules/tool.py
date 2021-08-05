from common.run_command import run_command
import os
import configparser
import shutil

class Tool:

  def __init__(self):
    tool_dir = os.path.dirname(__file__)
    config = configparser.ConfigParser()
    config.read(os.path.join(tool_dir, 'Hercules.config'))

    self.working_dir = config.get('paths', 'workingDir')
    self.hercules = config.get('paths', 'hercules_script')

    if os.path.exists(self.working_dir):
      shutil.rmtree(self.working_dir)
    os.mkdir(self.working_dir)
    
    self.test_dir = os.path.join(self.working_dir, 'test')

  def run(self, testcase: str):
    if os.path.exists(self.test_dir):
      shutil.rmtree(self.test_dir)
    os.mkdir(self.test_dir)

    ifdeftoif_dir = os.path.join(self.working_dir, 'ifdeftoif')
    if os.path.exists(ifdeftoif_dir):
      shutil.rmtree(ifdeftoif_dir)

    file_name = os.path.basename(testcase)
    copied_test = os.path.join(self.test_dir, file_name)
    shutil.copy2(testcase, copied_test)

    os.chdir(self.test_dir)

    args = [self.hercules, copied_test]
    hercules_code, hercules_out, err = run_command(args)

    # sugarC fails itself
    if hercules_code:
      return hercules_code

    ifdeftoif_file_name = file_name.replace('.c', '_ifdeftoif.c')
    ifdeftoif_file_path = os.path.join(self.test_dir, ifdeftoif_file_name)

    if not os.path.exists(ifdeftoif_file_path):
      return 1

    gcc_args = ['gcc', '-x', 'c', '-c', '-o', '/dev/null', ifdeftoif_file_path]
    gcc_ret, _, _ = run_command(gcc_args)

    return gcc_ret

  def clean(self):
    shutil.rmtree(self.working_dir)
