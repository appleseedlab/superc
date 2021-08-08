from common.run_command import run_command
from tools.utils import TestReturn

class Tool:

  def __init__(self):
    return

  def run(self, testcase: str):
    args = ['gcc', '-c', testcase, '-o', '/dev/null']
    returncode, stdout, stderr = run_command(args)
    return TestReturn(code=returncode)

  def clean(self):
    return
