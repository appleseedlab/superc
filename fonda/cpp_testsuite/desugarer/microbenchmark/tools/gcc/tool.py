from common.run_command import run_command

class Tool:

  def __init__(self):
    return

  def run(self, testcase: str):
    args = ['gcc', '-c', testcase, '-o', '/dev/null']
    returncode, stdout, stderr = run_command(args)
    return returncode

  def clean(self):
    return
