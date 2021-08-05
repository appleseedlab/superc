from common.run_command import run_command
import os
import configparser
import shutil
import tempfile

class Tool:

  def __init__(self):
    tool_dir = os.path.dirname(__file__)
    config = configparser.ConfigParser()
    config.read(os.path.join(tool_dir, 'sugarC.config'))

    self.run_dir = config.get('paths', 'runDir')


  def run(self, testcase: str):
    os.chdir(self.run_dir)
    args = ['java', 'superc.SugarC', testcase]
    sugarC_code, sugarC_out, _ = run_command(args)

    # sugarC fails itself
    if sugarC_code:
      return sugarC_code

    fd, path = tempfile.mkstemp()
    try:
      tmp = os.fdopen(fd, 'wb')
      tmp.write(sugarC_out)
      gcc_args = ['gcc', '-x', 'c', '-c', '-o', '/dev/null', path]
      gcc_ret, _, _ = run_command(gcc_args, stdin=tmp)
    finally:
      os.remove(path)

    return gcc_ret


  def clean(self):
    return
