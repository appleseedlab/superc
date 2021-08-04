import sys
import os
sys.path.append(os.path.abspath(os.path.dirname(os.path.dirname(__file__))))

import argparse
import importlib
from run_testcases import run_testcases
from common import utils
from tools.utils import get_tool_names
from analysis.generate_report import generate_report

def parse_args():
  parser = argparse.ArgumentParser(description='evaluate tools on microbenchmark')

  all_tools = get_tool_names()
  parser.add_argument('-t',
      '--tools',
      help='Tools to evaluate.',
      nargs='+',
      required=False,
      default=all_tools,
      choices=all_tools)
  args = parser.parse_args()
  return args

def import_tools(tool_names: list):
  tools = {}
  for tool_name in tool_names:
    module_name = '.'.join(['tools', tool_name, 'tool'])
    module = importlib.import_module(module_name, package=None)
    tools[tool_name] = module.Tool
  return tools

def run_tools(tools:dict):
  result_data = {}
  for tool_name, Tool in tools.items():
    tool = Tool()

    res = run_testcases(tool.run)
    tool.clean()
    result_data[tool_name] = res
  return result_data
  
def run_benchmark():
  args = parse_args()
  tools = import_tools(args.tools)
  result_data = run_tools(tools)
  generate_report(args.tools, result_data)

def main():
  run_benchmark()

if __name__ == '__main__':
  main()
