from common.run_command import run_command
import os
import configparser
import shutil

class Tool:

  def __init__(self):
    tool_dir = os.path.dirname(__file__)
    config = configparser.ConfigParser()
    config.read(os.path.join(tool_dir, 'Hercules.config'))

    self.ifdeftodef_dir = config.get('paths', 'ifdeftoifDir')
    self.hercules = config.get('paths', 'hercules_script')


  def run(self, testcase: str):
    if os.path.exists(self.ifdeftodef_dir):
      shutil.rmtree(self.ifdeftodef_dir)

    args = [self.hercules, testcase]
    hercules_code, hercules_out, err = run_command(args)

    # sugarC fails itself
    if hercules_code:
      return hercules_code

    print(hercules_code)
    print(hercules_out)
    print(err)

    print(os.listdir(self.ifdeftodef_dir))



  def clean(self):
    return
