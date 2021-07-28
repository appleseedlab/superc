import os
from common import utils

def run_testcases(tool):
  test_case_dir = os.path.join(utils.ROOT_DIR, 'testcases')
  for root, dirs, files in os.walk(test_case_dir):
    print(os.path.relpath(root, test_case_dir))
    for testcase in files:
      if testcase.endswith('.c'):
        testcase_path = os.path.join(root, testcase)
        run_testcase(tool, testcase_path)

def run_testcase(tool, testcase: str):
  returncode = tool(testcase)
  print(returncode)
