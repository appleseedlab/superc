from common.run_command import run_command

def run(testcase: str):
  args = ['gcc', '-c', testcase, '-o', '/dev/null']
  returncode, stdout, stderr = run_command(args)
  return returncode
