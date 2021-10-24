import subprocess
import os

def run_command(args: str, stdin=subprocess.PIPE, env=os.environ, shell=False, timeout=10):
  try:
    res = subprocess.run(args, shell=shell, stdin=stdin, env=env, capture_output=True, timeout=timeout)
  except subprocess.TimeoutExpired:
    return 124, None, None
  return res.returncode, res.stdout, res.stderr
