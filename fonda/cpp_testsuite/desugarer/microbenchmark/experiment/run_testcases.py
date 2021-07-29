import os
from collections import namedtuple
from common import utils

TestResult = namedtuple('TestResult', ['passed', 'total'])

def run_testcases(run_tool):
  test_case_dir = os.path.join(utils.ROOT_DIR, 'testcases')
  ret = {}

  for root, dirs, files in os.walk(test_case_dir):
    if not files:
      continue

    # TODO:avoid using dir names as type names
    test_type = os.path.basename(root)
    type_result = [0, 0]
    
    for testcase in files:
      if testcase.endswith('.c'):
        testcase_path = os.path.join(root, testcase)

        returncode = run_testcase(run_tool, testcase_path)
        type_result[1] += 1
        if pass_test(test_type, returncode):
          type_result[0] += 1

    ret[test_type] = TestResult(type_result[0], type_result[1])

  return ret

def run_testcase(run_tool, testcase: str):
  returncode = run_tool(testcase)
  return returncode

def pass_test(test_type: str, returncode: int):
  return not returncode

def get_test_types():
  test_case_dir = os.path.join(utils.ROOT_DIR, 'testcases')
  types = []
  for root, _, files in os.walk(test_case_dir):
    if files:
      types.append(os.path.basename(root))
  return types
  
