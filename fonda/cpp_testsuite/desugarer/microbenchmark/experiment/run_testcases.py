import os
from collections import namedtuple
import logging
from typing import Callable

from common import utils

TestResult = namedtuple('TestResult', ['passed', 'total'])

def run_testcases(tool_name: str, run_func: Callable):
  test_case_dir = utils.TEST_CASE_DIR
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

        test_ret = run_testcase(run_func, testcase_path)
        type_result[1] += 1
        if pass_test(test_type, test_ret.code):
          type_result[0] += 1
        else:
          logging.debug(f'{tool_name} fails testcase {os.path.relpath(testcase_path, test_case_dir)} with message {test_ret.msg}')

    ret[test_type] = TestResult(type_result[0], type_result[1])

  return ret

def run_testcase(run_func: Callable, testcase: str):
  test_ret = run_func(testcase)
  return test_ret

def pass_test(test_type: str, returncode: int):
  return not returncode

def get_test_types():
  test_case_dir = os.path.join(utils.ROOT_DIR, 'testcases')
  types = []
  for root, _, files in os.walk(test_case_dir):
    if files:
      types.append(os.path.basename(root))
  return types
  
