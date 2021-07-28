import subprocess

def run_command(args: str, shell=False):
  res = subprocess.run(args, shell=shell, capture_output=True)
  return res.returncode, res.stdout, res.stderr
