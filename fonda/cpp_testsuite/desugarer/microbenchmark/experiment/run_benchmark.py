import sys
import os
sys.path.append(os.path.abspath(os.path.dirname(os.path.dirname(__file__))))

import argparse
import importlib
from run_testcases import run_testcases
from common import utils
import tools.utils as tool_utils

def parse_args():
  parser = argparse.ArgumentParser(description='evaluate tools on microbenchmark')

  all_tools = tool_utils.get_tool_names()
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
  tools = []
  for tool_name in tool_names:
    module_name = '.'.join(['tools', tool_name, 'tool'])
    module = importlib.import_module(module_name, package=None)
    tools.append(module.run)
  return tools

def run_tools(tools:list):
  for tool in tools:  
    run_testcases(tool)
  

def run_benchmark():
  args = parse_args()
  tools = import_tools(args.tools)
  run_tools(tools)



  

def main():
  run_benchmark()

if __name__ == '__main__':
  main()
